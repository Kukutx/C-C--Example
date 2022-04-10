// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

extern "C" __declspec(dllexport)
void fun()
{
	MessageBox(NULL, L"你加载的是我注入的dll", L"提示", MB_OK);
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

