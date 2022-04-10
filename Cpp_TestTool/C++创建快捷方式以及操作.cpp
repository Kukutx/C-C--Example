#if 0
#include <iostream>
#include <Windows.h>
#include <ShlObj.h>
using namespace std;
//�ɲο�C++������ݷ�ʽ(lnk��url)����ӵ���ʼ�˵������桢������.md
//�޸Ŀ�ݷ�ʽ��Ŀ���ַ����������ݷ�ʽ���¶����Ŀ���ַ
bool CrnModifyShortcutArguments(LPCWSTR lpszLnkFilePath, LPCWSTR strArguments)
{
	//�ж��ļ��Ƿ����
	bool bResult = (CoInitialize(NULL) == S_OK);
	if (bResult)
	{
		IShellLink* pShellLink;
		//����IShellLink����
		bResult = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
			IID_IShellLink, (void**)&pShellLink) >= 0;

		if (!bResult)
			return false;

		//��IShellLink�����л�ȡIPersistFile�ӿ�
		IPersistFile* ppf;
		bResult = pShellLink->QueryInterface(IID_IPersistFile, (void**)&ppf) >= 0;
		if (!bResult)
		{
			pShellLink->Release();
			ppf->Release();
			return false;
		}
		//���ؿ�ݷ�ʽ�ļ�
		bResult = ppf->Load(lpszLnkFilePath, TRUE) >= 0;
		if (!bResult)
		{
			pShellLink->Release();
			ppf->Release();
			return false;
		}
		//�޸Ŀ�ݷ�ʽ�ļ�����
		bResult = pShellLink->SetPath(strArguments) >= 0;
		if (!bResult)
		{
			pShellLink->Release();
			ppf->Release();
			return false;
		}
		//���±����ݷ�ʽ�ļ�
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
//������ݷ�ʽ
void CreateLink()
{
	/*
	��C++������ݷ�ʽ
	��Ҫ�õ�����COM�����IShellLink��IPersistFile
	IPersistFile��Ҫ�õ�������Ա������
	1��Save���������ݵ��ļ���ȥ
	2��Load����ȡ
	Load�ĺ���ԭ��
	HRESULT Load(
	LPCOLSTR pszFileName, //��ݷ�ʽ���ļ�����Ӧ����ANSI�ַ�
	DWORD dwMode //��ȡ��ʽ
	);
	dwMode��ȡ����ֵ��
	STGM_READ��ֻ��
	STGM_WRITE��ֻд
	STGM_READWRITE����д
	IShellLink��Ҫ��Ա��
	1��GetArguments����ò�����Ϣ
	2��GetDescription�����������Ϣ����ע�У�
	3��GetHotkey����ÿ�ݼ�
	4��GetIconLocation�����ͼ��
	5��GetIDList����ÿ�ݷ�ʽ��Ŀ������item identifier list (Windows����е�ÿ���������ļ���Ŀ¼�ʹ�ӡ���ȶ���Ψһ��item identifiler list)
	6��GetPath: ��ÿ�ݷ�ʽ��Ŀ���ļ���Ŀ¼��ȫ·��
	7��GetShowCmd����ÿ�ݷ�ʽ�����з�ʽ�����糣�洰�ڣ����
	8��GetWorkingDirectory����ù���Ŀ¼
	9��Resolve������һ��������������ͼ���Ŀ����󣬼�ʹĿ������Ѿ���ɾ�����ƶ���������
	�����Ƕ�Ӧ��Ϣ�����÷���
	10��SetArguments
	11��SetDescription
	12��SetHotkey
	13��SetIconLocation
	14��SetIDList
	15��SetPath
	16��SetRelativePat
	17��SetShowCmd
	18��SetWorkingDirectory
	һ������������£�
	һ����ʼ��COM�ӿ�
	��������IShellLink����
	������IShellLink�����л�ȡIPersistFile����ӿ�
	�ġ�����IShellLink����
	�塢�ͷ�IPersistFile����ӿ�
	�����ͷ�IShellLink����
	�ߡ��ͷ�COM�ӿ�
	*/
	//��ʼ��com���
	::CoInitialize(NULL);
	LPITEMIDLIST pitemIlist;
	SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pitemIlist);
	TCHAR szPath[MAX_PATH]{ 0 };
	//��LPITEMIDLIST ��ȡ�����·��
	SHGetPathFromIDList(pitemIlist, szPath);
	wcscat_s(szPath, L"\\newLink.lnk");
	IShellLink* pShellLink;
	IPersistFile* pPerFile;
	//��������
	CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
		IID_IShellLink, (LPVOID*)&pShellLink);
	TCHAR szSrcPath[MAX_PATH]{ 0 };
	GetModuleFileName(NULL, szSrcPath, MAX_PATH);
	//  ��IShellLink��ȡ��IPersistFile�ӿ�
	pShellLink->QueryInterface(IID_IPersistFile, (LPVOID*)&pPerFile);
	//��������·��
	pShellLink->SetPath(szSrcPath);
	//�����ȼ� ��"Ctrl+Alt +Q"
	pShellLink->SetHotkey(MAKEWORD('Q', HOTKEYF_CONTROL | HOTKEYF_ALT));
	//����ͼ��
	pShellLink->SetIconLocation(L"C:\\Users\\liuzh\\Downloads\\test\\Cpp_TestTool\\link.ico", 0);
	//����·��
	pPerFile->Save(szPath, false);
	//�ͷţ�
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
//    const TCHAR* path = L"D:\\Program Files\\Tencent\\QQ\\Bin\\QQ.exe";//Ŀ���·��
//    const TCHAR* work = L"D:\\Program Files\\Tencent\\QQ\\Bin";//��ʼλ��
//    const TCHAR* dir = L"C:\\Documents and Settings\\Administrator\\����\\QQ.lnk"; //��ݷ�ʽ��·��
//    HRESULT hres;
//    IShellLink* psl;
//    IPersistFile* ppf;
//    WIN32_FIND_DATA fd;
//    //��ʼ��COM��
//    hres = CoInitialize(NULL);
//    if (!SUCCEEDED(hres))
//        return false;
//    hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&psl); //����һ��IID_IShellLinkʵ��
//    if (!SUCCEEDED(hres))
//        return false;
//    psl->SetPath(path);//����Ŀ���·��
//    psl->SetWorkingDirectory(work); //����Ŀ�����ʼλ��
//    hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);
//    //ȷ����ݷ�ʽ·����ANSI�ַ������
//    if (SUCCEEDED(hres))
//    {
//        WCHAR wsz[MAX_PATH];
//        MultiByteToWideChar(CP_ACP, 0, (LPCCH)dir, -1, wsz, MAX_PATH);
//        hres = ppf->Save(wsz, TRUE);
//        ppf->Release();
//    }
//    psl->Release();
//    hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&psl); //����һ��IID_IShellLinkʵ��
//    if (!SUCCEEDED(hres))
//        return false;
//    TCHAR filepath[MAX_PATH];
//    hres = psl->GetPath(filepath, MAX_PATH, &fd, 0);
//    cout << path << endl;
//    psl->Release();
//
//    CoUninitialize(); //�ͷ�com�ӿ�
//    return hres;
//}

/*
��Ҫ��ͷ�ļ���#include <shlobj.h>
IShellLink��Ҫ��Ա��
1��GetArguments����ò�����Ϣ
2��GetDescription�����������Ϣ����ע�У�
3��GetHotkey����ÿ�ݼ�
4��GetIconLocation�����ͼ��
5��GetIDList����ÿ�ݷ�ʽ��Ŀ������item identifier list(Windows����е�ÿ���������ļ���Ŀ¼�ʹ�ӡ���ȶ���Ψһ��item identifiler list)
6��GetPath: ��ÿ�ݷ�ʽ��Ŀ���ļ���Ŀ¼��ȫ·��
7��GetShowCmd����ÿ�ݷ�ʽ�����з�ʽ�����糣�洰�ڣ����
8��GetWorkingDirectory����ù���Ŀ¼
9��Resolve������һ��������������ͼ���Ŀ����󣬼�ʹĿ������Ѿ���ɾ�����ƶ��������������Ƕ�Ӧ��Ϣ�����÷���
10��SetArguments
11��SetDescription
12��SetHotkey
13��SetIconLocation
14��SetIDList
15��SetPath
16��SetRelativePat
17��SetShowCmd
18��SetWorkingDirectory
IPersistFile��Ҫ��Ա��
1��IsDirty��Checks an object for changes since it was last saved to its current file.
2��Load��Opens the specified file and initializes an object from the file contents.
3��Save��Saves the object into the specified file.
4��SaveCompleted��Notifies the object that it can revert from NoScribble mode to Normal mode.
5��GetCurFile��Gets the current name of the file associated with the object.
��ϸ���÷����ǲο�MSDN����Щ���Ǳ��ĵ��ص㡣�����õ���Load��Save
HRESULT Load(LPCOLSTR pszFileName, //��ݷ�ʽ���ļ�����Ӧ����ANSI�ַ�
	DWORD dwMode            //��ȡ��ʽ);
	dwMode��ȡ����ֵ��
	STGM_READ��ֻ��
	STGM_WRITE��ֻд
	STGM_READWRITE����д
	����ֵ��
	S_OK ���ɹ�
	E_OUTOFMEMORY ��ʧ�ܣ�ԭ������Ϊ�ڴ治��
	E_FAIL ��ʧ�ܣ�ԭ���ǳ��ڴ治���������ԭ��
	����һ��Ĳ��裺
	һ����ʼ��COM�ӿ�
	��������IShellLink����
	������IShellLink�����л�ȡIPersistFile����ӿ�
	�ġ�����IShellLink����
	�塢�ͷ�IPersistFile����ӿ�
	�����ͷ�IShellLink����
	�ߡ��ͷ�COM�ӿ�
*/
#endif // 0
