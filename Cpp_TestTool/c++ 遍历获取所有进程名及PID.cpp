#if 0
#include <iostream>  
#include <string>  
#include <map>  
#include <windows.h>  
#include <TlHelp32.h> 
using namespace std;
bool traverseProcesses()
{
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(pe32);
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//??????  
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        cout << "CreateToolhelp32Snapshot Error!" << endl;;
        return false;
    }
    BOOL bResult = Process32First(hProcessSnap, &pe32);
    int num(0);
    while (bResult)
    {
        int id = pe32.th32ProcessID;
        cout << "[" << ++num << "] : " << "Process Name:"
            << pe32.szExeFile << "  " << "ProcessID:" << id << endl;

        bResult = Process32Next(hProcessSnap, &pe32);
    }
    CloseHandle(hProcessSnap);
    return true;
}

int main()
{
    if (!traverseProcesses()) {
        cout << "Start Process Error!" << endl;
    }
    return 0;
}

#endif // 0
