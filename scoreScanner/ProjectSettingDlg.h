#pragma once

// CProjectSettingDlg 对话框

class CProjectSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProjectSettingDlg)

public:
	CProjectSettingDlg(CWnd* pParent = NULL, CString projectName = _T("未命名项目1"));   // 标准构造函数
	virtual ~CProjectSettingDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWPROJECT_DIALOG };
#endif

public:
	CString projectName;

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
