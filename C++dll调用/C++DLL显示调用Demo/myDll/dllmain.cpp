#ifdef __cplusplus         // 一般用于将C++代码以标准C形式输出（即以C的形式被调用）
extern"C" {                 // 告诉编译器下面大括号括起来的函数是c语言函数（因为c++和c语言对函数的编译转换不一样，主要是c++中存在重载）
#endif

	__declspec(dllexport) double __stdcall  seekArea(int a, int b);      // __declspec(dllexport)声明导出该函数供外部调用

	__declspec(dllexport) int __stdcall  add(int a, int b); // __stdcall是Windows API默认的函数调用协议，函数采用从右到左的压栈方式，自己在退出时清空堆栈，也可以不使用

#ifdef __cplusplus
}
#endif

double __stdcall seekArea(int a, int b)
{
	return a + b;
}

int __stdcall add(int a, int b)
{
	return a + b;
}
