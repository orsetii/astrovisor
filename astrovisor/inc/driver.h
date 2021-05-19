#pragma once

#include <wdm.h>

// Names to represent our device to the OS.
UNICODE_STRING DEVICE_NAME = RTL_CONSTANT_STRING(L"\\Device\\Astrovisor");
UNICODE_STRING DEVICE_SYMBOLIC_NAME = RTL_CONSTANT_STRING(L"\\??\\AstrovisorLink");

DRIVER_INITIALIZE DriverEntry;
