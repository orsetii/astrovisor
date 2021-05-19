#include "vmcb.h"
#include <ntddk.h>

struct __vmcb_t* vmcb_alloc_and_zero()
{
	const size_t VMCB_SIZE = 4096;
	PHYSICAL_ADDRESS highest;
    // The entire address range is OK for this allocation
    highest.QuadPart = -1;

	PVOID addr = MmAllocateContiguousMemory(VMCB_SIZE, highest);
	RtlSecureZeroMemory(addr, VMCB_SIZE);
	return addr;
}

int vmcb_init(struct __vmcb_t* vmcb)
{
	vmcb += 1;
	vmcb -= 1;
	// TODO above is warning shit
	return -1;
}
