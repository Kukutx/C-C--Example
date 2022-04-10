#include <Winsock.h>
#include <stdio.h>
#include<stdlib.h>
#include<iostream>
#include<thread>
#pragma comment(lib, "wsock32.lib")	
using namespace std;

#define RECV_PORT 2494  //'RECV_PORT' 应该与 sockclient.cpp 中的变量相同
SOCKET sockserver;
struct sockaddr_in ServerAddr;
SOCKET sockclient;
struct sockaddr_in ClientAddr;

void TCPRecv()
{
	#define BuffLength 800*1024	
	#define filename_length 100
	#define predix "C:\\Users\\liuzh\\Pictures\\Camera Roll\\"
	FILE* p = NULL;
	int recv_len = 0;
	char filename[filename_length] = {};
	char rbuff[BuffLength] = {};
	for (int number = 1;; number++)
	{
		memset(rbuff, 0, BuffLength);
		//第一次recv文件名，并创建文件。之后则传输文件
		if (1 == number)
		{
			recv_len = recv(sockclient, filename, filename_length, 0);
			if (recv_len <= 0)
			{
				closesocket(sockclient);
				cout << "filename error" << endl;
				break;
			}
			string str1 = predix + string(filename);
			fopen_s(&p, str1.c_str(), "wb");
		}
		else
		{
			recv_len = recv(sockclient, rbuff, BuffLength, 0);
			if (recv_len <= 0)
			{
				closesocket(sockclient);
				cout << "connection finish" << endl;
				fclose(p);
				break;
			}
			fwrite(rbuff, recv_len, 1, p);
			fflush(p);
		}
	}
	return;
}

//initialize winsock  
DWORD StartSock()     //load winsock
{
	WSADATA WSAData;
	//BOOL bReuseaddr = TRUE;
	//BOOL bDontLinger = FALSE;
	//setsockopt(sockclient, SOL_SOCKET, SO_DONTLINGER, (const char*)&bDontLinger, sizeof(BOOL));
	//setsockopt(sockclient, SOL_SOCKET, SO_REUSEADDR, (const char*)&bReuseaddr, sizeof(BOOL));
	//使用socket需要加载winsock库
	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)	//WSADATA: 它存储有关套接字的信息
	{
		cout << "socket init fail!" << endl;
		return  -1;
	}
	//通过socket()获取套接字，失败则WSACleanup，退出程序
	sockserver = socket(AF_INET, SOCK_STREAM, 0); 	//结构 SOCKET,load winsock，SOCK_STREAM 代表 TCP 协议
	if (sockserver == SOCKET_ERROR)
	{
		printf("sockserver create fail ! \n");
		WSACleanup();				//释放winsock
		return -1;
	}
	//设置sockserver的参数，AF_INET指IPV4，INADDR_ANY指任何地址，RECV_PORT指绑定的端口。
	ServerAddr.sin_family = AF_INET;		// sockaddr_in 是一种结构，serveraddr 与 sockaddr_in 相同
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ServerAddr.sin_port = htons(RECV_PORT);
	if (SOCKET_ERROR == ::bind(sockserver, (struct  sockaddr  FAR*) & ServerAddr, sizeof(ServerAddr)))
	{   //使用 addr 绑定套接字
		printf("bind is the error");
		return -1;
	}
	//绑定端口后，开始监听。SOMAXCONN代表最大数目，对于单对单通信没有影响。
	if (listen(sockserver, SOMAXCONN) < 0)
	{
		printf("Listen error");
		return -1;
	}
	//初始化后，for循环传输图片
	int Addrlen = sizeof(ClientAddr);
	//直到成功监控clientsocket，accept才会返回
	/*
		当前时间照片传输直到“接受”功能结束才能触发
	*/
	for (int i = 1;; i++)
	{
		sockclient = accept(sockserver, (struct sockaddr FAR*) & ClientAddr, &Addrlen);
		cout << "connection: " << i << endl;
		thread T(TCPRecv);
		T.join();
	}
}

void main()
{
	if (StartSock() == -1)
		return;
	system("pause");
}
