#pragma once

// CProjectSettingDlg �Ի���

class CProjectSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProjectSettingDlg)

public:
	CProjectSettingDlg(CWnd* pParent = NULL, CString projectName = _T("δ������Ŀ1"));   // ��׼���캯��
	virtual ~CProjectSettingDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWPROJECT_DIALOG };
#endif

public:
	CString projectName;

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
