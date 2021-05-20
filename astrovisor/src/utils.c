#include "utils.h"
#include "arch/segment.h"
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

ULONG get_proc_count(void)
{
    return KeQueryActiveProcessorCountEx(ALL_PROCESSOR_GROUPS);
}

ULONG get_proc_number(void) 
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


unsigned __int16 get_segment_access_right(_In_ segment_selector, _In_ gdt_base)
{
    PSEGMENT_DESCRIPTOR desc = (PSEGMENT_DESCRIPTOR)gdt_base + (segment_selector & (~3));
    SEGMENT_ATTRIBUTE attribute;
    attribute.bits.type = desc->bits.type;
    attribute.bits.system = desc->bits.system;
    attribute.bits.dpl = desc->bits.dpl;
    attribute.bits.present = desc->bits.present;
    attribute.bits.avl = desc->bits.avl;
    attribute.bits.longmode = desc->bits.longmode;
    attribute.bits.defaultbit = desc->bits.defaultbit;
    attribute.bits.granularity = desc->bits.granularity;
    attribute.bits.reserved1 = 0;
    return attribute.control;
}
