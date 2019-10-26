// scoreScannerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CscoreScannerDlg 对话框
class CSplashWindow : public CDialogEx
{
public:
	CSplashWindow(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CSplashWindow();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCORESCANNER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};