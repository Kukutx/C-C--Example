#include <iostream>
#include <windows.h>
using namespace std;

void Inject(int pID, char*Path)
{
	//��ȡ���̾��
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
	//����һ���ڴ��DLL·��
	LPVOID pReturnAddress = VirtualAllocEx(hProcess, NULL, strlen(Path) + 1, MEM_COMMIT, PAGE_READWRITE);
	//д��·������һ�д���������ڴ���
	WriteProcessMemory(hProcess, pReturnAddress, Path, strlen(Path) + 1, NULL);
	//��ȡLoadLibraryA�����ĵ�ַ
	HMODULE hModule = LoadLibraryA("KERNEL32.DLL");
	LPTHREAD_START_ROUTINE LpStartAddress = (LPTHREAD_START_ROUTINE)GetProcAddress(hModule, "LoadLibraryA");
	//��������һ�������е������ַ�ռ������е��߳�
	/*hThread��ȡ�̵߳ľ��*/HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, LpStartAddress, pReturnAddress, 0, NULL);
	//�ȴ��߳��¼�
	WaitForSingleObject(hThread, 2000);//��ֹ�߳�����
	//��ֹ�ڴ�й©
	CloseHandle(hThread);
	CloseHandle(hProcess);
}

int main()
{
	char *p = "D:\\Windows 7 Documents\\Desktop\\Զ�߳�ע��dll\\Release\\dll�ļ�1.dll";
	Inject(2280, p);

	system("pause");
	return 0;
}

