#if 0
#include<windows.h>
#include<stdio.h>
#include<time.h>
#include<conio.h>
int main()
{
	/*����Ҷ�
	system("title ");
	int x,y;
	printf("���������ͣ��");
	while(!_kbhit())
	{
		x=rand()%332+300;
		y=rand()%228+300;
		//�������������
		//x=1;
		//y=1;
		SetCursorPos(x,y);
	}
	*/
	while (1)
	{
		if (GetAsyncKeyState(VK_SPACE))//���¿ո񣬿�ʼִ��
		{
			while (1)
			{
				mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//��ǰλ�õ��һ�����
				Sleep(500);//ÿ0.5����һ��
				if (GetAsyncKeyState(VK_ESCAPE))return 0; //��esc�˳�
			}
		}
	}
	return 0;
}

#endif // 0
