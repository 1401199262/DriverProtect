#include "Fun.h"
#include <ntstrsafe.h>

//断链--被PG检测
NTSTATUS HideProcess(ULONG ulPID) {
	PEPROCESS pCurProcess = NULL;
	ULONG CurPID = 0;

	pCurProcess = PsGetCurrentProcess();//system process
	PLIST_ENTRY pActiveProcessLinks = (PLIST_ENTRY)((DWORD_PTR)pCurProcess + ProcessLinksOffset);
	PLIST_ENTRY pNextLinks = pActiveProcessLinks->Flink;
	while (pNextLinks->Flink != pActiveProcessLinks->Flink)
	{
		//DbgPrint("Founding...\n");
		pCurProcess = (DWORD_PTR)pNextLinks - ProcessLinksOffset;
		CurPID = *(ULONG*)((DWORD_PTR)pCurProcess + PIDOffset);
		if (CurPID == ulPID) {
			//*(ULONG*)((DWORD_PTR)pCurProcess + PIDOffset) += 123;
			pNextLinks->Flink->Blink = pNextLinks->Blink;
			pNextLinks->Blink->Flink = pNextLinks->Flink;
			DbgPrint("Found and Delete Chain\n");
			return STATUS_SUCCESS;
		}
		pNextLinks = pNextLinks->Flink;
	}
	DbgPrint("Pid Not Found\n");
	return STATUS_NOT_FOUND;
}

NTSTATUS SetRandomProcessID(ULONG ulPID) {//用PsLookupProcessByProcessId会导致改不回来
	PEPROCESS pCurProcess = NULL;
	ULONG CurPID = 0;

	pCurProcess = PsGetCurrentProcess();//system process
	PLIST_ENTRY pActiveProcessLinks = (PLIST_ENTRY)((DWORD_PTR)pCurProcess + ProcessLinksOffset);
	PLIST_ENTRY pNextLinks = pActiveProcessLinks->Flink;
	while (pNextLinks->Flink != pActiveProcessLinks->Flink)
	{
		//DbgPrint("Founding...\n");
		pCurProcess = (DWORD_PTR)pNextLinks - ProcessLinksOffset;
		CurPID = *(ULONG*)((DWORD_PTR)pCurProcess + PIDOffset);
		if (CurPID == ulPID) {
			*(ULONG*)((DWORD_PTR)pCurProcess + PIDOffset) += 1024;
			DbgPrint("Found Pid and Change to[%d]\n", *(ULONG*)((DWORD_PTR)pCurProcess + PIDOffset));
			return STATUS_SUCCESS;
		}
		pNextLinks = pNextLinks->Flink;
	}
	DbgPrint("Pid Not Found\n");
	return STATUS_NOT_FOUND;
}

NTSTATUS SetProcessID(ULONG origPID, ULONG SetPID) {//用PsLookupProcessByProcessId会导致改不回来
	PEPROCESS pCurProcess = NULL;
	ULONG CurPID = 0;

	pCurProcess = PsGetCurrentProcess();//system process
	PLIST_ENTRY pActiveProcessLinks = (PLIST_ENTRY)((DWORD_PTR)pCurProcess + ProcessLinksOffset);
	PLIST_ENTRY pNextLinks = pActiveProcessLinks->Flink;
	while (pNextLinks->Flink != pActiveProcessLinks->Flink)
	{
		//DbgPrint("Founding...\n");
		pCurProcess = (DWORD_PTR)pNextLinks - ProcessLinksOffset;
		CurPID = *(ULONG*)((DWORD_PTR)pCurProcess + PIDOffset);
		if (CurPID == origPID) {
			*(ULONG*)((DWORD_PTR)pCurProcess + PIDOffset) = SetPID;
			DbgPrint("Found Pid and Change to[%d]\n", *(ULONG*)((DWORD_PTR)pCurProcess + PIDOffset));
			return STATUS_SUCCESS;
		}
		pNextLinks = pNextLinks->Flink;
	}
	DbgPrint("Pid Not Found\n");
	return STATUS_NOT_FOUND;
}

NTSTATUS SetForbidAccessStatus(ULONG ulPID) {
	PEPROCESS pCurProcess = NULL;
	ULONG CurPID = 0;

	pCurProcess = PsGetCurrentProcess();//system process
	PLIST_ENTRY pActiveProcessLinks = (PLIST_ENTRY)((DWORD_PTR)pCurProcess + ProcessLinksOffset);
	PLIST_ENTRY pNextLinks = pActiveProcessLinks->Flink;
	while (pNextLinks->Flink != pActiveProcessLinks->Flink)
	{
		//DbgPrint("Founding...\n");
		pCurProcess = (DWORD_PTR)pNextLinks - ProcessLinksOffset;
		CurPID = *(ULONG*)((DWORD_PTR)pCurProcess + PIDOffset);
		if (CurPID == ulPID) {
			*(ULONG*)((DWORD_PTR)pCurProcess + ProtectLabelOffset) = 0x40000051;//设置为r3不可访问
			DbgPrint("Found and Set\n");
			return STATUS_SUCCESS;
		}
		pNextLinks = pNextLinks->Flink;
	}
	DbgPrint("Pid Not Found\n");
	return STATUS_NOT_FOUND;
}

NTSTATUS UnSetForbidAccessStatus(ULONG ulPID)
{
	PEPROCESS pCurProcess = NULL;
	ULONG CurPID = 0;

	pCurProcess = PsGetCurrentProcess();//system process
	PLIST_ENTRY pActiveProcessLinks = (PLIST_ENTRY)((DWORD_PTR)pCurProcess + ProcessLinksOffset);
	PLIST_ENTRY pNextLinks = pActiveProcessLinks->Flink;
	while (pNextLinks->Flink != pActiveProcessLinks->Flink)
	{
		//DbgPrint("Founding...\n");
		pCurProcess = (DWORD_PTR)pNextLinks - ProcessLinksOffset;
		CurPID = *(ULONG*)((DWORD_PTR)pCurProcess + PIDOffset);
		if (CurPID == ulPID) {
			*(ULONG*)((DWORD_PTR)pCurProcess + ProtectLabelOffset) = 0x40000000;//设置为r3可以访问
			DbgPrint("Found and Set\n");
			return STATUS_SUCCESS;
		}
		pNextLinks = pNextLinks->Flink;
	}
	DbgPrint("Pid Not Found\n");
	return STATUS_NOT_FOUND;
}

VOID DriverUnload(PDRIVER_OBJECT DriverObject) {
	DbgPrint("Driver Unload\n");
	UNICODE_STRING DeviceLinkName;
	PDEVICE_OBJECT NextDriver = NULL;
	PDEVICE_OBJECT DeleteDeviceObject = NULL;

	RtlInitUnicodeString(&DeviceLinkName, DEVICE_LINK_NAME);
	IoDeleteSymbolicLink(&DeviceLinkName);

	DeleteDeviceObject = DriverObject->DeviceObject;
	while (DeleteDeviceObject != NULL)
	{
		NextDriver = DeleteDeviceObject->NextDevice;
		IoDeleteDevice(DeleteDeviceObject);
		DeleteDeviceObject = NextDriver;
	}
}

//===========================================================================
/*
#pragma region unused
#define PROCESS_TERMINATE         0x0001  
#define PROCESS_VM_OPERATION      0x0008  
#define PROCESS_VM_READ           0x0010  
#define PROCESS_VM_WRITE          0x0020  
#define PROCESS_ALL_ACCESS        0x1FFFFF
BOOLEAN CallbackStatus = FALSE;
PVOID obHandle;
NTSTATUS ProtectProcess(BOOLEAN Enable)
{

	OB_CALLBACK_REGISTRATION obReg;
	OB_OPERATION_REGISTRATION opReg;
	RtlZeroMemory(&opReg, sizeof(opReg));
	RtlZeroMemory(&obReg, sizeof(obReg));
	obReg.Version = ObGetFilterVersion();//版本 OB_FLT_REGISTRATION_VERSION
	obReg.OperationRegistrationCount = 1;//注册一个回调
	obReg.RegistrationContext = NULL;

	UNICODE_STRING CBAltitude = { 0 };
	RtlInitUnicodeString(&CBAltitude, L"1000");
	obReg.Altitude = CBAltitude;

	opReg.ObjectType = PsProcessType;
	opReg.Operations = OB_OPERATION_HANDLE_CREATE | OB_OPERATION_HANDLE_DUPLICATE;

	opReg.PreOperation = preCall; //在这里注册一个回调函数指针
	opReg.PostOperation = postCall;


	obReg.OperationRegistration = &opReg; //注意这一条语句
	NTSTATUS code = ObRegisterCallbacks(&obReg, &obHandle);
	if (!NT_SUCCESS(code)) {//在这里注册回调函数
		CallbackStatus = FALSE;
		DbgPrint("Registercallbacks failed code=%ld\n", code);
		return;
	}
	CallbackStatus = TRUE;
}
extern
UCHAR*
PsGetProcessImageFileName(
	__in PEPROCESS Process
);
OB_PREOP_CALLBACK_STATUS
preCall(PVOID RegistrationContext, POB_PRE_OPERATION_INFORMATION pOperationInformation)
{
	//HANDLE pid = PsGetProcessId((PEPROCESS)pOperationInformation->Object);
	char szProcName[16] = { 0 };
	strcpy(szProcName, PsGetProcessImageFileName((PEPROCESS)pOperationInformation->Object));
	//strcpy(szProcName, GetProcessImageNameByProcessID((ULONG)pid));
	if (!_stricmp(szProcName, "Notepad.exe"))
	{
		if (pOperationInformation->Operation == OB_OPERATION_HANDLE_CREATE)
		{

			if ((pOperationInformation->Parameters->CreateHandleInformation.OriginalDesiredAccess & PROCESS_VM_READ) == PROCESS_VM_READ)
			{
				//Read to the address space of the process, such as by calling the user-mode ReadProcessMemory routine.
				pOperationInformation->Parameters->CreateHandleInformation.DesiredAccess &= ~PROCESS_VM_READ;
			}
			if ((pOperationInformation->Parameters->CreateHandleInformation.OriginalDesiredAccess & PROCESS_VM_WRITE) == PROCESS_VM_WRITE)
			{
				//Write to the address space of the process, such as by calling the user-mode WriteProcessMemory routine.
				pOperationInformation->Parameters->CreateHandleInformation.DesiredAccess &= ~PROCESS_VM_WRITE;
			}
		}
	}
exit:

	return OB_PREOP_SUCCESS;
}

VOID
postCall(_In_ PVOID RegistrationContext, _In_ POB_POST_OPERATION_INFORMATION PostInfo)
{
	return;
}

char*
GetProcessImageNameByProcessID(ULONG ulProcessID)
{
	NTSTATUS  Status;
	PEPROCESS  EProcess = NULL;

	//EPROCESS

 //通过句柄获取EProcess
	if (!NT_SUCCESS(PsLookupProcessByProcessId((HANDLE)ulProcessID, &EProcess)))
		return FALSE;

	ObDereferenceObject(EProcess);
	//通过EProcess获得进程名称
	return (char*)PsGetProcessImageFileName(EProcess);
}

VOID UnRegisterCallBack() {
	if (CallbackStatus != FALSE) {
		ObUnRegisterCallbacks(obHandle);
		obHandle = NULL;
	}
}
#pragma endregion unused
*/
//===========================================================================