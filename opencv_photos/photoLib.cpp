#include "photoLib.h"

cv::VideoCapture cap;
cv::Mat frame, srcImage, dstImage;
volatile bool photoIsReady = false;


photoLib::photoLib()
{
	OpenCamera();
}

photoLib::~photoLib()
{
	photoIsReady = true;
}

int photoLib::OpenCamera(int camera)
{
	cap.open(camera);
	cv::namedWindow("camera", CV_WINDOW_AUTOSIZE);
	if (!cap.isOpened())
	{
		printf("camera open failed \n");
		return -1;
	}
}

void DisplayImage()
{
	while (!photoIsReady) {
		cv::waitKey(40);
		cap >> frame;
		cv::imshow("camera", frame);
	}
}

int photoLib::HandleDisaplayCamera()
{
	photoIsReady = false;
	thread th_DisplayImage(DisplayImage);
	th_DisplayImage.detach();
	return 0;
}

int photoLib::HandleTakePhoto(string photoName, int photoFormat)
{
	photoIsReady = true;
	string fileName;
	if (photoFormat = img_jpg) {
		fileName = cv::format("%s.jpg", photoName);
	}
	else if (photoFormat = img_png) {
		fileName = cv::format("%s.png", photoName);
	}
	cap >> frame;
	cv::destroyWindow("camera");
	cv::namedWindow("photo", CV_WINDOW_AUTOSIZE);
	cv::imwrite(fileName, frame);
	
	cv::imshow("photo", frame);
}

int photoLib::HandleEnlargedImage(string filename, int stepping)
{
	srcImage = cv::imread(filename);
	width = srcImage.cols;
	image_ratio = (float)srcImage.cols / (float)srcImage.rows;
	if (srcImage.empty())
	{
		printf("%d : 图片打开失败 \n", __LINE__);
		return -1;
	}
	width += stepping;
	height = (int)(width / image_ratio);
	
	dsize = cv::Size(width, height);

	cv::resize(srcImage, dstImage, dsize, 0, 0, cv::INTER_CUBIC); //opencv建议放大时使用双三次插值
	cv::imshow("photo", dstImage);

}

int photoLib::HandleReductionImage(string filename, int stepping)
{
	srcImage = cv::imread(filename);
	width = srcImage.cols;
	image_ratio = (float)srcImage.cols / (float)srcImage.rows;
	if (srcImage.empty())
	{
		printf("%d: 图片打开失败 \n", __LINE__);
	}
	
	if (width - stepping > 100)
		width -= stepping;
	else
		width = 100;
	height = (int)(width / image_ratio);
	
	dsize = cv::Size(width, height);
	cv::resize(srcImage, dstImage, dsize, 0, 0, cv::INTER_AREA); //opencv建议缩小是使用像素区域重采样
	cv::imshow("photo", dstImage);
}
