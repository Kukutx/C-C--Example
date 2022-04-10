#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <exception>
#include <windows.h>

#include "my_exception.h"
#include "../common/base.h"

// 功能：加载plugins目录中的所有dll插件
// 参数：modules用于保存所有dll文件句柄，所有句柄最后会在main函数中被FreeLibrary()函数释放
// 返回：
std::vector<Base*> getPlugins(std::vector<HINSTANCE>& modules) {
    std::vector<Base*> ret;
    modules.clear();

    // 在plugins目录中查找dll文件并将文件信息保存在fileData中
    WIN32_FIND_DATA fileData;
    HANDLE fileHandle = FindFirstFile(L"plugins/*.dll", &fileData);

    if (fileHandle == (void*)ERROR_INVALID_HANDLE ||
        fileHandle == (void*)ERROR_FILE_NOT_FOUND) {
        // 没有找到任何dll文件，返回空vector
        return std::vector<Base*>();
    }

    // 循环加载plugins目录中的所有dll文件
    do {
        typedef Base* (__cdecl* ObjProc)(void);
        typedef const char* (__cdecl* NameProc)(void);

        // 将dll加载到当前进程的地址空间中
        HINSTANCE mod = LoadLibrary((L"./plugins/" + std::wstring(fileData.cFileName)).c_str());

        if (!mod) {
            // 加载dll失败，则释放所有已加载dll
            for (HINSTANCE hInst : modules)
                FreeLibrary(hInst);
            throw MyException(L"Library " + std::wstring(fileData.cFileName) + L" wasn't loaded successfully!");
        }
        // 从dll句柄中获取getObj和getName的函数地址
        ObjProc objFunc = (ObjProc)GetProcAddress(mod, "getObj");
        NameProc nameFunc = (NameProc)GetProcAddress(mod, "getName");

        if (!objFunc || !nameFunc)
            throw std::runtime_error("Invalid Plugin DLL: both 'getObj' and 'getName' must be defined.");

        ret.push_back(objFunc());  // 保存objFunc（即getObj）生成的对象指针
        modules.push_back(mod);  // 保存dll句柄

        std::clog << nameFunc() << " loaded!\n";
    } while (FindNextFile(fileHandle, &fileData));

    std::clog << std::endl;

    // 关闭文件句柄
    FindClose(fileHandle);
    return ret;
}

int main() {
    std::vector<HINSTANCE> modules;

    {
        std::vector<Base*> objs;

        // 加载插件
        try {
            objs = getPlugins(modules);
        }
        catch (const std::exception& e) {
            for (auto& x : objs) {
                delete x;
            }
            std::cerr << "Exception caught: " << e.what() << std::endl;
            return 1;
        }

        // 调用插件中对Base接口的实现
        for (auto& x : objs) {
            x->print();
            std::cout << "\t" << x->calc(10) << std::endl;
        }
        for (auto& x : objs) {
            delete x;
        }
    }

    // 释放所有dll
    for (HINSTANCE hInst : modules)
        FreeLibrary(hInst);
    system("pause");
    return 0;
}
