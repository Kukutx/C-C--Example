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
    //��ȡ�ֽڳ���   
    iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);
    //��tcharֵ����_char    
    WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);
}

void CharToTchar(const char* _char, TCHAR* tchar)
{
    int iLength;

    iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
    MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, tchar, iLength);
}

//ʵ��ȥ��ִ�н���е� "����\n"
void print(char* cmdstr)
{

    while (*((char*)cmdstr++) != '\n');
    printf(cmdstr);
}

int CmdProcessLine() {
    HANDLE hReadPipe1, hWritePipe1, hReadPipe2, hWritePipe2; //�ĸ�HANDLE �������������ܵ�
    CHAR Buff[SEND_BUFF_SIZE] = { 0 };
    CHAR sendBuff[SEND_BUFF_SIZE] = ("dir \n");
    //��ȫ���ԵĶ���
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = 0;
    sa.bInheritHandle = true;
    int ret;
    if (!CreatePipe(&hReadPipe1, &hWritePipe1, &sa, 0))//�������������ܵ����Ըı�DOS�ı�׼�������
        return -1;
    if (!CreatePipe(&hReadPipe2, &hWritePipe2, &sa, 0))
        return -1;

    //������Ϣ
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
    unsigned long lBytesRead, lBytesWrite;//���ʵ�ʶ�д�ֽڵı���
    while (TRUE) {
        lBytesRead = 0;
        Sleep(50);//�ȴ�cmd����ִ��
        ret = PeekNamedPipe(hReadPipe1, Buff, SEND_BUFF_SIZE, &lBytesRead, 0, 0);//�ܵ��Ƿ������ݿɶ�
        if (lBytesRead)
        {
            //��һ�ο��Զ���cmd�ĳ�ʼ����Ϣ
            ret = ReadFile(hReadPipe1, Buff, SEND_BUFF_SIZE, &lBytesRead, 0);//��ȡ�ܵ��������
            //����������ݣ�������ݽ�����һ������
            print(Buff);
            ZeroMemory(Buff, sizeof(Buff));
        }
        else {
            ////�������  ����windows����"\r\n"�����İɣ�����Ҫ������ִ�к���ʾ��ȫ��д�����
            ///***********************************************************/
            //WriteFile(hWritePipe2, "\r\n", 2, &lBytesWrite, 0);
            //Sleep(100);
            //ret = ReadFile(hReadPipe1, Buff, SEND_BUFF_SIZE, &lBytesWrite, 0);//��ȡ�ܵ��������
            ///***********************************************************/


            //�ܵ���������ʱ��������Իس�����
            char ch;
            int count = 0;
            ZeroMemory(sendBuff, sizeof(sendBuff));
            while ((ch = getchar()) != '\n')
            {
                sendBuff[count] = ch;
                count++;
            }
            sendBuff[count++] = '\n';
            if (!WriteFile(hWritePipe2, sendBuff, count, &lBytesWrite, 0))//д������                     
            {
                printf("WriteFile Error!!\n");
                return -1;
            }
            //�ȴ�cmd����ִ��
            Sleep(100);
        }
    }
    return 0;
}

//��ȡ������
string getCmdResult(const string& strCmd)//����string��ʽ�������ֵstring��ʽ��
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
//C/C++ �����е��������������ȡ������������
/// <summary>
/// �� c/c++ �����У�����ʹ�� system�������������������������ֻ�ܵõ��������е� int �ͷ���ֵ��
/// �����ܻ����ʾ���������system(��ls��)ֻ�ܵõ�0���0�����Ҫ���ls��ִ�н������Ҫͨ���ܵ�����ɵġ�
/// ������popen��һ�������еĹܵ���Ȼ��ͨ��fgets��øùܵ���������ݣ�Ҳ�������������еĽ����
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
/// ����δ����У�����cmdΪҪִ�е������У�resultΪ���������н���������cmd���������... 2>&1 ����ʽ��
/// ��������׼����Ҳ��������һ�������������ǣ�
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
    //0 �ɹ��� 1 ʧ��
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
