// scoreScanner.h :Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"

// CscoreScannerApp:
class CscoreScannerApp : public CWinApp
{
public:
	HANDLE handle;

public:
	CscoreScannerApp();

// ��д
public:
	virtual BOOL InitInstance();
	int ExitInstance();

// ʵ��
	DECLARE_MESSAGE_MAP()
};

extern CscoreScannerApp theApp;