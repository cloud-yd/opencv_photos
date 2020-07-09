#include "photoLib.h"

imageLib* p_imageLib = NULL;
cv::VideoCapture cap;
cv::Mat frame, srcImage, dstImage;
cv::Size dsize;
float image_ratio;
int width, height;

imageLib::imageLib()
{

}

imageLib::~imageLib()
{
	destroy();
}

void imageLib::destroy()
{
	cv::destroyAllWindows();
}

int imageLib::HandleOpenCamera(int camera)
{
	cap.open(camera);
	cv::namedWindow("camera", CV_WINDOW_AUTOSIZE);
	if (!cap.isOpened())
	{
		//printf("camera open failed \n");
		return -1;
	}
}

void imageLib::HandleDisaplayCamera()
{
	cap >> frame;
	if (!frame.empty())
		cv::imshow("camera", frame);
	cv::waitKey(40);
}

int imageLib::HandleTakePhoto(string photoName, int photoFormat)
{
	string fileName;
	if (photoFormat == img_jpg) {
		fileName = cv::format("%s.jpg", photoName);
	}
	else if (photoFormat == img_png) {
		fileName = cv::format("%s.png", photoName);
	}
	cap >> frame;
	cv::destroyWindow("camera");
	cv::namedWindow(fileName, CV_WINDOW_AUTOSIZE);
	cv::imwrite(fileName, frame);
	cv::imshow(fileName, frame);

	srcImage = frame;
	return 0;
}

int imageLib::HandleOpenImage(string filename)
{
	cv::Mat image = cv::imread(filename);
	cv::namedWindow(filename, CV_WINDOW_AUTOSIZE);
	cv::imshow(filename, image);
	srcImage = image;
	return 0;
}

int imageLib::HandleEnlargedImage(string windowName, int stepping)
{
	if (srcImage.empty())
		return -1;

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
	cv::imshow(windowName, dstImage);
	srcImage = dstImage;
	
	return 0;

}

int imageLib::HandleReductionImage(string windowName, int stepping)
{
	if (srcImage.empty())
		return -1;

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
	cv::resize(srcImage, dstImage, dsize, 0, 0, cv::INTER_AREA); //opencv建议缩小时使用像素区域重采样
	cv::imshow(windowName, dstImage);
	srcImage = dstImage;

	return 0;
}

imageLib* HandleReturnPhotoObject()
{
	p_imageLib = new imageLib();	

	return p_imageLib;
}

#if 0

int main()
{
	p_imageLib = HandleReturnPhotoObject();
	while (1)
	{
		//p_imageLib->HandleDisaplayCamera();
		//cv::waitKey();

		//p_imageLib->HandleTakePhoto("test");
		//cv::waitKey();

		p_imageLib->HandleOpenImage("test.jpg");
		cv::waitKey();

		p_imageLib->HandleEnlargedImage("test.jpg", 200);
		cv::waitKey();

		p_imageLib->HandleReductionImage("test.jpg", 400);
		cv::waitKey();


		break;
	}

	p_imageLib->~imageLib();
	delete p_imageLib;

	return 0;
}
#endif