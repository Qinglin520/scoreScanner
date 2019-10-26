// scoreScanner.cpp : ����Ӧ�ó��������Ϊ��
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

// CscoreScannerApp ����
CscoreScannerApp::CscoreScannerApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CscoreScannerApp ����
CscoreScannerApp theApp;

// CscoreScannerApp ��ʼ��
BOOL CscoreScannerApp::InitInstance()
{
	handle = ::CreateMutex(NULL, FALSE, one);//handleΪ������HANDLE���͵�ȫ�ֱ���
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		AfxMessageBox(_T("Ӧ�ó����Ѿ�������"));
		return FALSE;
	}

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õĹ����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի�������κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	SetRegistryKey(_T("��������ɨ����-PC�ͻ���"));
	ShellExecute(NULL, NULL, _T("toolbox\\bin\\logCleaner.bat"), NULL, NULL, SW_HIDE);

	CscoreScannerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	
	if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó��򣬶���������Ӧ�ó������Ϣ�á�
	return FALSE;
}

int CscoreScannerApp::ExitInstance()
{
	CloseHandle(handle);
	return CWinApp::ExitInstance();
}