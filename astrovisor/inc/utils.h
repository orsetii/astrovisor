#pragma once

#include <ntddk.h>
#include <wdm.h>

ULONGLONG get_physical_address(_In_ PVOID BaseAddress);
int get_proc_number(void);
int get_proc_count(void);
void dbgprint(_In_ PCCH Format, ...);
void AstroUnload(void);
