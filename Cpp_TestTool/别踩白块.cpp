#if 0
#include <stdio.h>
#include <stdlib.h> 
#include <easyx.h>
#include <tchar.h>//���ֽ�ͷ�ļ���ռ�����ֽڵ��ַ���ͷ�ļ�
#include <time.h>//ʱ��ͷ�ļ�
#include <graphics.h>
#pragma warning(disable : 4996)
/* ��Ҫ����ʱ���
#pragma comment (lib,"winmm.lib")
#include "resource.h"
//���������ļ��ĺ���
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
	//�����ļ��ļ����
	//mciSendString(L"open Horizon.mp3",0,0,0);
	//mciSendString(L"play Horizon.mp3", 0, 0, 0);

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
int map[4];//��ͼ�����ɫ�����λ��
int n;     //��¼�������ĺ�ɫ���������
void init() {
	for (int i = 0; i < 4; i++)
	{
		map[i] = rand() % 4;//�������
	}
	n = 0;//��ʼ���ڷ�����������
}
void drawmap() {
	BeginBatchDraw();//������ͼ
	cleardevice();   //����
	//���ư׷��鱳��
	setlinecolor(RGB(0, 0, 255));//����������ɫ
	setfillcolor(RGB(255, 255, 255));//���������ɫ��ɫ
	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++)
		{
			//�����ο�ĺ��������Ͻ�x���꣬���Ͻ�y���꣬���½�x���꣬���½�y���꣩
			fillrectangle(x * 100, y * 120, (x + 1) * 100, (y + 1) * 120);
		}
	//���ƺ�ɫ����
	setfillcolor(RGB(0, 0, 0));//���������ɫ��ɫ
	for (int i = 0; i < 4; i++) {
		//�����ο�ĺ��������Ͻ�x���꣬���Ͻ�y���꣬���½�x���꣬���½�y���꣩
		fillrectangle(map[i] * 100, i * 120, (map[i] + 1) * 100, (i + 1) * 120);
	}
	EndBatchDraw();//����������ͼ
}
int i;
int j;
bool play()//��ʼ�溯����c++�������ͣ���������ֵ��һ��Ϊ��һ��Ϊ�Ӽ�
{
	MOUSEMSG msg = GetMouseMsg();//��ȡ�����Ϣ
	switch (msg.uMsg)
	{
	case WM_LBUTTONDOWN:
		i = msg.y / 120;
		j = msg.x / 100;
		if (3 == i && map[3] == j)
		{
			for (int m = 3; m > 0; m--)
			{
				map[m] = map[m - 1]; // ������һ�еĺڷ��飬ǰ���еĺڷ����λ�����ƣ��������һ��
			}
			map[0] = rand() % 4;//�������һ�кڷ����λ��
			n++;//�����ڷ����������һ
		}
		else
			return false;//�㵽��λ���鷵�ؼ�
		break;
	}
	return true;//�㵽��ȷ�ĺڷ���ͷ�����
}
int main() {
	//playMusic();  //��Ҫ����ʱ���

	initgraph(4 * 100, 4 * 120);
	srand((unsigned)time(NULL));//�������
	init();
	while (1)
	{
		drawmap();
		if (false == play())
		{
			TCHAR str[60];//TCHARΪ���ֽڵ��ַ����ͣ�Ҳ����ռ�����ֽڵ��ַ���
			swprintf(str, _T("�ܹ�������%d���ڷ���"), n);//������Ϸ�������ı���Ϣ
			MessageBox(GetHWnd(), str, _T("��Ϸ����"), MB_OK);//����
			break;
		}
	}
	closegraph();
	return 0;
}


#endif // 0
