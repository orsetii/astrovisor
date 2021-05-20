NTSTATUS start_hv(void);
NTSTATUS virtualize_processor(_In_opt_ PCONTEXT Context);
NTSTATUS run_on_each_processor(
	_In_ NTSTATUS(*Callback)(PVOID),
	_In_opt_ PVOID Context,
	_Out_opt_ PULONG NumOfProcessorCompleted
);

_IRQL_requires_max_(DISPATCH_LEVEL) _IRQL_requires_min_(PASSIVE_LEVEL) _IRQL_requires_same_ DECLSPEC_NORETURN EXTERN_C VOID NTAPI astro_launch_vm(_In_ PVOID HostRsp); 
