
// MFCApplication1Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON10, &CMFCApplication1Dlg::OnBnClickedButton10)
    ON_BN_CLICKED(IDC_BUTTON9, &CMFCApplication1Dlg::OnBnClickedButton9)
    ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication1Dlg::OnBnClickedButton4)
    ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication1Dlg::OnBnClickedButton5)
    ON_BN_CLICKED(IDC_BUTTON7, &CMFCApplication1Dlg::OnBnClickedButton7)
    ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication1Dlg::OnBnClickedButton6)
    ON_BN_CLICKED(IDC_BUTTON11, &CMFCApplication1Dlg::OnBnClickedButton11)
    ON_BN_CLICKED(IDC_BUTTON8, &CMFCApplication1Dlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序
BOOL InitGlobals();
BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    InitGlobals();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
#pragma warning(disable:4996)
#include <Winsvc.h>
#include <strsafe.h>
#include <winioctl.h>
#define DRIVER_IMAGE_BASE_NAME         L"DriverHideProcess.sys"
#define DEVICE_LINK_NAME    L"\\\\.\\DriverHideProcessLink"
#define DRIVER_NAME        L"DriverHideProcess"
#define CTL_SetRandomProcessID CTL_CODE(FILE_DEVICE_UNKNOWN,0x800,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define CTL_HideProcess CTL_CODE(FILE_DEVICE_UNKNOWN,0x801,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define CTL_SetProcessID CTL_CODE(FILE_DEVICE_UNKNOWN,0x802,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define CTL_SetForbidAccessStatus CTL_CODE(FILE_DEVICE_UNKNOWN,0x803,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define CTL_UnSetForbidAccessStatus CTL_CODE(FILE_DEVICE_UNKNOWN,0x804,METHOD_BUFFERED,FILE_ANY_ACCESS)
HANDLE DeviceHandle = INVALID_HANDLE_VALUE;
WCHAR drvFullPath[MAX_PATH];
BOOL isSetPID = FALSE;
struct _Status
{
    BOOL isDriverInstalled = FALSE;
    BOOL isDriverRuned = FALSE;
    BOOL isDriverStoped = FALSE;
    BOOL isDriverUninstalled = FALSE;
}Status;
struct _PROTECTPID_INPUT {
    ULONG OriPID=0;
    ULONG NewPID=0;      
}PROTECTPID_INPUT;
HMODULE GetSelfModuleHandle()
{
    
    MEMORY_BASIC_INFORMATION mbi;
    return ((::VirtualQuery(GetSelfModuleHandle, &mbi, sizeof(mbi)) != 0) ? (HMODULE)mbi.AllocationBase : NULL);
}
inline bool CheckFileExists(LPCWSTR name) {
    struct _stat64 buffer;
    return (_wstat64(name, &buffer) == 0);
}
WCHAR* GetCurrentPath(void)
{
    WCHAR path[MAX_PATH] = { 0 };
    memset(path, 0, sizeof(path));
    GetModuleFileName(GetSelfModuleHandle(), path, sizeof(path));
    int l = _tcslen(path);
    TCHAR ch = 0;
    while ('\\' != (ch = *(path + --l)));
    *(path + l + 1) = 0;
    return path;
}
BOOL InitGlobals() {
    wcscpy(drvFullPath, GetCurrentPath());
    wcscat(drvFullPath, DRIVER_IMAGE_BASE_NAME);
    return TRUE;
}

#pragma region
// 安装驱动
BOOL installDvr() {
    if (!CheckFileExists(drvFullPath)) {
        MessageBoxW(0, L"未找到驱动", L"检测文件目录下有没有驱动", 0);
        return FALSE;
    }
    // 打开服务控制管理器数据库
    SC_HANDLE schSCManager = OpenSCManager(
        NULL,                   // 目标计算机的名称,NULL：连接本地计算机上的服务控制管理器
        NULL,                   // 服务控制管理器数据库的名称，NULL：打开 SERVICES_ACTIVE_DATABASE 数据库
        SC_MANAGER_ALL_ACCESS   // 所有权限
    );
    if (schSCManager == NULL)
        return FALSE;
    // 创建服务对象，添加至服务控制管理器数据库
    SC_HANDLE schService = CreateServiceW(
        schSCManager,               // 服务控件管理器数据库的句柄
        DRIVER_NAME,               // 要安装的服务的名称
        DRIVER_NAME,               // 用户界面程序用来标识服务的显示名称
        SERVICE_ALL_ACCESS,         // 对服务的访问权限：所有全权限
        SERVICE_KERNEL_DRIVER,      // 服务类型：驱动服务
        SERVICE_DEMAND_START,       // 服务启动选项：进程调用 StartService 时启动
        SERVICE_ERROR_NORMAL,       // 如果无法启动：忽略错误继续运行
        drvFullPath,                // 驱动文件绝对路径，如果包含空格需要多加双引号
        NULL,                       // 服务所属的负载订购组：服务不属于某个组
        NULL,                       // 接收订购组唯一标记值：不接收
        NULL,                       // 服务加载顺序数组：服务没有依赖项
        NULL,                       // 运行服务的账户名：使用 LocalSystem 账户
        NULL                        // LocalSystem 账户密码
    );
    if (schService == NULL) {
        CloseServiceHandle(schSCManager);
        return FALSE;
    }

    CloseServiceHandle(schService);
    CloseServiceHandle(schSCManager);
    return TRUE;
}

// 启动服务
BOOL startDvr() {
    
    // 打开服务控制管理器数据库
    SC_HANDLE schSCManager = OpenSCManager(
        NULL,                   // 目标计算机的名称,NULL：连接本地计算机上的服务控制管理器
        NULL,                   // 服务控制管理器数据库的名称，NULL：打开 SERVICES_ACTIVE_DATABASE 数据库
        SC_MANAGER_ALL_ACCESS   // 所有权限
    );
    if (schSCManager == NULL) {
        MessageBoxA(0, "打开服务控制管理器数据库Err", 0, 0);
        return FALSE;
    }

    // 打开服务
    SC_HANDLE hs = OpenService(
        schSCManager,           // 服务控件管理器数据库的句柄
        DRIVER_NAME,            // 要打开的服务名
        SERVICE_ALL_ACCESS      // 服务访问权限：所有权限
    );
    if (hs == NULL) {
        CloseServiceHandle(schSCManager);
        MessageBoxA(0, 0, "OpenServiceErr", 0);
        return FALSE;
    }
    if (!StartServiceW(hs, 0, 0)) {
        char lasterrchr[10] = "\0";
        DWORD lasterr = GetLastError();
        _itoa(lasterr, lasterrchr,10);
        MessageBoxA(0, lasterrchr, "StartServiceErr", 0);
        CloseServiceHandle(hs);
        CloseServiceHandle(schSCManager);
        return FALSE;
    }


    CloseServiceHandle(hs);
    CloseServiceHandle(schSCManager);
    return TRUE;
}

// 停止服务
BOOL stopDvr() {
   
    // 打开服务控制管理器数据库
    SC_HANDLE schSCManager = OpenSCManager(
        NULL,                   // 目标计算机的名称,NULL：连接本地计算机上的服务控制管理器
        NULL,                   // 服务控制管理器数据库的名称，NULL：打开 SERVICES_ACTIVE_DATABASE 数据库
        SC_MANAGER_ALL_ACCESS   // 所有权限
    );
    if (schSCManager == NULL) {
        MessageBoxA(0, "打开服务控制管理器数据库Err", 0, 0);
        return FALSE;
    }

    // 打开服务
    SC_HANDLE hs = OpenService(
        schSCManager,           // 服务控件管理器数据库的句柄
        DRIVER_NAME,            // 要打开的服务名
        SERVICE_ALL_ACCESS      // 服务访问权限：所有权限
    );
    if (hs == NULL) {
        MessageBoxA(0, "OpenServiceErr", 0, 0);
        CloseServiceHandle(schSCManager);
        return FALSE;
    }

    // 如果服务正在运行
    SERVICE_STATUS status;
    QueryServiceStatus(hs, &status);

    if (status.dwCurrentState != SERVICE_STOPPED &&
        status.dwCurrentState != SERVICE_STOP_PENDING
        ) {
        // 发送关闭服务请求
        if (ControlService(
            hs,                         // 服务句柄
            SERVICE_CONTROL_STOP,       // 控制码：通知服务应该停止
            &status                     // 接收最新的服务状态信息
        ) == 0) {
            CloseServiceHandle(hs);
            CloseServiceHandle(schSCManager);
            MessageBoxA(0, "ControlServiceErr", 0, 0);
            return FALSE;
        }

        // 判断超时
        INT timeOut = 0;
        while (status.dwCurrentState != SERVICE_STOPPED) {
            timeOut++;
            QueryServiceStatus(hs, &status);
                
            Sleep(50);
        }
        if (timeOut > 80) {
            CloseServiceHandle(hs);
            CloseServiceHandle(schSCManager);
            MessageBoxA(0, "KillDriverTimeout", 0, 0);
            return FALSE;
        }
    }

    CloseServiceHandle(hs);
    CloseServiceHandle(schSCManager);
    return TRUE;
}

// 卸载驱动
BOOL unloadDvr() {
   
    // 打开服务控制管理器数据库
    SC_HANDLE schSCManager = OpenSCManager(
        NULL,                   // 目标计算机的名称,NULL：连接本地计算机上的服务控制管理器
        NULL,                   // 服务控制管理器数据库的名称，NULL：打开 SERVICES_ACTIVE_DATABASE 数据库
        SC_MANAGER_ALL_ACCESS   // 所有权限
    );
    if (schSCManager == NULL) {
        return FALSE;
    }

    // 打开服务
    SC_HANDLE hs = OpenService(
        schSCManager,           // 服务控件管理器数据库的句柄
        DRIVER_NAME,            // 要打开的服务名
        SERVICE_ALL_ACCESS      // 服务访问权限：所有权限
    );
    if (hs == NULL) {
        CloseServiceHandle(schSCManager);
        return FALSE;
    }

    // 删除服务
    if (DeleteService(hs) == 0) {
        CloseServiceHandle(hs);
        CloseServiceHandle(schSCManager);
        return FALSE;
    }

    CloseServiceHandle(hs);
    CloseServiceHandle(schSCManager);
    return TRUE;
}
#pragma endregion

void CMFCApplication1Dlg::OnBnClickedButton3()
{
	CString BoxContent = 0;
	CEdit* BoxEdit = (CEdit*)GetDlgItem(IDC_EDIT3);
    if (!installDvr()) {
        BoxEdit->GetWindowTextW(BoxContent);
        BoxEdit->SetWindowTextW(BoxContent + L"[ERR]驱动加载失败\r\n");
        BoxEdit->LineScroll(BoxEdit->GetLineCount());
        return;
    }
    Status.isDriverInstalled = TRUE;
	BoxEdit->GetWindowTextW(BoxContent);
	BoxEdit->SetWindowTextW(BoxContent + L"驱动加载成功\r\n");
    BoxEdit->LineScroll(BoxEdit->GetLineCount());
}


void CMFCApplication1Dlg::OnBnClickedButton2()
{
    CString BoxContent = 0;
    CEdit* BoxEdit = (CEdit*)GetDlgItem(IDC_EDIT3);
    if (!unloadDvr()) {
        BoxEdit->GetWindowTextW(BoxContent);
        BoxEdit->SetWindowTextW(BoxContent + L"[ERR]驱动卸载失败\r\n");
        BoxEdit->LineScroll(BoxEdit->GetLineCount());
        return;
    }
    Status.isDriverUninstalled = TRUE;
    BoxEdit->GetWindowTextW(BoxContent);
    BoxEdit->SetWindowTextW(BoxContent + L"驱动卸载成功\r\n");
    BoxEdit->LineScroll(BoxEdit->GetLineCount());
}


void CMFCApplication1Dlg::OnBnClickedButton10()
{
    CString BoxContent = 0;
    CEdit* BoxEdit = (CEdit*)GetDlgItem(IDC_EDIT3);
    if (!startDvr()) {
        BoxEdit->GetWindowTextW(BoxContent);
        BoxEdit->SetWindowTextW(BoxContent + L"[ERR]驱动启动失败\r\n");
        BoxEdit->LineScroll(BoxEdit->GetLineCount());
        return;
    }
    Status.isDriverRuned = TRUE;
    BoxEdit->GetWindowTextW(BoxContent);
    BoxEdit->SetWindowTextW(BoxContent + L"驱动启动成功\r\n");
    BoxEdit->LineScroll(BoxEdit->GetLineCount());
}

void CMFCApplication1Dlg::OnBnClickedButton9()
{
    CString BoxContent = 0;
    CEdit* BoxEdit = (CEdit*)GetDlgItem(IDC_EDIT3);
    if (!stopDvr()) {
        BoxEdit->GetWindowTextW(BoxContent);
        BoxEdit->SetWindowTextW(BoxContent + L"[ERR]驱动停止失败\r\n");
        BoxEdit->LineScroll(BoxEdit->GetLineCount());
        return;
    }
    Status.isDriverStoped = TRUE;
    BoxEdit->GetWindowTextW(BoxContent);
    BoxEdit->SetWindowTextW(BoxContent + L"驱动停止成功\r\n");
    BoxEdit->LineScroll(BoxEdit->GetLineCount());
}
BOOL CheckLoaded() {
    return TRUE;// (Status.isDriverInstalled && Status.isDriverRuned && !(Status.isDriverStoped || Status.isDriverUninstalled));
}
VOID UpdatePIDData() {
    BOOL state = false, state2 = false;
    PROTECTPID_INPUT.OriPID = GetDlgItemInt(AfxGetMainWnd()->m_hWnd, IDC_EDIT2, &state, FALSE);
    PROTECTPID_INPUT.NewPID = GetDlgItemInt(AfxGetMainWnd()->m_hWnd, IDC_EDIT4, &state2, FALSE);
    return;
}
BOOL DriverCtrl(int DriverCtrlCode) {
    UpdatePIDData();
    
    if (!CheckLoaded()) {
        WCHAR BoxContent[5000];
        GetDlgItemTextW(AfxGetMainWnd()->m_hWnd, IDC_EDIT3, BoxContent, 4999);
        SetDlgItemTextW(AfxGetMainWnd()->m_hWnd, IDC_EDIT3, StrCatW(BoxContent, L"[ERR]驱动操作错误--请先加载并启动驱动\r\n"));
        return FALSE;
    }
    if (!PROTECTPID_INPUT.OriPID) {
        WCHAR BoxContent[5000];
        GetDlgItemTextW(AfxGetMainWnd()->m_hWnd, IDC_EDIT3, BoxContent, 4999);
        SetDlgItemTextW(AfxGetMainWnd()->m_hWnd, IDC_EDIT3, StrCatW(BoxContent, L"[ERR]请输入进程PID\r\n"));
        return FALSE;
    }
    HANDLE DeviceHandle = CreateFileW(DEVICE_LINK_NAME,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (DeviceHandle == INVALID_HANDLE_VALUE)
    {
        WCHAR BoxContent[5000];
        GetDlgItemTextW(AfxGetMainWnd()->m_hWnd, IDC_EDIT3, BoxContent, 4999);
        SetDlgItemTextW(AfxGetMainWnd()->m_hWnd, IDC_EDIT3, StrCatW(BoxContent, L"[ERR]驱动操作错误--CreateFile\r\n"));
        return FALSE;
    }
    char BufferData[MAX_PATH]="\0";
    DWORD ReturnLength = 0;
    if (!DeviceIoControl(DeviceHandle, DriverCtrlCode, &PROTECTPID_INPUT, sizeof(PROTECTPID_INPUT), (LPVOID)BufferData, MAX_PATH, &ReturnLength, NULL))
    {
       //瞎几把瞎几把写
        DWORD LastError = GetLastError();
        if (LastError == 0L) {//成功了
            goto success;
        }
        if (LastError == ERROR_NO_SYSTEM_RESOURCES)
        {
            MessageBoxA(0, "ERROR_NO_SYSTEM_RESOURCES", 0, 0);
        }
        WCHAR errchar[300], errcode[20];
        _itow(LastError, errcode, 10);
        wcscpy(errchar, L"[ERR]驱动操作错误--DeviceIoControl 错误码=");
        wcscat(errchar, errcode);
        wcscat(errchar, L"\r\n");
        WCHAR BoxContent[5000];
        GetDlgItemTextW(AfxGetMainWnd()->m_hWnd, IDC_EDIT3, BoxContent, 4999);
        SetDlgItemTextW(AfxGetMainWnd()->m_hWnd, IDC_EDIT3, StrCatW(BoxContent, errchar));

        return FALSE;
    }
    success:

    BOOL retval = FALSE;
    WCHAR BoxContent[5000]=L"\0";
    WCHAR BufferDataW[100]=L"\0";
    
    GetDlgItemTextW(AfxGetMainWnd()->m_hWnd, IDC_EDIT3, BoxContent, 4999);
    if (strcmp(BufferData, "123") == 0) {
        if (isSetPID == TRUE) {
            wcscat(BoxContent, L"驱动执行操作成功,原始PID=");
            _ultow(PROTECTPID_INPUT.OriPID, BufferDataW, 10);
            wcscat(BoxContent, BufferDataW);

            wcscat(BoxContent, L",现在PID=");
            _ultow(GetDlgItemInt(AfxGetMainWnd()->m_hWnd, IDC_EDIT4, &isSetPID, FALSE), BufferDataW, 10);
            wcscat(BoxContent, BufferDataW);
            wcscat(BoxContent, L"\r\n");
            SetDlgItemTextW(AfxGetMainWnd()->m_hWnd, IDC_EDIT3, BoxContent);
            retval = TRUE;
            goto end;
        }
        if (isSetPID == FALSE) {
            wcscat(BoxContent, L"驱动执行操作成功,原始PID=");
            _ultow(PROTECTPID_INPUT.OriPID, BufferDataW, 10);
            wcscat(BoxContent, BufferDataW);

            _ultow(PROTECTPID_INPUT.OriPID + 1024L, BufferDataW, 10);
            wcscat(BoxContent, L",现在PID=");
            wcscat(BoxContent, BufferDataW);
            wcscat(BoxContent, L"\r\n");
            SetDlgItemTextW(AfxGetMainWnd()->m_hWnd, IDC_EDIT3, BoxContent);
            retval = TRUE;
            goto end;
        }
        if (isSetPID == 4) {
            wcscat(BoxContent, L"驱动执行操作成功\r\n");
            wcscat(BoxContent, L"[警告]隐藏进程会导致蓝屏\r\n");
            SetDlgItemTextW(AfxGetMainWnd()->m_hWnd, IDC_EDIT3, BoxContent);
            goto end;
        }
        if (isSetPID == 3) {
            wcscat(BoxContent, L"驱动执行操作成功\r\n");
            SetDlgItemTextW(AfxGetMainWnd()->m_hWnd, IDC_EDIT3, BoxContent);
            goto end;
        }
        goto end;
    }
    if (BufferData[0] == '6'&& BufferData[1] == '6'&& BufferData[2] == '6') {
        SetDlgItemTextW(AfxGetMainWnd()->m_hWnd, IDC_EDIT3, StrCatW(BoxContent, L"[ERR]驱动执行操作失败,可能是没找到PID\r\n"));
        retval = FALSE;
        goto end;
    }
    SetDlgItemTextW(AfxGetMainWnd()->m_hWnd, IDC_EDIT3, StrCatW(BoxContent, L"[ERR]驱动发生其他错误\r\n"));
    retval = FALSE;
    end:
    if (DeviceHandle != NULL)
        CloseHandle(DeviceHandle);
    return retval;
}
void CMFCApplication1Dlg::OnBnClickedButton4()//随机pid
{
    isSetPID = FALSE;
    DriverCtrl(CTL_SetRandomProcessID);

}


void CMFCApplication1Dlg::OnBnClickedButton5()//指定pid
{
    isSetPID = TRUE;
    WCHAR BoxContent[5000] = L"\0";
    GetDlgItemTextW(IDC_EDIT3, BoxContent, 4999);
    UpdatePIDData();
    if (PROTECTPID_INPUT.NewPID < 4) {
        wcscat(BoxContent, L"请输入正常的要更改的PID\r\n");
        SetDlgItemTextW(IDC_EDIT3, BoxContent);
        isSetPID = FALSE;
        return;
    }
    DriverCtrl(CTL_SetProcessID);

    isSetPID = FALSE;
}


void CMFCApplication1Dlg::OnBnClickedButton7()//断链隐藏
{
    isSetPID = 4;
    DriverCtrl(CTL_HideProcess);

}


void CMFCApplication1Dlg::OnBnClickedButton6()//用户层不可访问
{
    isSetPID = 3;
    DriverCtrl(CTL_SetForbidAccessStatus);


}


void CMFCApplication1Dlg::OnBnClickedButton11()
{
    isSetPID = 3;
    DriverCtrl(CTL_UnSetForbidAccessStatus);

}


void CMFCApplication1Dlg::OnBnClickedButton8()
{
    MessageBoxW(L"待完成");
}
