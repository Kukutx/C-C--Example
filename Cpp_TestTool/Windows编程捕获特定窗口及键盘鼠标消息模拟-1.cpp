#if 0
#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
	//获取窗口句柄
	HWND htext = FindWindow(NULL, L"无标题 - 记事本");  //找到记事本窗口的句柄
	if (!htext)
	{
		cout << "not find text!" << endl;
		return 0;
	}
	// 获取子窗口句柄
	HWND hchild = FindWindowEx(htext, NULL, L"Edit", NULL);  //找到记事本的编辑区子窗口
	if (!hchild)
	{
		cout << "not find child!" << endl;
		return 0;
	}
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
	return 1;
}
#endif // 0
