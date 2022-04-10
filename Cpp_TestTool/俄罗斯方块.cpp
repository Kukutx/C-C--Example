#if 0
/*
��ɫ
1.������
2.��ʼ��Ϸ
�ı�
2.1����Ԥ������ͼƬ
2.2������Ҫ�����ͼ��
2.3��ÿһ����Ԫ�����ͼ��
3.�Ƿ��¼���
3.1 ����ƶ�
3.2 �ұ��ƶ�
3.3 �任ͼ��
3.4 ��������
��������
4. �����ж�
4.1�Ƿ�����(��ǰ������)
4.2 �Ƿ������Ϸ(��������)
5 ��Ϸ����
*/

#include <stdio.h>
#include <graphics.h>
#include<stdlib.h>
#include <conio.h>
#include <time.h>
#define unit 20
#define width 10
#define height 22



void OnRotate();
void OnLeft();
void OnRight();
void OnDown();
void OnSink();
void initGame();
void NewGame();
void NewBlock();
void GameOver();


//ȫ����������ʾ��Ϸ����
byte g_world[width][height] = { 0 };
//����״̬
enum cmd
{
	cmd_ritate,//��ת
	cmd_left,//���
	cmd_right,//�Ҽ�
	cmd_down,//����
	cmd_quit,//�˳�
	cmd_sink,//�³�
};

//ͼ�������е�״̬
enum draw
{
	show,//������ʾ
	clear,//���
	fix //�̶�
};

//��¼��ÿһ�����ӵ���Ϣ
struct blockinfo
{
	byte id; //�ڼ�������
	byte dir : 2; //��ʾ�Ƿ����еĵڼ���
	char x, y; //��ǰ���ӵ�λ��
}g_curblock/*��ǰ����*/, g_nextblock/*��һ������*/;

//���и��ӵ���Ϣ
struct block
{
	//ÿ��ͼ����16�����ӱ�ʾ�� 0û������   1��ʾ 
	WORD dir[4];
	COLORREF color;//��ɫ
}g_blocks[7] = {
	//{word,word,word,word,colorref}
	{ 0x0f00, 0x4444, 0x0f00, 0x4444, RED },//i
	{ 0x0660, 0x0660, 0x0660, 0x0660, BLUE },//��
	{ 0x4460, 0x02e0, 0x0622, 0x0740, BLUE },//l  //0100 0100 0110 0000
	{ 0x2260, 0x0e20, 0x0644, 0x0470, RED },//��l
	{ 0x0c60, 0x2640, 0x0c60, 0x2640, YELLOW },//z
	{ 0x0360, 0x4620, 0x0360, 0x4620, YELLOW },//��z
	{ 0x4e00, 0x4c40, 0xe400, 0x4640, BLUE }//t
};
//1.��ͼ��
void initGame()
{
	//��ʼ������
	initgraph(640, 480);
	setbkmode(TRANSPARENT);//���ñ�����ɫΪ͸��
	srand((unsigned)time(NULL));
	//��ʾ�ļ�
	settextstyle(14, 0, _T("����"));
	outtextxy(20, 280, _T("����˵��"));
	outtextxy(20, 300, _T("�ϣ� ��ת"));
	outtextxy(20, 320, _T("�£� ����"));
	outtextxy(20, 340, _T("�� ����"));
	outtextxy(20, 360, _T("�ң� ����"));
	outtextxy(20, 380, _T("�ո񣺿�������"));
	outtextxy(20, 400, _T("esc:�˳�����"));

	//����������

	//��������Բ��
	setorigin(220, 20);
	//������Ϸ����  ������
	rectangle(-1, -1, width * unit + 1, height * unit + 1);

	//�ұ߾���
	rectangle((width + 1) * unit - 1, -1, (width + 6) * unit, 6 * unit);
	//��ʼ����Ϸ
	NewGame();
}

//��ʼ����Ϸ
void NewGame()
{
	setfillcolor(BLACK);//����ɫ  �����Ϸ��
	ZeroMemory(g_world, width * height);  //��ʼ�������ֵ����Ϊ0
	//������һ������
	g_nextblock.id = rand() % 7;//������ɵĵ�һ������
	g_nextblock.dir = rand() % 4;//��ʾ�����еĵڼ���
	g_nextblock.x = width + 1; //11
	g_nextblock.y = height - 1; //

	//��ͼ��
	//drawblock(g_nextblock,show);
	NewBlock();
}
//����Ԫ��
void DrawUnit(int x, int y, COLORREF co, draw _draw)
{
	//���㵥Ԫ�����λ��
	int left = x * unit;  //11*20
	int right = (x + 1) * unit - 1;
	int top = (height - y/*22-(22-1)=1*/ - 1) * unit;
	int bottom = (height - y) * unit - 1;
	switch (_draw)
	{
	case show:
		setfillcolor(co);
		setlinecolor(LIGHTGRAY);
		fillrectangle(left, top, right, bottom);//���ڻ������Σ��б߿�)
		break;
	case clear:
		setfillcolor(BLACK);
		solidrectangle(x * unit, (height - y - 1) * unit, (x + 1) * unit - 1, (height - y) * unit - 1);
		break;
	case fix:
		setfillcolor(RGB(GetRValue(co) * 2 / 3, GetRValue(co) * 2 / 3, GetRValue(co) * 2 / 3));
		setlinecolor(DARKGRAY);
		fillrectangle(left, top, right, bottom);//���ڻ������Σ��б߿�)
		break;
	}
}
//��ͼ�� ����ͼ��
void DrawBlock(blockinfo _block, draw _draw)
{
	//word b = g_blocks[g_curblock.id].dir[g_curblock.dir];
	WORD b = g_blocks[_block.id].dir[_block.dir];
	int x, y;
	//�� 16�������е�ÿһ��
	for (int i = 0; i < 16; i++, b <<= 1)
	{
		if (b & 0x8000)
		{
			x = _block.x + i % 4;
			y = _block.y - i / 4;
			if (y < height)
			{
				//��һ��С����
				DrawUnit(x, y, g_blocks[_block.id].color, _draw);
			}
		}
	}
}
//�����µ�ͼ��
void NewBlock()
{
	//ͼ�ε���ʽ
	g_curblock.dir = g_nextblock.dir;
	g_nextblock.dir = rand() % 4;
	//��һ��ͼ��
	g_curblock.id = g_nextblock.id;
	g_nextblock.id = rand() % 7;


	g_curblock.x = (width - 4) / 2;
	g_curblock.y = height + 2;


	WORD c = g_blocks[g_curblock.id].dir[g_curblock.dir];
	while ((c & 0x000f) == 0)
	{
		g_curblock.y--;
		c >>= 4;
	}

	//��ͼ��
	DrawBlock(g_curblock, show);
	setfillcolor(BLACK);
	solidrectangle((width + 1) * unit, 0, (width + 6) * unit - 1, 6 * unit - 1);
	DrawBlock(g_nextblock, clear);
	DrawBlock(g_nextblock, show);
}

DWORD m_oldtime = 0;   //��ʼ���ʼ��ʱ��

//�ж��Ƿ񰴼�
cmd getcmd()
{
	while (true)
	{
		DWORD newtime = GetTickCount();  //�õ����ڵ�ʱ��
		if (newtime - m_oldtime > 500)
		{
			m_oldtime = newtime;
			return cmd_down;
		}
		if (_kbhit())
		{ //����Ƿ��е����Ϣ
			switch (_getch())
			{
			case 'w':
			case 'W': return  cmd_ritate;
			case 'a':
			case 'A': return  cmd_left;
			case 'd':
			case 'D': return  cmd_right;
			case 's':
			case 'S': return  cmd_down;
			case 27:return  cmd_quit;
			case ' ': return  cmd_sink;
			case 0:
			case 0xe0:
				switch (_getch())
				{
				case 72: return  cmd_ritate;
				case 75: return  cmd_left;
				case 77: return  cmd_right;
				case 80: return  cmd_down;

				}
			}
		}
		Sleep(20);

	}

}

//���ָ���ķ����Ƿ�����ƶ�
bool checkbloock(blockinfo _block)
{
	//word b = g_blocks[g_curblock.id].dir[g_curblock.dir];
	WORD b = g_blocks[_block.id].dir[_block.dir];
	int x, y;
	for (int i = 0; i < 16; i++, b <<= 1)
		if (b & 0x8000)
		{
			x = _block.x + i % 4;
			y = _block.y - i / 4;
			if ((x < 0) || (x >= width) || y < 0)
				return false;

			if ((y < height) && (g_world[x][y]))
				return false;
		}
	return true;
}

//���Ʒ���
void OnRight()
{
	blockinfo temp = g_curblock;    //��ǰͼ����Ϣ������temp 
	temp.x++;
	if (checkbloock(temp))
	{  //�Ƿ�����ƶ�
		DrawBlock(g_curblock, clear);  //�Ȳ��
		g_curblock.x++;
		DrawBlock(g_curblock, show); //����ʾ
	}
}

//���Ʒ���
void OnLeft()
{
	blockinfo temp = g_curblock;    //��ǰͼ����Ϣ������temp 
	temp.x--;
	if (checkbloock(temp))
	{  //�Ƿ�����ƶ�
		DrawBlock(g_curblock, clear);  //�Ȳ��
		g_curblock.x--;
		DrawBlock(g_curblock, show); //����ʾ
	}
}
//����
void OnDown()
{
	blockinfo temp = g_curblock;    //��ǰͼ����Ϣ������temp 
	temp.y--;
	if (checkbloock(temp))
	{  //�Ƿ�����ƶ�
		DrawBlock(g_curblock, clear);  //�Ȳ��
		g_curblock.y--;
		DrawBlock(g_curblock, show); //����ʾ
	}
	else
	{
		OnSink();  //����������   ִ�С��涨���顱����
	}
}
//  �̶�����  ���׷���
void OnSink()
{
	int i, x, y;

	// �������Ʒ���
	DrawBlock(g_curblock, clear);
	blockinfo tmp = g_curblock;
	tmp.y--;
	while (checkbloock(tmp))
	{
		g_curblock.y--;
		tmp.y--;
	}
	DrawBlock(g_curblock, fix);

	// �̶���������Ϸ��
	WORD b = g_blocks[g_curblock.id].dir[g_curblock.dir];
	for (i = 0; i < 16; i++, b <<= 1)
		if (b & 0x8000)  //��ʮ�������ӷֱ���д���
		{
			if (g_curblock.y - i / 4 >= height)
			{	// �������Ĺ̶�λ�ó����߶ȣ�������Ϸ
				GameOver();
				return;
			}
			else
				g_world[g_curblock.x + i % 4][g_curblock.y - i / 4] = 1;
		}

	// ����Ƿ���Ҫ�����У������
	byte remove = 0;	//  4 λ������Ƿ����漰�� 4 ���Ƿ���������Ϊ  //�����������
	for (y = g_curblock.y; y >= max(g_curblock.y - 3, 0); y--)
	{
		i = 0;
		for (x = 0; x < width; x++)
			if (g_world[x][y] == 1)
				i++;

		if (i == width)
		{
			remove |= (1 << (g_curblock.y - y/*0*/));//11   100 | 10 --11 111  1111
			//��һ���жϳ�����1

			//���ĳһ�м���������������������
			setfillcolor(LIGHTGREEN);//ǳ��ɫ
			setlinecolor(LIGHTGREEN);
			setfillstyle(BS_HATCHED, HS_DIAGCROSS);//��Ӱ�ߣ�ˮƽ��ֱ����
			fillrectangle(0, (height - y - 1) * unit + unit / 2 - 5, width * unit - 1, (height - y - 1) * unit + unit / 2 + 5);
			setfillstyle(BS_SOLID);//ʵ�Ļ�ˢ
		}
	}

	if (remove)	// ���������������
	{
		// ��ʱ 300 ����
		Sleep(300);

		// �����ղű�ǵ���
		IMAGE img;
		for (i = 0; i < 4; i++, remove >>= 1)
		{
			if (remove & 1)
			{
				for (y = g_curblock.y - i + 1; y < height; y++)
					for (x = 0; x < width; x++)
					{
						g_world[x][y - 1] = g_world[x][y];
						g_world[x][y] = 0;
					}

				getimage(&img, 0, 0, width * unit, (height - (g_curblock.y - i + 1)) * unit);
				putimage(0, unit, &img);
			}
		}
	}

	// �����·���
	NewBlock();
}

//��ת����
void  OnRotate()
{
	//��ȡ������ת��x��ƫ����
	int dx;
	blockinfo tmp = g_curblock;
	tmp.dir++;
	if (checkbloock(tmp)) { dx = 0; goto rotate; }
	tmp.x = g_curblock.x - 1;
	if (checkbloock(tmp)) { dx = -1; goto rotate; }
	tmp.x = g_curblock.x + 1; if (checkbloock(tmp)) { dx = 1;  goto rotate; }
	tmp.x = g_curblock.x - 2; if (checkbloock(tmp)) { dx = -2; goto rotate; }
	tmp.x = g_curblock.x + 2; if (checkbloock(tmp)) { dx = 2; goto rotate; }
	return;
rotate:
	//��ת
	DrawBlock(g_curblock, clear);
	g_curblock.dir++;
	g_curblock.x += dx;
	DrawBlock(g_curblock, show);

}

//��ȡ��ͼ���ھ��
void DispatchCMD(enum cmd cmd)
{
	switch (cmd)
	{
	case cmd_ritate:   OnRotate();
		break;
	case cmd_left:  OnLeft();
		break;
	case cmd_right: OnRight();
		break;
	case cmd_down: OnDown();
		break;
	case cmd_quit:
		break;
	case cmd_sink: OnSink();
		break;
		//default:
		//	break;
	}

}

void quit()
{
	closegraph();
	exit(0);
}
int main()
{
	initGame();
	cmd c;
	while (1)
	{
		//�ж��Ƿ��а���
		c = getcmd();
		DispatchCMD(c);  //�ж��û�����ʲô��
		if (c == cmd_quit)
		{  //esc
			HWND wnd = GetHWnd();//��ȡ��ͼ���ھ��
			if (MessageBox(wnd, _T("�˳���Ϸ��"), _T("��ʾ"),
				MB_OKCANCEL | MB_ICONASTERISK) == IDOK)
			{
				quit();
			}
		}
	}

	system("pause");
	//closegraph();
	return  0;
}

void GameOver()
{
	HWND wnd = GetHWnd();//��ȡ��ͼ���ھ��
	if (MessageBox(wnd, _T("��Ϸ����\n ����һ�֣�"), _T("��Ϸ����"),
		MB_YESNO | MB_ICONASTERISK) == IDYES)
	{
		initGame();
	}
	else
	{
		quit();
	}
}


#endif // 0
