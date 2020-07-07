#pragma once
/***************************
*�ļ�����photoLib.h
*���ߣ�� yd
*˵��������Ŀ����opencv3.4.1ʵ�������ա�ͼ�����š�ͼ����ת�Ĺ���
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

	int HandleDisaplayCamera(); //��ʾ���ͼ��
	int HandleTakePhoto(string photoName, int photoFormat = img_jpg); //����:����:����ͼƬ�����ơ������ʽ��1=��jpg,2=��png
	int HandleEnlargedImage(string filename, int stepping); //�Ŵ�ͼ�񣺲�����ͼƬ���ơ��Ŵ󲽽�
	int HandleReductionImage(string filename, int stepping); //��Сͼ�񣺲�����ͼƬ���ơ���С����
private:
	
	int OpenCamera(int camera = 0); //�����;����ֵΪ-1ʱ��˵�������ʧ��
	
};

void DisplayImage();


