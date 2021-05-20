#pragma once
#include <ntddk.h>

typedef struct _DESCRIPTOR_TABLE_REGISTER
{
    __int16   limit;
    ULONG_PTR base;
} DESCRIPTOR_TABLE_REGISTER, *PDESCRIPTOR_TABLE_REGISTER;
