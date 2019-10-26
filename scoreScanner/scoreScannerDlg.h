// scoreScannerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CscoreScannerDlg 对话框
class CscoreScannerDlg : public CDialogEx
{
public:
	CscoreScannerDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CscoreScannerDlg();

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
	void UpdateOpenCVWindow(const char* name, const char* picture);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();

	afx_msg void OnNMClickList5(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()

protected:
	void UpdateOutlookBar();
	void UpdateScoreList();
	void UpdateComboBoxes();
	void UpdateEditBoxes();
	void UpdateButtons();
	void deleteArea(IplImage *src);
	void AdaptiveThereshold(Mat &src, Mat &dst);
	BOOL NewProject();
	BOOL writeAsText(CString pathFile);
	INT modeChange(INT objectMode);
	DOUBLE findROI(Mat &src, Mat &image, Mat &dst);

public:
	BOOL isProject;// 当前是否存在打开的工程
	BOOL isEdit;// 是否正在修改成绩扫描结果
	BOOL isSaved;// 当前工程是否已保存
	INT progMode;// 当前程序的工作状态：0-等待，1-扫描，2-查看
	CString m_project;// 当前编辑的工程名称
	CString pathFile;// 当前工程的保存路径
	CListCtrl m_listCtrl5;
	CListCtrl m_listCtrl6;
	CImageList m_imageList;

protected:
	CCriticalSection global_CriticalSection;// 线程资源临界区

protected:
	BOOL isDelay;
	DOUBLE proportion;// ROI区域宽高比
	INT threadsFlag;// 线程运行数标志
	CWinThread *m_cvShow;
	Mat roi;
	IplImage *tempImg;
	static UINT __cdecl CVShowCamera(LPVOID lparam);

public:
	// 菜单->文件(F) 按钮事件处理程序
	afx_msg void OnNewProject();
	afx_msg void OnNewFile();
	afx_msg void OnOpenProject();
	afx_msg void OnSaveProject();
	afx_msg void OnSaveProjectAs();
	afx_msg void OnImportFiles();
	afx_msg void OnExportAsText();
	afx_msg void OnExportAsExcel();
	afx_msg void OnExportAsImage();
	afx_msg void OnExportAsCertificates();
	afx_msg void OnCloseProject();
	afx_msg void OnExitProcedure();
	// 菜单->编辑(E) 按钮事件处理程序
	afx_msg void OnSetModeScan();
	afx_msg void OnSetModeView();
	afx_msg void OnAlterFile();
	afx_msg void OnDeleteFile();
	afx_msg void OnLastItem();
	afx_msg void OnNextItem();
	afx_msg void OnFindItem();
	afx_msg void OnSetPreference();
	// 菜单->工具(T) 按钮事件处理程序
	afx_msg void OnCheckCurrentFile();
	afx_msg void OnCheckDesignatedFiles();
	afx_msg void OnCheckAllFiles();
	afx_msg void OnProjectSetting();
	afx_msg void OnCheckUpdate();
	// 菜单->帮助(H) 按钮事件处理程序
	afx_msg void OnViewHelp();
	afx_msg void OnReportingProblems();
	afx_msg void OnOfferAdvice();
	afx_msg void OnEvaluateProcedure();
	afx_msg void OnInputtingActivationCode();
	afx_msg void OnTechnicalSupport();
	afx_msg void OnAbout();
};
