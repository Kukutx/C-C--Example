#if 0
#include<iostream>
#include<Windows.h>
#include <tchar.h>
#include <fstream>
#include <atlbase.h>
using namespace std;
/*
URLDownloadToFile ������ҳ���� ��֧���ض���(���ױ���
ifstream ���ĵ��ļ����� ���鿴https://www.runoob.com/cplusplus/cpp-files-streams.html


����ҳ�˿��Գ�����github.io��gitee����
*/
void CharToTchar(const char* _char, const TCHAR* tchar)
{
	int iLength;

	iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, tchar, iLength);
}
int main() {
	string xiaves;
	cout << "�Ƿ�����beta��(1/2)";
	int betayes;
	cin >> betayes;
	if (betayes == 1) {
		xiaves = "beta.html";
	}
	else {
		xiaves = "update.html";
	}
	string wangye = "http://******/update/" + xiaves;   //����giyhub
	LPCSTR wangzhi = wangye.c_str();
	LPCWSTR wangzhiTest;
	CharToTchar(wangzhi, wangzhiTest);
	HRESULT dyes;
	cout << "�����" << endl;
	dyes = URLDownloadToFile(0, wangzhiTest, _T("C:\\bugfixed_update.txt"), 0, NULL); //���ؼ���ļ�
	if (dyes == S_OK) //���سɹ�
	{
		string temp; //��ȡ�ļ�
		ifstream infile;
		infile.open("C:\\bugfixed_update.txt", ios::in | ios::trunc);
		ifstream readFile("C:\\bugfixed_update.txt");
		readFile >> temp;
		cout << temp << endl;
		readFile.close();
		if (temp == "0.4") {  //==��Ϊ��ǰ�汾  //ŵ�����ǰ����ͬ
			cout << "�ް汾����";
			Sleep(100000);
			return 0;
		}
		else {
			cout << "��⵽�°汾" << endl; //��ͬ
			cout << "�Ƿ�������װ(1/2)";
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
					cout << "����ʧ��" << endl;
				}
			}
			else {
				return 0;
			}
		}
	}
	else {
		cout << "���ʧ��" << endl;
	}
}
#endif // 0
