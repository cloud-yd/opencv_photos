#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main()
{
	cv::VideoCapture cap;
	cv::Mat frame;
	int i = 1;
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
		switch (Key)
		{
		case 'p':
			cv::namedWindow("photos", CV_WINDOW_AUTOSIZE);
			i++;
			cv::imwrite(filename, frame);
			cv::imshow("photos", frame);
			cv::waitKey(1000);
			cv::destroyWindow("photos");
			break;
		default:
			break;
		}
	}
	cv::destroyAllWindows();
	return 0;
}