#include <iostream>
using namespace std;
#include <windows.h>
typedef void(*p)();//����ָ��,����ָ����ÿ�����ĺ���
int main()
{
	getchar();
	HMODULE hModul = LoadLibrary(L"dll�ļ�1");//��̬����dll�ļ�
	p pMsg = (p)GetProcAddress(hModul, "fun");//��ȡdll�ļ��е�fun����
	pMsg();
	system("pause");
	return 0;
}

