#include "Fun.h"
typedef struct _PROTECTPID_INPUT {
    ULONG OriPID;
    ULONG NewPID;
}PROTECTPID_INPUT;
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING pRegPath) {
	DbgPrint("Driver Loaded\n");
	NTSTATUS Status = STATUS_SUCCESS;
	PDEVICE_OBJECT DeviceObject = NULL;
	UNICODE_STRING DeviceObjectName;
	UNICODE_STRING DeviceLinkName;

	DriverObject->DriverUnload = DriverUnload;
	RtlInitUnicodeString(&DeviceObjectName, DEVICE_NAME);
	
	Status = IoCreateDevice(DriverObject, NULL,
		&DeviceObjectName,
		FILE_DEVICE_UNKNOWN,
		0, FALSE,
		&DeviceObject);
	if (!NT_SUCCESS(Status))
		return Status;
	
	RtlInitUnicodeString(&DeviceLinkName, DEVICE_LINK_NAME);
	Status = IoCreateSymbolicLink(&DeviceLinkName, &DeviceObjectName);
	if (!NT_SUCCESS(Status))
	{
		IoDeleteDevice(DeviceObject);
		return Status;
	}

	//设计符合我们代码的派遣历程
	for (ULONG i = 0; i < IRP_MJ_MAXIMUM_FUNCTION; i++)
	{
		DriverObject->MajorFunction[i] = PassThroughDispatch;   
	}
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = ControlThroughDispatch;
	return Status;
}
//派遣历程
NTSTATUS PassThroughDispatch(PDEVICE_OBJECT  DeviceObject, PIRP Irp)
{
	Irp->IoStatus.Status = STATUS_SUCCESS;     //LastError()
	Irp->IoStatus.Information = 0;             //ReturnLength
	IoCompleteRequest(Irp, IO_NO_INCREMENT);   //将Irp返回给Io管理器
	return STATUS_SUCCESS;
}
NTSTATUS ControlThroughDispatch(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    PROTECTPID_INPUT inPid = { 0,0 };
    NTSTATUS Status=STATUS_SUCCESS;
    ULONG_PTR Informaton = 0;
    PVOID InputData = NULL;
    ULONG InputDataLength = 0;
    PVOID OutputData = NULL;
    ULONG OutputDataLength = 0;
    ULONG IoControlCode = 0;
    PIO_STACK_LOCATION  IoStackLocation = IoGetCurrentIrpStackLocation(Irp);  //Irp堆栈  
    IoControlCode = IoStackLocation->Parameters.DeviceIoControl.IoControlCode;
    InputData = Irp->AssociatedIrp.SystemBuffer;
    OutputData = Irp->AssociatedIrp.SystemBuffer;
    InputDataLength = IoStackLocation->Parameters.DeviceIoControl.InputBufferLength;
    OutputDataLength = IoStackLocation->Parameters.DeviceIoControl.OutputBufferLength;
    switch (IoControlCode)
    {
    case CTL_SetRandomProcessID:
    {
        if (InputData != NULL && InputDataLength > 0)
        {
            RtlMoveMemory(&inPid, InputData, InputDataLength);
            DbgPrint("Get[%d][%d]\r\n", inPid.OriPID, inPid.NewPID);
        }
        if (OutputData != NULL)
        {
            if (SetRandomProcessID(inPid.OriPID) == STATUS_SUCCESS) {
                memcpy(OutputData, "123", strlen("123") + 1);
                Status = STATUS_SUCCESS;
            }
            else {
                memcpy(OutputData, "666", strlen("666") + 1);
                Status = STATUS_SUCCESS;
            }
            Informaton = strlen("666")+1;
        }
        else
        {
            Status = STATUS_INSUFFICIENT_RESOURCES;   //内存不够
            Informaton = 0;
        }
        break;
    }
    case CTL_SetProcessID:
    {
        if (InputData != NULL && InputDataLength > 0)
        {
            RtlMoveMemory(&inPid, InputData, InputDataLength);
            DbgPrint("Get[%d][%d]\r\n", inPid.OriPID, inPid.NewPID);
        }
        if (OutputData != NULL)
        {
            if (SetProcessID(inPid.OriPID,inPid.NewPID) == STATUS_SUCCESS) {
                memcpy(OutputData, "123", strlen("123") + 1);
                Status = STATUS_SUCCESS;
            }
            else {
                memcpy(OutputData, "666", strlen("666") + 1);
                Status = STATUS_SUCCESS;
            }
            Informaton = strlen("666") + 1;
        }
        else
        {
            Status = STATUS_INSUFFICIENT_RESOURCES;   //内存不够
            Informaton = 0;
        }
        break;
    }
    case CTL_HideProcess:
    {
        if (InputData != NULL && InputDataLength > 0)
        {
            RtlMoveMemory(&inPid, InputData, InputDataLength);
            DbgPrint("Get[%d][%d]\r\n", inPid.OriPID, inPid.NewPID);
        }
        if (OutputData != NULL)
        {
            if (HideProcess(inPid.OriPID) == STATUS_SUCCESS) {
                memcpy(OutputData, "123", strlen("123") + 1);
                Status = STATUS_SUCCESS;
            }
            else {
                memcpy(OutputData, "666", strlen("666") + 1);
                Status = STATUS_SUCCESS;
            }
            Informaton = strlen("666") + 1;
        }
        else
        {
            Status = STATUS_INSUFFICIENT_RESOURCES;   //内存不够
            Informaton = 0;
        }
        break;
    }
    case CTL_SetForbidAccessStatus:
    {
        if (InputData != NULL && InputDataLength > 0)
        {
            RtlMoveMemory(&inPid, InputData, InputDataLength);
            DbgPrint("Get[%d][%d]\r\n", inPid.OriPID, inPid.NewPID);
        }
        if (OutputData != NULL)
        {
            if (SetForbidAccessStatus(inPid.OriPID) == STATUS_SUCCESS) {
                memcpy(OutputData, "123", strlen("123") + 1);
                Status = STATUS_SUCCESS;
            }
            else {
                memcpy(OutputData, "666", strlen("666") + 1);
                Status = STATUS_SUCCESS;
            }
            Informaton = strlen("666") + 1;
        }
        else
        {
            Status = STATUS_INSUFFICIENT_RESOURCES;   //内存不够
            Informaton = 0;
        }
        break;
    }
    case CTL_UnSetForbidAccessStatus:
    {
        if (InputData != NULL && InputDataLength > 0)
        {
            RtlMoveMemory(&inPid, InputData, InputDataLength);
            DbgPrint("Get[%d][%d]\r\n", inPid.OriPID, inPid.NewPID);
        }
        if (OutputData != NULL)
        {
            if (UnSetForbidAccessStatus(inPid.OriPID) == STATUS_SUCCESS) {
                memcpy(OutputData, "123", strlen("123") + 1);
                Status = STATUS_SUCCESS;
            }
            else {
                memcpy(OutputData, "666", strlen("666") + 1);
                Status = STATUS_SUCCESS;
            }
            Informaton = strlen("666") + 1;
        }
        else
        {
            Status = STATUS_INSUFFICIENT_RESOURCES;   //内存不够
            Informaton = 0;
        }
        break;
    }
    default:
        break;
    }
    Irp->IoStatus.Status = Status;             //Ring3 GetLastError();
    Irp->IoStatus.Information = Informaton;    //返回值长度(很tm关键) 
    IoCompleteRequest(Irp, IO_NO_INCREMENT);  //将Irp返回给Io管理器

    return Status;                            //Ring3 DeviceIoControl()返回值
}

