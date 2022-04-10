#if 0
#include <stdio.h>
#include <string.h>
#include<windows.h>
#include<ShlObj.h>
#pragma warning(disable:4996)
VOID DelItself()
{
	/********************************************************************
	* 第一种方法
	* 调用接口函数库类型: Windows API,标准C库函数
	* 程序原理: Windows加载程序后，进程无法删除进程映像，利用进程优先级,
	*父进程结束，子进程删除父进程映像后结束,实现自删除
	*********************************************************************/
	SHELLEXECUTEINFO stShellDel;
	TCHAR szBat[MAX_PATH];
	//获取文件路径名
	TCHAR szFileName[MAX_PATH], szComspec[MAX_PATH];
	if ((GetModuleFileName(0, szFileName, MAX_PATH) != 0) &&
		(GetShortPathName(szFileName, szFileName, MAX_PATH) != 0) &&
		(GetEnvironmentVariable(L"COMSPEC", szComspec, MAX_PATH) != 0))
	{
		lstrcpy(szBat, L"/c del ");
		lstrcat(szBat, szFileName);
		lstrcat(szBat, L" > nul");

		stShellDel.cbSize = sizeof(stShellDel);
		stShellDel.hwnd = 0;//命令窗口进程句柄，ShellExecuteEx函数执行时设置。
		stShellDel.lpVerb = L"Open";
		stShellDel.lpFile = szComspec;
		stShellDel.lpParameters = szBat;
		stShellDel.lpDirectory = NULL;
		stShellDel.nShow = SW_HIDE;
		stShellDel.fMask = SEE_MASK_NOCLOSEPROCESS;//设置为SellExecuteEx函数结束后进程退出。 
		//创建执行命令窗口进程。 
		if (ShellExecuteEx(&stShellDel))
		{
			//设置命令行进程的执行级别为空闲执行,这使本程序有足够的时间从内存中退出。 
			SetPriorityClass(stShellDel.hProcess, IDLE_PRIORITY_CLASS);
			//设置本程序进程的执行级别为实时执行，这保证本程序能立即获取CPU执行权，快速退出。 
			SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
			SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
			//通知Windows资源管理器，本程序文件已经被删除。 
			SHChangeNotify(SHCNE_DELETE, SHCNF_PATH, szFileName, 0);
			ExitProcess(0);
		}
	}
}


void DelItself2()
{
	/**********************************************************************************
	* 第二种方法
	* 调用接口函数库类型: Windows API,标准C库函数
	* 程序原理: Windows加载程序后，进程无法删除进程映像，利用批处理延时加载，进程退出后，
	* 利用批处理删除映像文件
	* 该方法在vs运行下效果不明显需要独立运行操作
	***********************************************************************************/
	HANDLE hFile = CreateFileA("1.bat", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return;
	}
	const char* szBat = "del Project1.exe\r\n del 1.bat";   //这里写当前编译程序的程序名
	DWORD dwNum = 0;
	//向1.bat批处理文件中写入删除进程映像的命令
	WriteFile(hFile, szBat, lstrlenA(szBat) + 1, &dwNum, NULL);
	CloseHandle(hFile);
	ShellExecuteA(NULL, "open", "1.bat", "", "", SW_HIDE);
}


void DeleteAppSelf()
{
	/// <summary>
	/// 第三种方法
	/// </summary>
	char szCommandLine[MAX_PATH + 10] = { 0 };
	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
	SetThreadPriority(GetCurrentProcess(), THREAD_PRIORITY_TIME_CRITICAL);
	SHChangeNotify(SHCNE_DELETE, SHCNF_PATH, _pgmptr, NULL);
	char szFilePath[MAX_PATH] = { 0 };
	sprintf(szFilePath, R"(%s)", _pgmptr);
	sprintf(szCommandLine, "/c del /q %s", szFilePath);
	ShellExecuteA(NULL, "open", "cmd.exe", szCommandLine, NULL, SW_HIDE);
	ExitProcess(0);
}
int main()
{

	/// <summary>
	/// 第一种方式
	/// </summary>
	/// <returns></returns>
	char szInputStr[MAXBYTE];
	//输入delete,触发程序自删除
	scanf("%s", szInputStr);
	if (0 == (strncmp(szInputStr, "delete", MAXBYTE)))
	{
		printf("程序正在自删除...........\n");
		//第一种方法
		//DelItself();

		//第二种方法
		//DelItself2();

		//第三种方法
		DeleteAppSelf();
	}
	return 0;
}



#endif // 0
