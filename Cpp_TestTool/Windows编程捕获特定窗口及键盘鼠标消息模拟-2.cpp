#if 0
#include <iostream>
#include <string.h>
#include <Windows.h>
using namespace std;
//��ö�ٵ��Ӵ��ڽ��в���
BOOL CALLBACK EnumChildProc(HWND hchild, LPARAM lparam)
{
	wchar_t cls_name[50];
	GetClassName(hchild, cls_name, 50);  //��ȡ�Ӵ��ڵ�����
	wprintf(L"%s", cls_name);            //���Ӵ��ڵ�������ӡ����Ļ
	wchar_t* p = wcsstr(cls_name, (wchar_t*)lparam);  //�жϲ��ҵ����Ӵ����Ƿ��Ǳ༭������
	if (p == NULL)
	{
		return TRUE;
	}
	else
	{
		/*��༭�����Ͱ������µ���Ϣ�����ݷֱ�hello world*/
		PostMessage(hchild, WM_KEYDOWN, 0x48, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x45, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x4c, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x4c, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x4f, 0);
		PostMessage(hchild, WM_KEYDOWN, VK_SPACE, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x57, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x4f, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x52, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x4c, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x44, 0);
		return TRUE;

	}
}

int main()
{
	HWND htext = FindWindow(NULL, L"�ޱ��� - ���±�");  //�ҵ����±����ڵľ��
	if (!htext)
	{
		cout << "not find text!" << endl;
		return 0;
	}
	wchar_t class_name[] = { L"Edit" };   //�趨Ҫ�༭�����ڵ�����
	EnumChildWindows(htext, EnumChildProc, (LPARAM)class_name);  //ö�������Ӵ��ڣ���EnumChildProc�����ж���Щ����һһ����
	return 1;
}
#endif // 0
