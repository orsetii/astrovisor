#pragma once

typedef struct _GUEST_REGISTERS
{
    unsigned __int64 r15;
    unsigned __int64 r14;
    unsigned __int64 r13;
    unsigned __int64 r12;
    unsigned __int64 r11;
    unsigned __int64 r10;
    unsigned __int64 r9;
    unsigned __int64 r8;
    unsigned __int64 rdi;
    unsigned __int64 rsi;
    unsigned __int64 rbp;
    unsigned __int64 rsp;
    unsigned __int64 rbx;
    unsigned __int64 rdx;
    unsigned __int64 rcx;
    unsigned __int64 rax;
} GUEST_REGISTERS, *PGUEST_REGISTERS;

typedef struct _GUEST_CONTEXT
{
    PGUEST_REGISTERS VpRegs;
    BOOLEAN ExitVm;
} GUEST_CONTEXT, *PGUEST_CONTEXT;
