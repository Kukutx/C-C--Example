#if 0
#include<iostream>
#include<ctime>
using namespace std;
#define CLK 1000.0

//ʱ��
void t1()
{
	time_t start = time(nullptr);       //��ȡ��ǰʱ��
	cout << start << endl;
	for (size_t i = 0; i < INT_MAX; i++);;
	time_t end;
	time(&end);     //�ڶ��ֻ�ȡ��ʽ
	cout << end << endl;
	cout << "ʱ���:" << difftime(end, start) << "m" << endl;
}
//��ʱ��
void t2()
{
	clock_t start = clock();        //���뼶���
	cout << start << endl;
	for (size_t i = 0; i < INT_MAX; i++);;
	clock_t end = clock();
	cout << "����ʱ��" << end - start << "ms" << endl;
}
//����
void t3()
{
	tm date;        //���ڽṹ��
	time_t t = time(nullptr);
	localtime_s(&date, &t);
	cout << "��ǰʱ��:"
		<< date.tm_year + 1900 << "��"
		<< date.tm_mon + 1 << "��"
		<< date.tm_mday << "��"
		<< date.tm_hour << "ʱ"
		<< date.tm_min << "��"
		<< date.tm_sec << "��"
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
    cout << "����������ʱ��" << fixed << duration << " s" << endl;
	test();
    system("pause");
    return 0;
}
#endif // 0


