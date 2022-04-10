#if 0
#include<iostream>
#include<ctime>
using namespace std;
#define CLK 1000.0

//时间
void t1()
{
	time_t start = time(nullptr);       //获取当前时间
	cout << start << endl;
	for (size_t i = 0; i < INT_MAX; i++);;
	time_t end;
	time(&end);     //第二种获取方式
	cout << end << endl;
	cout << "时间差:" << difftime(end, start) << "m" << endl;
}
//计时器
void t2()
{
	clock_t start = clock();        //毫秒级别的
	cout << start << endl;
	for (size_t i = 0; i < INT_MAX; i++);;
	clock_t end = clock();
	cout << "花费时间" << end - start << "ms" << endl;
}
//日期
void t3()
{
	tm date;        //日期结构体
	time_t t = time(nullptr);
	localtime_s(&date, &t);
	cout << "当前时间:"
		<< date.tm_year + 1900 << "年"
		<< date.tm_mon + 1 << "月"
		<< date.tm_mday << "日"
		<< date.tm_hour << "时"
		<< date.tm_min << "分"
		<< date.tm_sec << "秒"
		<< endl;
}

void test()
{
	t1();
	t2();
	t3();
}

//clock_t startTime = clock();
int main()
{
    clock_t startTime = clock();
    int arr[100000];
    for (int i = 0; i < 100000; i++)
        arr[i] = i;
    for (int i = 0; i < 99999; i++)
        swap(arr[i], arr[i + 1]);
    //getchar();
    clock_t endTime = clock();
    double duration = double((endTime - startTime) / CLK);
    cout << "整个程序用时：" << fixed << duration << " s" << endl;
	test();
    system("pause");
    return 0;
}
#endif // 0


