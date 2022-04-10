#if 0
#include<windows.h>
#include<stdio.h>
#include<time.h>
#include<conio.h>
int main()
{
	/*鼠标乱抖
	system("title ");
	int x,y;
	printf("按任意键暂停！");
	while(!_kbhit())
	{
		x=rand()%332+300;
		y=rand()%228+300;
		//这样可鼠标隐藏
		//x=1;
		//y=1;
		SetCursorPos(x,y);
	}
	*/
	while (1)
	{
		if (GetAsyncKeyState(VK_SPACE))//按下空格，开始执行
		{
			while (1)
			{
				mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//当前位置点击一次鼠标
				Sleep(500);//每0.5秒点击一次
				if (GetAsyncKeyState(VK_ESCAPE))return 0; //按esc退出
			}
		}
	}
	return 0;
}

#endif // 0
