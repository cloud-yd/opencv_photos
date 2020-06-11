#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
	cv::VideoCapture cap;
	cv::Mat frame, srcImage, dstImage;
	cv::Size dsize;
	float image_ratio;
	static int width, height, init_data;
	int i = 1;
	static int photoIsReady = 0;
	cap.open(0);
	cv::namedWindow("camera", CV_WINDOW_AUTOSIZE);
	
	while (1)
	{
		if (!cap.isOpened())
		{
			printf("camera open failed \n");
		}
		string filename = cv::format("photo%d.jpg", i);
		char Key = (char)cv::waitKey(30);
		cap >> frame;
		cv::imshow("camera", frame);
		if (!init_data)
		{
			width = frame.cols;
			image_ratio = (float)frame.cols / (float)frame.rows;
			printf("image_ratio = %f \n", image_ratio);
			init_data = 1;
		}
		
		switch (Key)
		{
		case 'p':
			cv::namedWindow("photos", CV_WINDOW_AUTOSIZE);
			i++;
			cv::imwrite(filename, frame);
			cv::imshow("photos", frame);
			
			photoIsReady = 1;
			cv::waitKey(1000);
			
			break;

		case 'c':
			cv::destroyWindow("photos");
			break;

		case 'u':
			if (photoIsReady)
			{
				srcImage = cv::imread("photo1.jpg");
				if (srcImage.empty())
				{
					printf("%d : 图片打开失败 \n", __LINE__);
					return -1;
				}
				width += 5;
				height = (int)(width / image_ratio);
				printf("Enlagre==> W = %d, H = %d \n", width, height);
				dsize = cv::Size(width, height);
				cv::namedWindow("Enlagre", cv::WINDOW_AUTOSIZE);
				cv::resize(srcImage, dstImage, dsize, 0, 0, cv::INTER_LINEAR);
				cv::imshow("Enlagre", dstImage);
			}
			break;

		case 'd':
			if (photoIsReady)
			{
				srcImage = cv::imread("photo1.jpg");
				if (srcImage.empty())
				{
					printf("%d: 图片打开失败 \n",__LINE__);
				}
				if(width > 50)
					width -= 5;
				height = (int)(width / image_ratio);
				printf("Shrink==> W = %d, H = %d \n", width, height);
				//cv::namedWindow("Shrink", cv::WINDOW_AUTOSIZE);
				dsize = cv::Size(width, height);
				cv::resize(srcImage, dstImage, dsize, 0, 0, cv::INTER_LINEAR);
				cv::imshow("Enlagre", dstImage);
			}
			break;

		default:
			break;
		}
	}
	cv::destroyAllWindows();
	return 0;
}