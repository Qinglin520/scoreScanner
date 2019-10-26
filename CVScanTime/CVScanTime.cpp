// CVScanTime.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "CVScanTime.h"
#include "opencv2/opencv.hpp"					// OpenCV 图像处理程序的支持
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>

BOOL ScanTime(const char* name, const char* picture)
{
	// 加载图片
	IplImage *image = cvLoadImage(picture);
	cvShowImage(name, image);
	return TRUE;
}