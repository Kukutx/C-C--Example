// dlltest.h   头文件，使用动态链接库时需要包含头文件

#pragma once
#ifdef __DLLEXPORT
#define __DLL_EXP _declspec(dllexport)    // 导出函数 - 生成dll文件时使用
#else
#define __DLL_EXP _declspec(dllimport)    // 导入函数 -使用dll是使用
#endif // __DLLEXPORT

// 判断是否是c++
#if defined(__cplusplus)||defined(c_plusplus)
extern "C"
{
#endif
    __DLL_EXP int add(int a, int b);
    __DLL_EXP int sub(int a, int b);

#if defined(__cplusplus)||defined(c_plusplus)
}
#endif