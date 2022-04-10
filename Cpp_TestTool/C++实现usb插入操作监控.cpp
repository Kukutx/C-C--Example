#if 0
#include <tchar.h>  
#include <string>  
#include <iostream>  
#include <Windows.h>  
#include <dbt.h>  
using namespace std;
/*------------------------------------------------------------------
FirstDriveFromMask( unitmask )
Description
Finds the first valid drive letter from a mask of drive letters.
The mask must be in the format bit 0 = A, bit 1 = B, bit 2 = C,
and so on. A valid drive letter is defined when the
corresponding bit is set to 1.
��һ����������ĸ��������ҵ���һ����Ч����������ĸ��
�����������ڸ�ʽλ0=A��λ1=B��λ2=C��
�ȵȡ�һ����Ч����������ĸ����
��Ӧλ����Ϊ1��
Returns the first drive letter that was found.
--------------------------------------------------------------------*/
char FirstDriveFromMask(ULONG unitmask)
{
	char i;

	for (i = 0; i < 26; ++i)
	{
		if (unitmask & 0x1)
			break;
		unitmask = unitmask >> 1;
	}

	return(i + 'A');
}

/*
	ÿ�����ڻ���һ����Ϊ���ڹ��̵Ļص�����(WndProc)���������ĸ��������ֱ�Ϊ��
	���ھ��(Window Handle) HWND,
	��ϢID(Message ID) UINT,
	��������Ϣ����(wParam, lParam)WPARAM��LPARAM,
	WndProc�ĵ�һ������hWnd���ǵ�ǰ������Ϣ�Ĵ��ھ�����ڶ����������Ǳ����͹�������Ϣ��
	���������ĸ��������Ǹ�������Ϣ�ϵ����ݣ����MSG�ṹ����һ����
	������˽����/���Ĳ����뵽https://baike.baidu.com/item/WPARAM/6098975?fr=aladdin
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;
	PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
	TCHAR szMsg[80];
	char driveName;

	/*
	��USB�豸������ߵ���ʱ��Windows�����һ��ȫ����Ϣ��WM_DEVICECHANGE
������Ҫ�����ǣ����������Ϣ��wParam���������ΪDBT_DEVICEARRIVAL���ʾ���豸���벢���ã�
�����DBT_DEVICEREMOVECOMPLETE���ʾ���豸�Ѿ��Ƴ����ٲ鿴lParam����ΪDBT_DEVTYP_VOLUMEʱ��
�Ϳ���ȡ��DEV_BROADCAST_VOLUME�ṹ�ľ��dbcv_unitmask����֪�����ĸ���������ߵ�����
	*/
	switch (uMsg)
	{
	case WM_DEVICECHANGE:
		switch (wParam)
		{
		case DBT_DEVICEARRIVAL:
			//��ȡ���
			driveName = FirstDriveFromMask(lpdbv->dbcv_unitmask);
			cout << szMsg << "USB Drive %c: has inserted" << endl;
			cout << driveName << endl;
			//�滻��cout ��� sprintf(szMsg, "USB Drive %c: has inserted.\n", driveName);
			printf("%s\r\n", szMsg);
			MessageBox(hWnd, szMsg, TEXT("WM_DEVICECHANGE"), MB_OK);
			break;
		case DBT_DEVICEREMOVECOMPLETE:
			driveName = FirstDriveFromMask(lpdbv->dbcv_unitmask);
			cout << szMsg << "USB Drive %c: has removed." << endl;
			cout << driveName << endl;
			//�滻��cout ��� sprintf(szMsg, "USB Drive %c: has removed.\n", driveName);
			printf("%s\r\n", szMsg);
			MessageBoxW(hWnd, szMsg, TEXT("WM_DEVICECHANGE"), MB_OK);
			break;
		default:
			;
		}
		break;
	default:
		;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

/*
	_tmain()��unicode�汾�ĵ�main()???
_tmain������Ŷ����VC++�����Ŀ���̨�����У������Ϊ�˱�֤��ֲunicode�������
��һ��_t��_T��T()��Щ��������unicode�й�ϵ��������ʹ�÷�unicode�ַ����Ĺ�����˵
��ʵ���Ϻ�mainû�в����ʵ������ʹ��unicode�ַ���Ҳδ���ж��Ĳ�𣩡�
1��?main��C����ĺ�����_tmain��mainΪ��֧��unicode��ʹ�õ�main�ı���
2��?_tmain�Ķ�����<tchar.h>�����ҵ�,��#define?_tmain?main������Ҫ�ӣ�i nclude <tchar.h>�����á�
3�����_tmain?compile����Ϊmain�����Զ�����ִ��
����,wmainҲ��main����һ������,��Ϊ��֧�ֶ����ֽڵ����Ի���
*/
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	TCHAR szClassName[] = _T("MyApp");
	/*
		WNDCLASS��һ����ϵͳ֧�ֵĽṹ��
		��������ĳһ�ര�ڵ���Ϣ,��ClassStyle,��Ϣ��������Icon,Cursor,����Brush�ȡ�
		Ҳ����˵��CreateWindowֻ�ǽ�ĳ��WNDCLASS����Ĵ�����ʵ��
		https://baike.baidu.com/item/WNDCLASS/6488732?fr=aladdin
	*/
	WNDCLASS wndcls = { 0 }; // zeroMemory����
	//���ڵı���ɫ
	wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	//���ڵ������
	wndcls.hCursor = (HCURSOR)LoadCursor(NULL, IDC_ARROW);
	//���ڵ���С��ͼ��
	wndcls.hIcon = (HICON)LoadIcon(NULL, IDI_APPLICATION);
	//���ڵĴ�����
	wndcls.lpfnWndProc = WndProc;
	//��������
	wndcls.lpszClassName = szClassName;
	/*
		���ʹ��RegisterClassA��ע�ᴰ�ڣ�Ӧ�ó���֪ͨϵͳ��ע����Ĵ��ڵ���Ϣʹ��ANSI�ַ������ı����ַ�������
		���ʹ��RegisterClassW��ע�ᴰ�ڣ�Ӧ�ó�����Ҫϵͳ��Unicode��������Ϣ���ı�����
	*/
	if (!RegisterClassW(&wndcls))
	{
		printf("RegisterClass Failed!\r\n");
		return 0;
	}
	/*
	h ��������������ʾ���(handle)�� Wnd �Ǳ���������������ʾ���ڣ�����hWnd ��ʾ���ھ��
	����CreateWindow ��鿴 https://baike.baidu.com/item/CreateWindow/5076220?fr=aladdin
	*/
	HWND hWnd = CreateWindow(szClassName, szClassName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, NULL, NULL);
	if (NULL == hWnd)
	{
		printf("CreateWindow Failed!\r\n");
		return 0;
	}
	//�ú�������ָ�����ڵ���ʾ״̬��
	ShowWindow(hWnd, SW_HIDE);
	UpdateWindow(hWnd);

	MSG msg;
	//��������message ��������԰ٶȰٿ��˽�ɡ�
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
#endif // 0
