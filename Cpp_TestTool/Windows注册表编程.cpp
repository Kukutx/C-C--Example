#if 0
#include <Windows.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
    HKEY hKey;
    DWORD dwType;
    TCHAR d[4096];
    DWORD nLen = sizeof(d);
    const TCHAR* data = L"https://www.baidu.com/";
    RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Internet Explorer\\Main", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, &hKey);
    RegQueryValueEx(hKey, L"Start Page", 0, &dwType, (LPBYTE)d, &nLen);
    printf("before change: %ls\n", d);
    memset(d, 0, wcslen(d));
    RegSetValueEx(hKey, L"Start Page", 0, REG_SZ, (BYTE*)data, wcslen(data) * 10);
    RegQueryValueEx(hKey, L"Start Page", 0, &dwType, (LPBYTE)d, &nLen);
    printf("after change: %ls\n", d);
    //RegDeleteValue(hKey, "Start Page");
    //RegQueryValueEx(hKey, "Start Page", 0, &dwType, (LPBYTE)d, &nLen);
    //printf("after delete: %s\n", d);
    RegCloseKey(hKey);
    system("pause");
    return 0;
}

/*
这里稍微说一下这段代码的含义，总的作用就是修改ie浏览器的默认页面，改成baidu的首页。那么首先利用RegOpenKeyEx打开注册表，并且将句柄放到先前声明的hKey中，
这里的参数前两个比较好理解，分别是注册表的主键和子建，第三个REG_OPTION_NON_VOLATILE意思是将注册表项存入文件中，使得重启后修改有效，相反的就是REG_OPTION_VOLATILE，意思是重启后无效，KEY_ALL_ACCESS的意思是打开子建后允许任意操作，最后一个是用来存放句柄的。
之后我们使用RegQueryKeyEx函数进行查询，这里第三个选项为保留值，一般为0，第四个是我门声明的一个DWORD变量，这个是用来存放查询的注册表值的类型，第五个是用来存放查询后的值的缓冲区，然后是缓冲区的大小。
查询后我们在利用RegSetValueEx函数进行修改，第三个选项为保留值，一般为0，第四个选项是要修改的注册表的类型，这里是REG_SZ，之后是要修改的数据的缓冲区以及他的大小。
当然了，使用RegDeleteValue即可删除注册表选项，参数也很简单，一个句柄，一个要删除的名字
最后用RegCloseKey来关闭注册表的句柄即可。
*/
#endif // 0
