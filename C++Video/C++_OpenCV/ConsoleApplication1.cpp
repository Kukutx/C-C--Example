#include <opencv2/opencv.hpp>
using namespace cv;
int main()
{
	//从摄像头读人视频
	VideoCapture capture(0);
	//循环显示每一帧
	while (1)
	{
		Mat frame;//存储每一帧图像
		capture >> frame;//读取当前帧
		imshow("读取视频", frame);
		waitKey(30);//延时30毫秒
	}
}