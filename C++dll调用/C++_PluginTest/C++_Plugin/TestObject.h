#pragma once
#ifndef TESTPLUGIN1_EXPORTS
#define TESTPLUGIN1_EXPORTS
#include "../PluginInterface/Object.h"
#include <iostream>

// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� TESTPLUGIN1_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// TESTPLUGIN1_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef TESTPLUGIN1_EXPORTS
#define TESTPLUGIN1_API __declspec(dllexport)   // �������� - ����dll�ļ�ʱʹ��
#else
#define TESTPLUGIN1_API __declspec(dllimport)   // ���뺯�� -ʹ��dll��ʹ��
#endif //TESTPLUGIN1_EXPORTS

/****************************************************************/

class TESTPLUGIN1_API TestObject:public Object
{
public:
    TestObject() = default;
    ~TestObject() = default;
    int ntestPlugin1 = 0;
    virtual int Dump();
    // TODO:  �ڴ�������ķ�����
};

extern "C" {
    TESTPLUGIN1_API int add(int a, int b);
    TESTPLUGIN1_API int sub(int a, int b);
    TESTPLUGIN1_API int fntestPlugin1(); 
    TESTPLUGIN1_API void* Instance();
}          

#endif


