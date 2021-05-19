#pragma once

enum msr_addr {
	EFER  = 0xC0000080,
	VM_CR = 0xC0010114,
	IGNNE = 0xC0010115, // not used 15.30.2 for ref
	SMM_CTL = 0xC0010116,
	VM_HSAVE_PA = 0xC0010117,
};


// Extended Features MSR
union __amd64_efer_t {
	unsigned __int64 control;
	struct
	{
		unsigned __int64 syscall_enable : 1;
		unsigned __int64 reserved_0 : 7;
		unsigned __int64 long_mode_enable : 1;
		unsigned __int64 reserved_1 : 1;
		unsigned __int64 long_mode_active : 1;
		// No-Execute Page Capability
		unsigned __int64 execute_disable : 1;
		unsigned __int64 svm_enable : 1;
		unsigned __int64 long_mode_segment_limit_enable : 1;
		// Fast FXSAVE/FRSTOR enable
		unsigned __int64 ffxse : 1;
		unsigned __int64 reserved_2 : 1;
		unsigned __int64 mbz_reserved : 48;
	} bits;
};


// Virtual Machine Control MSR
union __amd64_vm_cr_t {
	unsigned __int64 control;
	struct
	{
		// disable the external hardware debug port and certain internal debug features
		unsigned __int64 disable_debug_features : 1;
		// controls how init is delivered
		unsigned __int64 intercept_init : 1;
		unsigned __int64 disable_a20_masking : 1;
		unsigned __int64 svm_lock : 1;
		unsigned __int64 svm_disable : 1;
		unsigned __int64 mbz_reserved : 59;
	} bits;
};


union __amd64_smm_ctl { // 15.30.3
	unsigned __int64 control;
	struct {
		// Clear the processor-internal 'smi pending' flag
		unsigned __int64 dismiss : 1;
		unsigned __int64 enter: 1;
		unsigned __int64 smm_cycle : 1;
		unsigned __int64 exit : 1;
		unsigned __int64 rsm_cycle : 1;
		unsigned __int64 mbz_reserved : 59;
	} bits;
};

union __amd64_vm_hsave_pa { // 15.30.4
	unsigned __int64 physaddr;
};
