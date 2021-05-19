#include "arch/cpuid.h"
#include <wdm.h>

int cpuid_vme_support()
{
	union __cpuid_t cpuid = { 0 };
	__cpuid(cpuid.cpu_info, 0x80000001);
	return cpuid.feature_edx.vme;
}

int cpuid_svm_support()
{
	union __cpuid_t cpuid = { 0 };
	__cpuid(cpuid.cpu_info, 0x80000001);
	return cpuid.feature_ecx.svm;
}
