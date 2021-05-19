union __cr0_t
{
	unsigned __int64 control;
	struct
	{
		unsigned __int64 protection_enable : 1;
		unsigned __int64 monitor_coprocessor : 1;
		unsigned __int64 emulate_fpu : 1;
		unsigned __int64 task_switched : 1;
		unsigned __int64 extension_type : 1;
		unsigned __int64 numeric_error : 1;
		unsigned __int64 reserved_0 : 10;
		unsigned __int64 write_protection : 1;
		unsigned __int64 reserved_1 : 1;
		unsigned __int64 alignment_mask : 1;
		unsigned __int64 reserved_2 : 10;
		unsigned __int64 not_writethrough : 1;
		unsigned __int64 cache_disable : 1;
		unsigned __int64 paging: 1;
		unsigned __int64 reserved_mbz : 32;
	} bits;
};

union __cr4_t
{
	unsigned __int64 control;
	struct
	{
		unsigned __int64 vme : 1;								
		unsigned __int64 pvi : 1;								
		unsigned __int64 time_stamp_disable : 1;				
		unsigned __int64 debug_extensions : 1;					
		unsigned __int64 page_size_extension : 1;				
		unsigned __int64 physical_address_extension : 1;		
		unsigned __int64 machine_check_enable : 1;				
		unsigned __int64 page_global_enable : 1;				
		unsigned __int64 perf_counter_enable : 1;				
		unsigned __int64 os_fxsave_support : 1;					
		unsigned __int64 os_xmm_exception_support : 1;			
		unsigned __int64 usermode_ins_execution_prevention : 1;		
		unsigned __int64 reserved_0 : 4;						
		unsigned __int64 fs_gs_enable : 1;						
		unsigned __int64 process_context_identifer : 1;						
		unsigned __int64 osx_save : 1;						
		unsigned __int64 reserved_1: 1;						
		unsigned __int64 smep: 1;								
		unsigned __int64 smap : 1;							
		unsigned __int64 protection_key_enable : 1;						
		unsigned __int64 cet : 1;								
		unsigned __int64 reserved_mbz : 40;								
	} bits;
};
