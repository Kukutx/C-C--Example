#if 0
#include <iostream>
#include <Windows.h>
#include <ShlObj.h>
using namespace std;
//可参考C++创建快捷方式(lnk、url)并添加到开始菜单、桌面、任务栏.md
//修改快捷方式的目标地址：参数：快捷方式，新定义的目标地址
bool CrnModifyShortcutArguments(LPCWSTR lpszLnkFilePath, LPCWSTR strArguments)
{
	//判断文件是否存在
	bool bResult = (CoInitialize(NULL) == S_OK);
	if (bResult)
	{
		IShellLink* pShellLink;
		//创建IShellLink对象
		bResult = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
			IID_IShellLink, (void**)&pShellLink) >= 0;

		if (!bResult)
			return false;

		//从IShellLink对象中获取IPersistFile接口
		IPersistFile* ppf;
		bResult = pShellLink->QueryInterface(IID_IPersistFile, (void**)&ppf) >= 0;
		if (!bResult)
		{
			pShellLink->Release();
			ppf->Release();
			return false;
		}
		//加载快捷方式文件
		bResult = ppf->Load(lpszLnkFilePath, TRUE) >= 0;
		if (!bResult)
		{
			pShellLink->Release();
			ppf->Release();
			return false;
		}
		//修改快捷方式文件参数
		bResult = pShellLink->SetPath(strArguments) >= 0;
		if (!bResult)
		{
			pShellLink->Release();
			ppf->Release();
			return false;
		}
		//重新保存快捷方式文件
		bResult = ppf->Save(lpszLnkFilePath, TRUE) >= 0;
		if (!bResult)
		{
			pShellLink->Release();
			ppf->Release();
			return false;
		}

		ppf->Release();
		pShellLink->Release();
		CoUninitialize();
	}
	return bResult;
}
//创建快捷方式
void CreateLink()
{
	/*
	用C++创建快捷方式
	主要用到的是COM组件。IShellLink和IPersistFile
	IPersistFile主要用到两个成员函数：
	1、Save。保存内容到文件中去
	2、Load。读取
	Load的函数原型
	HRESULT Load(
	LPCOLSTR pszFileName, //快捷方式的文件名，应该是ANSI字符
	DWORD dwMode //读取方式
	);
	dwMode可取如下值：
	STGM_READ：只读
	STGM_WRITE：只写
	STGM_READWRITE：读写
	IShellLink主要成员：
	1、GetArguments：获得参数信息
	2、GetDescription：获得描述信息（备注行）
	3、GetHotkey：获得快捷键
	4、GetIconLocation：获得图标
	5、GetIDList：获得快捷方式的目标对象的item identifier list (Windows外壳中的每个对象如文件，目录和打印机等都有唯一的item identifiler list)
	6、GetPath: 获得快捷方式的目标文件或目录的全路径
	7、GetShowCmd：获得快捷方式的运行方式，比如常规窗口，最大化
	8、GetWorkingDirectory：获得工作目录
	9、Resolve：按照一定的搜索规则试图获得目标对象，即使目标对象已经被删除或移动，重命名
	下面是对应信息的设置方法
	10、SetArguments
	11、SetDescription
	12、SetHotkey
	13、SetIconLocation
	14、SetIDList
	15、SetPath
	16、SetRelativePat
	17、SetShowCmd
	18、SetWorkingDirectory
	一般情况操作如下：
	一、初始化COM接口
	二、创建IShellLink对象
	三、从IShellLink对象中获取IPersistFile对象接口
	四、操作IShellLink对象
	五、释放IPersistFile对象接口
	六、释放IShellLink对象
	七、释放COM接口
	*/
	//初始化com组件
	::CoInitialize(NULL);
	LPITEMIDLIST pitemIlist;
	SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pitemIlist);
	TCHAR szPath[MAX_PATH]{ 0 };
	//从LPITEMIDLIST 获取桌面的路径
	SHGetPathFromIDList(pitemIlist, szPath);
	wcscat_s(szPath, L"\\newLink.lnk");
	IShellLink* pShellLink;
	IPersistFile* pPerFile;
	//创建对象
	CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
		IID_IShellLink, (LPVOID*)&pShellLink);
	TCHAR szSrcPath[MAX_PATH]{ 0 };
	GetModuleFileName(NULL, szSrcPath, MAX_PATH);
	//  从IShellLink获取其IPersistFile接口
	pShellLink->QueryInterface(IID_IPersistFile, (LPVOID*)&pPerFile);
	//设置启动路径
	pShellLink->SetPath(szSrcPath);
	//设置热键 ："Ctrl+Alt +Q"
	pShellLink->SetHotkey(MAKEWORD('Q', HOTKEYF_CONTROL | HOTKEYF_ALT));
	//设置图标
	pShellLink->SetIconLocation(L"C:\\Users\\liuzh\\Downloads\\test\\Cpp_TestTool\\link.ico", 0);
	//保存路径
	pPerFile->Save(szPath, false);
	//释放！
	pPerFile->Release();
	pShellLink->Release();
	::CoUninitialize();
}


int main() {
	cout << CrnModifyShortcutArguments(L"C:\\Users\\liuzh\\Desktop\\1111.lnk", L"C:\\Users\\liuzh\\Desktop\\22222.txt");
	CreateLink();
	return 0;
}




//#include <iostream>
//#include <shlobj.h>
//using namespace std;
//int main()
//{
//    const TCHAR* path = L"D:\\Program Files\\Tencent\\QQ\\Bin\\QQ.exe";//目标的路径
//    const TCHAR* work = L"D:\\Program Files\\Tencent\\QQ\\Bin";//起始位置
//    const TCHAR* dir = L"C:\\Documents and Settings\\Administrator\\桌面\\QQ.lnk"; //快捷方式的路径
//    HRESULT hres;
//    IShellLink* psl;
//    IPersistFile* ppf;
//    WIN32_FIND_DATA fd;
//    //初始化COM库
//    hres = CoInitialize(NULL);
//    if (!SUCCEEDED(hres))
//        return false;
//    hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&psl); //建立一个IID_IShellLink实例
//    if (!SUCCEEDED(hres))
//        return false;
//    psl->SetPath(path);//设置目标的路径
//    psl->SetWorkingDirectory(work); //设置目标的起始位置
//    hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);
//    //确保快捷方式路径由ANSI字符串组成
//    if (SUCCEEDED(hres))
//    {
//        WCHAR wsz[MAX_PATH];
//        MultiByteToWideChar(CP_ACP, 0, (LPCCH)dir, -1, wsz, MAX_PATH);
//        hres = ppf->Save(wsz, TRUE);
//        ppf->Release();
//    }
//    psl->Release();
//    hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&psl); //建立一个IID_IShellLink实例
//    if (!SUCCEEDED(hres))
//        return false;
//    TCHAR filepath[MAX_PATH];
//    hres = psl->GetPath(filepath, MAX_PATH, &fd, 0);
//    cout << path << endl;
//    psl->Release();
//
//    CoUninitialize(); //释放com接口
//    return hres;
//}

/*
需要的头文件：#include <shlobj.h>
IShellLink主要成员：
1、GetArguments：获得参数信息
2、GetDescription：获得描述信息（备注行）
3、GetHotkey：获得快捷键
4、GetIconLocation：获得图标
5、GetIDList：获得快捷方式的目标对象的item identifier list(Windows外壳中的每个对象如文件，目录和打印机等都有唯一的item identifiler list)
6、GetPath: 获得快捷方式的目标文件或目录的全路径
7、GetShowCmd：获得快捷方式的运行方式，比如常规窗口，最大化
8、GetWorkingDirectory：获得工作目录
9、Resolve：按照一定的搜索规则试图获得目标对象，即使目标对象已经被删除或移动，重命名下面是对应信息的设置方法
10、SetArguments
11、SetDescription
12、SetHotkey
13、SetIconLocation
14、SetIDList
15、SetPath
16、SetRelativePat
17、SetShowCmd
18、SetWorkingDirectory
IPersistFile主要成员：
1、IsDirty：Checks an object for changes since it was last saved to its current file.
2、Load：Opens the specified file and initializes an object from the file contents.
3、Save：Saves the object into the specified file.
4、SaveCompleted：Notifies the object that it can revert from NoScribble mode to Normal mode.
5、GetCurFile：Gets the current name of the file associated with the object.
详细的用法还是参考MSDN，这些不是本文的重点。。常用的是Load和Save
HRESULT Load(LPCOLSTR pszFileName, //快捷方式的文件名，应该是ANSI字符
	DWORD dwMode            //读取方式);
	dwMode可取如下值：
	STGM_READ：只读
	STGM_WRITE：只写
	STGM_READWRITE：读写
	返回值：
	S_OK ：成功
	E_OUTOFMEMORY ：失败，原因是因为内存不足
	E_FAIL ：失败，原因是除内存不足的其它的原因
	程序一般的步骤：
	一、初始化COM接口
	二、创建IShellLink对象
	三、从IShellLink对象中获取IPersistFile对象接口
	四、操作IShellLink对象
	五、释放IPersistFile对象接口
	六、释放IShellLink对象
	七、释放COM接口
*/
#endif // 0
