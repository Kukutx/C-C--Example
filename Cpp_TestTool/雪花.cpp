#if 0
#include <easyx.h>
#include <cstdlib>
int wid = 600;        //ͼ�δ��ڴ�С
void drawCircle(int x, int y, int r, int step, int depth)
{
	if (r < 1)
		return;
	COLORREF color = RGB(rand() % 255, rand() % 255, rand() % 255);
	setlinecolor(color);
	circle(x, y, r);
	drawCircle(x, y, r - step, step, depth + 1);
}
void drawSnow(int x, int y, float w, int depth, int step)
{
	//�ݹ����������
	if (w <= 1 || depth >= step)
	{
		setfillcolor(RGB(24, 212, 250));
		setlinecolor(RGB(0x00, 0xff, 0xff));
		w = max(w, 1);
		fillrectangle(x, y, x + w, y + w);
		return;
	}
	float p = w / 3;          //���������εķֳɿ�Ĵ�С
	//x+p��ʾ���Ƶ�����λ���ڵڶ���������
	drawSnow(x + p, y, p, depth + 1, step);            //{0,1}
	drawSnow(x, y + p, p, depth + 1, step);            //{1,0}
	drawSnow(x + p, y + p, p, depth + 1, step);        //{1,1}
	drawSnow(x + p * 2, y + p, p, depth + 1, step);    //{1,2}
	drawSnow(x + p, y + p * 2, p, depth + 1, step);    //{2,1}
}
void test1()
{
	drawCircle(wid / 2, wid / 2, wid / 2, 1, 1);
	std::system("pause");
}
void test2()
{
	int step = 0;
	while (step < 7)
	{
		BeginBatchDraw();
		cleardevice();
		drawSnow(0, 0, wid, 0, step++);
		EndBatchDraw();
		std::system("pause");
	}
}

int main()
{
	//���ո���Ч
	initgraph(wid, wid);
	//test1();
	test2();
	return 0;
}
#endif // 0







