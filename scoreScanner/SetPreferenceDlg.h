#pragma once


// CSetPreferenceDlg �Ի���

class CSetPreferenceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetPreferenceDlg)

public:
	CSetPreferenceDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetPreferenceDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETPREFERENCE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
