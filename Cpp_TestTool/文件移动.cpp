#if 0
#include <windows.h>
#include <Shobjidl.h>
#include <iostream>
#include <cassert>
#include <cstring>
#include <atlstr.h>
#include<securitybaseapi.h> 
#pragma comment(lib,"Advapi32.lib")
#pragma warning(disable : 4996)
using namespace std;

//判断管理员权限
bool IsAdmin()
{
    BOOL b;
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    PSID AdministratorsGroup;
    b = AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &AdministratorsGroup);
    if (b)
    {
        if (!CheckTokenMembership(NULL, AdministratorsGroup, &b))
        {
            b = FALSE;
        }
        FreeSid(AdministratorsGroup);
    }

    return(b);
}

//判断系统版本是否是win7以上
bool IsAboveVistaVersion()
{
    OSVERSIONINFOEX WinVersion;
    ZeroMemory(&WinVersion, sizeof(OSVERSIONINFOEX));
    WinVersion.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    BOOL flag = (BOOL)GetVersionEx((OSVERSIONINFO*)&WinVersion);
    assert(flag);

    if (WinVersion.dwMajorVersion < 6)
        return false;

    if (WinVersion.dwMajorVersion == 6 && WinVersion.dwMinorVersion == 1)
        return false;

    if (WinVersion.dwMajorVersion == 6 && WinVersion.dwMinorVersion >= 2)
        return true;

    if (WinVersion.dwMajorVersion > 6)
        return true;

    return true;
}

HRESULT Movefile(__in PCWSTR pszSrcItem, __in PCWSTR pszDest, PCWSTR pszNewName)
{
    //
    // Initialize COM as STA.
    //
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr))
    {
        IFileOperation* pfo;

        //
        // Create the IFileOperation interface
        //
        hr = CoCreateInstance(CLSID_FileOperation,
            NULL,
            CLSCTX_ALL,
            IID_PPV_ARGS(&pfo));
        if (SUCCEEDED(hr))
        {
            // Set the operation flags. Turn off all UI from being shown to the
            // user during the operation. This includes error, confirmation,
            // and progress dialogs.
            hr = pfo->SetOperationFlags(FOF_NO_UI);
            if (SUCCEEDED(hr))
            {
                // Create an IShellItem from the supplied source path.
                IShellItem* psiFrom = NULL;
                hr = SHCreateItemFromParsingName(pszSrcItem,
                    NULL,
                    IID_PPV_ARGS(&psiFrom));
                if (SUCCEEDED(hr))
                {
                    IShellItem* psiTo = NULL;
                    if (NULL != pszDest)
                    {
                        // Create an IShellItem from the supplied
                        // destination path.
                        hr = SHCreateItemFromParsingName(pszDest,
                            NULL,
                            IID_PPV_ARGS(&psiTo));
                    }

                    if (SUCCEEDED(hr))
                    {
                        // Add the operation
                        hr = pfo->MoveItem(psiFrom, psiTo, pszNewName, NULL);
                        if (NULL != psiTo)
                        {
                            psiTo->Release();
                        }
                    }
                    psiFrom->Release();
                }

                if (SUCCEEDED(hr))
                {
                    // Perform the operation to copy the file.
                    hr = pfo->PerformOperations();
                }
            }
            // Release the IFileOperation interface.
            pfo->Release();
        }

        CoUninitialize();
    }
    return hr;
}

int main()
{
    //cout<<Movefile(L"C:\\Users\\liuzh\\Downloads\\MoveFile\\Test\\test.exe", L"C:\\Windows\\zh-CN\\", NULL);

    //参数一：源文件，参数二：目标文件，参数三：//false代表覆盖，true不覆盖
    cout << CopyFile(L"C:\\Users\\liuzh\\Downloads\\MoveFile\\Test\\test.exe", L"C:\\Windows\\zh-CN\\jb.exe", FALSE);
    system("pause");
    return 0;
}
#endif // 0
