#pragma once
#ifndef TESTPLUGIN1_EXPORTS
#define TESTPLUGIN1_EXPORTS
#include "../PluginInterface/Object.h"
#include <iostream>

// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 TESTPLUGIN1_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// TESTPLUGIN1_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef TESTPLUGIN1_EXPORTS
#define TESTPLUGIN1_API __declspec(dllexport)   // 导出函数 - 生成dll文件时使用
#else
#define TESTPLUGIN1_API __declspec(dllimport)   // 导入函数 -使用dll是使用
#endif //TESTPLUGIN1_EXPORTS

/****************************************************************/

class TESTPLUGIN1_API TestObject:public Object
{
public:
    TestObject() = default;
    ~TestObject() = default;
    int ntestPlugin1 = 0;
    virtual int Dump();
    // TODO:  在此添加您的方法。
};

extern "C" {
    TESTPLUGIN1_API int add(int a, int b);
    TESTPLUGIN1_API int sub(int a, int b);
    TESTPLUGIN1_API int fntestPlugin1(); 
    TESTPLUGIN1_API void* Instance();
}          

#endif


