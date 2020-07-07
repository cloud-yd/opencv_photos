#pragma once
/***************************
*文件名：photoLib.h
*作者：杨栋 yd
*说明：本项目基于opencv3.4.1实现了拍照、图像缩放、图像旋转的功能
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

class photoLib
{
public:
	cv::Size dsize;
	float image_ratio;
	int width, height, init_data;

public:
	photoLib();
	~photoLib();

	int HandleDisaplayCamera(); //显示相机图像
	int HandleTakePhoto(string photoName, int photoFormat = img_jpg); //拍照:参数:保存图片的名称、保存格式：1=》jpg,2=》png
	int HandleEnlargedImage(string filename, int stepping); //放大图像：参数：图片名称、放大步进
	int HandleReductionImage(string filename, int stepping); //缩小图像：参数：图片名称、缩小步进
private:
	
	int OpenCamera(int camera = 0); //打开相机;返回值为-1时，说明打开相机失败
	
};

void DisplayImage();


