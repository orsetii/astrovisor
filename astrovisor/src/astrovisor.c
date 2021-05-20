#include <ntifs.h>
#include <intrin.h>

#include "arch/cpuid.h"
#include "arch/msr.h"
#include "arch/dtr.h"
#include "vmcb.h"
#include "vcpu.h"
#include "arch/context.h"
#include "utils.h"
#include "astrovisor.h"


void enable_svm(void)
{
	AMD64_EFER_MSR efer = { 0 };
	efer.control = __readmsr(IA32_EFER_MSR);
	efer.bits.svm_enable = 1;
	__writemsr(IA32_EFER_MSR, efer.control);
}

_IRQL_requires_same_
EXTERN_C
BOOLEAN
NTAPI
SvHandleVmExit (
    _Inout_ PVIRTUAL_PROCESSOR VpData,
    _Inout_ PGUEST_REGISTERS GuestRegisters
    )
{
    GUEST_CONTEXT guestContext;
    KIRQL oldIrql;

    guestContext.VpRegs = GuestRegisters;
    guestContext.ExitVm = FALSE;

    //
    // Load some host state that are not loaded on #VMEXIT.
    //
    __svm_vmload(VpData->host_stack_layout.host_vmcb_pa);

    NT_ASSERT(VpData->host_stack_layout.reserved1 == MAXUINT64);

    //
    // Raise the IRQL to the DISPATCH_LEVEL level. This has no actual effect since
    // interrupts are disabled at #VMEXI but warrants bug check when some of
    // kernel API that are not usable on this context is called with Driver
    // Verifier. This protects developers from accidentally writing such #VMEXIT
    // handling code. This should actually raise IRQL to HIGH_LEVEL to represent
    // this running context better, but our Logger code is not designed to run at
    // that level unfortunately. Finally, note that this API is a thin wrapper
    // of mov-to-CR8 on x64 and safe to call on this context.
    //
    oldIrql = KeGetCurrentIrql();
    if (oldIrql < DISPATCH_LEVEL)
    {
        KeRaiseIrqlToDpcLevel();
    }

    //
    // Guest's RAX is overwritten by the host's value on #VMEXIT and saved in
    // the VMCB instead. Reflect the guest RAX to the context.
    //
    GuestRegisters->rax = VpData->guest_vmcb.statesave.rax;

    //
    // Update the _KTRAP_FRAME structure values in hypervisor stack, so that
    // Windbg can reconstruct call stack of the guest during debug session.
    // This is optional but very useful thing to do for debugging.
    //
    VpData->host_stack_layout.trap_frame.Rsp = VpData->guest_vmcb.statesave.rsp;
    VpData->host_stack_layout.trap_frame.Rip = VpData->guest_vmcb.control.next_rip;

    //
    // Handle #VMEXIT according with its reason.
    //
    switch (VpData->guest_vmcb.control.exitcode)
    {
    case VMEXIT_CPUID:
        break;
    case VMEXIT_MSR:
        break;
    case VMEXIT_VMRUN:
        break;
    default:
        ASTRO_DEBUG_BREAK();
#pragma prefast(disable : __WARNING_USE_OTHER_FUNCTION, "Unrecoverble path.")
        KeBugCheck(MANUALLY_INITIATED_CRASH);
    }

    //
    // Again, no effect to change IRQL but restoring it here since a #VMEXIT
    // handler where the developers most likely call the kernel API inadvertently
    // is already executed.
    //
    if (oldIrql < DISPATCH_LEVEL)
    {
        KeLowerIrql(oldIrql);
    }

    //
    // Terminate the SimpleSvm hypervisor if requested.
    //
    if (guestContext.ExitVm != FALSE)
    {
        NT_ASSERT(VpData->guest_vmcb.control.exitcode == VMEXIT_CPUID);

        //
        // Set return values of CPUID instruction as follows:
        //  RBX     = An address to return
        //  RCX     = A stack pointer to restore
        //  EDX:EAX = An address of per processor data to be freed by the caller
        //
        guestContext.VpRegs->rax = (unsigned __int64)(VpData) & MAXUINT32;
        guestContext.VpRegs->rbx = VpData->guest_vmcb.control.next_rip;
        guestContext.VpRegs->rcx = VpData->guest_vmcb.statesave.rsp;
        guestContext.VpRegs->rdx =(unsigned __int64)(VpData) >> 32;

        //
        // Load guest state (currently host state is loaded).
        //
        __svm_vmload(MmGetPhysicalAddress(&VpData->guest_vmcb).QuadPart);

        //
        // Set the global interrupt flag (GIF) but still disable interrupts by
        // clearing IF. GIF must be set to return to the normal execution, but
        // interruptions are not desirable until SVM is disabled as it would
        // execute random kernel-code in the host context.
        //
        _disable();
        __svm_stgi();

        //
        // Disable SVM, and restore the guest RFLAGS. This may enable interrupts.
        // Some of arithmetic flags are destroyed by the subsequent code.
        //
        __writemsr(IA32_EFER_MSR, __readmsr(IA32_EFER_MSR) & ~(1UL<< 12));
        __writeeflags(VpData->guest_vmcb.statesave.rflags);
        goto Exit;
    }

    //
    // Reflect potentially updated guest's RAX to VMCB. Again, unlike other GPRs,
    // RAX is loaded from VMCB on VMRUN.
    //
    VpData->guest_vmcb.statesave.rax = guestContext.VpRegs->rax;

Exit:
    NT_ASSERT(VpData->host_stack_layout.reserved1 == MAXUINT64);
    return guestContext.ExitVm;
}

NTSTATUS run_on_each_processor(
	_In_ NTSTATUS(*Callback)(PVOID),
	_In_opt_ PVOID Context,
	_Out_opt_ PULONG NumOfProcessorCompleted)
{
	NTSTATUS status;
	PROCESSOR_NUMBER proc_number;
	GROUP_AFFINITY affinity, old_affinity;
	ULONG i, proc_count;

	proc_count = get_proc_count();

	for (i = 0; i < proc_count; i++)
	{
		status = KeGetProcessorNumberFromIndex(i, &proc_number);
		if (!NT_SUCCESS(status)) goto Exit;

		// Switch execution of this code to a processor #i.
		affinity.Group = proc_number.Group;
		affinity.Mask = 1ULL << proc_number.Number;
		affinity.Reserved[0] = affinity.Reserved[1] = affinity.Reserved[2] = 0;
		KeSetSystemGroupAffinityThread(&affinity, &old_affinity);

		// execute the callback
		status = Callback(Context);

		// revert to previously used processor
		KeRevertToUserGroupAffinityThread(&old_affinity);

		if (!NT_SUCCESS(status)) goto Exit;
	}

Exit:
	// i must be the same as the number of processors on the system when this
   // function returns STATUS_SUCCESS;
	NT_ASSERT(!NT_SUCCESS(status) || (i == proc_count));

	//
	// Set a number of processors that successfully executed callback if the
	// out parameter is present.
	//
	if (ARGUMENT_PRESENT(NumOfProcessorCompleted))
	{
		*NumOfProcessorCompleted = i;
	}
	return status;
}

NTSTATUS start_hv(void)
{
	NTSTATUS status;
	PSHARED_VIRTUAL_PROCESSOR_DATA shared_vcpu_data = NULL;
	ULONG done_proc_count = 0U;
	// Check that SVM is enabled as per AMD spec.
	int ret = cpuid_svm_support();
	// If returned an error, print the error and 
	// return -1.
	if (ret != SVM_ALLOWED) {
		if (ret == SVM_NOT_AVAIL) {
			dbgprint("SVM Not Available.");
		}
		else if (ret == SVM_DISABLED_AT_BIOS_NOT_UNLOCKABLE) {
			dbgprint("SVM Disabled at BIOS.");
		}
		else if (ret == SVM_DISABLED_WITH_KEY) {
			dbgprint("SVM Disabled with Key.");
		}
		return STATUS_FAIL_CHECK;
	}

	shared_vcpu_data = alloc_pagealigned_physical_memory_with_tag(sizeof(SHARED_VIRTUAL_PROCESSOR_DATA));
	if (shared_vcpu_data == NULL)
    {
        dbgprint("Insufficient memory.\n");
        status = STATUS_INSUFFICIENT_RESOURCES;
        goto Exit;
    }

	status = run_on_each_processor(virtualize_processor, shared_vcpu_data, &done_proc_count);
	return status;

Exit:
    if (shared_vcpu_data != NULL)
    {
        ExFreePoolWithTag(shared_vcpu_data, TAG);
    }
    if ((!NT_SUCCESS(status)) && (shared_vcpu_data != NULL))
    {
        //
        // Frees per processor data if allocated and this function is
        // unsuccessful.
        //
        free_pagealigned_physical_memory_with_tag(shared_vcpu_data);
    }
    return status;
}

// Starts the hypervisor for some processor
NTSTATUS virtualize_processor(_In_opt_ PCONTEXT Context)
{
	NTSTATUS status;
	PVIRTUAL_PROCESSOR vcpu;
	PSHARED_VIRTUAL_PROCESSOR_DATA shared_vcpu_data = NULL;
	PCONTEXT context_record = NULL;
	ASTRO_DEBUG_BREAK();

	// Enable SVM in the EFER MSR
	enable_svm();
	dbgprint("SVM Enabled!");

	// Create Virtual Processer Structure
	vcpu = (PVIRTUAL_PROCESSOR)alloc_pagealigned_physical_memory_with_tag(sizeof(VIRTUAL_PROCESSOR));
	if (vcpu == NULL) {
		dbgprint("Not enough memory, couldn't allocate VCPU strucure at %s:%d", __FILE__, __LINE__);
		status = STATUS_INSUFFICIENT_RESOURCES;
		goto Exit;
	}

	shared_vcpu_data = (PSHARED_VIRTUAL_PROCESSOR_DATA)Context;

	RtlCaptureContext(context_record);


	// Prepare vcpu state for running the hypervisor
	prepare_vcpu(vcpu, shared_vcpu_data, context_record);

	astro_launch_vm(&vcpu->host_stack_layout.guest_vmcb_pa);
	// should never get here!
	ASTRO_DEBUG_BREAK();
	KeBugCheck(MANUALLY_INITIATED_CRASH);

	return STATUS_SUCCESS;

Exit:
    if (context_record != NULL)
    {
        ExFreePoolWithTag(context_record, TAG);
    }
    if ((!NT_SUCCESS(status)) && (shared_vcpu_data != NULL))
    {
        //
        // Frees per processor data if allocated and this function is
        // unsuccessful.
        //
        free_pagealigned_physical_memory_with_tag(vcpu);
    }
    return status;
}


