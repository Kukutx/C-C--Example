#if 0
#include <stdio.h>
#include <stdlib.h> 
#include <conio.h>
#include <time.h>
#include <graphics.h> 
//#include "resource.h"   需要音乐时添加
//#pragma comment (lib,"winmm.lib")
#define MAX 100
typedef struct { int x; int y; }PLACE;//位置
struct mySnack//蛇
{
	int num;       //记蛇体节数
	PLACE xy[MAX]; //蛇皮数组
	char direction;//方向
}snack;
PLACE foodxy;//食物位置
enum  direction { up, down, left, right };
//函数声明
char dir;//上一次方向
void init();//初始化
void food();//生成食物
void keyDown();//蛇头动向
void move();//蛇移动
void draw();//绘画蛇和食物
void eat();//蛇吃食物
void over();//游戏结束
void run();//运行
/*
//加载音乐文件的函数，需要音乐时添加
bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName)
{
	//创建文件
	HANDLE hFile = ::CreateFile(strDstFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;
	//查找资源文件中
	HRSRC hRes = ::FindResource(NULL, strResName, strResType);
	//加载资源到内存
	HGLOBAL hMem = ::LoadResource(NULL, hRes);
	// 得到资源大小
	DWORD dwsize = ::SizeofResource(NULL, hRes);
	//写入文件
	DWORD dWrite = 0;//返回写入字节
	::WriteFile(hFile, hMem, dwsize, &dWrite, NULL);
	::CloseHandle(hFile);
	return true;
}
//播放音乐
void playMusic() {
	//产生临时文件文件名
	TCHAR tmpmp3[_MAX_PATH];
	::GetTempPath(_MAX_PATH, tmpmp3);
	_tcscat(tmpmp3, _T("testapp_attheage.mp3"));
	//将MP3资源提取为临时文件
	ExtractResource(tmpmp3, _T("mp3"), MAKEINTRESOURCE(IDR_MP31));
	//打开音乐
	_TCHAR mcicmd[300];
	_stprintf(mcicmd, _T("open \"%s\" alias mymusic"), tmpmp3);
	mciSendString(mcicmd, NULL, 0, NULL);
	//播放音乐
	mciSendString(_T("play mymusic"), NULL, 0, NULL);
}
*/
int main() {
	//playMusic();
	run();
	return 0;
}
void init()
{
	//生成食物随机种子
	srand((unsigned int)time(NULL));
	initgraph(640, 480);
	//初始化蛇 食物
	for (int i = 0; i < 3; i++)
	{
		snack.xy[2 - i].x = 10 * 1;
		snack.xy[2 - i].y = 0;
	}
	snack.num = 3;
	snack.direction = right;
	food();
}
void keyDown()
{
	//确定方向
	switch (_getch())
	{
	case'w': case'W':
		if (dir != down)
			snack.direction = up; break;
	case's': case'S':
		if (dir != up)
			snack.direction = down; break;
	case'a': case'A':
		if (dir != right)
			snack.direction = left; break;
	case'd': case'D':
		if (dir != left)
			snack.direction = right; break;
	}
}
void move()
{
	//移动蛇
	for (int i = snack.num; i > 0; i--)
	{
		snack.xy[i].x = snack.xy[i - 1].x;
		snack.xy[i].y = snack.xy[i - 1].y;
	}
	switch (dir = snack.direction)
	{
	case right:snack.xy[0].x += 10; break;
	case left:snack.xy[0].x -= 10; break;
	case down:snack.xy[0].y += 10; break;
	case up:snack.xy[0].y -= 10; break;
	}
}
void draw() {
	//蛇·食物
	for (int i = 0; i < snack.num; i++)//画蛇
	{
		setlinecolor(RED);
		fillrectangle(snack.xy[i].x, snack.xy[i].y, snack.xy[i].x + 10, snack.xy[i].y + 10);
	}
	//食物
	fillrectangle(foodxy.x, foodxy.y, foodxy.x + 10, foodxy.y + 10);
}
void food()
{
	foodxy.x = rand() % 64 * 10;
	foodxy.y = rand() % 48 * 10;
	int i = 0;
	while (i < snack.num)
		if (foodxy.x == snack.xy[i++].x && foodxy.y == snack.xy[i++].y)
		{
			foodxy.x = rand() % 64 * 10;
			foodxy.y = rand() % 48 * 10;
			i = 0;
		}
}
void eat()
{
	if (snack.xy[0].x == foodxy.x && snack.xy[0].y == foodxy.y)
	{
		snack.num++;
		food();
	}
}
void over()
{
	//游戏结束
	//自食 撞墙
	if (snack.xy[0].x > 640 || snack.xy[0].x < 0 || snack.xy[0].y>480 || snack.xy[0].y < 0)
	{
		MessageBox(GetHWnd(), L"挂了", L"游戏结束", 0);
		exit(0);
	}
	for (int i = 1; i < snack.num; i++)
		if (snack.xy[0].x == snack.xy[i].x && snack.xy[0].y == snack.xy[i].y)
		{
			MessageBox(GetHWnd(), L"挂了", L"游戏结束", 0);
			exit(0);
		}
}
void run()
{
	init();
	while (1)
	{
		cleardevice();
		while (_kbhit())//无按键返回0，按键返回非0
			keyDown();
		move();
		eat();
		over();
		draw();
		Sleep(50);//移动速度
	}
}
#endif // 0
