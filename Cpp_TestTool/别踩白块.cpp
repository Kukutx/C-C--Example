#if 0
#include <stdio.h>
#include <stdlib.h> 
#include <easyx.h>
#include <tchar.h>//宽字节头文件，占两个字节的字符的头文件
#include <time.h>//时间头文件
#include <graphics.h>
#pragma warning(disable : 4996)
/* 需要音乐时添加
#pragma comment (lib,"winmm.lib")
#include "resource.h"
//加载音乐文件的函数
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
	//音乐文件文件里的
	//mciSendString(L"open Horizon.mp3",0,0,0);
	//mciSendString(L"play Horizon.mp3", 0, 0, 0);

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
int map[4];//地图，存黑色方块的位置
int n;     //记录所消除的黑色方块的数量
void init() {
	for (int i = 0; i < 4; i++)
	{
		map[i] = rand() % 4;//随机函数
	}
	n = 0;//初始化黑方块消除数量
}
void drawmap() {
	BeginBatchDraw();//批量绘图
	cleardevice();   //清屏
	//绘制白方块背景
	setlinecolor(RGB(0, 0, 255));//设置线条蓝色
	setfillcolor(RGB(255, 255, 255));//设置填充颜色白色
	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++)
		{
			//画矩形框的函数（左上角x坐标，左上角y坐标，右下角x坐标，右下角y坐标）
			fillrectangle(x * 100, y * 120, (x + 1) * 100, (y + 1) * 120);
		}
	//绘制黑色方块
	setfillcolor(RGB(0, 0, 0));//设置填充颜色黑色
	for (int i = 0; i < 4; i++) {
		//画矩形框的函数（左上角x坐标，左上角y坐标，右下角x坐标，右下角y坐标）
		fillrectangle(map[i] * 100, i * 120, (map[i] + 1) * 100, (i + 1) * 120);
	}
	EndBatchDraw();//结束批量绘图
}
int i;
int j;
bool play()//开始玩函数，c++的新类型，其有两个值，一个为真一个为加假
{
	MOUSEMSG msg = GetMouseMsg();//获取鼠标消息
	switch (msg.uMsg)
	{
	case WM_LBUTTONDOWN:
		i = msg.y / 120;
		j = msg.x / 100;
		if (3 == i && map[3] == j)
		{
			for (int m = 3; m > 0; m--)
			{
				map[m] = map[m - 1]; // 点击最后一行的黑方块，前几行的黑方块的位置下移，覆盖最后一行
			}
			map[0] = rand() % 4;//随机给第一行黑方块的位置
			n++;//消除黑方块的数量加一
		}
		else
			return false;//点到错位方块返回假
		break;
	}
	return true;//点到正确的黑方块就返回真
}
int main() {
	//playMusic();  //需要音乐时添加

	initgraph(4 * 100, 4 * 120);
	srand((unsigned)time(NULL));//随机种子
	init();
	while (1)
	{
		drawmap();
		if (false == play())
		{
			TCHAR str[60];//TCHAR为宽字节的字符类型，也就是占两个字节的字符型
			swprintf(str, _T("总共消除了%d个黑方块"), n);//保存游戏结束的文本信息
			MessageBox(GetHWnd(), str, _T("游戏结束"), MB_OK);//弹窗
			break;
		}
	}
	closegraph();
	return 0;
}


#endif // 0
