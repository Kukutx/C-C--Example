#if 0
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>			//����time������
// ʹ��c++����qq����demo����������λ�ö�̬������λ�á�
void main()			//������
{
	HWND win = FindWindowA("TXGuiFoundation", "QQ");		//��ȡqq����ľ��
	if (win == NULL)		//�������ǿյģ���ʾ��ǰ���û���ҵ�
	{
		printf("qq��ʧ��");		//������
		ShellExecuteA(0, "open", "\"A:\\Program Files\\Tencent\\QQ\\Bin\\QQScLauncher.exe\"", 0, 0, 0);		//ִ��һ��shell����
		Sleep(2000);			//��Ϣ����ȴ�qq����
	}
	win = FindWindowA("TXGuiFoundation", "QQ");
	while (1)
	{
		POINT pt;		//����һ��λ�ñ���
		pt.x = pt.y = 0;		//��ʼ��x����y��
		//GetCursorPos(&pt);
		GetCursorPos(&pt);			//��ȡ����λ�ã�����pt
		printf("\n���x��=%d############���y��=%d", pt.x, pt.y);
		// SetWindowPos(win, 0, pt.x + 10, pt.y + 10, 0, 0, 1);

		time_t ts;		//������һ��ts�ı���
		unsigned int num = time(&ts);		//ͨ��time������ȡһ�����ַ���
		srand(num);		//�����
		int data = rand() % 4;		//����4���ࡣ�õ�һ��1��4������
		printf("%d", data);
		switch (data)			//�ֱ��1��4����ͬ�Ĵ���
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
		Sleep(200);		//��Ϣ0.2��
	}
}
#endif // 0


//��һ��˼·��������ָ�򲡶��Ŀ�ݼ������滻ָ��QQ����Ŀ�ݼ����ӣ�ͬ����qq��ͼ�꣩������߱�����˼·��
//0.������������ݼ���ʽ��Ϊ��ѶQQ���滻�����qq��ݷ�ʽ��ָ�򲡶���ִ���ļ�
//1.������ΪQQScLauncherCall
//2.���������ִ��qq����
//3.�������������hook���̼�¼������¼������������룬��Ϣ��qq�ŵȵ�
//4.��ȡqq�����о�����Ҳٿ�qq����ȵ�
