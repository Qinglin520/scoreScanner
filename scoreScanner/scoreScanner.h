// scoreScanner.h :应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"

// CscoreScannerApp:
class CscoreScannerApp : public CWinApp
{
public:
	HANDLE handle;

public:
	CscoreScannerApp();

// 重写
public:
	virtual BOOL InitInstance();
	int ExitInstance();

// 实现
	DECLARE_MESSAGE_MAP()
};

extern CscoreScannerApp theApp;