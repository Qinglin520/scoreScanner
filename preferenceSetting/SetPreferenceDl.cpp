// SetPreferenceDl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "preferenceSetting.h"
#include "SetPreferenceDl.h"
#include "afxdialogex.h"


extern "C" __declspec(dllexport) void ShowPreferenceDialog()
{
	// ��չ������ⲿ�ӿ�
	CSetPreferenceDl preferenceDlg;
	preferenceDlg.DoModal();
}

// CSetPreferenceDl �Ի���
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

// CSetPreferenceDl ��Ϣ�������