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
	1）头文件ctime里面提供了一个函数:  clock_t clock();
	 该函数返回的是从程序开始运行到调用clock函数时所打的点数,即clock tick(时钟打点);
	2）有一个常数CLK_TCK,是机器时钟每秒所走的时钟打点数，是这样定义
	  的，#define CLK_TCK  CLOCKS_PER_SEC   # define CLOCKS_PER_SEC 1000
	3） 所以，定义两个clock的变量Begin,End;然后在要测试的函数前后分别调
	  用clock函数就可以得出时钟打点数，再除以CLK_TCK就得到时间了
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

