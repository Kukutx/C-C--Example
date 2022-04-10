#if 0
/*
颜色
1.画界面
2.开始游戏
文本
2.1生成预备下落图片
2.2生成正要下落的图形
2.3画每一个单元格组成图形
3.是否按下键盘
3.1 左边移动
3.2 右边移动
3.3 变换图形
3.4 快速下落
自由下落
4. 消除判断
4.1是否消除(当前行满格)
4.2 是否结束游戏(整列满格)
5 游戏结束
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


//全局数组来表示游戏区域
byte g_world[width][height] = { 0 };
//操作状态
enum cmd
{
	cmd_ritate,//旋转
	cmd_left,//左键
	cmd_right,//右键
	cmd_down,//下落
	cmd_quit,//退出
	cmd_sink,//下沉
};

//图像下落中的状态
enum draw
{
	show,//正常显示
	clear,//察除
	fix //固定
};

//记录了每一个格子的信息
struct blockinfo
{
	byte id; //第几个方块
	byte dir : 2; //表示是方块中的第几个
	char x, y; //当前格子的位置
}g_curblock/*当前格子*/, g_nextblock/*下一个格子*/;

//所有格子的信息
struct block
{
	//每个图形用16个格子表示， 0没有内容   1显示 
	WORD dir[4];
	COLORREF color;//颜色
}g_blocks[7] = {
	//{word,word,word,word,colorref}
	{ 0x0f00, 0x4444, 0x0f00, 0x4444, RED },//i
	{ 0x0660, 0x0660, 0x0660, 0x0660, BLUE },//田
	{ 0x4460, 0x02e0, 0x0622, 0x0740, BLUE },//l  //0100 0100 0110 0000
	{ 0x2260, 0x0e20, 0x0644, 0x0470, RED },//反l
	{ 0x0c60, 0x2640, 0x0c60, 0x2640, YELLOW },//z
	{ 0x0360, 0x4620, 0x0360, 0x4620, YELLOW },//反z
	{ 0x4e00, 0x4c40, 0xe400, 0x4640, BLUE }//t
};
//1.画图形
void initGame()
{
	//初始化窗口
	initgraph(640, 480);
	setbkmode(TRANSPARENT);//设置背景颜色为透明
	srand((unsigned)time(NULL));
	//显示文件
	settextstyle(14, 0, _T("宋体"));
	outtextxy(20, 280, _T("操作说明"));
	outtextxy(20, 300, _T("上： 旋转"));
	outtextxy(20, 320, _T("下： 下落"));
	outtextxy(20, 340, _T("左： 左移"));
	outtextxy(20, 360, _T("右： 右移"));
	outtextxy(20, 380, _T("空格：快速下落"));
	outtextxy(20, 400, _T("esc:退出程序"));

	//画两个矩形

	//设置坐标圆点
	setorigin(220, 20);
	//绘制游戏区域  画矩形
	rectangle(-1, -1, width * unit + 1, height * unit + 1);

	//右边矩形
	rectangle((width + 1) * unit - 1, -1, (width + 6) * unit, 6 * unit);
	//开始新游戏
	NewGame();
}

//开始新游戏
void NewGame()
{
	setfillcolor(BLACK);//填充黑色  清空游戏区
	ZeroMemory(g_world, width * height);  //初始化区域把值设置为0
	//生成下一个方块
	g_nextblock.id = rand() % 7;//随机生成的第一个方块
	g_nextblock.dir = rand() % 4;//表示方块中的第几个
	g_nextblock.x = width + 1; //11
	g_nextblock.y = height - 1; //

	//画图形
	//drawblock(g_nextblock,show);
	NewBlock();
}
//画单元格
void DrawUnit(int x, int y, COLORREF co, draw _draw)
{
	//计算单元方块的位置
	int left = x * unit;  //11*20
	int right = (x + 1) * unit - 1;
	int top = (height - y/*22-(22-1)=1*/ - 1) * unit;
	int bottom = (height - y) * unit - 1;
	switch (_draw)
	{
	case show:
		setfillcolor(co);
		setlinecolor(LIGHTGRAY);
		fillrectangle(left, top, right, bottom);//用于画填充矩形（有边框)
		break;
	case clear:
		setfillcolor(BLACK);
		solidrectangle(x * unit, (height - y - 1) * unit, (x + 1) * unit - 1, (height - y) * unit - 1);
		break;
	case fix:
		setfillcolor(RGB(GetRValue(co) * 2 / 3, GetRValue(co) * 2 / 3, GetRValue(co) * 2 / 3));
		setlinecolor(DARKGRAY);
		fillrectangle(left, top, right, bottom);//用于画填充矩形（有边框)
		break;
	}
}
//画图形 整体图形
void DrawBlock(blockinfo _block, draw _draw)
{
	//word b = g_blocks[g_curblock.id].dir[g_curblock.dir];
	WORD b = g_blocks[_block.id].dir[_block.dir];
	int x, y;
	//画 16个格子中的每一个
	for (int i = 0; i < 16; i++, b <<= 1)
	{
		if (b & 0x8000)
		{
			x = _block.x + i % 4;
			y = _block.y - i / 4;
			if (y < height)
			{
				//画一个小格子
				DrawUnit(x, y, g_blocks[_block.id].color, _draw);
			}
		}
	}
}
//生成新的图形
void NewBlock()
{
	//图形的样式
	g_curblock.dir = g_nextblock.dir;
	g_nextblock.dir = rand() % 4;
	//那一个图形
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

	//画图形
	DrawBlock(g_curblock, show);
	setfillcolor(BLACK);
	solidrectangle((width + 1) * unit, 0, (width + 6) * unit - 1, 6 * unit - 1);
	DrawBlock(g_nextblock, clear);
	DrawBlock(g_nextblock, show);
}

DWORD m_oldtime = 0;   //初始化最开始的时间

//判断是否按键
cmd getcmd()
{
	while (true)
	{
		DWORD newtime = GetTickCount();  //得到现在的时间
		if (newtime - m_oldtime > 500)
		{
			m_oldtime = newtime;
			return cmd_down;
		}
		if (_kbhit())
		{ //检测是否有点击消息
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

//检测指定的方块是否可以移动
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

//右移方块
void OnRight()
{
	blockinfo temp = g_curblock;    //当前图形信息保存在temp 
	temp.x++;
	if (checkbloock(temp))
	{  //是否可以移动
		DrawBlock(g_curblock, clear);  //先察除
		g_curblock.x++;
		DrawBlock(g_curblock, show); //在显示
	}
}

//左移方块
void OnLeft()
{
	blockinfo temp = g_curblock;    //当前图形信息保存在temp 
	temp.x--;
	if (checkbloock(temp))
	{  //是否可以移动
		DrawBlock(g_curblock, clear);  //先察除
		g_curblock.x--;
		DrawBlock(g_curblock, show); //在显示
	}
}
//下落
void OnDown()
{
	blockinfo temp = g_curblock;    //当前图形信息保存在temp 
	temp.y--;
	if (checkbloock(temp))
	{  //是否可以移动
		DrawBlock(g_curblock, clear);  //先察除
		g_curblock.y--;
		DrawBlock(g_curblock, show); //在显示
	}
	else
	{
		OnSink();  //不可以下移   执行“规定方块”操作
	}
}
//  固定方块  沉底方块
void OnSink()
{
	int i, x, y;

	// 连续下移方块
	DrawBlock(g_curblock, clear);
	blockinfo tmp = g_curblock;
	tmp.y--;
	while (checkbloock(tmp))
	{
		g_curblock.y--;
		tmp.y--;
	}
	DrawBlock(g_curblock, fix);

	// 固定方块在游戏区
	WORD b = g_blocks[g_curblock.id].dir[g_curblock.dir];
	for (i = 0; i < 16; i++, b <<= 1)
		if (b & 0x8000)  //对十六个格子分别进行处理
		{
			if (g_curblock.y - i / 4 >= height)
			{	// 如果方块的固定位置超出高度，结束游戏
				GameOver();
				return;
			}
			else
				g_world[g_curblock.x + i % 4][g_curblock.y - i / 4] = 1;
		}

	// 检查是否需要消掉行，并标记
	byte remove = 0;	//  4 位用来标记方块涉及的 4 行是否有消除行为  //最多消除四行
	for (y = g_curblock.y; y >= max(g_curblock.y - 3, 0); y--)
	{
		i = 0;
		for (x = 0; x < width; x++)
			if (g_world[x][y] == 1)
				i++;

		if (i == width)
		{
			remove |= (1 << (g_curblock.y - y/*0*/));//11   100 | 10 --11 111  1111
			//第一次判断出来是1

			//标记某一行即将发生消除操作的特性
			setfillcolor(LIGHTGREEN);//浅绿色
			setlinecolor(LIGHTGREEN);
			setfillstyle(BS_HATCHED, HS_DIAGCROSS);//阴影线，水平垂直方向
			fillrectangle(0, (height - y - 1) * unit + unit / 2 - 5, width * unit - 1, (height - y - 1) * unit + unit / 2 + 5);
			setfillstyle(BS_SOLID);//实心画刷
		}
	}

	if (remove)	// 如果产生整行消除
	{
		// 延时 300 毫秒
		Sleep(300);

		// 擦掉刚才标记的行
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

	// 产生新方块
	NewBlock();
}

//旋转方块
void  OnRotate()
{
	//获取可以旋转的x的偏移量
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
	//旋转
	DrawBlock(g_curblock, clear);
	g_curblock.dir++;
	g_curblock.x += dx;
	DrawBlock(g_curblock, show);

}

//获取绘图窗口句柄
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
		//判断是否有按键
		c = getcmd();
		DispatchCMD(c);  //判断用户按的什么键
		if (c == cmd_quit)
		{  //esc
			HWND wnd = GetHWnd();//获取绘图窗口句柄
			if (MessageBox(wnd, _T("退出游戏？"), _T("提示"),
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
	HWND wnd = GetHWnd();//获取绘图窗口句柄
	if (MessageBox(wnd, _T("游戏结束\n 再来一局？"), _T("游戏结束"),
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
