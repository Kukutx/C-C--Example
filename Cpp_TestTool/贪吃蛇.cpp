#if 0
#include <stdio.h>
#include <stdlib.h> 
#include <conio.h>
#include <time.h>
#include <graphics.h> 
//#include "resource.h"   ��Ҫ����ʱ���
//#pragma comment (lib,"winmm.lib")
#define MAX 100
typedef struct { int x; int y; }PLACE;//λ��
struct mySnack//��
{
	int num;       //���������
	PLACE xy[MAX]; //��Ƥ����
	char direction;//����
}snack;
PLACE foodxy;//ʳ��λ��
enum  direction { up, down, left, right };
//��������
char dir;//��һ�η���
void init();//��ʼ��
void food();//����ʳ��
void keyDown();//��ͷ����
void move();//���ƶ�
void draw();//�滭�ߺ�ʳ��
void eat();//�߳�ʳ��
void over();//��Ϸ����
void run();//����
/*
//���������ļ��ĺ�������Ҫ����ʱ���
bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName)
{
	//�����ļ�
	HANDLE hFile = ::CreateFile(strDstFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;
	//������Դ�ļ���
	HRSRC hRes = ::FindResource(NULL, strResName, strResType);
	//������Դ���ڴ�
	HGLOBAL hMem = ::LoadResource(NULL, hRes);
	// �õ���Դ��С
	DWORD dwsize = ::SizeofResource(NULL, hRes);
	//д���ļ�
	DWORD dWrite = 0;//����д���ֽ�
	::WriteFile(hFile, hMem, dwsize, &dWrite, NULL);
	::CloseHandle(hFile);
	return true;
}
//��������
void playMusic() {
	//������ʱ�ļ��ļ���
	TCHAR tmpmp3[_MAX_PATH];
	::GetTempPath(_MAX_PATH, tmpmp3);
	_tcscat(tmpmp3, _T("testapp_attheage.mp3"));
	//��MP3��Դ��ȡΪ��ʱ�ļ�
	ExtractResource(tmpmp3, _T("mp3"), MAKEINTRESOURCE(IDR_MP31));
	//������
	_TCHAR mcicmd[300];
	_stprintf(mcicmd, _T("open \"%s\" alias mymusic"), tmpmp3);
	mciSendString(mcicmd, NULL, 0, NULL);
	//��������
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
	//����ʳ���������
	srand((unsigned int)time(NULL));
	initgraph(640, 480);
	//��ʼ���� ʳ��
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
	//ȷ������
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
	//�ƶ���
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
	//�ߡ�ʳ��
	for (int i = 0; i < snack.num; i++)//����
	{
		setlinecolor(RED);
		fillrectangle(snack.xy[i].x, snack.xy[i].y, snack.xy[i].x + 10, snack.xy[i].y + 10);
	}
	//ʳ��
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
	//��Ϸ����
	//��ʳ ײǽ
	if (snack.xy[0].x > 640 || snack.xy[0].x < 0 || snack.xy[0].y>480 || snack.xy[0].y < 0)
	{
		MessageBox(GetHWnd(), L"����", L"��Ϸ����", 0);
		exit(0);
	}
	for (int i = 1; i < snack.num; i++)
		if (snack.xy[0].x == snack.xy[i].x && snack.xy[0].y == snack.xy[i].y)
		{
			MessageBox(GetHWnd(), L"����", L"��Ϸ����", 0);
			exit(0);
		}
}
void run()
{
	init();
	while (1)
	{
		cleardevice();
		while (_kbhit())//�ް�������0���������ط�0
			keyDown();
		move();
		eat();
		over();
		draw();
		Sleep(50);//�ƶ��ٶ�
	}
}
#endif // 0
