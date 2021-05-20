#pragma once

#include <ntddk.h>
#include <wdm.h>

#define TAG 'ASTR'

#define ASTRO_DEBUG_BREAK() \
    if (KD_DEBUGGER_NOT_PRESENT) \
    { \
        NOTHING; \
    } \
    else \
    { \
        __debugbreak(); \
    } \
   (void*)0

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

unsigned __int16 get_segment_access_right(_In_ segment_selector, _In_ gdt_base);

ULONG get_proc_number(void);
ULONG get_proc_count(void);
void dbgprint(_In_ PCCH Format, ...);
void AstroUnload(void);
