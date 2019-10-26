// ProjectSettingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "scoreScanner.h"
#include "ProjectSettingDlg.h"
#include "afxdialogex.h"

// CProjectSettingDlg 对话框
IMPLEMENT_DYNAMIC(CProjectSettingDlg, CDialogEx)

CProjectSettingDlg::CProjectSettingDlg(CWnd* pParent, CString projectName)
	: CDialogEx(IDD_PROJECTSETTING_DIALOG, pParent)
{
	this->projectName = projectName;
}

CProjectSettingDlg::~CProjectSettingDlg()
{
}

BOOL CProjectSettingDlg::OnInitDialog()
{
	GetDlgItem(IDC_PROJECTSETEDIT1)->SetWindowText(projectName);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CProjectSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProjectSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CProjectSettingDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CNewProjectDlg 消息处理程序


void CProjectSettingDlg::OnBnClickedOk()
{
	GetDlgItem(IDC_PROJECTSETEDIT1)->GetWindowText(projectName);
	CDialogEx::OnOK();
}
