using namespace System;
using namespace CSharpTestDll;
//#using "..\CSharpTestDll\bin\Debug\CSharpTestDll.dll"  //����#includeͷ�ļ��Ĳ���
#include<iostream>
using namespace std;
int main()
{
    Console::WriteLine("Hello World\n");

    cout << "Hello World!1111\n";
    CharpClass^ c = gcnew CharpClass();

    c->Name = "zzj";
    cout << "\n";
    c->HelloWord();
    cout << c->fnAdd(1, 2) << endl;

    printf("%s\n", c->Name);
    system("pause");
    return 0;
}


/*
* ������ĿҪѡ�� ��⣨ .NET Framework�������� ��⣨ .NET Core������Ҫѡ�Զ�Ӧ�汾����Ȼ�����
* ʹ��#using����C# DLL��������#include���������ֱ��������ӿ���ʡȥ���������
* ������using namespace CSharpTestDll������ʹ����������ռ䣻
* ʹ��C++/clr�﷨��������ȷ�ķ����йܶ��󣬼���ʹ��'^'���������Ǻ�'*
* ע��Ҫʹ��ͬһvs�汾�༭�����ɴ���
* ���c++������ִ���fatal error C1190: �й�Ŀ�������Ҫ��/clr��ѡ���ѡ����Ŀ-������-����������-������-��������������ʱ֧��-��������������ʱ֧��(/clr)
*/