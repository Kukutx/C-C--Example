#if 0
#include<iostream>
#include<windows.h>
#define MEASURE(func) do{ \
LARGE_INTEGER m_nFreq,m_nBeginTime,nEndTime;\
QueryPerformanceFrequency(&m_nFreq);\
QueryPerformanceCounter(&m_nBeginTime);\
func;\
QueryPerformanceCounter(&nEndTime);\
std::cout << (double)(nEndTime.QuadPart - m_nBeginTime.QuadPart) * 1000 / m_nFreq.QuadPart << "ms" << std::endl;\
}while(0);
template<typename T>
T sum(T&& a, T&& b) {
    return a + b;
}
void f() {
    std::cout << "faQ" << std::endl;
}
void g(int a) {
    std::cout << a << std::endl;
}
void h(int* a, double& b) {
    std::cout << *a << ' ' << b << std::endl;
}
int main() {
    LARGE_INTEGER m_nFreq, m_nBeginTime, nEndTime;
    {
        LARGE_INTEGER m_nFreq, m_nBeginTime, nEndTime; MEASURE(sum(1, 2))int c = 1;
    }
    MEASURE(f())
        MEASURE(g(1))
        int a = 2;
    double b = 5;
    MEASURE(h(&a, b));
    MEASURE(MEASURE(sum(1, 2)))
        return 0;
}
#endif // 0
