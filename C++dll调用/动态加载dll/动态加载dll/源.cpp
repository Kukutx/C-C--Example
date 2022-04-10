#include <iostream>
using namespace std;
#include <windows.h>
typedef void(*p)();//函数指针,用来指向调用库里面的函数
int main()
{
	getchar();
	HMODULE hModul = LoadLibrary(L"dll文件1");//动态加载dll文件
	p pMsg = (p)GetProcAddress(hModul, "fun");//获取dll文件中的fun函数
	pMsg();
	system("pause");
	return 0;
}

