#include<wtypes.h>   
#include <winbase.h>   
#include <iostream>
#include "../PluginInterface/Object.h"

typedef Object* Instance();

int main()
{
    HINSTANCE hDLL;
    hDLL = LoadLibrary(L"C++_Plugin.dll");  //加载 DLL文件  
    if (hDLL == NULL)
        std::cout << "Error!!! Can not find plugin\n";
    Instance* GetInstance = (Instance*)GetProcAddress(hDLL, "Instance");  //取DLL中的函数地址，以备调用  
   //Instance *GetInstance = (Instance *)dlsym(handle, "Instance");


    if (!GetInstance)
    {
        std::cout << "Error Instance function" << std::endl;
    }
    else
    {
        Object* obj = GetInstance();
        if (0 != obj)
        {
            obj->Dump();
        }
        delete obj;
    }
    FreeLibrary(hDLL);
    getchar();
    return 0;
}