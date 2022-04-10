#include <iostream>
#include <windows.h>
using namespace std;

void Inject(int pID, char*Path)
{
	//获取进程句柄
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
	//申请一块内存给DLL路径
	LPVOID pReturnAddress = VirtualAllocEx(hProcess, NULL, strlen(Path) + 1, MEM_COMMIT, PAGE_READWRITE);
	//写入路径到上一行代码申请的内存中
	WriteProcessMemory(hProcess, pReturnAddress, Path, strlen(Path) + 1, NULL);
	//获取LoadLibraryA函数的地址
	HMODULE hModule = LoadLibraryA("KERNEL32.DLL");
	LPTHREAD_START_ROUTINE LpStartAddress = (LPTHREAD_START_ROUTINE)GetProcAddress(hModule, "LoadLibraryA");
	//创建在另一个进程中的虚拟地址空间中运行的线程
	/*hThread获取线程的句柄*/HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, LpStartAddress, pReturnAddress, 0, NULL);
	//等待线程事件
	WaitForSingleObject(hThread, 2000);//防止线程阻塞
	//防止内存泄漏
	CloseHandle(hThread);
	CloseHandle(hProcess);
}

int main()
{
	char *p = "D:\\Windows 7 Documents\\Desktop\\远线程注入dll\\Release\\dll文件1.dll";
	Inject(2280, p);

	system("pause");
	return 0;
}

