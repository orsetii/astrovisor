#pragma once
#include <ntddk.h>

struct descriptor_table_register_t
{
    __int16   limit;
    ULONG_PTR base;
};
