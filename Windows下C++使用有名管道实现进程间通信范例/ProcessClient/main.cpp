#include <iostream>
#include <Windows.h>
#define INPUT_SIZE  4096   //�ڴ��ַ�Ĵ�С
#define PROCESS_NAME  L"MemoryShare"
#define  _CRT_SECURE_NO_WARNINGS 
using namespace std;
#pragma warning(disable : 4996)
//�������ǿͻ��ˣ��������ǣ�������ռ䣬���Ҷ�ȡ���������
int main()
{
	//�򿪹�����ļ�����
	HANDLE hFileMap_Handle = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, PROCESS_NAME);
	//�жϾ���Ƿ����
	if (hFileMap_Handle)
	{
		LPVOID lpBase = MapViewOfFile(hFileMap_Handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		char szBuffer[INPUT_SIZE] = { 0 };
		strcpy(szBuffer, (char*)lpBase);
		cout << "��ȡ������Ϊ��" << szBuffer << endl;
		//���ӳ��
		UnmapViewOfFile(lpBase);
		//�رվ��
		CloseHandle(hFileMap_Handle);
	}
	system("pause");
	return 0;
}