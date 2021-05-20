#pragma once

unsigned __int64 __readmsr(unsigned __int32 register);

#define IA32_PAT_MSR			 0x00000277U
#define IA32_EFER_MSR			 0xC0000080U
#define SVM_VM_CR_MSR			 0xC0010114U
#define SVM_IGNNE_MSR			 0xC0010115U // not used 15.30.2 for ref
#define SVM_SMM_CTL_MSR		 0xC0010116U
#define SVM_VM_HSAVE_PA_MSR	 0xC0010117U


// Extended Features MSR
typedef struct _AMD64_EFER_MSR {
	union {
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
} AMD64_EFER_MSR, *PAMD64_EFER_MSR;


// Virtual Machine Control MSR
typedef union _AMD64_VM_CR_MSR {
	union {
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
} AMD64_VM_CR_MSR,*PAMD64_VM_CR_MSR;


typedef struct _AMD64_SMM_CTL_MSR { // 15.30.3
	union {
		unsigned __int64 control;
		struct {
			// Clear the processor-internal 'smi pending' flag
			unsigned __int64 dismiss : 1;
			unsigned __int64 enter : 1;
			unsigned __int64 smm_cycle : 1;
			unsigned __int64 exit : 1;
			unsigned __int64 rsm_cycle : 1;
			unsigned __int64 mbz_reserved : 59;
		} bits;
	};
} AMD64_SMM_CTL_MSR ,*PAMD64_SMM_CTL_MSR ;

typedef struct _AMD64_VM_HSAVE_PA_MSR { // 15.30.4
	unsigned __int64 physaddr;
} AMD64_VM_HSAVE_PA_MSR ,*PAMD64_VM_HSAVE_PA_MSR;
