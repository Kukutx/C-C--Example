#if 0
#include <iostream>  
#include <string>  
using namespace std;
#ifdef linux  
#include <unistd.h>  
#include <pwd.h>  

void GetUserAndPid()
{
    uid_t userid;
    struct passwd* pwd;
    userid = getuid();
    pwd = getpwuid(userid);
    FILE* fp = fopen("/home/stamp_temp/ao.log", "ab+");
    fprintf(fp, "user:%s, pid:%d, ppid:%d, uid:%d, gid:%d\n", pwd->pw_name, getpid(), getppid(), getuid(), getgid());
    fclose(fp);
}
#endif  

#ifdef _WIN32  
#include<Windows.h>  
#endif  

void TcharToChar(const TCHAR* tchar, char* _char)
{
    int iLength;
    //��ȡ�ֽڳ���   
    iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);
    //��tcharֵ����_char    
    WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);
}

string getUserName()
{
#if defined linux   //linux system  
    uid_t userid;
    struct passwd* pwd;
    userid = getuid();
    pwd = getpwuid(userid);
    return pwd->pw_name;

#elif defined _WIN32  //windows system  
    const int MAX_LEN = 100;
    char str[100];
    TCHAR szBuffer[MAX_LEN] = L"\0";
    DWORD len = MAX_LEN;
    if (GetUserName(szBuffer, &len))     //�û���������szBuffer��,len���û����ĳ���  
    {
        TcharToChar(szBuffer, str);
        return str;
    }
#else  //outher system  
    return "";
#endif  
    }

int main()
{
    string ss = getUserName();
    cout << ss << endl;

    //GetUserAndPid()   //linux����������
    return 0;
}
#endif // 0
