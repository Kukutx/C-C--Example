#if 0
#include <stdio.h>
#include <string.h>
#include<windows.h>
#include<ShlObj.h>
#pragma warning(disable:4996)
VOID DelItself()
{
	/********************************************************************
	* ��һ�ַ���
	* ���ýӿں���������: Windows API,��׼C�⺯��
	* ����ԭ��: Windows���س���󣬽����޷�ɾ������ӳ�����ý������ȼ�,
	*�����̽������ӽ���ɾ��������ӳ������,ʵ����ɾ��
	*********************************************************************/
	SHELLEXECUTEINFO stShellDel;
	TCHAR szBat[MAX_PATH];
	//��ȡ�ļ�·����
	TCHAR szFileName[MAX_PATH], szComspec[MAX_PATH];
	if ((GetModuleFileName(0, szFileName, MAX_PATH) != 0) &&
		(GetShortPathName(szFileName, szFileName, MAX_PATH) != 0) &&
		(GetEnvironmentVariable(L"COMSPEC", szComspec, MAX_PATH) != 0))
	{
		lstrcpy(szBat, L"/c del ");
		lstrcat(szBat, szFileName);
		lstrcat(szBat, L" > nul");

		stShellDel.cbSize = sizeof(stShellDel);
		stShellDel.hwnd = 0;//����ڽ��̾����ShellExecuteEx����ִ��ʱ���á�
		stShellDel.lpVerb = L"Open";
		stShellDel.lpFile = szComspec;
		stShellDel.lpParameters = szBat;
		stShellDel.lpDirectory = NULL;
		stShellDel.nShow = SW_HIDE;
		stShellDel.fMask = SEE_MASK_NOCLOSEPROCESS;//����ΪSellExecuteEx��������������˳��� 
		//����ִ������ڽ��̡� 
		if (ShellExecuteEx(&stShellDel))
		{
			//���������н��̵�ִ�м���Ϊ����ִ��,��ʹ���������㹻��ʱ����ڴ����˳��� 
			SetPriorityClass(stShellDel.hProcess, IDLE_PRIORITY_CLASS);
			//���ñ�������̵�ִ�м���Ϊʵʱִ�У��Ᵽ֤��������������ȡCPUִ��Ȩ�������˳��� 
			SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
			SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
			//֪ͨWindows��Դ���������������ļ��Ѿ���ɾ���� 
			SHChangeNotify(SHCNE_DELETE, SHCNF_PATH, szFileName, 0);
			ExitProcess(0);
		}
	}
}


void DelItself2()
{
	/**********************************************************************************
	* �ڶ��ַ���
	* ���ýӿں���������: Windows API,��׼C�⺯��
	* ����ԭ��: Windows���س���󣬽����޷�ɾ������ӳ��������������ʱ���أ������˳���
	* ����������ɾ��ӳ���ļ�
	* �÷�����vs������Ч����������Ҫ�������в���
	***********************************************************************************/
	HANDLE hFile = CreateFileA("1.bat", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return;
	}
	const char* szBat = "del Project1.exe\r\n del 1.bat";   //����д��ǰ�������ĳ�����
	DWORD dwNum = 0;
	//��1.bat�������ļ���д��ɾ������ӳ�������
	WriteFile(hFile, szBat, lstrlenA(szBat) + 1, &dwNum, NULL);
	CloseHandle(hFile);
	ShellExecuteA(NULL, "open", "1.bat", "", "", SW_HIDE);
}


void DeleteAppSelf()
{
	/// <summary>
	/// �����ַ���
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
	/// ��һ�ַ�ʽ
	/// </summary>
	/// <returns></returns>
	char szInputStr[MAXBYTE];
	//����delete,����������ɾ��
	scanf("%s", szInputStr);
	if (0 == (strncmp(szInputStr, "delete", MAXBYTE)))
	{
		printf("����������ɾ��...........\n");
		//��һ�ַ���
		//DelItself();

		//�ڶ��ַ���
		//DelItself2();

		//�����ַ���
		DeleteAppSelf();
	}
	return 0;
}



#endif // 0
