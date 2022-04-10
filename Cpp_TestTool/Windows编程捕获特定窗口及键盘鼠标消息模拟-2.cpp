#if 0
#include <iostream>
#include <string.h>
#include <Windows.h>
using namespace std;
//对枚举的子窗口进行操作
BOOL CALLBACK EnumChildProc(HWND hchild, LPARAM lparam)
{
	wchar_t cls_name[50];
	GetClassName(hchild, cls_name, 50);  //获取子窗口的类名
	wprintf(L"%s", cls_name);            //将子窗口的类名打印到屏幕
	wchar_t* p = wcsstr(cls_name, (wchar_t*)lparam);  //判断查找到的子窗口是否是编辑区窗口
	if (p == NULL)
	{
		return TRUE;
	}
	else
	{
		/*像编辑区发送按键按下的消息，内容分别hello world*/
		PostMessage(hchild, WM_KEYDOWN, 0x48, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x45, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x4c, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x4c, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x4f, 0);
		PostMessage(hchild, WM_KEYDOWN, VK_SPACE, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x57, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x4f, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x52, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x4c, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x44, 0);
		return TRUE;

	}
}

int main()
{
	HWND htext = FindWindow(NULL, L"无标题 - 记事本");  //找到记事本窗口的句柄
	if (!htext)
	{
		cout << "not find text!" << endl;
		return 0;
	}
	wchar_t class_name[] = { L"Edit" };   //设定要编辑区窗口的类名
	EnumChildWindows(htext, EnumChildProc, (LPARAM)class_name);  //枚举所有子窗口，在EnumChildProc函数中对这些窗口一一操作
	return 1;
}
#endif // 0
