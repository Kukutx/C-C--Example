#if 0
//防止程序多开
#include <iostream>
#include <windows.h>
int main()
{
    //默认使用互斥体防多开
    HANDLE g_hMutex = CreateMutex(NULL, FALSE, L"HackTool");
    //如果创建互斥体失败或互斥体已经存在
    if (g_hMutex == NULL || GetLastError() == ERROR_ALREADY_EXISTS)
    {
        MessageBox(NULL, L"yyy", L"请勿双开本程序，即将退出", NULL);
        exit(0);//正常退出
    }
    std::cout << "Hello World!\n";
    system("pause");
    return 0;
}
#endif // 0


