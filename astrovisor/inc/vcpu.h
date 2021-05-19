#pragma once
#include "vmcb.h"
#include <ntddk.h>


// TODO get shared_vcpu_data on, page table stuff?? not rly sure but sounds useful.


struct __vcpu_t {

	__declspec(align(PAGE_SIZE)) unsigned char host_stack_limit[KERNEL_STACK_SIZE];

	struct
	{
		unsigned char stack_contents[KERNEL_STACK_SIZE - (sizeof(PVOID) * 6) - sizeof(KTRAP_FRAME)];
		KTRAP_FRAME trap_frame;
		unsigned __int64 guest_vmcb_pa;
		unsigned __int64 host_vmcb_pa;
		struct __vcpu_t* self;

		// TODO put the shared vcpu_data below!
        //struct shared_vcpu_data_t* shared_vcpu_datab;

		UINT64 padding1;        // To keep host rsp 16 bytes aligned
        UINT64 reserved1;
	} host_stack_layout;

	__declspec(align(PAGE_SIZE)) struct __vmcb_t guest_vmcb;
	__declspec(align(PAGE_SIZE)) struct __vmcb_t host_vmcb;
	__declspec(align(PAGE_SIZE)) unsigned char host_state_area[PAGE_SIZE];
};

void prepare_vcpu(struct __vcpu_t* vcpu);
