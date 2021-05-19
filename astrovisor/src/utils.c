#include "utils.h"
#include <stdarg.h>

void dbgprint (_In_ PCCH Format, ...)
{
    va_list arglist = { 0 };

    va_start(arglist, Format);
    vDbgPrintExWithPrefix("[*]", DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, Format, arglist);
    va_end(arglist);
}

PHYSICAL_ADDRESS get_physical_address(_In_ PVOID BaseAddress)
{
    return MmGetPhysicalAddress(BaseAddress);
}

int get_proc_count(void)
{
    return KeQueryActiveProcessorCountEx(ALL_PROCESSOR_GROUPS);
}

int get_proc_number(void) 
{
    return KeGetCurrentProcessorNumberEx(NULL);
}

void AstroUnload(void)
{
    // TODO!
}


// TODO look into adding 'CONTEXT' functions to restore state, its a windows structure.

// A copied function, but seems well optimized.
__drv_allocatesMem(Mem)
_Post_writable_byte_size_(NumberOfBytes)
_Post_maybenull_
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_requires_same_
_Must_inspect_result_
void* alloc_pagealigned_physical_memory_with_tag(_In_ SIZE_T NumberOfBytes)
{
     void* memory;

    // The size must be equal or greater than PAGE_SIZE in order to allocate
    // page aligned memory.
    NT_ASSERT(NumberOfBytes >= PAGE_SIZE);

    memory = ExAllocatePoolWithTag(NonPagedPool, NumberOfBytes, TAG);
    if (memory != NULL)
    {
        NT_ASSERT(PAGE_ALIGN(memory) == memory);
        RtlSecureZeroMemory(memory, NumberOfBytes);
    }
    return memory;
}

_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_requires_same_
void free_pagealigned_physical_memory_with_tag(_Pre_notnull_ __drv_freesMem(Mem) PVOID BaseAddress)
{
    ExFreePoolWithTag(BaseAddress, TAG);
}
