#include "vcpu.h"
#include "arch/dtr.h"
#include "arch/msr.h"
#include "utils.h"


void prepare_vcpu(struct __vcpu_t* vcpu)
{
	struct descriptor_table_register_t gdtr, idtr;

	// Save the current GDTR and IDTR to use as intial values of the guest mode
	_sgdt(&gdtr);
	__sidt(&idtr);

	// Configure to trigger #VMEXIT with CPUID and VMRUN instructions.
	//		CPUID is intercepted to present the existence of the hypervisor
	//		and provide an interface to ask it to unload itself.
	//	
	//		VMRUN is intercepted because it otherwise #VMEXIT occurs due to VMEXIT_INVALID 
	//		when a processor attempts to enter the guest mode via (another) VMRUN.
	vcpu->guest_vmcb.control.intercept_cpuid = 1;
	vcpu->guest_vmcb.control.intercept_vmrun = 1;

	// TODO maybe intercept MSR access here, via msrpm.

	// Set guest's address space ID (ASID) not sure why or what the fuck this do TODO look it up :D
	vcpu->guest_vmcb.control.guest_asid = 1;

	// Set the loaded GDTR and IDTR
	vcpu->guest_vmcb.statesave.gdtr.base = gdtr.base;
	vcpu->guest_vmcb.statesave.gdtr.limit = gdtr.limit;

	vcpu->guest_vmcb.statesave.idtr.base = idtr.base;
	vcpu->guest_vmcb.statesave.idtr.limit = idtr.limit;

	// TODO get Segments from CONTEXT structure, which should be passed to this function.

	vcpu->guest_vmcb.statesave.efer = __readmsr(IA32_EFER_MSR);
	vcpu->guest_vmcb.statesave.cr0 = __readcr0();
	vcpu->guest_vmcb.statesave.cr2 = __readcr2();
	vcpu->guest_vmcb.statesave.cr3 = __readcr3();
	vcpu->guest_vmcb.statesave.cr4 = __readcr4();
	// TODO Get RFLAGS from CONTEXT
	// TODO Get RSP from CONTEXT
	// TODO Get RIP from CONTEXT
	vcpu->guest_vmcb.statesave.efer = __readmsr(IA32_PAT_MSR);

	// Save some of the current state on VMCB. Some of those states are:
    // - FS, GS, TR, LDTR (including all hidden state)
    // - KernelGsBase
    // - STAR, LSTAR, CSTAR, SFMASK
    // - SYSENTER_CS, SYSENTER_ESP, SYSENTER_EIP
    // See "VMSAVE and VMLOAD Instructions" for mode details.
	// 
	// Those are restored to the processor right before #VMEXIT with the VMLOAD
    // instruction so that the guest can start its execution with saved state,
    // and also, re-saved to the VMCS with right after #VMEXIT with the VMSAVE
    // instruction so that the host (hypervisor) do not destroy guest's state.
	__svm_vmsave(vcpu->host_stack_layout.guest_vmcb_pa);

	// Store data to stack so hypervisor can use those values.
	vcpu->host_stack_layout.reserved1 = MAXUINT64;
	vcpu->host_stack_layout.self = vcpu;
	vcpu->host_stack_layout.host_vmcb_pa = get_physical_address(&vcpu->host_vmcb).QuadPart;
	vcpu->host_stack_layout.guest_vmcb_pa = get_physical_address(&vcpu->guest_vmcb).QuadPart;

	// Write the Host VMCB's physical address to the VM_HSAVE_PA MSR
	__writemsr(SVM_VM_HSAVE_PA_MSR, vcpu->host_stack_layout.host_vmcb_pa);

    // Save some of the current state to VMCB for the host. This is loaded
    // after #VMEXIT to reproduce the current state for the host (hypervisor).
    __svm_vmsave(vcpu->host_stack_layout.host_vmcb_pa);

}
