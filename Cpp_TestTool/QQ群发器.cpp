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
	* qq��ը�����װ�
	 int i,num;
     char name [128];
     printf("����һ������:\n");
     scanf("%s",&name);
     printf("������Ϣ����:\n");
     scanf("%d",&num);
     HWND hwnd=FindWindow(0,name);     //����qq���ѵ�ǰ������
     for(i=0;;i++){
		SendMessage(hwnd,WM_PASTE,0,0);   /	//ճ����Ϣ��windows��Ϣ  WM windowsmessage
		SendMessage(hwnd,WM_KEYDOWN,VK_RETURN,0);  //3.�س����� �س� VK_RETURN��WM_KEYDOWN ���ڰ�������
     }
	 */
	system("pause");
	return 0;
}

#endif // 0
