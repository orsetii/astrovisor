#include "utils.h"
#include <stdarg.h>

void dbgprint (_In_ PCCH Format, ...)
{
    va_list arglist = { 0 };

    va_start(arglist, Format);
    vDbgPrintExWithPrefix("[*]", DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, Format, arglist);
    va_end(arglist);
}

ULONGLONG get_physical_address(_In_ PVOID BaseAddress)
{
    return MmGetPhysicalAddress(BaseAddress).QuadPart;
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
