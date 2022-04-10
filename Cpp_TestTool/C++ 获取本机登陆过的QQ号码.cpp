#if 0
#include<iostream>
#include <vector>
#include <Windows.h>
#include <Shlobj.h>
#include <atlstr.h>
#pragma comment(lib, "shell32.lib")
using namespace std;

int main() {
    vector<CString> m_qqNum;
    TCHAR pathBuffer[MAX_PATH] = { 0 };
    ::SHGetSpecialFolderPath(NULL, pathBuffer, CSIDL_APPDATA, FALSE);
    CString strPath(pathBuffer);
    strPath += _T("\\Tencent\\Users\\*.*");

    HANDLE hFile;
    WIN32_FIND_DATA fileData;
    hFile = FindFirstFile(strPath, &fileData);
    FindNextFile(hFile, &fileData);
    while (FindNextFile(hFile, &fileData))
    {
        // 如果是一个文件夹目录
        if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            m_qqNum.push_back(fileData.cFileName);
            fileData.cFileName;
        }
    }
    for (auto& i : m_qqNum)
    {
        cout << i + "\n";
    }
    return 0;
}
#endif // 0
