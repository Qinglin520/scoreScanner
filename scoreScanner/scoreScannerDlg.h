// scoreScannerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CscoreScannerDlg �Ի���
class CscoreScannerDlg : public CDialogEx
{
public:
	CscoreScannerDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CscoreScannerDlg();

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
	BOOL isProject;// ��ǰ�Ƿ���ڴ򿪵Ĺ���
	BOOL isEdit;// �Ƿ������޸ĳɼ�ɨ����
	BOOL isSaved;// ��ǰ�����Ƿ��ѱ���
	INT progMode;// ��ǰ����Ĺ���״̬��0-�ȴ���1-ɨ�裬2-�鿴
	CString m_project;// ��ǰ�༭�Ĺ�������
	CString pathFile;// ��ǰ���̵ı���·��
	CListCtrl m_listCtrl5;
	CListCtrl m_listCtrl6;
	CImageList m_imageList;

protected:
	CCriticalSection global_CriticalSection;// �߳���Դ�ٽ���

protected:
	BOOL isDelay;
	DOUBLE proportion;// ROI�����߱�
	INT threadsFlag;// �߳���������־
	CWinThread *m_cvShow;
	Mat roi;
	IplImage *tempImg;
	static UINT __cdecl CVShowCamera(LPVOID lparam);

public:
	// �˵�->�ļ�(F) ��ť�¼��������
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
	// �˵�->�༭(E) ��ť�¼��������
	afx_msg void OnSetModeScan();
	afx_msg void OnSetModeView();
	afx_msg void OnAlterFile();
	afx_msg void OnDeleteFile();
	afx_msg void OnLastItem();
	afx_msg void OnNextItem();
	afx_msg void OnFindItem();
	afx_msg void OnSetPreference();
	// �˵�->����(T) ��ť�¼��������
	afx_msg void OnCheckCurrentFile();
	afx_msg void OnCheckDesignatedFiles();
	afx_msg void OnCheckAllFiles();
	afx_msg void OnProjectSetting();
	afx_msg void OnCheckUpdate();
	// �˵�->����(H) ��ť�¼��������
	afx_msg void OnViewHelp();
	afx_msg void OnReportingProblems();
	afx_msg void OnOfferAdvice();
	afx_msg void OnEvaluateProcedure();
	afx_msg void OnInputtingActivationCode();
	afx_msg void OnTechnicalSupport();
	afx_msg void OnAbout();
};
