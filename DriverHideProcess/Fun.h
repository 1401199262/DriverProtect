#pragma once
#include <ntifs.h>

#define PIDOffset (UINT32)0x2e0
#define ProcessLinksOffset (UINT32)0x2e8
#define FileNameOffset (UINT32)0x450
#define ProtectLabelOffset (UINT32)0x6ca

// DeviceType（设备类型，高16位（16-31位））
// Function（功能2-13 位）
// Method（I/O访问内存使用方式）
// Access（访问限制，14-15位）

#define CTL_SetRandomProcessID CTL_CODE(FILE_DEVICE_UNKNOWN,0x800,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define CTL_HideProcess CTL_CODE(FILE_DEVICE_UNKNOWN,0x801,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define CTL_SetProcessID CTL_CODE(FILE_DEVICE_UNKNOWN,0x802,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define CTL_SetForbidAccessStatus CTL_CODE(FILE_DEVICE_UNKNOWN,0x803,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define CTL_UnSetForbidAccessStatus CTL_CODE(FILE_DEVICE_UNKNOWN,0x804,METHOD_BUFFERED,FILE_ANY_ACCESS)

#define DEVICE_NAME  L"\\Device\\DriverHideProcess"
//设备与设备之间通信
#define DEVICE_LINK_NAME    L"\\DosDevices\\DriverHideProcessLink"
//设备与Ring3之间通信

VOID DriverUnload(PDRIVER_OBJECT pDriverObject);
NTSTATUS SetRandomProcessID(ULONG ulPID);
NTSTATUS SetProcessID(ULONG origPID, ULONG SetPID);
NTSTATUS HideProcess(ULONG ulPID);
NTSTATUS SetForbidAccessStatus(ULONG ulPID);
NTSTATUS UnSetForbidAccessStatus(ULONG ulPID);
NTSTATUS PassThroughDispatch(PDEVICE_OBJECT  DeviceObject, PIRP Irp);
NTSTATUS ControlThroughDispatch(PDEVICE_OBJECT DeviceObject, PIRP Irp);

VOID postCall(_In_ PVOID RegistrationContext, _In_ POB_POST_OPERATION_INFORMATION PostInfo);
OB_PREOP_CALLBACK_STATUS preCall(PVOID RegistrationContext, POB_PRE_OPERATION_INFORMATION pOperationInformation);
