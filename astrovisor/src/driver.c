#include "driver.h"

void DriverUnload(PDRIVER_OBJECT dob)
{
	DbgPrint("Driver unloaded, deleting symbolic links and devices");
	IoDeleteDevice(dob->DeviceObject);
	IoDeleteSymbolicLink(&DEVICE_SYMBOLIC_NAME);
}

NTSTATUS MajorFunctions(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	PIO_STACK_LOCATION stackLocation = NULL;
	stackLocation = IoGetCurrentIrpStackLocation(Irp);

	switch (stackLocation->MajorFunction)
	{
	case IRP_MJ_CREATE:
		DbgPrint("Handle to %wZ opened", DEVICE_SYMBOLIC_NAME);
		// TODO: Add the HV start code here.
		break;
	case IRP_MJ_CLOSE:
		DbgPrint("Handle to %wZ closed", DEVICE_SYMBOLIC_NAME);
		// TODO: Add the HV Destructor Code here.
		break;
	default:
		break;
	}
	
	Irp->IoStatus.Information = 0;
	Irp->IoStatus.Status = STATUS_SUCCESS;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);

	NTSTATUS status = 0;

	DriverObject->DriverUnload = DriverUnload;

	// NOTE: When we are debugging, we don't want to start and exec
	// 	   some user mode program every time to perform a IRP_MJ_CREATE IOCTL,
	// 	   so, there is a DEBUG define here, which auto-executes the hypervisor in kernel space, 
	// 	   no user interaction required. (Implemented in the Visual Studio Project C/C++->Preprocessor Settings)

#ifdef DEBUG
#else
	// Routines to handle create/close to the device symlink
	DriverObject->MajorFunction[IRP_MJ_CREATE] = MajorFunctions;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = MajorFunctions;
#endif

	return status;
}


