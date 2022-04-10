#if 0
#include <stdio.h>
#include <WINDOWS.H>
#include <string>
#include <iostream>

#pragma warning(disable:4996)
#define SEND_BUFF_SIZE 1024
using namespace std;
void TcharToChar(const TCHAR* tchar, char* _char)
{
    int iLength;
    //获取字节长度   
    iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);
    //将tchar值赋给_char    
    WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);
}

void CharToTchar(const char* _char, TCHAR* tchar)
{
    int iLength;

    iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
    MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, tchar, iLength);
}

//实现去除执行结果中的 "命令\n"
void print(char* cmdstr)
{

    while (*((char*)cmdstr++) != '\n');
    printf(cmdstr);
}

int CmdProcessLine() {
    HANDLE hReadPipe1, hWritePipe1, hReadPipe2, hWritePipe2; //四个HANDLE 用来创建两个管道
    CHAR Buff[SEND_BUFF_SIZE] = { 0 };
    CHAR sendBuff[SEND_BUFF_SIZE] = ("dir \n");
    //安全属性的东西
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = 0;
    sa.bInheritHandle = true;
    int ret;
    if (!CreatePipe(&hReadPipe1, &hWritePipe1, &sa, 0))//创建两个匿名管道，以改变DOS的标准输入输出
        return -1;
    if (!CreatePipe(&hReadPipe2, &hWritePipe2, &sa, 0))
        return -1;

    //启动信息
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    //GetStartupInfo(&si);
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    si.wShowWindow = SW_HIDE;
    si.hStdInput = hReadPipe2;
    si.hStdOutput = si.hStdError = hWritePipe1;
    TCHAR cmdLine[256] = { 0 };
    char cmdLineTest[256] = { 0 };
    GetSystemDirectory(cmdLine, sizeof(cmdLine));

    TcharToChar(cmdLine, cmdLineTest);
    strcat(cmdLineTest, ("\\cmd.exe"));
    CharToTchar(cmdLineTest, cmdLine);

    PROCESS_INFORMATION ProcessInformation;
    if (CreateProcess(cmdLine, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &si, &ProcessInformation) == 0)
    {

        return -1;
    }
    unsigned long lBytesRead, lBytesWrite;//存放实际读写字节的变量
    while (TRUE) {
        lBytesRead = 0;
        Sleep(50);//等待cmd程序执行
        ret = PeekNamedPipe(hReadPipe1, Buff, SEND_BUFF_SIZE, &lBytesRead, 0, 0);//管道是否有数据可读
        if (lBytesRead)
        {
            //第一次可以读到cmd的初始化信息
            ret = ReadFile(hReadPipe1, Buff, SEND_BUFF_SIZE, &lBytesRead, 0);//读取管道里的数据
            //如果读到数据，则对数据进行下一步处理
            print(Buff);
            ZeroMemory(Buff, sizeof(Buff));
        }
        else {
            ////解决方案  估计windows是以"\r\n"结束的吧，所以要在命令执行后，显示完全后写入这个
            ///***********************************************************/
            //WriteFile(hWritePipe2, "\r\n", 2, &lBytesWrite, 0);
            //Sleep(100);
            //ret = ReadFile(hReadPipe1, Buff, SEND_BUFF_SIZE, &lBytesWrite, 0);//读取管道里的数据
            ///***********************************************************/


            //管道中无数据时输入命令，以回车结束
            char ch;
            int count = 0;
            ZeroMemory(sendBuff, sizeof(sendBuff));
            while ((ch = getchar()) != '\n')
            {
                sendBuff[count] = ch;
                count++;
            }
            sendBuff[count++] = '\n';
            if (!WriteFile(hWritePipe2, sendBuff, count, &lBytesWrite, 0))//写入数据                     
            {
                printf("WriteFile Error!!\n");
                return -1;
            }
            //等待cmd程序执行
            Sleep(100);
        }
    }
    return 0;
}

//获取命令行
string getCmdResult(const string& strCmd)//传参string格式命令，返回值string格式；
{
    char buf[10240] = { 0 };
    FILE* pf = NULL;
    if ((pf = _popen(strCmd.c_str(), "rt")) == NULL)
        return "";

    string strResult;
    while (fgets(buf, sizeof buf, pf))
        strResult += buf;
    _pclose(pf);
    unsigned int iSize = strResult.size();
    if (iSize > 0 && strResult[iSize - 1] == '\n')
        strResult = strResult.substr(0, iSize - 1);
    return strResult;
}

void CmdResult() {
    char buf[10240] = { 0 };
    FILE* pf = NULL;
    if ((pf = _popen("cmd\0", "rt")) == NULL) {
        fprintf(stderr, "error");
        return 0;
    }
    while (fgets(buf, sizeof(buf), pf) != NULL) {
        fprintf(stdout, "%s", buf);
    }
    _pclose(pf);
}
#ifdef linux
//C/C++ 程序中调用命令行命令并获取命令行输出结果
/// <summary>
/// 在 c/c++ 程序中，可以使用 system（）函数运行命令行命令，但是只能得到该命令行的 int 型返回值，
/// 并不能获得显示结果。例如system(“ls”)只能得到0或非0，如果要获得ls的执行结果，则要通过管道来完成的。
/// 首先用popen打开一个命令行的管道，然后通过fgets获得该管道传输的内容，也就是命令行运行的结果。
/// </summary>
/// <param name="cmd"></param>
/// <param name="result"></param>
void executeCMD(const char* cmd, char* result)
{
    char buf_ps[1024];
    char ps[1024] = { 0 };
    FILE* ptr;
    strcpy(ps, cmd);
    if ((ptr = popen(ps, "r")) != NULL)
    {
        while (fgets(buf_ps, 1024, ptr) != NULL)
        {
            strcat(result, buf_ps);
            if (strlen(result) > 1024)
                break;
        }
        pclose(ptr);
        ptr = NULL;
    }
    else
        printf("popen %s error\n", ps);
}

/// <summary>
/// 在这段代码中，参数cmd为要执行的命令行，result为命令行运行结果。输入的cmd命令最好用... 2>&1 的形式，
/// 这样将标准错误也读进来。一个完整的例子是：
/// </summary>
void executeCMD() {
    FILE* fp = NULL;
    char cmd[512];
    sprintf(cmd, "pwd 2>/dev/null; echo $?");
    if ((fp = popen(cmd, "r")) != NULL)
    {
        fgets(cmd, sizeof(cmd), fp);
        pclose(fp);
    }
    //0 成功， 1 失败
    printf("cmd is %s\n", cmd);
}
#endif // linux


int main()
{
    //demo 1
    //CmdProcessLine();

    //demo 2
    //printf("USERPROFILE = %s\n", getenv("USERPROFILE"));
    //printf("HOMEDRIVE   = %s\n", getenv("HOMEDRIVE"));
    //printf("HOMEPATH    = %s\n", getenv("HOMEPATH"));
    ////cout << getenv("USERPROFILE");
    //string str = "";
    //do{
    //    cout <<"Test#1>";
    //    getline(cin, str);
    //    cout <<getCmdResult(str)<<endl;
    //} while (true);

    //demo 3
    CmdResult();
    system("pause");
    return 0;
}
#endif // 0
