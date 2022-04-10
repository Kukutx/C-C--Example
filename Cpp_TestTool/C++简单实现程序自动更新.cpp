#if 0
#include<iostream>
#include<Windows.h>
#include <tchar.h>
#include <fstream>
#include <atlbase.h>
using namespace std;
/*
URLDownloadToFile 保存网页内容 不支持重定向(容易报毒
ifstream 恶心的文件与流 详情看https://www.runoob.com/cplusplus/cpp-files-streams.html


像网页端可以尝试下github.io或gitee博客
*/
void CharToTchar(const char* _char, const TCHAR* tchar)
{
	int iLength;

	iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, tchar, iLength);
}
int main() {
	string xiaves;
	cout << "是否下载beta版(1/2)";
	int betayes;
	cin >> betayes;
	if (betayes == 1) {
		xiaves = "beta.html";
	}
	else {
		xiaves = "update.html";
	}
	string wangye = "http://******/update/" + xiaves;   //可以giyhub
	LPCSTR wangzhi = wangye.c_str();
	LPCWSTR wangzhiTest;
	CharToTchar(wangzhi, wangzhiTest);
	HRESULT dyes;
	cout << "检查中" << endl;
	dyes = URLDownloadToFile(0, wangzhiTest, _T("C:\\bugfixed_update.txt"), 0, NULL); //下载检测文件
	if (dyes == S_OK) //下载成功
	{
		string temp; //读取文件
		ifstream infile;
		infile.open("C:\\bugfixed_update.txt", ios::in | ios::trunc);
		ifstream readFile("C:\\bugfixed_update.txt");
		readFile >> temp;
		cout << temp << endl;
		readFile.close();
		if (temp == "0.4") {  //==后为当前版本  //诺后端与前端相同
			cout << "无版本更新";
			Sleep(100000);
			return 0;
		}
		else {
			cout << "检测到新版本" << endl; //不同
			cout << "是否立即安装(1/2)";
			cin >> betayes;
			if (betayes == 1) {
				string down = "http://****/download/" + xiaves;
				LPCSTR download = down.c_str();
				LPCWSTR downloadTest;
				CharToTchar(download, downloadTest);
				dyes = URLDownloadToFile(0, downloadTest, _T("C:\\update.msi"), 0, NULL);
				if (dyes == S_OK) {
					system("start c:\\update.msi");
					system("del c:\\update.msi");
					return 0;
				}
				else {
					cout << "下载失败" << endl;
				}
			}
			else {
				return 0;
			}
		}
	}
	else {
		cout << "检测失败" << endl;
	}
}
#endif // 0
