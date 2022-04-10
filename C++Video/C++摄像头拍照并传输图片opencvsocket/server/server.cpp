#include <Winsock.h>
#include <stdio.h>
#include<stdlib.h>
#include<iostream>
#include<thread>
#pragma comment(lib, "wsock32.lib")	
using namespace std;

#define RECV_PORT 2494  //'RECV_PORT' Ӧ���� sockclient.cpp �еı�����ͬ
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
		//��һ��recv�ļ������������ļ���֮�������ļ�
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
	//ʹ��socket��Ҫ����winsock��
	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)	//WSADATA: ���洢�й��׽��ֵ���Ϣ
	{
		cout << "socket init fail!" << endl;
		return  -1;
	}
	//ͨ��socket()��ȡ�׽��֣�ʧ����WSACleanup���˳�����
	sockserver = socket(AF_INET, SOCK_STREAM, 0); 	//�ṹ SOCKET,load winsock��SOCK_STREAM ���� TCP Э��
	if (sockserver == SOCKET_ERROR)
	{
		printf("sockserver create fail ! \n");
		WSACleanup();				//�ͷ�winsock
		return -1;
	}
	//����sockserver�Ĳ�����AF_INETָIPV4��INADDR_ANYָ�κε�ַ��RECV_PORTָ�󶨵Ķ˿ڡ�
	ServerAddr.sin_family = AF_INET;		// sockaddr_in ��һ�ֽṹ��serveraddr �� sockaddr_in ��ͬ
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ServerAddr.sin_port = htons(RECV_PORT);
	if (SOCKET_ERROR == ::bind(sockserver, (struct  sockaddr  FAR*) & ServerAddr, sizeof(ServerAddr)))
	{   //ʹ�� addr ���׽���
		printf("bind is the error");
		return -1;
	}
	//�󶨶˿ں󣬿�ʼ������SOMAXCONN���������Ŀ�����ڵ��Ե�ͨ��û��Ӱ�졣
	if (listen(sockserver, SOMAXCONN) < 0)
	{
		printf("Listen error");
		return -1;
	}
	//��ʼ����forѭ������ͼƬ
	int Addrlen = sizeof(ClientAddr);
	//ֱ���ɹ����clientsocket��accept�Ż᷵��
	/*
		��ǰʱ����Ƭ����ֱ�������ܡ����ܽ������ܴ���
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
