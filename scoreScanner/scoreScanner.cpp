// scoreScanner.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "scoreScanner.h"
#include "scoreScannerDlg.h"
#include "SplashWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define one _T("0xbe8e2ce1, 0xdab6, 0x11d6, 0xad, 0xd0, 0x0, 0xe0, 0x4c, 0x53, 0xf6, 0xe6")

// CscoreScannerApp
BEGIN_MESSAGE_MAP(CscoreScannerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

// CscoreScannerApp 构造
CscoreScannerApp::CscoreScannerApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CscoreScannerApp 对象
CscoreScannerApp theApp;

// CscoreScannerApp 初始化
BOOL CscoreScannerApp::InitInstance()
{
	handle = ::CreateMutex(NULL, FALSE, one);//handle为声明的HANDLE类型的全局变量
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		AfxMessageBox(_T("应用程序已经在运行"));
		return FALSE;
	}

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	SetRegistryKey(_T("比赛评分扫描器-PC客户端"));
	ShellExecute(NULL, NULL, _T("toolbox\\bin\\logCleaner.bat"), NULL, NULL, SW_HIDE);

	CscoreScannerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	
	if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，而不是启动应用程序的消息泵。
	return FALSE;
}

int CscoreScannerApp::ExitInstance()
{
	CloseHandle(handle);
	return CWinApp::ExitInstance();
}