#include "arch/cpuid.h"
#include "arch/msr.h"
#include <ntddk.h>

int cpuid_vme_support(void)
{
	union __cpuid_t cpuid = { 0 };
	__cpuid(cpuid.cpu_info, 0x80000001);
	return cpuid.feature_edx.vme;
}

int cpuid_svm_support(void)
{
	union __cpuid_t cpuid = { 0 };
	__cpuid(cpuid.cpu_info, 0x80000001);
	if (cpuid.feature_ecx.svm == 0) {
		return SVM_NOT_AVAIL;
	}

	union __amd64_vm_cr_t vm_cr = { 0 };
	vm_cr.control = __readmsr(SVM_VM_CR_MSR);
	if (vm_cr.bits.svm_disable == 0) {
		return SVM_ALLOWED;
	}
	
	__cpuid(cpuid.cpu_info, 0x8000000A);
	if (cpuid.svm_feature_edx.svml == 0) {
		return SVM_DISABLED_AT_BIOS_NOT_UNLOCKABLE;
	}
	else {
		return SVM_DISABLED_WITH_KEY;
	}
}
