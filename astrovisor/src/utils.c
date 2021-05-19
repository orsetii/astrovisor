#include "utils.h"

void dbgprint (_In_ PCCH Format, ...)
{
    va_list arglist;

    va_start(arglist, Format);
    vDbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, Format, arglist);
    va_end(arglist);
}

void get_physical_address(_In_ PVOID BaseAddress)
{
    return MmGetPhysicalAddress(BaseAddress).QuadPart;
}

int get_proc_count()
{
    return KeQueryActiveProcessorCountEx(ALL_PROCESSOR_GROUPS);
}

int get_proc_number() 
{
    return KeGetCurrentProcessorNumberEx(NULL);
}

// TODO look into adding 'CONTEXT' functions to restore state, its a windows structure.
