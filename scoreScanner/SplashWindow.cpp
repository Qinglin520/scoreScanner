// SplashWindow.cpp : 实现文件
//

#include "stdafx.h"
#include "scoreScanner.h"
#include "SplashWindow.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSplashWindow 对话框
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

	// TODO:额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// CSplashWindow 消息处理程序
