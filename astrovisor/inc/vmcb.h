#pragma once
#include <ntddk.h>

__declspec(align(1024)) struct __vmcb_control_t {

	unsigned __int64 intercept_read_cr0 : 1;
	unsigned __int64 intercept_read_cr1 : 1;
	unsigned __int64 intercept_read_cr2 : 1;
	unsigned __int64 intercept_read_cr3 : 1;
	unsigned __int64 intercept_read_cr4 : 1;
	unsigned __int64 intercept_read_cr5 : 1;
	unsigned __int64 intercept_read_cr6 : 1;
	unsigned __int64 intercept_read_cr7 : 1;
	unsigned __int64 intercept_read_cr8 : 1;
	unsigned __int64 intercept_read_cr9 : 1;
	unsigned __int64 intercept_read_cr10 : 1;
	unsigned __int64 intercept_read_cr11 : 1;
	unsigned __int64 intercept_read_cr12 : 1;
	unsigned __int64 intercept_read_cr13 : 1;
	unsigned __int64 intercept_read_cr14 : 1;
	unsigned __int64 intercept_read_cr15 : 1;

	unsigned __int64 intercept_write_cr0 : 1;
	unsigned __int64 intercept_write_cr1 : 1;
	unsigned __int64 intercept_write_cr2 : 1;
	unsigned __int64 intercept_write_cr3 : 1;
	unsigned __int64 intercept_write_cr4 : 1;
	unsigned __int64 intercept_write_cr5 : 1;
	unsigned __int64 intercept_write_cr6 : 1;
	unsigned __int64 intercept_write_cr7 : 1;
	unsigned __int64 intercept_write_cr8 : 1;
	unsigned __int64 intercept_write_cr9 : 1;
	unsigned __int64 intercept_write_cr10 : 1;
	unsigned __int64 intercept_write_cr11 : 1;
	unsigned __int64 intercept_write_cr12 : 1;
	unsigned __int64 intercept_write_cr13 : 1;
	unsigned __int64 intercept_write_cr14 : 1;
	unsigned __int64 intercept_write_cr15 : 1;

	unsigned __int64 intercept_read_dr0 : 1;
	unsigned __int64 intercept_read_dr1 : 1;
	unsigned __int64 intercept_read_dr2 : 1;
	unsigned __int64 intercept_read_dr3 : 1;
	unsigned __int64 intercept_read_dr4 : 1;
	unsigned __int64 intercept_read_dr5 : 1;
	unsigned __int64 intercept_read_dr6 : 1;
	unsigned __int64 intercept_read_dr7 : 1;
	unsigned __int64 intercept_read_dr8 : 1;
	unsigned __int64 intercept_read_dr9 : 1;
	unsigned __int64 intercept_read_dr10 : 1;
	unsigned __int64 intercept_read_dr11 : 1;
	unsigned __int64 intercept_read_dr12 : 1;
	unsigned __int64 intercept_read_dr13 : 1;
	unsigned __int64 intercept_read_dr14 : 1;
	unsigned __int64 intercept_read_dr15 : 1;

	unsigned __int64 intercept_write_dr0 : 1;
	unsigned __int64 intercept_write_dr1 : 1;
	unsigned __int64 intercept_write_dr2 : 1;
	unsigned __int64 intercept_write_dr3 : 1;
	unsigned __int64 intercept_write_dr4 : 1;
	unsigned __int64 intercept_write_dr5 : 1;
	unsigned __int64 intercept_write_dr6 : 1;
	unsigned __int64 intercept_write_dr7 : 1;
	unsigned __int64 intercept_write_dr8 : 1;
	unsigned __int64 intercept_write_dr9 : 1;
	unsigned __int64 intercept_write_dr10 : 1;
	unsigned __int64 intercept_write_dr11 : 1;
	unsigned __int64 intercept_write_dr12 : 1;
	unsigned __int64 intercept_write_dr13 : 1;
	unsigned __int64 intercept_write_dr14 : 1;
	unsigned __int64 intercept_write_dr15 : 1;

	unsigned __int64 intercept_exception_vector_0 : 1;
	unsigned __int64 intercept_exception_vector_1 : 1;
	unsigned __int64 intercept_exception_vector_2 : 1;
	unsigned __int64 intercept_exception_vector_3 : 1;
	unsigned __int64 intercept_exception_vector_4 : 1;
	unsigned __int64 intercept_exception_vector_5 : 1;
	unsigned __int64 intercept_exception_vector_6 : 1;
	unsigned __int64 intercept_exception_vector_7 : 1;
	unsigned __int64 intercept_exception_vector_8 : 1;
	unsigned __int64 intercept_exception_vector_9 : 1;
	unsigned __int64 intercept_exception_vector_10 : 1;
	unsigned __int64 intercept_exception_vector_11 : 1;
	unsigned __int64 intercept_exception_vector_12 : 1;
	unsigned __int64 intercept_exception_vector_13 : 1;
	unsigned __int64 intercept_exception_vector_14 : 1;
	unsigned __int64 intercept_exception_vector_15 : 1;


	unsigned __int64 intercept_intr : 1;
	unsigned __int64 intercept_nmi : 1;
	unsigned __int64 intercept_smi : 1;
	unsigned __int64 intercept_init : 1;
	unsigned __int64 intercept_vintr : 1;
	// Intercept CR0 writes that change bits other than CR0.TS or CR0.MP.
	unsigned __int64 intercept_cr0_changing_writes : 1;
	unsigned __int64 intercept_read_idtr : 1;
	unsigned __int64 intercept_read_gdtr : 1;
	unsigned __int64 intercept_read_ldtr : 1;
	unsigned __int64 intercept_read_tr : 1;
	unsigned __int64 intercept_write_idtr : 1;
	unsigned __int64 intercept_write_gdtr : 1;
	unsigned __int64 intercept_write_ldtr : 1;
	unsigned __int64 intercept_write_tr : 1;
	unsigned __int64 intercept_rdtsc : 1;
	unsigned __int64 intercept_rdpmc : 1;
	unsigned __int64 intercept_pushf : 1;
	unsigned __int64 intercept_popf : 1;
	unsigned __int64 intercept_cpuid : 1;
	unsigned __int64 intercept_rsm : 1;
	unsigned __int64 intercept_iret : 1;
	unsigned __int64 intercept_intn : 1;
	unsigned __int64 intercept_invd : 1;
	unsigned __int64 intercept_pause : 1;
	unsigned __int64 intercept_hlt : 1;
	unsigned __int64 intercept_invlpg : 1;
	unsigned __int64 intercept_invlpga : 1;
	// Intercept IN/OUT accesses to selected ports
	unsigned __int64 ioio_prot : 1;
	// intercept RDMSR or WRMSR accesses to selected MSRs
	unsigned __int64 msr_prot : 1;
	unsigned __int64 intercept_task_switches : 1;
	// intercept processor “freezing” during legacy FERR handling
	unsigned __int64 ferr_freeze : 1;
	unsigned __int64 intercept_shutdown_events : 1;


	unsigned __int64 intercept_vmrun : 1;
	unsigned __int64 intercept_vmmcall : 1;
	unsigned __int64 intercept_vmsave : 1;
	unsigned __int64 intercept_stgi : 1;
	unsigned __int64 intercept_clgi : 1;
	unsigned __int64 intercept_skinit : 1;
	unsigned __int64 intercept_rdtscp : 1;
	unsigned __int64 intercept_icebp : 1;
	unsigned __int64 intercept_wbinvd : 1;
	unsigned __int64 intercept_monitor : 1;
	unsigned __int64 intercept_mwait_unconditionally : 1;
	unsigned __int64 intercept_mwait_if_armed : 1;
	unsigned __int64 intercept_xsetbv : 1;
	unsigned __int64 intercept_rdpru : 1;
	unsigned __int64 intercept_write_efer_after_guest_inst_finishes : 1;
	unsigned __int64 intercept_write_cr0_after_guest_inst_finishes : 1;
	unsigned __int64 intercept_write_cr1_after_guest_inst_finishes : 1;
	unsigned __int64 intercept_write_cr2_after_guest_inst_finishes : 1;
	unsigned __int64 intercept_write_cr3_after_guest_inst_finishes : 1;
	unsigned __int64 intercept_write_cr4_after_guest_inst_finishes : 1;
	unsigned __int64 intercept_write_cr5_after_guest_inst_finishes : 1;
	unsigned __int64 intercept_write_cr6_after_guest_inst_finishes : 1;
	unsigned __int64 intercept_write_cr7_after_guest_inst_finishes : 1;
	unsigned __int64 intercept_write_cr8_after_guest_inst_finishes : 1;
	unsigned __int64 intercept_write_cr9_after_guest_inst_finishes : 1;
	unsigned __int64 intercept_write_cr10_after_guest_inst_finishes : 1;
	unsigned __int64 intercept_write_cr11_after_guest_inst_finishes : 1;
	unsigned __int64 intercept_write_cr12_after_guest_inst_finishes : 1;
	unsigned __int64 intercept_write_cr13_after_guest_inst_finishes : 1;
	unsigned __int64 intercept_write_cr14_after_guest_inst_finishes : 1;
	unsigned __int64 intercept_write_cr15_after_guest_inst_finishes : 1;


	unsigned __int64 intercept_all_invlpg : 1;
	unsigned __int64 intercept_illegal_invlpg : 1;
	unsigned __int64 intercept_pcid : 1;
	unsigned __int64 intercept_mcommit : 1;
	unsigned __int64 intercept_tlbsync : 1;
	// sbz
	unsigned __int64 reserved0 : 27;

	// sbz
	unsigned char reserved1[39];


	unsigned __int64 pause_filter_threshold : 15;
	unsigned __int64 pause_filter_count : 1;

	// Physical base address of IOPM (bits 11:0 are ignored.)
	unsigned __int64 iopm_base_pa;

	unsigned __int64 msrpm_base_pa;

	unsigned __int64 tsc_offset;

	unsigned __int64 guest_asid: 32;
	unsigned __int64 tlb_control : 8;
	unsigned __int64 reserved2 : 24;


	unsigned __int64 v_tpr : 8;
	// If non zero, virtual INTR is pending
	unsigned __int64 v_irq : 1;
	// 0 – Virtual interrupts are masked, 1 – Virtual Interrupts are unmasked
	unsigned __int64 vgif : 1;
	unsigned __int64 reserved3 : 6;
	unsigned __int64 v_intr_prio : 4;
	// If nonzero, the current virtual interrupt ignores the (virtual) TPR
	unsigned __int64 v_ign_tpr : 4;
	unsigned __int64 reserved4 : 3;
	// Virtualize masking of INTR interrupts 
	unsigned __int64 v_intr_masking : 4;
	// AMD Virtual GIF Enabled for this guest
	unsigned __int64 amd_vgif : 4;
	unsigned __int64 reserved5 : 5;
	unsigned __int64 avic_enable : 5;
	unsigned __int64 v_intr_vector : 8;
	unsigned __int64 reserved6 : 24;
	
	unsigned __int64 interrupt_shadow : 1;
	// Value of the RFLAGS.IF bit for the guest
	unsigned __int64 guest_interrupt_mask : 1;
	unsigned __int64 reserved7 : 62;

	unsigned __int64 exitcode;

	unsigned __int64 exitinfo1;

	unsigned __int64 exitinfo2;

	unsigned __int64 exitintinfo;

	unsigned __int64 np_enable: 1;
	unsigned __int64 secure_encrypted_virtualization: 1;
	unsigned __int64 encrypted_state_for_sev: 1;
	unsigned __int64 guest_mode_execute_trap: 1;
	// Enable supervisor shadow stack restrictions in nested page tables
	unsigned __int64 sss_check_en: 1;
	unsigned __int64 virtual_transparent_encryption: 1;
	unsigned __int64 reserved8: 1;
	unsigned __int64 enable_invlpgb_tlbsync: 1;
	unsigned __int64 reserved9: 56;

	unsigned __int64 avic_apic_bar: 52;
	unsigned __int64 reserved10: 12;


	unsigned __int64 guest_phys_addr_ghcb;

	unsigned __int64 event_injection;

	unsigned __int64 nested_page_table_cr3;

	unsigned __int64 lbr_virt_enable: 1;
	unsigned __int64 virtualized_vmsave_vmload: 1;
	unsigned __int64 reserved11: 62;

	unsigned __int64 vmcb_clean_bits: 32;
	unsigned __int64 reserved12: 32;
	
	// nRIP—Next sequential instruction pointer
	unsigned __int64 next_rip;

	unsigned __int64 number_of_bytes_fetched: 8;
	unsigned char guest_instruction_bytes[120];

	unsigned __int64 avic_apic_backing_page_pointer: 52;
	unsigned __int64 reserved13: 12;

	unsigned char reserved14[8];

	unsigned __int64 reserved15: 12;
	unsigned __int64 avic_logical_table_pointer: 40;
	unsigned __int64 reserved16: 12;

	unsigned __int64 avic_physical_max_index: 8;
	unsigned __int64 reserved17: 4;
	unsigned __int64 avic_physical_table_pointer: 40;
	unsigned __int64 reserved18: 12;

	unsigned char reserved19[8];
	unsigned __int64 reserved20: 12;
	unsigned __int64 vmsa_pointer: 40;
	unsigned __int64 reserved21: 12;

	// Remaining n-1024 reserved.
};

// 16 bytes
struct segment_t {
	unsigned __int16 selector;
	unsigned __int16 attrib;
	unsigned __int32 limit;
	unsigned __int64 base;
};

struct __vmcb_statesave_t {
	struct segment_t es;
	struct segment_t cs;
	struct segment_t ss;
	struct segment_t ds;
	struct segment_t fs;
	struct segment_t gs;
	struct segment_t gdtr;
	struct segment_t ldtr;
	struct segment_t idtr;
	struct segment_t tr;

	unsigned char reserved0[0x2B];

	// If the guest is real-mode then the CPL is forced to 0; 
	// if the guest is virtual-mode then the CPL is forced to 3.
	unsigned __int8 cpl;

	unsigned char reserved1[4];

	unsigned __int64 efer;
	
	unsigned char reserved2[0x70];


	unsigned __int64 cr4;
	unsigned __int64 cr3;
	unsigned __int64 cr0;
	unsigned __int64 dr7;
	unsigned __int64 dr6;
	unsigned __int64 rflags;
	unsigned __int64 rip;

	unsigned char reserved3[0x58];

	unsigned __int64 rsp;
	unsigned __int64 s_cet;
	unsigned __int64 ssp;
	unsigned __int64 isst_addr;
	unsigned __int64 rax;
	unsigned __int64 star;
	unsigned __int64 lstar;
	unsigned __int64 cstar;
	unsigned __int64 sfmask;
	unsigned __int64 kernel_gs_base;
	unsigned __int64 sysenter_cs;
	unsigned __int64 sysenter_esp;
	unsigned __int64 sysenter_eip;
	unsigned __int64 cr2;

	unsigned char reserved4[0x20];

	unsigned __int64 guest_pat;
	unsigned __int64 dbgctl;
	unsigned __int64 br_from;
	unsigned __int64 br_to;
	unsigned __int64 lastexcpfrom;

	unsigned char reserved5[0x48];
	unsigned __int32 spec_ctrl;

	// remaining reserved bits
};

__declspec(align(4096)) struct __vmcb_t {
	struct __vmcb_control_t control;
	struct __vmcb_statesave_t statesave;
};

struct __vmcb_t* vmcb_alloc_and_zero();
int vmcb_init(struct __vmcb_t*);
