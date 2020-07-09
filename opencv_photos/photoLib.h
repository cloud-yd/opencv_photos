#pragma once
/***************************
*文件名：photoLib.h
*作者：杨栋 yd
*说明：本项目基于opencv3.4.1实现了拍照、图像缩放、图像旋转的功能
*程序入口：int DllMain();
****************************/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <thread>

using namespace std;

typedef enum {
	img_jpg = 1,
	img_png = 2
}imageFormat;

class imageLib
{

public:
	imageLib();
	~imageLib();

	void destroy();

	int HandleOpenCamera(int camera = 0); //打开相机;返回值为-1时，说明打开相机失败
	void HandleDisaplayCamera(); //显示相机图像
	int HandleTakePhoto(string photoName, int photoFormat = img_jpg); //拍照; 参数:保存图片的名称、保存格式：1=》jpg,2=》png
	int HandleOpenImage(string filename); //打开图片；参数：图片名称

	int HandleEnlargedImage(string windowName, int stepping); //放大图像; 参数：窗口名称、放大步进
	/*返回值为-1时:没有打开的图片*/
	int HandleReductionImage(string windowName, int stepping); //缩小图像; 参数：窗口名称、缩小步进	
	
};

imageLib* HandleReturnPhotoObject(); //获取类对象


