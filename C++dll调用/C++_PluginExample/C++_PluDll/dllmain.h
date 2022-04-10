#pragma once
#ifndef __MAIN_HPP_INCLUDED__
#define __MAIN_HPP_INCLUDED__

#define BUILD_DLL

#include <memory>
#include <string>
#include "../common/base.h"

#ifdef BUILD_DLL
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI __declspec(dllimport)
#endif // BUILD_DLL

// DLL导出函数
/* 为了让应用程序动态加载插件，需要将插件编译为dll文件。在dllmain.h中，插件声明两个导出函数：
   - getObj：用于新建一个Test1对象并返回该对象的指针；
   - getName：用于打印Test1相关信息
*/
#ifdef __cplusplus
extern "C" {
#endif

    DLLAPI Base* getObj(void);
    DLLAPI const char* getName(void);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_HPP_INCLUDED__
