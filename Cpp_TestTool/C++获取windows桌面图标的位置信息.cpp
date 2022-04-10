#if 0
#include <tchar.h>
#include <Commctrl.h>
#include <Shlwapi.h>
#pragma comment(lib,"Shlwapi.lib")
/*
要获取windows桌面图标的位置，大致是下面几个步骤，具体请参阅后面的代码：
1：获取桌面图标层的窗口句柄，也就是SysListView32层，当然xp系统和非xp系统父窗口是不同的，具体请看GetIconRect中的代码。
2：根据窗口句柄获取到进程id，然后往进程中分配一块内存，用于存储图标信息，32位系统和64位系统分配的内存大小是不一样的。
3：通过LVM_GETITEMCOUNT获取到图标的个数，通过LVM_GETITEMTEXTA获取图标的名字判断是否为我们需要获取的图标，然后通过LVM_GETITEMRECT获取图标的位置信息。
*/

typedef void (WINAPI* LPFN_PGNSI)(LPSYSTEM_INFO);
typedef struct tagLVITEM64A {
	UINT mask;
	int iItem;
	int iSubItem;
	UINT state;
	UINT stateMask;
	INT64 pszText;
	int cchTextMax;
	int iImage;
	LPARAM lParam;
#if (_WIN32_IE >= 0x0300)
	int iIndent;
#endif
#if (_WIN32_WINNT >= 0x501)
	int iGroupId;
	UINT cColumns; // tile view columns
	PUINT puColumns;
#endif
} LVITEM64A, * LPLVITEM64A;
//==取桌面图标位置=======================
BOOL GetIconRect(char* strIconName, LPRECT lpRect, HWND& hDeskListView) {
	HWND hDeskWnd = NULL;//桌面上SysListView32的窗口句柄
	HWND hWnd = ::FindWindow(_T("WorkerW"), NULL);//先当WIN7系统查找
	while (hWnd) {
		HWND hShellView = ::FindWindowEx(hWnd, NULL, _T("SHELLDLL_DefView"),
			NULL);
		if (hShellView) {
			hDeskWnd = ::FindWindowEx(hShellView, NULL, _T("SysListView32"), NULL);
			break;
		}
		hWnd = ::GetWindow(hWnd, GW_HWNDNEXT);
	}
	if (!hDeskWnd) { // 如果没找到，再按XP方式查找
		hWnd = ::FindWindow(_T("Progman"), _T("Program Manager"));
		if (hWnd) {
			hWnd = ::FindWindowEx(hWnd, NULL, _T("SHELLDLL_DefView"), NULL);
			hDeskWnd = ::FindWindowEx(hWnd, NULL, _T("SysListView32"), NULL);
		}
	}
	if (!hDeskWnd) {
		return FALSE;
	}
	hDeskListView = hDeskWnd;
	BOOL bRet = FALSE;
	if (Is64Bit_OS()) {
		bRet = GetIconRect64(hDeskWnd, strIconName, lpRect);
	}
	else {
		bRet = GetIconRect32(hDeskWnd, strIconName, lpRect);
	}
	if (bRet) {
		POINT pt;
		pt.x = lpRect->left;
		pt.y = lpRect->top;
		::ClientToScreen(hDeskWnd, &pt);
		OffsetRect(lpRect, pt.x - lpRect->left, pt.y - lpRect->top);
	}
	return bRet;
}
BOOL GetIconRect32(HWND hDeskWnd, char* strIconName, LPRECT lpRect) {
	BOOL bRet = FALSE;
	//-----------------------------
	//遍历外部进程所有图标
	DWORD PID = 0;
	GetWindowThreadProcessId(hDeskWnd, &PID);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, PID);
	if (hProcess != NULL) {
		LVITEMA* pLVITEM = (LVITEMA*)VirtualAllocEx(hProcess, NULL,
			sizeof(LVITEM), MEM_COMMIT, PAGE_READWRITE);
		char* pszText = (char*)VirtualAllocEx(hProcess, NULL, 512, MEM_COMMIT,
			PAGE_READWRITE);
		RECT* pItemRc = (RECT*)VirtualAllocEx(hProcess, NULL, sizeof(RECT),
			MEM_COMMIT, PAGE_READWRITE);
		RECT rc;
		if (pItemRc != NULL && pLVITEM != NULL) {
			LVITEMA LVITEM;
			LVITEM.mask = LVIF_TEXT;
			LVITEM.cchTextMax = 512;
			LVITEM.pszText = pszText;
			char ItemBuf[512];
			int nCount = ::SendMessage(hDeskWnd, LVM_GETITEMCOUNT, 0, 0);
			for (int iItem = 0; iItem < nCount; iItem++) {
				LVITEM.iItem = iItem;
				LVITEM.iSubItem = 0;
				//将设置好的结构插入目标进程
				WriteProcessMemory(hProcess, pLVITEM, &LVITEM, sizeof(LVITEM), NULL);
				//发送LVM_GETITEM消息
				BOOL r = (BOOL)::SendMessage(hDeskWnd, LVM_GETITEMTEXTA, iItem, (
					LPARAM)pLVITEM);
				//获取pszText
				ReadProcessMemory(hProcess, pszText, ItemBuf, 512, NULL);
				if (StrCmpA(ItemBuf, strIconName) == 0) {
					::SendMessage(hDeskWnd, LVM_GETITEMRECT, iItem, (LPARAM)pItemRc);
					ReadProcessMemory(hProcess, pItemRc, &rc, sizeof(RECT), NULL);
					memcpy(lpRect, &rc, sizeof(RECT));
					bRet = TRUE;
					break;
				}
			}
			VirtualFreeEx(hProcess, pLVITEM, 0, MEM_RELEASE);
			VirtualFreeEx(hProcess, pszText, 0, MEM_RELEASE);
			VirtualFreeEx(hProcess, pItemRc, 0, MEM_RELEASE);//释放内存
		}
		CloseHandle(hProcess);
	}
	return bRet;
}
BOOL GetIconRect64(HWND hDeskWnd, char* strIconName, LPRECT lpRect) {
	BOOL bRet = FALSE;
	//遍历外部进程所有图标
	DWORD PID = 0;
	GetWindowThreadProcessId(hDeskWnd, &PID);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, PID);
	if (hProcess != NULL) {
		LVITEM64A* pLVITEM = (LVITEM64A*)VirtualAllocEx(hProcess, NULL, sizeof(LVITEM64A), MEM_COMMIT, PAGE_READWRITE);
		char* pszText = (char*)VirtualAllocEx(hProcess, NULL, 512, MEM_COMMIT, PAGE_READWRITE);
		RECT* pItemRc = (RECT*)VirtualAllocEx(hProcess, NULL, sizeof(RECT), MEM_COMMIT, PAGE_READWRITE);
		RECT rc;
		if (pItemRc != NULL || pLVITEM != NULL) {
			LVITEM64A LVITEM;
			LVITEM.mask = LVIF_TEXT;
			LVITEM.cchTextMax = 512;
			LVITEM.pszText = (INT64)pszText;
			char ItemBuf[512];
			int nCount = ::SendMessage(hDeskWnd, LVM_GETITEMCOUNT, 0, 0);
			for (int iItem = 0; iItem < nCount; iItem++) {
				LVITEM.iItem = iItem;
				LVITEM.iSubItem = 0;
				//将设置好的结构插入目标进程
				WriteProcessMemory(hProcess, pLVITEM, &LVITEM, sizeof(LVITEM), NULL);
				//发送LVM_GETITEM消息
				BOOL r = (BOOL)::SendMessage(hDeskWnd, LVM_GETITEMTEXTA, iItem, (LPARAM)pLVITEM);
				//获取pszText
				ReadProcessMemory(hProcess, pszText, ItemBuf, 512, NULL);
				if (StrCmpA(ItemBuf, strIconName) == 0) {
					::SendMessage(hDeskWnd, LVM_GETITEMRECT, iItem, (LPARAM)pItemRc);
					ReadProcessMemory(hProcess, pItemRc, &rc, sizeof(RECT), NULL);
					memcpy(lpRect, &rc, sizeof(RECT));
					bRet = TRUE;
					break;
				}
			}
			VirtualFreeEx(hProcess, pLVITEM, 0, MEM_RELEASE);
			VirtualFreeEx(hProcess, pszText, 0, MEM_RELEASE);
			VirtualFreeEx(hProcess, pItemRc, 0, MEM_RELEASE);//释放内存
		}
		CloseHandle(hProcess);
	}
	return bRet;
}
BOOL Is64Bit_OS() {
	BOOL bRetVal = FALSE;
	SYSTEM_INFO si = { 0 };
	LPFN_PGNSI pGNSI =
		(LPFN_PGNSI)GetProcAddress(GetModuleHandle(_T("kernel32.dll")),
			"GetNativeSystemInfo");
	if (pGNSI == NULL) {
		return FALSE;
	}
	pGNSI(&si);
	if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ||
		si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64) {
		bRetVal = TRUE;
	}
	return bRetVal;
}
void main() {
	GetIconRect((char*)"Internet Explorer", ...);
}
#endif // 0
