#if 0
#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
	//��ȡ���ھ��
	HWND htext = FindWindow(NULL, L"�ޱ��� - ���±�");  //�ҵ����±����ڵľ��
	if (!htext)
	{
		cout << "not find text!" << endl;
		return 0;
	}
	// ��ȡ�Ӵ��ھ��
	HWND hchild = FindWindowEx(htext, NULL, L"Edit", NULL);  //�ҵ����±��ı༭���Ӵ���
	if (!hchild)
	{
		cout << "not find child!" << endl;
		return 0;
	}
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
	return 1;
}
#endif // 0
