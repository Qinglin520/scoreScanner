#pragma once


// CSetPreferenceDlg 对话框

class CSetPreferenceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetPreferenceDlg)

public:
	CSetPreferenceDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetPreferenceDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETPREFERENCE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
