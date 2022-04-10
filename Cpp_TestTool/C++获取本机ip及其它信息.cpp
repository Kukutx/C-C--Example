#if 0
#include "cstdio"
#include "cstring"
#include "string"
#include "winsock2.h"
#pragma comment(lib, "WS2_32")
#pragma comment(lib, "urlmon.lib")
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

// 获取本机ip
char* getlocal_ip()
{
	char* ret = nullptr;
	char host_name[256] = "";
	WSADATA wsaData;
	WSAStartup(0x101, &wsaData);

	if (!gethostname(host_name, 256))
	{
		ret = inet_ntoa(*((struct in_addr*)gethostbyname(host_name)->h_addr));
	}

	WSACleanup();
	return ret;
}

// 获取本机名
char* getlocal_name(char* name, int len)
{
	WSADATA wsaData;
	WSAStartup(0x101, &wsaData);
	gethostname(name, len);
	WSACleanup();
	return name;
}

// 获取公网ip (也叫外网ip)
char* getPub_ip(char* ip)
{
	const char* dest = "<code>";
	const char* dest1 = "</code>";
	const char* szFileName = "./ip.txt";
	if (URLDownloadToFile(NULL, L"https://www.ip.cn/", (const wchar_t*)szFileName, 0, NULL) == S_OK)
	{
		FILE* fp = fopen(szFileName, "r");
		if (fp)
		{
			char line[512];
			while (fgets(line, 512, fp))
			{
				char* fd = strstr(line, dest);
				if (fd)
				{
					char* star = fd + strlen(dest);
					strncpy(ip, star, strstr(star, dest1) - star);//16
					break;
				}
			}
			fclose(fp);
			remove(szFileName);// 删除文件
		}
	}

	return ip;
}

// 获取某个网站的ip
char* getipFromHttp(char* http, char* result)
{
	const char* fileName = "D:/1.txt";
	string cmd = string("ping ") + http + string(">") + fileName;
	system(cmd.c_str());
	FILE* fp = fopen(fileName, "r");
	if (fp)
	{
		char line[512];
		while (fgets(line, 512, fp))
		{
			char* fd = strchr(line, '[');
			if (fd)
			{
				char* star = fd + 1;
				strncpy(result, star, strchr(star, ']') - star);
				break;
			}
		}
		fclose(fp);
		remove(fileName);
	}
	return NULL;
}

int main()
{
	char name[28] = "";
	printf("本地IP:%s\n", getlocal_ip());

	printf("主机名：%s\n", getlocal_name(name, 28));
	char ip[25] = "";
	printf("外网：%s\n", getPub_ip(ip));

	const char* http = "www.taobao.com";
	getipFromHttp((char*)http, ip);
	printf("%s --DNS--> %s\n", http, ip);
	system("pause");
	return 0;
}
#endif // 0
