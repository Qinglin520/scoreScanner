// scoreScannerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CscoreScannerDlg �Ի���
class CSplashWindow : public CDialogEx
{
public:
	CSplashWindow(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CSplashWindow();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCORESCANNER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};