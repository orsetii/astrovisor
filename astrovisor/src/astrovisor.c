#include "arch/cpuid.h"
#include "arch/msr.h"
#include "arch/dtr.h"
#include "vmcb.h"
#include "vcpu.h"
#include "utils.h"


void enable_svm(void)
{
	union __amd64_efer_t efer = { 0 };
	efer.control = __readmsr(IA32_EFER_MSR);
	efer.bits.svm_enable = 1;
	__writemsr(IA32_EFER_MSR, efer.control);
}

// Starts the hypervisor for some processor
int start_hv(void) 
{

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
		return -1;
	}
	// Enable SVM in the EFER MSR
	enable_svm();
	dbgprint("SVM Enabled!");

	// Create Virtual Processer Structure
	struct __vcpu_t* vcpu = (struct __vcpu_t*)alloc_pagealigned_physical_memory_with_tag(sizeof(struct __vcpu_t));



	// Prepare vcpu state for running the hypervisor
	prepare_vcpu(vcpu);



	return 0;
}

