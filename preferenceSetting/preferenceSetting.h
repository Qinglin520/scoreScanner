// preferenceSetting.h : preferenceSetting DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CpreferenceSettingApp
// �йش���ʵ�ֵ���Ϣ������� preferenceSetting.cpp
//

class CpreferenceSettingApp : public CWinApp
{
public:
	CpreferenceSettingApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
