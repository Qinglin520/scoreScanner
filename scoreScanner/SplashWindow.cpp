// SplashWindow.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "scoreScanner.h"
#include "SplashWindow.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSplashWindow �Ի���
CSplashWindow::CSplashWindow(CWnd* pParent)
	: CDialogEx(IDD_SPLASHWINDOW_DIALOG, pParent)
{

}

CSplashWindow::~CSplashWindow()
{
}

void CSplashWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSplashWindow, CDialogEx)
END_MESSAGE_MAP()

BOOL CSplashWindow::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:����ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// CSplashWindow ��Ϣ�������
