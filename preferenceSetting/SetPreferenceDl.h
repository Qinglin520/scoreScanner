#pragma once
#include "Resource.h"

// CSetPreferenceDl �Ի���

class CSetPreferenceDl : public CDialogEx
{
	DECLARE_DYNAMIC(CSetPreferenceDl)

public:
	CSetPreferenceDl(CWnd* pParent = NULL);// ��׼���캯��
	virtual ~CSetPreferenceDl();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETPREFERENCEDLL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);// DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	BOOL OnInitDialog();
};
