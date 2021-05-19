#pragma once

#include <ntddk.h>

void get_physical_address(_In_ PVOID BaseAddress);
int get_proc_number();
int get_proc_count();
void dbgprint(_In_ PCCH Format, ...);

