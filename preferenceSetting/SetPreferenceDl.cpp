// SetPreferenceDl.cpp : 实现文件
//

#include "stdafx.h"
#include "preferenceSetting.h"
#include "SetPreferenceDl.h"
#include "afxdialogex.h"


extern "C" __declspec(dllexport) void ShowPreferenceDialog()
{
	// 扩展程序的外部接口
	CSetPreferenceDl preferenceDlg;
	preferenceDlg.DoModal();
}

// CSetPreferenceDl 对话框
IMPLEMENT_DYNAMIC(CSetPreferenceDl, CDialogEx)

CSetPreferenceDl::CSetPreferenceDl(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SETPREFERENCEDLL_DIALOG, pParent)
{

}

CSetPreferenceDl::~CSetPreferenceDl()
{
}

BOOL CSetPreferenceDl::OnInitDialog()
{
	return TRUE;
}

void CSetPreferenceDl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSetPreferenceDl, CDialogEx)
END_MESSAGE_MAP()

// CSetPreferenceDl 消息处理程序