// callDLLSee.cpp : 定义控制台应用程序的入口点。
//通过调用windowsAPI 来加载和卸载DLL
#include <iostream>
#include<TCHAR.h>
#include <Windows.h>
using namespace std;


// 动态调用DLL库
void DynamicUse()
{
	// 运行时加载DLL库
	HMODULE module = LoadLibrary(L"myDLL.dll");     // 根据DLL文件名，加载DLL，返回一个模块句柄
	if (module == NULL)
	{
		printf("加载DLLTest1.dll动态库失败\n");
		FreeLibrary(module);
		return;
	}
	typedef int(*AddFunc)(int, int);                  // 定义函数指针类型
	AddFunc add;
	// 导出函数地址
	add = (AddFunc)GetProcAddress(module, "add");     // GetProcAddress返回指向的函数名的函数地址

	int sum = add(100, 200);
	printf("动态调用，sum = %d\n", sum);
	FreeLibrary(module);
}

int main()
{
	DynamicUse();
	HMODULE hdll = LoadLibrary(L"myDLL.dll");
	if (hdll == NULL)
	{
		cout << "加载失败";
		FreeLibrary(hdll);
		return 0;
	}
	typedef double(*Dllfun)(int, int);
	Dllfun funName;
	funName = (Dllfun)GetProcAddress(hdll, "seekArea");
	if (funName == NULL)
	{
		FreeLibrary(hdll);
		return 0;
	}
	int r = 1, h = 10;
	double area = funName(r, h);
	printf("area = %f\n", area);
	FreeLibrary(hdll);
	return 0;
}