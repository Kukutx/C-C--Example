## C++创建快捷方式(lnk、url)并添加到开始菜单、桌面、任务栏

windows快捷方式有lnk和url两种，其中lnk以打开应用程序为主，而url以打开网页链接为主。下面创建快捷方式的方法均是调用Com接口，所以一定要在调用此方法前初始化com接口(CoInitialize)。

## **创建lnk快捷方式**

```c++
#include <ShlObj.h>
/**
* 参数
*   file：需要打开的文件或应用程序
*   path：快捷方式保存的路径
*   desc：快捷方式的描述
*   work_dir：快捷方式所打开程序的工作路径
* 返回值：成功返回true，否则返回false
*/
bool CreateLnkShortcut(
const wchar_t* file,
const wchar_t* path,
const wchar_t* desc = nullptr,
const wchar_t* work_dir = nullptr) {
IShellLink* pIShellLink = nullptr;
HRESULT hRes = ::CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER,
IID_IShellLink, (void**)&pIShellLink);
if (!SUCCEEDED(hRes))
return false;
hRes = pIShellLink->SetPath(file);
if (!SUCCEEDED(hRes))
return false;
hRes = pIShellLink->SetDescription(desc);
if (!SUCCEEDED(hRes))
return false;
hRes = pIShellLink->SetWorkingDirectory(work_dir);
if (!SUCCEEDED(hRes))
return false;
IPersistFile* pIPersistFile = nullptr;
hRes = pIShellLink->QueryInterface(IID_IPersistFile, (void**)&pIPersistFile);
if (!SUCCEEDED(hRes))
return false;
hRes = pIPersistFile->Save(path, TRUE);
if (!SUCCEEDED(hRes))
return false;
pIPersistFile->Release();
pIShellLink->Release();
return true;
}
```

## 创建**url快捷方式**

```cpp
#include <IntShCut.h>
#include <propvarutil.h>
/**
* 参数
*   url：网页地址
*   path：快捷方式保存的路径
*   icon_file：快捷方式的图标文件
*   icon_index：快捷方式的图标索引,默认为第一个图标(0)
* 返回值：成功返回true，否则返回false
*/
bool CreateUrlShortcut(
const wchar_t* url,
const wchar_t* path,
const wchar_t* icon_file = L"",
const int icon_index = 0) {
IUniformResourceLocatorW* pIInternetLink = nullptr;
HRESULT hRes = ::CoCreateInstance(CLSID_InternetShortcut, nullptr, CLSCTX_INPROC_SERVER,
IID_IUniformResourceLocatorW, (void**)&pIInternetLink);
if (!SUCCEEDED(hRes))
return false;
hRes = pIInternetLink->SetURL(url, IURL_SETURL_FL_GUESS_PROTOCOL);
if (!SUCCEEDED(hRes))
return false;
IPropertySetStorage* pss = nullptr;
hRes = pIInternetLink->QueryInterface(IID_IPropertySetStorage, (void**)&pss);
if (SUCCEEDED(hRes)) {
IPropertyStorage *ps = nullptr;
hRes = pss->Open(FMTID_Intshcut, STGM_WRITE, &ps);
if (SUCCEEDED(hRes)) {
// 设置两个属性，一个图标文件路径，一个图标索引
PROPSPEC pids[2] = { { PRSPEC_PROPID, PID_IS_ICONFILE },{ PRSPEC_PROPID, PID_IS_ICONINDEX } };
PROPVARIANT pvar[2] = { 0 };
// 图标文件
::InitPropVariantFromString(icon_file, &pvar[0]);
// 图标索引,默认0
::InitPropVariantFromInt16(icon_index, &pvar[1]);
ULONG n = sizeof(pids) / sizeof(pids[0]);
ps->WriteMultiple(n, pids, pvar, 0);
ps->Commit(STGC_DEFAULT);
ps->Release();
::PropVariantClear(&pvar[0]);
::PropVariantClear(&pvar[1]);
}
pss->Release();
}
IPersistFile *pf = nullptr;
hRes = pIInternetLink->QueryInterface(IID_IPersistFile, (void**)&pf);
if (SUCCEEDED(hRes)) {
pf->Save(path, TRUE);
pf->Release();
}
pIInternetLink->Release();
return true;
}
```

## 将快捷方式添加到桌面(桌面快捷方式)

要创建桌面快捷方式，其实就是创建一个快捷方式并且将之放到桌面即可。调用SHGetSpecialFolderPath接口传入CSIDL_DESKTOPDIRECTORY即可获取到当前用户的桌面路径，有时候需要放到所有用户的桌面 CSIDL_COMMON_DESKTOPDIRECTORY ，但是一般需要管理员权限。

```cpp
void main() {
::CoInitialize(NULL);
wchar_t desk_path[MAX_PATH] = { 0 };
::SHGetSpecialFolderPath(NULL, (LPWSTR)desk_path, CSIDL_DESKTOPDIRECTORY, FALSE);
wchar_t lnk_path[MAX_PATH] = { 0 };
::PathAppend(lnk_path, desk_path);
::PathAppend(lnk_path, L"记事本.lnk");
CreateLnkShortcut(L"C:\\Windows\\system32\\notepad.exe", lnk_path);
wchar_t url_path[MAX_PATH] = { 0 };
::PathAppend(url_path, desk_path);
::PathAppend(url_path, L"百度.url");
CreateUrlShortcut(L"https://www.baidu.com", url_path);
::CoUninitialize();
}
```

## **将快捷方式添加到开始菜单**

和添加到桌面并无不同，唯一需要修改的地方就是把桌面路径改为开始菜单路径即可，也就是SHGetSpecialFolderPath中将CSIDL_DESKTOPDIRECTORY改为CSIDL_PROGRAMS，CSIDL_COMMON_PROGRAMS使用所有用户的开始菜单目录，这个目录一般也需要管理员权限才能写入。

```CPP
void main() {
::CoInitialize(NULL);
wchar_t programs_path[MAX_PATH] = { 0 };
::SHGetSpecialFolderPath(NULL, (LPWSTR)programs_path, CSIDL_PROGRAMS, FALSE);
wchar_t lnk_path[MAX_PATH] = { 0 };
::PathAppend(lnk_path, programs_path);
::PathAppend(lnk_path, L"记事本.lnk");
CreateLnkShortcut(L"C:\\Windows\\system32\\notepad.exe", lnk_path);
wchar_t url_path[MAX_PATH] = { 0 };
::PathAppend(url_path, programs_path);
::PathAppend(url_path, L"百度.url");
CreateUrlShortcut(L"https://www.baidu.com", url_path);
::CoUninitialize();
}
```

## **将快捷方式添加到任务栏：**

调用ShellExecute(NULL, L”taskbarpin”, linkPath, NULL, NULL, 0); // linkPath则是快捷方式文件的路径，但是这个方法在win10已经被禁止了。关于固定到任务栏可以参考本站文章[c++ windows固定到任务栏(应用程序或快捷方式)](https://www.xuwenyan.com/archives/2299)。