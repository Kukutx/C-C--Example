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

// DLL��������
/* Ϊ����Ӧ�ó���̬���ز������Ҫ���������Ϊdll�ļ�����dllmain.h�У����������������������
   - getObj�������½�һ��Test1���󲢷��ظö����ָ�룻
   - getName�����ڴ�ӡTest1�����Ϣ
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
