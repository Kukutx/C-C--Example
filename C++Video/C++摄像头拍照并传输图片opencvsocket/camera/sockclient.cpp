#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <Winsock.h>
#include <stdio.h>
#include <iostream>
#include<thread>
#include <time.h>
#include <Windows.h>
#pragma comment(lib, "wsock32.lib")
using namespace cv;
using namespace std;

#define RECV_PORT 2494		//设置服务器端口
#define ServerIPAddr 16		
#define predix "C:\\Users\\liuzh\\Pictures\\Saved Pictures\\store\\"

SOCKET Server;
sockaddr_in ServerAddr;
//第一个是局域网ip，第二个为本机测试
//char server_IP[ServerIPAddr] = "192.168.1.4";     	
char server_IP[ServerIPAddr] = "127.0.0.1"; 

//启动套接字项目
DWORD StartSock()			
{
	WSADATA WSAData;
	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)	// 加载winsock
		return -1;
	return 1;
}

//创建 socket
DWORD CreateSocket()
{	//套接字函数将返回一个套接字对象； SOCK_STREAM 相关 TCP
	Server = socket(AF_INET, SOCK_STREAM, 0);
	if (Server == SOCKET_ERROR)
	{
		WSACleanup();
		return -1;
	}
	return 1;
}

//请求连接
DWORD CallServer() 
{
	//client需要指定server的ip地址与端口
	ServerAddr.sin_family = AF_INET;		//Ipv4
	ServerAddr.sin_addr.s_addr = inet_addr(server_IP);
	ServerAddr.sin_port = htons(RECV_PORT);
	if (connect(Server, (struct  sockaddr*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
	{
		WSACleanup();
		closesocket(Server);
		return -1;
	}
	return 1;
}

int SendFile(char* filename)
{
#define BuffLen 800*1024
	FILE* pFile;
	char sbuff[BuffLen] = {};
	string str1 = predix + string(filename);
	fopen_s(&pFile, str1.c_str(), "rb+");
	int DataLength;
	if (pFile)
	{
		//逻辑与server端的逻辑对应，传输文件名时需间隔一定时间，再传输文件，防止两次传输间隔太短，server端将文件名与文件内容一起recv
		int j = send(Server, filename, strlen(filename) + 1, 1);
		Sleep(100);
		while (true)
		{
			memset(sbuff, 0, BuffLen);
			DataLength = fread(sbuff, 1, BuffLen, pFile);
			cout << DataLength << endl;
			if (DataLength < BuffLen)	//基于原理：逻辑数据可以连续存储
			{
				int i = send(Server, sbuff, DataLength + 1, 1);
				break;
			}
			else
			{
				send(Server, sbuff, DataLength, 1);
			}
		}
		return 1;
	}
	else
	{
		WSACleanup();
		closesocket(Server);
		return -1;
	}
}

int client(char* filename)		//该函数将以数据流的方式发送照片文件
{
	if (-1 == StartSock())
		return -1;
	if (-1 == CreateSocket())
		return -1;
	if (-1 == CallServer())
		return -1;
	if (-1 == SendFile(filename))
		return -1;
	/*
	因为send函数实质是将数据搬到本机的缓冲区，传输的过程是由系统完成的。
    因此传输完成后，需要等待一定时间，防止传输不全。
    需要释放winsock库，关闭sock client。才能进行下一次传输，否则server端可能还没断开本次连接，从而之后的连接一直呆在listen的队列中。
    */
	Sleep(1000);
	WSACleanup();
	closesocket(Server);
}

//项目目录temp文件夹中与.SLN相同的临时文件
string writePath = "C:\\Users\\liuzh\\Pictures\\Saved Pictures\\store\\";
void camera()
{
	VideoCapture capture(0);		//0 代表原装相机，外用 1, 2, 3, ……
	time_t times;
	struct tm nowtime;
	namedWindow("hello", CV_WINDOW_AUTOSIZE);
	char name[64];
	while (1)
	{
		Sleep(1000);		//in milliseconds
		Mat frame;
		capture >> frame;
		time(&times);
		localtime_s(&nowtime, &times);
		//在程序中设定了5秒拍一次，可以自行设置
		if (nowtime.tm_sec % 5 == 0)
		{
			strftime(name, sizeof(name) - 1, "%Y-%m-%d-%H-%M-%S", &nowtime);
			imwrite(writePath + name + ".jpg", frame);
			//程序在局域网上的两台主机上测试，如果传输图片不全，可能是网络问题，
			// 可以通过Sleep()给予server端足够时间。若无法解决，则可通过WSASetLastError()、
			// WSAGetLastError()两个函数获取错误信息，具体请search。
			//Sleep(2000);
			string str = name + string(".jpg");
			char* filename = (char*)str.data();
			client(filename);
		}
		//在opencv库中，以下两个函数是配套使用的
		//waitKey的作用是刷新图像帧，否则imshow的窗口无法显示，但可以正常传输。
		imshow("hello", frame);
		waitKey(10);
	}
}

int main(int argc, char** argv) {
	camera();
}
