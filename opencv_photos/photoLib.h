#pragma once
/***************************
*�ļ�����photoLib.h
*���ߣ�� yd
*˵��������Ŀ����opencv3.4.1ʵ�������ա�ͼ�����š�ͼ����ת�Ĺ���
*������ڣ�int DllMain();
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

	int HandleOpenCamera(int camera = 0); //�����;����ֵΪ-1ʱ��˵�������ʧ��
	void HandleDisaplayCamera(); //��ʾ���ͼ��
	int HandleTakePhoto(string photoName, int photoFormat = img_jpg); //����; ����:����ͼƬ�����ơ������ʽ��1=��jpg,2=��png
	int HandleOpenImage(string filename); //��ͼƬ��������ͼƬ����

	int HandleEnlargedImage(string windowName, int stepping); //�Ŵ�ͼ��; �������������ơ��Ŵ󲽽�
	/*����ֵΪ-1ʱ:û�д򿪵�ͼƬ*/
	int HandleReductionImage(string windowName, int stepping); //��Сͼ��; �������������ơ���С����	
	
};

imageLib* HandleReturnPhotoObject(); //��ȡ�����


