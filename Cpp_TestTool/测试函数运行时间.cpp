#if 0
#include<iostream>
#include<ctime>
using namespace std;
#define N 1000.0
clock_t Begin, End;
void Fun(int n)
{
	int i = 0;
	for (i = 0; i < n; i++)
	{
		cout << i << endl;
	}
}
int main()
{
	/*
	1��ͷ�ļ�ctime�����ṩ��һ������:  clock_t clock();
	 �ú������ص��Ǵӳ���ʼ���е�����clock����ʱ����ĵ���,��clock tick(ʱ�Ӵ��);
	2����һ������CLK_TCK,�ǻ���ʱ��ÿ�����ߵ�ʱ�Ӵ����������������
	  �ģ�#define CLK_TCK  CLOCKS_PER_SEC   # define CLOCKS_PER_SEC 1000
	3�� ���ԣ���������clock�ı���Begin,End;Ȼ����Ҫ���Եĺ���ǰ��ֱ��
	  ��clock�����Ϳ��Եó�ʱ�Ӵ�������ٳ���CLK_TCK�͵õ�ʱ����
	*/
	Begin = clock();
	Fun(100);
	End = clock();
	double duration = double((End - Begin) / N);
	cout << "tick:" << End - Begin << endl;
	cout << CLK_TCK << endl;
	cout << "duration:" << fixed << duration << endl;
	return 0;
}
#endif // 0

