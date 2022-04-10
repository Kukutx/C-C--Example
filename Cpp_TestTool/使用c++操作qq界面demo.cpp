#if 0
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>			//引用time函数库
// 使用c++操作qq界面demo。根据鼠标的位置动态的跳动位置。
void main()			//主程序
{
	HWND win = FindWindowA("TXGuiFoundation", "QQ");		//获取qq界面的句柄
	if (win == NULL)		//如果句柄是空的，表示当前句柄没有找到
	{
		printf("qq玩失踪");		//输出语句
		ShellExecuteA(0, "open", "\"A:\\Program Files\\Tencent\\QQ\\Bin\\QQScLauncher.exe\"", 0, 0, 0);		//执行一个shell命令
		Sleep(2000);			//休息两秒等待qq启动
	}
	win = FindWindowA("TXGuiFoundation", "QQ");
	while (1)
	{
		POINT pt;		//定义一个位置变量
		pt.x = pt.y = 0;		//初始化x轴与y轴
		//GetCursorPos(&pt);
		GetCursorPos(&pt);			//获取鼠标的位置，放入pt
		printf("\n鼠标x轴=%d############鼠标y轴=%d", pt.x, pt.y);
		// SetWindowPos(win, 0, pt.x + 10, pt.y + 10, 0, 0, 1);

		time_t ts;		//定义了一个ts的变量
		unsigned int num = time(&ts);		//通过time函数获取一个数字放入
		srand(num);		//随机数
		int data = rand() % 4;		//除以4求余。得到一个1到4的数字
		printf("%d", data);
		switch (data)			//分别对1到4做不同的处理
		{
		case 0:
			SetWindowPos(win, NULL, pt.x - 300, pt.y - 300, 500, 400, 0);
			break;
		case 1:
			SetWindowPos(win, NULL, pt.x - 300, pt.y + 300, 500, 400, 0);
			break;
		case 2:
			SetWindowPos(win, NULL, pt.x + 300, pt.y - 300, 500, 400, 0);
			break;
		case 3:
			SetWindowPos(win, NULL, pt.x + 300, pt.y + 300, 500, 400, 0);
			break;
		}
		Sleep(200);		//休息0.2秒
	}
}
#endif // 0


//有一种思路，可以用指向病毒的快捷键链接替换指向QQ程序的快捷键链接（同样用qq的图标），程序具备以下思路：
//0.病毒创建个快捷键方式名为腾讯QQ且替换桌面的qq快捷方式，指向病毒可执行文件
//1.程序名为QQScLauncherCall
//2.当被激活后执行qq程序
//3.当被激活后启动hook键盘记录器，记录键盘输入的密码，消息，qq号等等
//4.获取qq的所有句柄，且操控qq界面等等
