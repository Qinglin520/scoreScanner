#pragma once
#include "Resource.h"

// CSetPreferenceDl 对话框

class CSetPreferenceDl : public CDialogEx
{
	DECLARE_DYNAMIC(CSetPreferenceDl)

public:
	CSetPreferenceDl(CWnd* pParent = NULL);// 标准构造函数
	virtual ~CSetPreferenceDl();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETPREFERENCEDLL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);// DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	BOOL OnInitDialog();
};
