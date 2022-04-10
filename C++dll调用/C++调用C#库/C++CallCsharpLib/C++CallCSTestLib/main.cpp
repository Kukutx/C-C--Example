using namespace System;
using namespace CSharpTestDll;
//#using "..\CSharpTestDll\bin\Debug\CSharpTestDll.dll"  //类似#include头文件的操作
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
* 创建项目要选择 类库（ .NET Framework）而不是 类库（ .NET Core），且要选对对应版本，不然会出错
* 使用#using引用C# DLL，而不是#include，但是如果直接引用添加可以省去这个操作；
* 别忘了using namespace CSharpTestDll，代表使用这个命名空间；
* 使用C++/clr语法，采用正确的访问托管对象，即：使用'^'，而不是星号'*
* 注意要使用同一vs版本编辑器生成代码
* 如果c++编译出现错误：fatal error C1190: 托管目标代码需要“/clr”选项，请选择项目-》属性-》配置属性-》常规-》公共语言运行时支持-》公共语言运行时支持(/clr)
*/