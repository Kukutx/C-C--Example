#include <iostream>
#include <Windows.h>
#define INPUT_SIZE  4096   //�ڴ�ռ�Ĵ�С
#define PROCESS_NAME  L"MemoryShare"  //���ʵ�ַ�ı�־���������ֵ��е�key
#define  _CRT_SECURE_NO_WARNINGS 
using namespace std;
#pragma warning(disable : 4996)
//�����Ƿ������ˣ����𴴽������ڴ��ַ�ռ�ͷ����ݽ�ȥ
int main()
{
	char input_str[] = "test data";//��ŵ�����
	//1.���������ڴ�
	HANDLE hFileMap_Handle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_EXECUTE_READWRITE, 0, INPUT_SIZE, PROCESS_NAME);
	//2.�õ������ڴ��ָ��
	LPVOID share_memory_ptr = MapViewOfFile(hFileMap_Handle, FILE_MAP_ALL_ACCESS, 0, 0, INPUT_SIZE);
	//3.����Ҫ�ͻ��˶�ȡ�����ݷ��ڹ����ڴ�ĵ�ַ��
	strcpy((char*)share_memory_ptr, input_str);
	Sleep(5000000);//���õȴ�ʱ�䣬��Ϊ�ڴ�Ĵ��ʱ�䣬�ȴ�����ͷ�
	//4.���ӳ��
	UnmapViewOfFile(share_memory_ptr);
	//5.�رվ��
	CloseHandle(hFileMap_Handle);
	cout << "���ʽ���" << endl;
	system("pause");
	return 0;
}