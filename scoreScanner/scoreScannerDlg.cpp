// scoreScannerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "scoreScanner.h"
#include "scoreScannerDlg.h"
#include "ProjectSettingDlg.h"
#include "SetPreferenceDlg.h"
#include "afxdialogex.h"

#define ELPP_NO_DEFAULT_LOG_FILE
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP
TIMED_SCOPE(appTimer, "Score Scanner");

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CscoreScannerDlg 对话框
CscoreScannerDlg::CscoreScannerDlg(CWnd* pParent)
	: CDialogEx(IDD_SCORESCANNER_DIALOG, pParent), isProject(FALSE), isEdit(FALSE),
	isSaved(TRUE), progMode(0), threadsFlag(0), isDelay(FALSE), pathFile(L"")
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

CscoreScannerDlg::~CscoreScannerDlg()
{
}

// 提供成员变量和控件的绑定
void CscoreScannerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST5, m_listCtrl5);
	DDX_Control(pDX, IDC_LIST6, m_listCtrl6);
	DDX_Text(pDX, IDC_PROJRCT, m_project);
	DDV_MaxChars(pDX, m_project, 100);
}

// 消息映射
BEGIN_MESSAGE_MAP(CscoreScannerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDOK, &CscoreScannerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CscoreScannerDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CscoreScannerDlg::OnBnClickedButton1)

	ON_NOTIFY(NM_CLICK, IDC_LIST5, &CscoreScannerDlg::OnNMClickList5)

	ON_COMMAND(ID_32789, &CscoreScannerDlg::OnNewProject)
	ON_COMMAND(ID_32790, &CscoreScannerDlg::OnNewFile)
	ON_COMMAND(ID_32799, &CscoreScannerDlg::OnOpenProject)
	ON_COMMAND(ID_32772, &CscoreScannerDlg::OnSaveProject)
	ON_COMMAND(ID_32773, &CscoreScannerDlg::OnSaveProjectAs)
	ON_COMMAND(ID_32774, &CscoreScannerDlg::OnImportFiles)
	ON_COMMAND(ID_32801, &CscoreScannerDlg::OnExportAsText)
	ON_COMMAND(ID_32802, &CscoreScannerDlg::OnExportAsExcel)
	ON_COMMAND(ID_32803, &CscoreScannerDlg::OnExportAsImage)
	ON_COMMAND(ID_32804, &CscoreScannerDlg::OnExportAsCertificates)
	ON_COMMAND(ID_32776, &CscoreScannerDlg::OnCloseProject)
	ON_COMMAND(ID_32800, &CscoreScannerDlg::OnExitProcedure)

	ON_COMMAND(ID_32791, &CscoreScannerDlg::OnSetModeScan)
	ON_COMMAND(ID_32805, &CscoreScannerDlg::OnSetModeView)
	ON_COMMAND(ID_32806, &CscoreScannerDlg::OnAlterFile)
	ON_COMMAND(ID_32778, &CscoreScannerDlg::OnDeleteFile)
	ON_COMMAND(ID_32807, &CscoreScannerDlg::OnLastItem)
	ON_COMMAND(ID_32808, &CscoreScannerDlg::OnNextItem)
	ON_COMMAND(ID_32779, &CscoreScannerDlg::OnFindItem)
	ON_COMMAND(ID_32780, &CscoreScannerDlg::OnSetPreference)

	ON_COMMAND(ID_32793, &CscoreScannerDlg::OnCheckCurrentFile)
	ON_COMMAND(ID_32794, &CscoreScannerDlg::OnCheckDesignatedFiles)
	ON_COMMAND(ID_32795, &CscoreScannerDlg::OnCheckAllFiles)
	ON_COMMAND(ID_32782, &CscoreScannerDlg::OnProjectSetting)
	ON_COMMAND(ID_32783, &CscoreScannerDlg::OnCheckUpdate)

	ON_COMMAND(ID_32784, &CscoreScannerDlg::OnViewHelp)
	ON_COMMAND(ID_32796, &CscoreScannerDlg::OnReportingProblems)
	ON_COMMAND(ID_32797, &CscoreScannerDlg::OnOfferAdvice)
	ON_COMMAND(ID_32798, &CscoreScannerDlg::OnEvaluateProcedure)
	ON_COMMAND(ID_32786, &CscoreScannerDlg::OnInputtingActivationCode)
	ON_COMMAND(ID_32787, &CscoreScannerDlg::OnTechnicalSupport)
	ON_COMMAND(ID_32788, &CscoreScannerDlg::OnAbout)
END_MESSAGE_MAP()

// 初始化图片控件
void CscoreScannerDlg::UpdateOpenCVWindow(const char* name, const char* picture)
{
	// 启动并重绘OpenCV窗口
	cvNamedWindow(name, WINDOW_AUTOSIZE);
	HWND hWnd = (HWND)cvGetWindowHandle(name);
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_STATIC_CV)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

	// 加载欢迎图片
	IplImage *image = cvLoadImage(picture);
	cvShowImage(name, image);
}

// 初始化功能选择列表
void CscoreScannerDlg::UpdateOutlookBar()
{
	m_listCtrl5.SetBkColor(RGB(250, 250, 250));

	m_imageList.Create(32, 32, ILC_COLOR16 | ILC_MASK, 5, 5);
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_ICON2));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_ICON3));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_ICON4));
	m_imageList.Add(AfxGetApp()->LoadIcon(IDI_ICON5));

	m_listCtrl5.SetImageList(&m_imageList, LVSIL_NORMAL);
	CRect rc;
	m_listCtrl5.GetClientRect(rc);
	m_listCtrl5.SetIconSpacing(rc.Width() / 5, 64);
	m_listCtrl5.InsertColumn(0, _T("OutlookBar"));
	m_listCtrl5.InsertItem(0, _T("扫描"), 0);
	m_listCtrl5.InsertItem(1, _T("查看"), 1);
	m_listCtrl5.InsertItem(2, _T("导入"), 2);
	m_listCtrl5.InsertItem(3, _T("导出"), 3);
	m_listCtrl5.InsertItem(4, _T("退出"), 4);
}

// 初始化得分显示列表
void CscoreScannerDlg::UpdateScoreList()
{
	m_listCtrl6.SetBkColor(RGB(255, 255, 255));
	m_listCtrl6.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_COLUMNSNAPPOINTS);
	m_listCtrl6.InsertColumn(0, _T(""), LVCFMT_RIGHT, 0);
	m_listCtrl6.InsertColumn(1, _T("项目"), LVCFMT_CENTER, 50);
	m_listCtrl6.InsertColumn(2, _T("班级"), LVCFMT_CENTER, 100);
	m_listCtrl6.InsertColumn(3, _T("创意特色(10)"), LVCFMT_CENTER, 105);
	m_listCtrl6.InsertColumn(4, _T("色彩搭配(10)"), LVCFMT_CENTER, 105);
	m_listCtrl6.InsertColumn(5, _T("寓意内涵(15)"), LVCFMT_CENTER, 105);
	m_listCtrl6.InsertColumn(6, _T("现场展示(15)"), LVCFMT_CENTER, 105);
	m_listCtrl6.InsertColumn(7, _T("总成绩"), LVCFMT_CENTER, 80);
	m_listCtrl6.InsertColumn(8, _T("校验码"), LVCFMT_CENTER, 300);
	m_listCtrl6.InsertColumn(9, _T("校验结果"), LVCFMT_CENTER, 110);
}

void CscoreScannerDlg::UpdateComboBoxes()
{
	((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("--请选择--"));
	((CComboBox*)GetDlgItem(IDC_COMBO2))->AddString(_T("--请选择--"));

	((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);

	GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO2)->EnableWindow(FALSE);
}

void CscoreScannerDlg::UpdateEditBoxes()
{
	((CEdit*)GetDlgItem(IDC_EDIT1))->SetReadOnly(TRUE);
	((CEdit*)GetDlgItem(IDC_EDIT2))->SetReadOnly(TRUE);
	((CEdit*)GetDlgItem(IDC_EDIT3))->SetReadOnly(TRUE);
	((CEdit*)GetDlgItem(IDC_EDIT4))->SetReadOnly(TRUE);

	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
}

void CscoreScannerDlg::UpdateButtons()
{
	GetDlgItem(IDC_BUTTON1)->SetWindowText(_T("修改"));
	GetDlgItem(IDC_BUTTON2)->SetWindowText(_T("取消"));
	GetDlgItem(IDC_BUTTON3)->SetWindowText(_T("删除"));
	GetDlgItem(IDC_BUTTON4)->SetWindowText(_T("上一项"));
	GetDlgItem(IDC_BUTTON5)->SetWindowText(_T("新建"));
	GetDlgItem(IDC_BUTTON6)->SetWindowText(_T("下一项"));

	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(FALSE);
}

// CscoreScannerDlg 消息处理程序
BOOL CscoreScannerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 初始化控件
	UpdateOpenCVWindow("showWindow", "res\\1.ress");
	UpdateOutlookBar();
	UpdateScoreList();
	UpdateComboBoxes();
	UpdateEditBoxes();
	UpdateButtons();

	// 初始化成员变量
	String projectName = "(无)";
	m_project = projectName.c_str();
	UpdateData(FALSE);

	el::Loggers::addFlag(el::LoggingFlag::StrictLogFileSizeCheck);
	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::MaxLogFileSize, "2097152");

	el::Configurations conf("settings\\logsetting.conf");
	el::Loggers::reconfigureAllLoggers(conf);

	LOG(INFO) << "The window ScoreScanner has been started";

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码来绘制该图标
void CscoreScannerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示
HCURSOR CscoreScannerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CscoreScannerDlg::deleteArea(IplImage *src)
{
	double temparea;
	CvMemStorage *pmemstorage = cvCreateMemStorage();
	CvSeq *pcontourseq = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq), sizeof(CvPoint), pmemstorage);
	double clearblock;
	clearblock = 100;

	IplImage *g_pdeletesmallareamask = NULL;
	g_pdeletesmallareamask = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
	cvCopy(src, g_pdeletesmallareamask);

	cvFindContours(g_pdeletesmallareamask, pmemstorage, &pcontourseq, sizeof(CvContour), CV_RETR_EXTERNAL);

	IplImage *g_pdeletesmallareacontour = NULL;
	g_pdeletesmallareacontour = cvCreateImage(cvGetSize(src), 8, 1);
	cvSetZero(g_pdeletesmallareacontour);

	for (; pcontourseq != 0; pcontourseq = pcontourseq->h_next) {
		temparea = fabs(cvContourArea(pcontourseq));
		if (temparea>clearblock) {
			cvDrawContours(g_pdeletesmallareacontour, pcontourseq, cvScalar(255, 255, 255), cvScalar(255, 255, 255), 0, CV_FILLED);
		}
	}

	cvCopy(g_pdeletesmallareacontour, src);
	cvReleaseMemStorage(&pmemstorage);
	cvReleaseImage(&g_pdeletesmallareamask);
	cvReleaseImage(&g_pdeletesmallareacontour);
}

DOUBLE CscoreScannerDlg::findROI(Mat &src, Mat &image, Mat &dst)
{
	int *horizontal = new int[src.cols];// 横向投影
	int *vertical = new int[src.rows];// 纵向投影

	for (int col = 0; col < src.cols; col++) {
		horizontal[col] = 0;
	}
	for (int row = 0; row < src.rows; row++) {
		vertical[row] = 0;
	}

	for (int row = 0; row < src.rows; row++) {
		for (int col = 0; col < src.cols; col++) {
			if (src.at<uchar>(row, col) != 0) {
				horizontal[col]++;
				vertical[row]++;
			}
		}
	}

	int minX = 0, minY = 0, maxX = src.cols, maxY = src.rows, width, height;
	bool isminx = false, isminy = false, ismaxx = false, ismaxy = false;

	for (int col = 0; col < src.cols; col++) {
		if (isminx == false && horizontal[col] > 100) { isminx = true; minX = col; }
		if (horizontal[col] > 100) { maxX = col; }
	}
	for (int row = 0; row < src.rows; row++) {
		if (isminy == false && vertical[row] > 100) { isminy = true; minY = row; }
		if (vertical[row] > 100) { maxY = row; }
	}

	width = maxX - minX;
	height = maxY - minY;
	DOUBLE proportion = (DOUBLE)width / (DOUBLE)height;
	dst = image(Rect(minX, minY, width, height));

	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 0.5, 0.5, 1, 1, 8);

	rectangle(image, Rect(minX, minY, width, height), Scalar(0x00, 0xFF, 0x00), 2);
	cvPutText(&IplImage(image), "Detected_area", Point(minX + 4, maxY - 4), &font, CV_RGB(0xFF, 0x00, 0x00));

	rectangle(image, Rect(55, 155, 530, 170), Scalar(0xFF, 0x00, 0x00), 2);
	cvPutText(&IplImage(image), "Object_area", Point(55, 150), &font, CV_RGB(0xFF, 0x00, 0x00));

	delete[] horizontal;
	delete[] vertical;

	if (minX >= 55 && minX <= 75 && maxX <= 585 && minY >= 155 && minY <= 175 && maxY >= 305 && maxY <= 325) {
		return proportion;
	}
	else { return 0; }
}

void CscoreScannerDlg::AdaptiveThereshold(Mat &src, Mat &dst)
{
	cvtColor(src, dst, CV_BGR2GRAY);

	int x1, y1, x2, y2;
	int count = 0;
	long long sum = 0;
	int S = src.rows >> 3;  //划分区域的大小S*S  
	int T = 15;         //If the value of the current pixel is t percent less than this average then it is set to black, otherwise it is set to white.
	int W = dst.cols;
	int H = dst.rows;
	long long **Argv;

	Argv = new long long*[dst.rows];

	for (int ii = 0; ii < dst.rows; ii++) {
		Argv[ii] = new long long[dst.cols];
	}

	for (int i = 0; i < W; i++) {
		sum = 0;
		for (int j = 0; j < H; j++) {
			sum += dst.at<uchar>(j, i);
			Argv[j][i] = i == 0 ? sum : Argv[j][i - 1] + sum;
		}
	}

	for (int i = 0; i < W; i++) {
		for (int j = 0; j<H; j++) {
			x1 = i - S / 2;
			x2 = i + S / 2;
			y1 = j - S / 2;
			y2 = j + S / 2;
			if (x1 < 0) { x1 = 0; }
			if (x2 >= W) { x2 = W - 1; }
			if (y1 < 0) { y1 = 0; }
			if (y2 >= H) { y2 = H - 1; }
			count = (x2 - x1)*(y2 - y1);
			sum = Argv[y2][x2] - Argv[y1][x2] - Argv[y2][x1] + Argv[y1][x1];

			if ((long long)(dst.at<uchar>(j, i)*count) < (long long)sum*(100 - T) / 100) {
				dst.at<uchar>(j, i) = 255;
			}
			else { dst.at<uchar>(j, i) = 0; }
		}
	}

	for (int i = 0; i < dst.rows; ++i) {
		delete[] Argv[i];
	}
	delete[] Argv;
}

UINT __cdecl CscoreScannerDlg::CVShowCamera(LPVOID lparam)
{
	CscoreScannerDlg *threadol = (CscoreScannerDlg*)lparam;
	threadol->threadsFlag++;// 运行时线程数+1

	int delayTime = 0, photoNum = 0;
	Mat image, local, sobelx, sobely, gradient, blurred, thresh, kernel, closed;

	CvCapture *cap = cvCreateCameraCapture(1);//初始化相机 来捕获视频的每一帧
	if (!cap)
	{
		exit(-1);
	}
	threadol->tempImg = cvQueryFrame(cap);

	while (cvWaitKey(50) && threadol->isDelay == TRUE)//设置每50ms抓取一帧
	{
		threadol->tempImg = cvQueryFrame(cap);//获取当前帧的下一个帧,并且将获取到的帧加载到内存中
		image = cvarrToMat(threadol->tempImg);

		// 转为灰度图
		cvtColor(image, local, CV_BGR2GRAY);

		// 求得x和y方向的一阶微分 
		Sobel(local, sobelx, CV_32F, 1, 0, -1);
		Sobel(local, sobely, CV_32F, 0, 1, -1);

		subtract(sobelx, sobely, gradient);
		convertScaleAbs(gradient, gradient);

		blur(gradient, blurred, Size(9, 9));
		threshold(blurred, thresh, 90, 255, THRESH_BINARY);

		kernel = getStructuringElement(MORPH_RECT, Size(25, 25));
		morphologyEx(thresh, closed, MORPH_CLOSE, kernel);

		threadol->deleteArea(&IplImage(closed));

		threadol->global_CriticalSection.Lock();
		threadol->proportion = threadol->findROI(closed, image, threadol->roi);
		threadol->global_CriticalSection.Unlock();

		cvShowImage("showWindow", &IplImage(image));

		if (threadol->proportion >= 3.3 && threadol->proportion <= 3.6) {
			delayTime++;
			if (delayTime >= 20) {
				delayTime = 0;
				Beep(2500, 500);
				resize(threadol->roi, threadol->roi, Size(510, 150));
				threadol->AdaptiveThereshold(threadol->roi, threadol->roi);
				cvShowImage("ROI", &IplImage(threadol->roi));
				imwrite("temp\\" + std::to_string(photoNum++) + ".jpg", threadol->roi);
				cvWaitKey(1500);
				cvDestroyWindow("ROI");
			}
		}
		else { delayTime = 0; }
	}

	cvReleaseCapture(&cap);

	threadol->threadsFlag--;// 运行时线程数-1

	LOG(INFO) << "Thread CVShowCamera has withdrawn";
	return 0;
}

void CscoreScannerDlg::OnBnClickedOk() {}// 重写消息处理程序，禁止回车键关闭窗口

void CscoreScannerDlg::OnBnClickedCancel()
{
	if (MessageBox(TEXT("真的要退出吗？"), TEXT("提示"), MB_YESNO | MB_ICONQUESTION | MB_SYSTEMMODAL) == 6)
	{
		if (threadsFlag != 0)// 是否存在未退出的线程
		{
			isDelay = FALSE;
			WaitForSingleObject(m_cvShow->m_hThread, INFINITE);
		}
		CDialogEx::OnCancel();
	}
}

// 按钮辅助处理程序
BOOL CscoreScannerDlg::NewProject()
{
	if (isProject && !isSaved)
	{
		MessageBox((_T("是否将更改保存到 ") + m_project + _T(" 中？\r\n\r\n如果单击“否”，将不会保存本次对此工程的任何修改。")), _T("比赛评分扫描器"), MB_YESNOCANCEL | MB_DEFBUTTON1 | MB_ICONEXCLAMATION);
	}

	CProjectSettingDlg projectSettingDlg(this);
	INT_PTR nResponse = projectSettingDlg.DoModal();

	if (IDOK == nResponse)
	{
		isProject = TRUE;
		isSaved = FALSE;

		m_project = projectSettingDlg.projectName;
		UpdateData(FALSE);

		GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO2)->EnableWindow(TRUE);

		GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT3)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT4)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);

		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON6)->EnableWindow(TRUE);

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CscoreScannerDlg::writeAsText(CString pathFile)// 文件保存逻辑
{
	CString strEdit1, strEdit2, strEdit3, strEdit4;
	GetDlgItemText(IDC_EDIT1, strEdit1);// 获取指定ID的编辑框内容
	GetDlgItemText(IDC_EDIT2, strEdit2);
	GetDlgItemText(IDC_EDIT3, strEdit3);
	GetDlgItemText(IDC_EDIT4, strEdit4);

	CStdioFile file;
	if (file.Open(pathFile, CStdioFile::modeCreate | CStdioFile::modeNoTruncate | CStdioFile::modeWrite))// 创建/打开文件
	{
		file.WriteString(strEdit1);// 写入内容
		file.WriteString(_T("\r\n"));// 换行
		file.WriteString(strEdit2);
		file.WriteString(_T("\r\n"));
		file.WriteString(strEdit3);
		file.WriteString(_T("\r\n"));
		file.WriteString(strEdit4);

		file.Close();// 关闭输出文件
	}

	this->pathFile = pathFile;
	EnableWindow(TRUE);

	return TRUE;
}

INT CscoreScannerDlg::modeChange(INT objectMode)
{
	switch (objectMode) {
		case 0:	// 扫描
			if (progMode == 1) { break; }
			if (isProject == FALSE) { if (NewProject()) { pathFile = L""; } else { break; } }

			tempImg = cvLoadImage("res\\2.ress");
			CvFont font;
			cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 1, 1, 0, 2, 8);
			cvPutText(tempImg, "Starting camera...", Point(150, 244), &font, CV_RGB(0, 255, 255));
			cvShowImage("showWindow", tempImg);

			progMode = 1;
			isDelay = TRUE;
			m_cvShow = AfxBeginThread(CVShowCamera, (LPVOID)this, THREAD_PRIORITY_NORMAL, 0, 0);
			break;

		case 1:	// 查看
			if (progMode == 2) { break; }
			progMode = 2;

			if (threadsFlag != 0)// 是否存在未退出的线程
			{
				isDelay = FALSE;
				WaitForSingleObject(m_cvShow->m_hThread, INFINITE);
			}

			cvShowImage("showWindow", cvLoadImage("res\\1.ress"));

			break;

		case 2:	// 导入
				// TODO:先关闭当前工程
			break;

		case 3:	// 导出
			break;

		case 4:	// 退出
			OnBnClickedCancel();
			break;
		default:
			break;
	}

	return progMode;
}

// 菜单->文件(F) 按钮事件处理程序
void CscoreScannerDlg::OnNewProject()// 新建工程
{
	if (NewProject()) { pathFile = L""; }
}

void CscoreScannerDlg::OnNewFile()// 新建项目
{
}

void CscoreScannerDlg::OnOpenProject()// 打开工程
{
}

void CscoreScannerDlg::OnSaveProject()// 保存工程
{
	if (pathFile != L"")
	{
		writeAsText(pathFile);
	}
	else
	{
		OnSaveProjectAs();
	}
}

void CscoreScannerDlg::OnSaveProjectAs()// 工程另存为
{
	CFileDialog dlg(FALSE, _T("txt"), (m_project + _T(".txt")));// FALSE表示为“另存为”对话框，否则为“打开”对话框

	if (dlg.DoModal() == IDOK)
	{
		CString strFile = dlg.GetPathName();// 获取完整路径
		writeAsText(strFile);

		isSaved = TRUE;
	}
}

void CscoreScannerDlg::OnImportFiles()// 导入项目
{
}

void CscoreScannerDlg::OnExportAsText()// 导出为文本文档
{
}

void CscoreScannerDlg::OnExportAsExcel()// 导出为EXCEL表格
{
}

void CscoreScannerDlg::OnExportAsImage()// 导出为图片
{
}

void CscoreScannerDlg::OnExportAsCertificates()// 导出为奖状模板
{
}

void CscoreScannerDlg::OnCloseProject()// 关闭工程
{
}

void CscoreScannerDlg::OnExitProcedure()// 退出程序
{
	OnBnClickedCancel();
}

// 菜单->编辑(E) 按钮事件处理程序
void CscoreScannerDlg::OnSetModeScan()// 更改为扫描模式
{
}

void CscoreScannerDlg::OnSetModeView()// 更改为查看模式
{
}

void CscoreScannerDlg::OnAlterFile()// 修改当前项目
{
	isEdit = TRUE;
	GetDlgItem(IDC_BUTTON1)->SetWindowText(_T("确定"));

	((CEdit*)GetDlgItem(IDC_EDIT1))->SetReadOnly(FALSE);
	((CEdit*)GetDlgItem(IDC_EDIT2))->SetReadOnly(FALSE);
	((CEdit*)GetDlgItem(IDC_EDIT3))->SetReadOnly(FALSE);
	((CEdit*)GetDlgItem(IDC_EDIT4))->SetReadOnly(FALSE);
}

void CscoreScannerDlg::OnDeleteFile()// 删除当前项目
{
}

void CscoreScannerDlg::OnLastItem()// 上一项
{
}

void CscoreScannerDlg::OnNextItem()// 下一项
{
}

void CscoreScannerDlg::OnFindItem()// 查找项目
{
}

void CscoreScannerDlg::OnSetPreference()// 编辑首选项
{
	typedef void(*ShowPreferenceDialog)(void);
	HINSTANCE hDLL;
	ShowPreferenceDialog ShowPreference;
	hDLL = LoadLibrary(L"toolbox\\bin\\preferenceSetting.dll");
	ShowPreference = (ShowPreferenceDialog)GetProcAddress(hDLL, "ShowPreferenceDialog");
	ShowPreference();
	FreeLibrary(hDLL);
}

// 菜单->工具(T) 按钮事件处理程序
void CscoreScannerDlg::OnCheckCurrentFile()// 校验当前项目
{
	//typedef char*(*MD5)(char* str);
	//HINSTANCE hDLL;
	//MD5 digestString;
	//hDLL = LoadLibrary(L"..\\toolbox\\bin\\md5Calculater.dll");
	//digestString = (MD5)GetProcAddress(hDLL, "digestString");

	//char* project = new char;
	//std::stringstream cache;
	//cache << m_project;
	//cache >> project;

	//char* solution = new char;
	//CString mdSolution;
	//solution = digestString(project);
	//mdSolution.Format(_T("%s"), solution);

	//AllocConsole();
	//freopen("CONOUT$", "w", stdout);
	////project = "deuif";
	//_cprintf("md5:%s\t%s\n", m_project, project);

	//GetDlgItem(IDC_EDIT7)->SetWindowText(mdSolution);

	//FreeLibrary(hDLL);
	//delete project;
	//delete solution;
}

void CscoreScannerDlg::OnCheckDesignatedFiles()// 校验指定项目
{
}

void CscoreScannerDlg::OnCheckAllFiles()// 校验全部项目
{
}

void CscoreScannerDlg::OnProjectSetting()// 工程设置
{
	CProjectSettingDlg projectSettingDlg(this, m_project);
	INT_PTR nResponse = projectSettingDlg.DoModal();

	if (IDOK == nResponse)
	{
		m_project = projectSettingDlg.projectName;
		UpdateData(FALSE);
	}
}

void CscoreScannerDlg::OnCheckUpdate()// 检查更新
{
}

// 菜单->帮助(H) 按钮事件处理程序
void CscoreScannerDlg::OnViewHelp()// 查看帮助
{
}

void CscoreScannerDlg::OnReportingProblems()// 报告问题
{
}

void CscoreScannerDlg::OnOfferAdvice()// 提供建议
{
}

void CscoreScannerDlg::OnEvaluateProcedure()// 对此产品评分
{
}

void CscoreScannerDlg::OnInputtingActivationCode()// 授权本产品
{
}

void CscoreScannerDlg::OnTechnicalSupport()// 技术支持
{
}

void CscoreScannerDlg::OnAbout()// 关于
{
}

// 按钮单击事件处理程序
void CscoreScannerDlg::OnBnClickedButton1()
{
	if (isEdit == TRUE)
	{
		isEdit = FALSE;
		GetDlgItem(IDC_BUTTON1)->SetWindowText(_T("修改"));

		((CEdit*)GetDlgItem(IDC_EDIT1))->SetReadOnly(TRUE);
		((CEdit*)GetDlgItem(IDC_EDIT2))->SetReadOnly(TRUE);
		((CEdit*)GetDlgItem(IDC_EDIT3))->SetReadOnly(TRUE);
		((CEdit*)GetDlgItem(IDC_EDIT4))->SetReadOnly(TRUE);
	}
	else if (isEdit == FALSE)
	{
		isEdit = TRUE;
		GetDlgItem(IDC_BUTTON1)->SetWindowText(_T("确定"));

		((CEdit*)GetDlgItem(IDC_EDIT1))->SetReadOnly(FALSE);
		((CEdit*)GetDlgItem(IDC_EDIT2))->SetReadOnly(FALSE);
		((CEdit*)GetDlgItem(IDC_EDIT3))->SetReadOnly(FALSE);
		((CEdit*)GetDlgItem(IDC_EDIT4))->SetReadOnly(FALSE);
	}
	else
	{
		MessageBox(L"出现未知错误");
	}
}

void CscoreScannerDlg::OnNMClickList5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	modeChange(pNMItemActivate->iItem);
	*pResult = 0;
}