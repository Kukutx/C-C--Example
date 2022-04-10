#if 0
#include <iostream>
using namespace std;
#include <Windows.h>
BOOL CALLBACK EnumWindowsPro(HWND hwnd, LPARAM  param)
{
	char strClassName[MAXBYTE] = { 0 };
	GetClassNameA(hwnd, strClassName, MAXBYTE);
	if (strcmp(strClassName, "TXGuiFoundation") == 0)
	{
		SendMessageW(hwnd, WM_PASTE, 0, 0);
		SendMessageW(hwnd, WM_KEYDOWN, VK_RETURN, 0);
		//SendMassageW(hwnd, WM_CLOSE, 0, 0);
	}
	return true;
}
int main()
{
	HWND hQQMain = FindWindowA("TXGuiFoundation", "QQ");
	ShowWindow(hQQMain, SW_SHOW);
	for (int i = 0; i < 25; i++)
	{
		SendMessageA(hQQMain, WM_KEYDOWN, VK_DOWN, 0);
		SendMessageA(hQQMain, WM_KEYDOWN, VK_RETURN, 0);
		EnumWindows(EnumWindowsPro, NULL);
	}
	/*
	* qq轰炸机简易版
	 int i,num;
     char name [128];
     printf("输入一个名字:\n");
     scanf("%s",&name);
     printf("输入消息次数:\n");
     scanf("%d",&num);
     HWND hwnd=FindWindow(0,name);     //输入qq好友当前窗体名
     for(i=0;;i++){
		SendMessage(hwnd,WM_PASTE,0,0);   /	//粘贴消息，windows消息  WM windowsmessage
		SendMessage(hwnd,WM_KEYDOWN,VK_RETURN,0);  //3.回车发送 回车 VK_RETURN，WM_KEYDOWN 窗口按键按下
     }
	 */
	system("pause");
	return 0;
}

#endif // 0
