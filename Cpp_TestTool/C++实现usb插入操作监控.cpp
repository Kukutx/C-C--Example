#if 0
#include <tchar.h>  
#include <string>  
#include <iostream>  
#include <Windows.h>  
#include <dbt.h>  
using namespace std;
/*------------------------------------------------------------------
FirstDriveFromMask( unitmask )
Description
Finds the first valid drive letter from a mask of drive letters.
The mask must be in the format bit 0 = A, bit 1 = B, bit 2 = C,
and so on. A valid drive letter is defined when the
corresponding bit is set to 1.
从一个驱动器字母的面具中找到第一个有效的驱动器字母。
这个掩码必须在格式位0=A，位1=B，位2=C，
等等。一个有效的驱动器字母是在
对应位设置为1。
Returns the first drive letter that was found.
--------------------------------------------------------------------*/
char FirstDriveFromMask(ULONG unitmask)
{
	char i;

	for (i = 0; i < 26; ++i)
	{
		if (unitmask & 0x1)
			break;
		unitmask = unitmask >> 1;
	}

	return(i + 'A');
}

/*
	每个窗口会有一个称为窗口过程的回调函数(WndProc)，它带有四个参数，分别为：
	窗口句柄(Window Handle) HWND,
	消息ID(Message ID) UINT,
	和两个消息参数(wParam, lParam)WPARAM、LPARAM,
	WndProc的第一个参数hWnd就是当前接收消息的窗口句柄，第二个参数就是被传送过来的消息，
	第三、第四个参数都是附加在消息上的数据，这和MSG结构体是一样的
	想更加了解第三/第四参数请到https://baike.baidu.com/item/WPARAM/6098975?fr=aladdin
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;
	PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
	TCHAR szMsg[80];
	char driveName;

	/*
	当USB设备插入或者弹出时，Windows会产生一条全局消息：WM_DEVICECHANGE
我们需要做的是，获得这条消息的wParam参数，如果为DBT_DEVICEARRIVAL则表示有设备插入并可用，
如果是DBT_DEVICEREMOVECOMPLETE则表示有设备已经移除。再查看lParam参数为DBT_DEVTYP_VOLUME时，
就可以取出DEV_BROADCAST_VOLUME结构的卷号dbcv_unitmask，就知道是哪个卷被插入或者弹出。
	*/
	switch (uMsg)
	{
	case WM_DEVICECHANGE:
		switch (wParam)
		{
		case DBT_DEVICEARRIVAL:
			//获取卷号
			driveName = FirstDriveFromMask(lpdbv->dbcv_unitmask);
			cout << szMsg << "USB Drive %c: has inserted" << endl;
			cout << driveName << endl;
			//替换成cout 输出 sprintf(szMsg, "USB Drive %c: has inserted.\n", driveName);
			printf("%s\r\n", szMsg);
			MessageBox(hWnd, szMsg, TEXT("WM_DEVICECHANGE"), MB_OK);
			break;
		case DBT_DEVICEREMOVECOMPLETE:
			driveName = FirstDriveFromMask(lpdbv->dbcv_unitmask);
			cout << szMsg << "USB Drive %c: has removed." << endl;
			cout << driveName << endl;
			//替换成cout 输出 sprintf(szMsg, "USB Drive %c: has removed.\n", driveName);
			printf("%s\r\n", szMsg);
			MessageBoxW(hWnd, szMsg, TEXT("WM_DEVICECHANGE"), MB_OK);
			break;
		default:
			;
		}
		break;
	default:
		;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

/*
	_tmain()是unicode版本的的main()???
_tmain这个符号多见于VC++创建的控制台工程中，这个是为了保证移植unicode而加入的
（一般_t、_T、T()这些东西都和unicode有关系），对于使用非unicode字符集的工程来说
，实际上和main没有差别（其实就算是使用unicode字符集也未必有多大的差别）。
1。?main是C程序的函数，_tmain是main为了支持unicode所使用的main的别名
2。?_tmain的定义在<tchar.h>可以找到,如#define?_tmain?main，所以要加＃i nclude <tchar.h>才能用。
3。因此_tmain?compile后仍为main，所以都可以执行
另外,wmain也是main的另一个别名,是为了支持二个字节的语言环境
*/
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	TCHAR szClassName[] = _T("MyApp");
	/*
		WNDCLASS是一个由系统支持的结构，
		用来储存某一类窗口的信息,如ClassStyle,消息处理函数，Icon,Cursor,背景Brush等。
		也就是说，CreateWindow只是将某个WNDCLASS定义的窗体变成实例
		https://baike.baidu.com/item/WNDCLASS/6488732?fr=aladdin
	*/
	WNDCLASS wndcls = { 0 }; // zeroMemory方法
	//窗口的背景色
	wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	//窗口的鼠标光标
	wndcls.hCursor = (HCURSOR)LoadCursor(NULL, IDC_ARROW);
	//窗口的最小化图标
	wndcls.hIcon = (HICON)LoadIcon(NULL, IDI_APPLICATION);
	//窗口的处理函数
	wndcls.lpfnWndProc = WndProc;
	//窗口类名
	wndcls.lpszClassName = szClassName;
	/*
		如果使用RegisterClassA来注册窗口，应用程序通知系统被注册类的窗口的消息使用ANSI字符集的文本和字符参数；
		如果使用RegisterClassW来注册窗口，应用程序需要系统以Unicode来传递消息的文本参数
	*/
	if (!RegisterClassW(&wndcls))
	{
		printf("RegisterClass Failed!\r\n");
		return 0;
	}
	/*
	h 是类型描述，表示句柄(handle)， Wnd 是变量对象描述，表示窗口，所以hWnd 表示窗口句柄
	关于CreateWindow 请查看 https://baike.baidu.com/item/CreateWindow/5076220?fr=aladdin
	*/
	HWND hWnd = CreateWindow(szClassName, szClassName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, NULL, NULL);
	if (NULL == hWnd)
	{
		printf("CreateWindow Failed!\r\n");
		return 0;
	}
	//该函数设置指定窗口的显示状态。
	ShowWindow(hWnd, SW_HIDE);
	UpdateWindow(hWnd);

	MSG msg;
	//以下三个message 方法请各自百度百科了解吧。
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
#endif // 0
