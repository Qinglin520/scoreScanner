// CVScanTime.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "CVScanTime.h"
#include "opencv2/opencv.hpp"					// OpenCV ͼ��������֧��
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>

BOOL ScanTime(const char* name, const char* picture)
{
	// ����ͼƬ
	IplImage *image = cvLoadImage(picture);
	cvShowImage(name, image);
	return TRUE;
}