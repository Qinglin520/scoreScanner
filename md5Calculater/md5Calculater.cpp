// md5Calculater.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "md5.h"
#include "md5Calculater.h"

char* digestFile(char* str)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());

	MD5 md5;
	return md5.digestFile(str);
}

char* digestString(char* str)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());

	MD5 md5;
	return md5.digestString(str);
}
