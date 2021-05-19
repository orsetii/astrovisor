#pragma once

int cpuid_vme_support();
int cpuid_svm_support();

union  __cpuid_t
{
	struct
	{
		unsigned __int32 cpu_info[4];
	};

	struct
	{
		unsigned __int32 eax;
		unsigned __int32 ebx;
		unsigned __int32 ecx;
		unsigned __int32 edx;
	} registers;

	struct
	{
		union
		{
			unsigned __int32 flags;

			struct
			{
				unsigned __int32 stepping_id : 4;
				unsigned __int32 model : 4;
				unsigned __int32 family_id : 4;
				unsigned __int32 processor_type : 2;
				unsigned __int32 reserved1 : 2;
				unsigned __int32 extended_model_id : 4;
				unsigned __int32 extended_family_id : 8;
				unsigned __int32 reserved2 : 4;
			};
		} version_information;

		union
		{
			unsigned __int32 flags;

			struct
			{
				unsigned __int32 brand_index : 8;
				unsigned __int32 clflush_line_size : 8;
				unsigned __int32 max_addressable_ids : 8;
				unsigned __int32 initial_apic_id : 8;
			} additional_information;
		};

		union
		{
			unsigned __int32 flags;

			struct
			{
				// LAHF and SAHF instruction support.
				unsigned __int32 lahfsahf : 1;
				// Core multi-processing legacy mode
				unsigned __int32 cmplegacy : 1;
				// Secure Virtual Machine
				unsigned __int32 svm : 1;
				// Extended APIC Space.
				unsigned __int32 extapicspace : 1;
				// LOCK MOV CR0 means MOV CR8
				unsigned __int32 altmovcr8 : 1;
				// Advanced Bit Manipulation
				unsigned __int32 abm : 1;
				// EXTRQ, INSERTQ, MOVNTSS, and MOVNTSD instruction support
				unsigned __int32 sse4a : 1;
				// Misaligned SSE mode
				unsigned __int32 misalignsse : 1;
				// PREFETCH and PREFETCHW instruction support
				unsigned __int32 _3dnowprefetch : 1;
				// OS-visible workaround support
				unsigned __int32 osvw : 1;
				// Instruction based sampling
				unsigned __int32 ibs : 1;
				// Extended operation support
				unsigned __int32 xop : 1;
				// SKINIT and STGI are supported
				unsigned __int32 skinit : 1;
				// Watchdog timer support
				unsigned __int32 wdt : 1;
				unsigned __int32 reserved0 : 1;
				// lightweight profiling support
				unsigned __int32 lwp : 1;
				// four-operand fma instruction support
				unsigned __int32 fma4 : 1;
				unsigned __int32 reserved1 : 4;
				// Trailing bit manipulation instruction support
				unsigned __int32 tbm : 1;
				// Topology extensions support
				unsigned __int32 topologyextensions : 1;
				// Processor performance counter extensions support
				unsigned __int32 perfctrextcore : 1;
				// NB performance counter extensions support
				unsigned __int32 perfctrextnb : 1;
				unsigned __int32 reserved2 : 1;
				// data access breakpoint extension
				unsigned __int32 databkptext : 1;
				// performance time-stamp counter
				unsigned __int32 perftsc : 1;
				// Support for L3 performance counter extension
				unsigned __int32 perfctrextllc : 1;
				// Support for MWAITX and MONITORX instructions
				unsigned __int32 monitorx : 1;
				// Breakpoint Addressing masking extended to bit 31
				unsigned __int32 addrmaskext : 1;
			};
		} feature_ecx;

		union
		{
			unsigned __int32 flags;

			struct
			{
				// Onboard x87 FPU
				unsigned __int32 fpu : 1;
				// Virtual mode extensions (VIF)
				unsigned __int32 vme : 1;
				// Debugging Extensions (CR4 bit 3)
				unsigned __int32 de : 1;
				// Page Size Extension
				unsigned __int32 pse : 1;
				// Time Stamp Counter
				unsigned __int32 tsc : 1;
				// Model-specific Registers
				unsigned __int32 msr : 1;
				// Page Size Extension
				unsigned __int32 pae : 1;
				// Machine Check Exception
				unsigned __int32 mce : 1;
				// CMPXCHG8 (compare and swap) instruction
				unsigned __int32 cx8 : 1;
				// Onboard Advanced Programmable Interrupt Controller
				unsigned __int32 apic : 1;
				// SYSENTER and SYSEXIT instructions
				unsigned __int32 sysenterexit : 1;
				// Memory Type Range Registers
				unsigned __int32 mtrr : 1;
				// Page Global Enable bit in CR4
				unsigned __int32 pge : 1;
				// Machine check architecture
				unsigned __int32 mca : 1;
				// Conditional move and FCMOV instructions
				unsigned __int32 cmov : 1;
				// Page Attribute Table
				unsigned __int32 pat : 1;
				// 36-bit page size extension
				unsigned __int32 pse36 : 1;
				// CFLUSH instruction support
				unsigned __int32 cflush : 1;
				// MMX Instructions
				unsigned __int32 mmx : 1;
				// FXSAVE, FXRSTOR Instructions, CR4 Bit 9
				unsigned __int32 fxsr : 1;
				// SSE instruction support
				unsigned __int32 sse : 1;
				// SSE2 instruction support
				unsigned __int32 sse2 : 1;
				// Hyperthreading
				unsigned __int32 htt : 1;

			};
		} feature_edx;
	};
};