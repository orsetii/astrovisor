#pragma once

#include <ntddk.h>
#include <wdm.h>

#define TAG 'ASTR'

PHYSICAL_ADDRESS get_physical_address(_In_ PVOID BaseAddress);

__drv_allocatesMem(Mem)
_Post_writable_byte_size_(NumberOfBytes)
_Post_maybenull_
_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_requires_same_
_Must_inspect_result_
void* alloc_pagealigned_physical_memory_with_tag(_In_ SIZE_T NumberOfBytes);

_IRQL_requires_max_(DISPATCH_LEVEL)
_IRQL_requires_same_
void free_pagealigned_physical_memory_with_tag(_Pre_notnull_ __drv_freesMem(Mem) PVOID BaseAddress);

int get_proc_number(void);
int get_proc_count(void);
void dbgprint(_In_ PCCH Format, ...);
void AstroUnload(void);
