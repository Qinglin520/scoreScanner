// md5Calculater.cpp : 定义 DLL 应用程序的导出函数。
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
