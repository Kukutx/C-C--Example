// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include <iostream>
#include <cmath>
#include <windows.h>
#include "dllmain.h"
#include "test1.h"

extern "C" Base * getObj(void) {
    return new Test1;
}

extern "C" const char* getName(void) {
    return "Test1:Maths";
}

extern "C" DLLAPI BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        // attach to process
        // return FALSE to fail DLL load
        break;

    case DLL_PROCESS_DETACH:
        // detach from process
        break;

    case DLL_THREAD_ATTACH:
        // attach to thread
        break;

    case DLL_THREAD_DETACH:
        // detach from thread
        break;
    }
    return TRUE; // succesful
}
