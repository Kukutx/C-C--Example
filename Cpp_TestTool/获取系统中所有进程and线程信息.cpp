#if 0
#include <stdio.h>  
#include <windows.h>  
#include <tchar.h>  
#include <TlHelp32.h>  
#include <Psapi.h>  

#pragma comment(lib, "psapi.lib")   
/// <summary>
/// ��������&�̳߳���
/// </summary>
/// <returns></returns>
int test() {
    // Ϊ���̵������߳��ĸ�����  
    HANDLE hSnapshort = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshort == INVALID_HANDLE_VALUE)
    {
        printf("CreateToolhelp32Snapshot����ʧ�ܣ�\n");
        return -1;
    }

    // ����߳��б������¼���̵߳���ϸ��Ϣ����ʹ��Thread32First��Thread32Next���������м�¼��ÿ���߳���Ϣ  
    PROCESSENTRY32 stcProcessInfo;
    stcProcessInfo.dwSize = sizeof(stcProcessInfo);

    BOOL  bRet = Process32First(hSnapshort, &stcProcessInfo);

    printf("������\t\t\t ����ID\t �߳���\t ������ID\n");

    while (bRet)
    {
        printf("%ls\t\t %d\t %d\t %d\n", stcProcessInfo.szExeFile, stcProcessInfo.th32ProcessID, stcProcessInfo.cntThreads, stcProcessInfo.th32ParentProcessID);

        bRet = Process32Next(hSnapshort, &stcProcessInfo);
    }
    CloseHandle(hSnapshort);
}

int test2() {
    // Ϊ���̵������߳��ĸ�����  
    HANDLE hSnapshort = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hSnapshort == INVALID_HANDLE_VALUE)
    {
        printf("CreateToolhelp32Snapshot����ʧ�ܣ�\n");
        return -1;
    }

    // ����߳��б������¼���̵߳���ϸ��Ϣ����ʹ��Thread32First��Thread32Next���������м�¼��ÿ���߳���Ϣ  
    THREADENTRY32 stcThreadInfo;
    stcThreadInfo.dwSize = sizeof(stcThreadInfo);

    BOOL  bRet = Thread32First(hSnapshort, &stcThreadInfo);
    DWORD dwProId = -1;  // ������һ���̵߳Ľ���ID   
    unsigned unCount = 0;

    while (bRet)
    {
        if (dwProId != stcThreadInfo.th32OwnerProcessID)
        {

            // ��¼PID������PID��ͬ��������������ͬһ���̵��߳�  
            if (dwProId != -1)
            {
                // ���ǵ�һ�α���  
                printf("\n����%d���߳�������%d\n", dwProId, unCount);
                unCount = 0;
                printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n\n");
            }

            dwProId = stcThreadInfo.th32OwnerProcessID;
            printf("����%d��\n\n ", dwProId);
            printf("�߳�TID\t\t�߳���������PID\t\t�߳����ȼ�\n");
        }

        printf("  %d\t\t\t%d\t\t\t %d\n", stcThreadInfo.th32ThreadID, stcThreadInfo.th32OwnerProcessID, stcThreadInfo.tpBasePri);
        unCount++;

        bRet = Thread32Next(hSnapshort, &stcThreadInfo);
    }

    printf("\n����%d���߳�������%d\n", dwProId, unCount);
    unCount = 0;
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n\n");

    CloseHandle(hSnapshort);

}


/// <summary>
/// ��ȡ���̵�������Ϣ
/// </summary>
/// <returns></returns>
void TransPath(PTCHAR pPath)
{
    // ��ȡ�������ַ���λ��  
    PTCHAR pFind = _tcsstr(pPath, _T("HarddiskVolume"));
    if (pFind == NULL)
        return;

    TCHAR tcDriver[5] = { 'C', 'D', 'E', 'F', 'G' };  // ��д��24���ַ�������ֻ��һ��demo  

    int nNum = pFind[_tcslen(_T("HarddiskVolume"))] - 0x30;

    PTCHAR pTemp = _tcsstr(pFind, _T("\\"));

    // ƴ���ַ����Ļ�����  
    TCHAR tcBuffer[MAX_PATH];
    memset(tcBuffer, 0, MAX_PATH * sizeof(TCHAR));

    _stprintf_s(tcBuffer, _T("%c:%s"), tcDriver[nNum - 1], pTemp);
    memset(pPath, 0, _tcslen(pPath));
    _tcscpy_s(pPath, 256, tcBuffer);
}

int test3() {
    // ����\Device\HarddiskVolume1\WINDOWS\System32\notepad.exe   
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
