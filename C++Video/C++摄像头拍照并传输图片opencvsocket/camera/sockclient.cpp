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

#define RECV_PORT 2494		//���÷������˿�
#define ServerIPAddr 16		
#define predix "C:\\Users\\liuzh\\Pictures\\Saved Pictures\\store\\"

SOCKET Server;
sockaddr_in ServerAddr;
//��һ���Ǿ�����ip���ڶ���Ϊ��������
//char server_IP[ServerIPAddr] = "192.168.1.4";     	
char server_IP[ServerIPAddr] = "127.0.0.1"; 

//�����׽�����Ŀ
DWORD StartSock()			
{
	WSADATA WSAData;
	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)	// ����winsock
		return -1;
	return 1;
}

//���� socket
DWORD CreateSocket()
{	//�׽��ֺ���������һ���׽��ֶ��� SOCK_STREAM ��� TCP
	Server = socket(AF_INET, SOCK_STREAM, 0);
	if (Server == SOCKET_ERROR)
	{
		WSACleanup();
		return -1;
	}
	return 1;
}

//��������
DWORD CallServer() 
{
	//client��Ҫָ��server��ip��ַ��˿�
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
		//�߼���server�˵��߼���Ӧ�������ļ���ʱ����һ��ʱ�䣬�ٴ����ļ�����ֹ���δ�����̫�̣�server�˽��ļ������ļ�����һ��recv
		int j = send(Server, filename, strlen(filename) + 1, 1);
		Sleep(100);
		while (true)
		{
			memset(sbuff, 0, BuffLen);
			DataLength = fread(sbuff, 1, BuffLen, pFile);
			cout << DataLength << endl;
			if (DataLength < BuffLen)	//����ԭ���߼����ݿ��������洢
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

int client(char* filename)		//�ú��������������ķ�ʽ������Ƭ�ļ�
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
	��Ϊsend����ʵ���ǽ����ݰᵽ�����Ļ�����������Ĺ�������ϵͳ��ɵġ�
    ��˴�����ɺ���Ҫ�ȴ�һ��ʱ�䣬��ֹ���䲻ȫ��
    ��Ҫ�ͷ�winsock�⣬�ر�sock client�����ܽ�����һ�δ��䣬����server�˿��ܻ�û�Ͽ��������ӣ��Ӷ�֮�������һֱ����listen�Ķ����С�
    */
	Sleep(1000);
	WSACleanup();
	closesocket(Server);
}

//��ĿĿ¼temp�ļ�������.SLN��ͬ����ʱ�ļ�
string writePath = "C:\\Users\\liuzh\\Pictures\\Saved Pictures\\store\\";
void camera()
{
	VideoCapture capture(0);		//0 ����ԭװ��������� 1, 2, 3, ����
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
		//�ڳ������趨��5����һ�Σ�������������
		if (nowtime.tm_sec % 5 == 0)
		{
			strftime(name, sizeof(name) - 1, "%Y-%m-%d-%H-%M-%S", &nowtime);
			imwrite(writePath + name + ".jpg", frame);
			//�����ھ������ϵ���̨�����ϲ��ԣ��������ͼƬ��ȫ���������������⣬
			// ����ͨ��Sleep()����server���㹻ʱ�䡣���޷���������ͨ��WSASetLastError()��
			// WSAGetLastError()����������ȡ������Ϣ��������search��
			//Sleep(2000);
			string str = name + string(".jpg");
			char* filename = (char*)str.data();
			client(filename);
		}
		//��opencv���У�������������������ʹ�õ�
		//waitKey��������ˢ��ͼ��֡������imshow�Ĵ����޷���ʾ���������������䡣
		imshow("hello", frame);
		waitKey(10);
	}
}

int main(int argc, char** argv) {
	camera();
}
