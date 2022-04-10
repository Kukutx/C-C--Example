#include <iostream>
#include <Windows.h>
using namespace std;
void CallQtDll() {
	typedef bool(*pShowDialog)(HWND parent);      //句柄取名
	//在中间显示窗口
	RECT rcDesk;
	GetWindowRect(GetDesktopWindow(), &rcDesk);
	RECT rc;
	GetWindowRect(GetConsoleWindow(), &rc);
	int x = rcDesk.left + (rcDesk.right - rcDesk.left) / 2 - (rc.right - rc.left) / 2;
	int y = rcDesk.top + (rcDesk.bottom - rcDesk.top) / 2 - (rc.bottom - rc.top) / 2;
	int cx = (rc.right - rc.left);
	int cy = (rc.bottom - rc.top);
	SetWindowPos(GetConsoleWindow(), NULL, x, y, cx, cy, SWP_NOSIZE);
	//打印Hello Word
	cout << "Hello World!\n";
	//开始调用qtdialog.dll文件
	const char* dllName = "qtdialog.dll";
	HMODULE hDLL = LoadLibraryA(dllName);     //记载dll库文件
	if (hDLL != NULL)
	{
		//用句柄获取qtdll函数
		pShowDialog fp = pShowDialog(GetProcAddress(hDLL, "showDialog"));
		if (fp != NULL)
		{
			//ShowWindow(GetConsoleWindow(), SW_HIDE);   //让控制台不可见
			cout << "pShowDialog!\n";
			fp(GetConsoleWindow());   //用句柄获取本控制台程序的标识符，用于监听控制台是否程序开启，方便dll函数调用
		}
		pShowDialog fp2 = pShowDialog(GetProcAddress(hDLL, "ShowDirDialog"));
		if (fp2 != NULL)
		{
			cout << "pShowDirDialog!\n";
			fp2(GetConsoleWindow());
		}
		//释放DLL库
		FreeLibrary(hDLL);
	}
	else
	{
		cout << "Cannot Find " << dllName << endl;
	}
}
int main()
{
	CallQtDll();
	system("pause");
	return 0;
}
