// Debug Register Definition for DR0-DR3
// Note on DR4 and DR5:
//		Debug registers DR4 and DR5 are reserved when debug extensions are enabled (when the DE flag in control
//		register CR4 is set) and attempts to reference the DR4 and DR5 registers cause invalid-opcode exceptions (#UD).
//
//		When debug extensions are not enabled (when the DE flag is clear), these registers are aliased to debug registers
//		DR6 and DR7.
//
//		MOV DRn instructions do not check that addresses written to DR0–DR3 are in the linear-address limits of
//		the processor implementation. Breakpoint conditions for 8-byte memory read/writes are supported in all modes.
union __drx_t {
	unsigned __int64 bp_linear_address;
	void* breakpoint_address;
};

union __dr6_t {
	unsigned __int64 control;
	struct
	{
		unsigned __int64 bp_0_condition_detected : 1;
		unsigned __int64 bp_1_condition_detected : 1;
		unsigned __int64 bp_2_condition_detected : 1;
		unsigned __int64 bp_3_condition_detected : 1;
		unsigned __int64 reserved0_mb1 : 8; // mb1 = must be one
		unsigned __int64 reserved1 : 1; 
		unsigned __int64 bp_debug_access_detected : 1;
		unsigned __int64 bp_single_step : 1;
		unsigned __int64 bp_task_switch : 1;
		unsigned __int64 reserved2_mb1 : 16;
		unsigned __int64 reserved3 : 16;
	};
};
union __dr7_t {
	unsigned __int64 control;
	struct
	{
		unsigned __int64 local_exact_bp_0_enabled : 1;
		unsigned __int64 global_exact_bp_0_enabled : 1;
		unsigned __int64 local_exact_bp_1_enabled : 1;
		unsigned __int64 global_exact_bp_1_enabled : 1;
		unsigned __int64 local_exact_bp_2_enabled : 1;
		unsigned __int64 global_exact_bp_2_enabled : 1;
		unsigned __int64 local_exact_bp_3_enabled : 1;
		unsigned __int64 global_exact_bp_3_enabled : 1;
		unsigned __int64 local_exact_bp_enabled : 1;
		unsigned __int64 global_exact_bp_enabled : 1;
		unsigned __int64 reserved0_mb1 : 1; // mb1 = must be one
		unsigned __int64 reserved1z : 2; 
		unsigned __int64 general_detect_enabled : 1;
		unsigned __int64 reserved_2 : 2; 
		unsigned __int64 type_of_trans_to_trap_0 : 2;
		unsigned __int64 bp_0_length : 2;
		unsigned __int64 type_of_trans_to_trap_1 : 2;
		unsigned __int64 bp_1_length : 2;
		unsigned __int64 type_of_trans_to_trap_2 : 2;
		unsigned __int64 bp_2_length : 2;
		unsigned __int64 type_of_trans_to_trap_3 : 2;
		unsigned __int64 bp_3_length : 2;
		unsigned __int64 reserved3_mbz : 32;
	};
};
