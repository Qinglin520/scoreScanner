// SetPreferenceDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "scoreScanner.h"
#include "SetPreferenceDlg.h"
#include "afxdialogex.h"


// CSetPreferenceDlg 对话框

IMPLEMENT_DYNAMIC(CSetPreferenceDlg, CDialogEx)

CSetPreferenceDlg::CSetPreferenceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SETPREFERENCE_DIALOG, pParent)
{

}

CSetPreferenceDlg::~CSetPreferenceDlg()
{
}

void CSetPreferenceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetPreferenceDlg, CDialogEx)
END_MESSAGE_MAP()


// CSetPreferenceDlg 消息处理程序
