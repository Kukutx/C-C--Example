#if 0
#include <stdio.h>  
#include <windows.h>  
#include <tchar.h>  
#include <TlHelp32.h>  
#include <Psapi.h>  

#pragma comment(lib, "psapi.lib")   
/// <summary>
/// 遍历进程&线程程序
/// </summary>
/// <returns></returns>
int test() {
    // 为进程的所有线程拍个快照  
    HANDLE hSnapshort = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshort == INVALID_HANDLE_VALUE)
    {
        printf("CreateToolhelp32Snapshot调用失败！\n");
        return -1;
    }

    // 获得线程列表，里面记录了线程的详细信息，再使用Thread32First和Thread32Next遍历快照中记录的每个线程信息  
    PROCESSENTRY32 stcProcessInfo;
    stcProcessInfo.dwSize = sizeof(stcProcessInfo);

    BOOL  bRet = Process32First(hSnapshort, &stcProcessInfo);

    printf("进程名\t\t\t 进程ID\t 线程数\t 父进程ID\n");

    while (bRet)
    {
        printf("%ls\t\t %d\t %d\t %d\n", stcProcessInfo.szExeFile, stcProcessInfo.th32ProcessID, stcProcessInfo.cntThreads, stcProcessInfo.th32ParentProcessID);

        bRet = Process32Next(hSnapshort, &stcProcessInfo);
    }
    CloseHandle(hSnapshort);
}

int test2() {
    // 为进程的所有线程拍个快照  
    HANDLE hSnapshort = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hSnapshort == INVALID_HANDLE_VALUE)
    {
        printf("CreateToolhelp32Snapshot调用失败！\n");
        return -1;
    }

    // 获得线程列表，里面记录了线程的详细信息，再使用Thread32First和Thread32Next遍历快照中记录的每个线程信息  
    THREADENTRY32 stcThreadInfo;
    stcThreadInfo.dwSize = sizeof(stcThreadInfo);

    BOOL  bRet = Thread32First(hSnapshort, &stcThreadInfo);
    DWORD dwProId = -1;  // 保存上一个线程的进程ID   
    unsigned unCount = 0;

    while (bRet)
    {
        if (dwProId != stcThreadInfo.th32OwnerProcessID)
        {

            // 记录PID与所属PID不同，遍历至不属于同一进程的线程  
            if (dwProId != -1)
            {
                // 不是第一次遍历  
                printf("\n进程%d的线程总数：%d\n", dwProId, unCount);
                unCount = 0;
                printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n\n");
            }

            dwProId = stcThreadInfo.th32OwnerProcessID;
            printf("进程%d：\n\n ", dwProId);
            printf("线程TID\t\t线程所属进程PID\t\t线程优先级\n");
        }

        printf("  %d\t\t\t%d\t\t\t %d\n", stcThreadInfo.th32ThreadID, stcThreadInfo.th32OwnerProcessID, stcThreadInfo.tpBasePri);
        unCount++;

        bRet = Thread32Next(hSnapshort, &stcThreadInfo);
    }

    printf("\n进程%d的线程总数：%d\n", dwProId, unCount);
    unCount = 0;
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n\n");

    CloseHandle(hSnapshort);

}


/// <summary>
/// 获取进程的其他信息
/// </summary>
/// <returns></returns>
void TransPath(PTCHAR pPath)
{
    // 获取驱动器字符串位置  
    PTCHAR pFind = _tcsstr(pPath, _T("HarddiskVolume"));
    if (pFind == NULL)
        return;

    TCHAR tcDriver[5] = { 'C', 'D', 'E', 'F', 'G' };  // 可写满24个字符，这里只是一个demo  

    int nNum = pFind[_tcslen(_T("HarddiskVolume"))] - 0x30;

    PTCHAR pTemp = _tcsstr(pFind, _T("\\"));

    // 拼接字符串的缓冲区  
    TCHAR tcBuffer[MAX_PATH];
    memset(tcBuffer, 0, MAX_PATH * sizeof(TCHAR));

    _stprintf_s(tcBuffer, _T("%c:%s"), tcDriver[nNum - 1], pTemp);
    memset(pPath, 0, _tcslen(pPath));
    _tcscpy_s(pPath, 256, tcBuffer);
}

int test3() {
    // 传入\Device\HarddiskVolume1\WINDOWS\System32\notepad.exe   
    DWORD dwNeed;
    PDWORD pdwMem = new DWORD[4000];
    BOOL bRet = EnumProcesses(pdwMem, 4000, &dwNeed);

    if (!bRet)
    {
        if (pdwMem != NULL)
        {
            delete[] pdwMem;
            pdwMem = nullptr;
            return -1;
        }
    }

    int nNumProc = dwNeed / 4;
    HANDLE hProcess = NULL;
    DWORD dwPathLength = 0;
    TCHAR tcBuffer[256] = { 0 };

    for (int i = 0; i < nNumProc; i++)
    {
        hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pdwMem[i]);

        if (hProcess == NULL)
            continue;

        memset(tcBuffer, 0, 256 * sizeof(TCHAR));
        dwPathLength = GetProcessImageFileName(hProcess, tcBuffer, 256);

        if (dwPathLength != 0)
        {
            TransPath(tcBuffer);
            printf("%08d %ls\n", pdwMem[i], tcBuffer);
        }

        CloseHandle(hProcess);
    }

    if (pdwMem != NULL)
    {
        delete[] pdwMem;
        pdwMem = NULL;
    }
}
int main()
{
    //test();

    //test2();

    //test3();
    system("pause");
    return 0;
}
#endif // 0
