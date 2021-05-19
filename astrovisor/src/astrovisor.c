#include "arch/cpuid.h"
#include "arch/msr.h"
#include "vmcb.h"
#include "vcpu.h"
#include "utils.h"

void enable_svm(void)
{
	union __amd64_efer_t efer = { 0 };
	efer.control = __readmsr(EFER);
	efer.bits.svm_enable = 1;
	__writemsr(EFER, efer.control);
}

// Starts the hypervisor for some processor
int start_hv(void) 
{

	// Check that SVM is enabled as per AMD spec.
	int ret = cpuid_svm_support();
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
		return -1;
	}
	enable_svm();
	dbgprint("SVM Enabled!");

	struct __vcpu_t vcpu = { 0 };

	vcpu.vmcb = vmcb_alloc_and_zero();
	vcpu.vmcb_physical = get_physical_address(vcpu.vmcb);
	dbgprint("VMCB Allocated at virtual: %p and at physical: 0x%x", vcpu.vmcb, vcpu.vmcb_physical);



	return 0;
}

