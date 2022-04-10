# Windows编程捕获特定窗口及键盘鼠标消息模拟-爱代码爱编程

### Windows编程捕获特定窗口及键盘鼠标消息模拟

- [一、简介](https://icode.best/i/80555530773811#_2)
- [二、使用到的API简介](https://icode.best/i/80555530773811#API_22)
- [三、获取Windows记事本的编辑区窗口的句柄并模拟输入操作](https://icode.best/i/80555530773811#Windows_35)
- [四、后记](https://icode.best/i/80555530773811#_139)

# 一、简介

窗口是Windows的核心组件，Windoows下的绝大部分应用都是利用Windows提供的原生窗口，通过一些GUI编程框架（如Qt，MFC）加以渲染来生成的。本质上讲，这些框架都是基于Windows提供的一些API函数作进一步封装来实现的。

对于一个应用程序最重要的功能就是与人的交互，使得我们可以通过键盘输入和鼠标输入来实现对应用程序的控制。

Windows是利用**消息**(Message)来实现窗口与用户的输入之间通信的，当应用程序在内存中初始化注册成功后，操作系统会为应用程序创建一个**消息队列**，应用程序通过在消息队列中取出消息来判断要执行的相应操作，具体如下：
![在这里插入图片描述](https://img-bc.icode.best/20191219193739809.jpg)

- ① 操作系统捕获用户的键盘或者鼠标输入。
- ② 操作系统根据当前的焦点窗口判断当前用户的输入是属于哪一个应用的，然后将消息投递到相应的应用程序的消息队列中。
- ③ 应用程序调用**GetMessage**()函数从消息队列中获取一条消息，根据消息的类型(比如按下鼠标左键，按下w键等)进行处理。
- ④ 应用程序调用**DispatchMessage**()函数将消息回传给操作系统。
- ⑤ 操作系统收到应用程序的回传之后，调用应用程序的窗口过程函数处理这条消息。

# 二、使用到的API简介

这里主要是使用Windows提供的API，利用以上的消息机制，来模拟操作系统给某一个应用程序发送消息。

使用到的API函数在<**Windows.h**>头文件中，使用到了以下函数：

- FindWindow()函数：遍历当前内存中的所有注册窗口，根据相关信息搜索匹配的窗口，返回窗口的句柄。
- FindWindowEx()函数：根据传入的父窗口(句柄)，搜索满足相关条件的子窗口(控件也是窗口)，找到第一个即退出，返回窗口的句柄。
- PostMessage()函数：向指定窗口的消息队列发送消息，可以指定消息的类型，类似以上过程②。
- GetWindow()函数：根据传入的窗口(句柄)以及输入的关系信息，查找满足条件的窗口，返回窗口的句柄。
- EnumChildWindows()和EnumChildProc()函数：其中EnumChildProc()函数是EnumChildWindows()的回调函数，EnumChildWindows()会穷举传入窗口(句柄)的所有子窗口，而EnumChileProc()回调函数接收到每个子窗口的句柄，然后进行相关的操作。

以上函数的具体方法可以查阅MSDN官方文档。

# 三、获取Windows记事本的编辑区窗口的句柄并模拟输入操作

## 1、分析

主要包括以下几个步骤：

1. 获取记事本窗口的句柄。
2. 遍历记事本窗口的所有子窗口，找到编辑区子窗口。
3. 向编辑区子窗口的消息队列发送消息。
4. 子窗口作出响应。

## 2、代码一

```cpp
#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
	HWND htext = FindWindow(NULL, L"无标题 - 记事本");  //找到记事本窗口的句柄
	if (!htext)
	{
		cout << "not find text!" << endl;
		return 0;
	}
	HWND hchild = FindWindowEx(htext, NULL, L"Edit", NULL);  //找到记事本的编辑区子窗口
	if (!hchild)
	{
		cout << "not find child!" << endl;
		return 0;
	}
	/*像编辑区发送按键按下的消息，内容分别hello world*/
	PostMessage(hchild, WM_KEYDOWN, 0x48, 0);
	PostMessage(hchild, WM_KEYDOWN, 0x45, 0);
	PostMessage(hchild, WM_KEYDOWN, 0x4c, 0);
	PostMessage(hchild, WM_KEYDOWN, 0x4c, 0);
	PostMessage(hchild, WM_KEYDOWN, 0x4f, 0);
	PostMessage(hchild, WM_KEYDOWN, VK_SPACE, 0);
	PostMessage(hchild, WM_KEYDOWN, 0x57, 0);
	PostMessage(hchild, WM_KEYDOWN, 0x4f, 0);
	PostMessage(hchild, WM_KEYDOWN, 0x52, 0);
	PostMessage(hchild, WM_KEYDOWN, 0x4c, 0);
	PostMessage(hchild, WM_KEYDOWN, 0x44, 0);
	return 1;
}
```

运行结果如下：
![在这里插入图片描述](https://img-bc.icode.best/20191219205835275.jpg)
可以看到在记事本中成功输入了hello world，完全由代码生成的。

## 3、代码二

除了以上利用FindWindowEx()函数查找子窗口外，还可以利用EnumChildWindows()函数来遍历所有窗口，对所有子窗口进行操作。以下是代码：

```cpp
#include <iostream>
#include <string.h>
#include <Windows.h>
using namespace std;
//对枚举的子窗口进行操作
BOOL CALLBACK EnumChildProc(HWND hchild, LPARAM lparam)
{
	wchar_t cls_name[50];
	GetClassName(hchild, cls_name, 50);  //获取子窗口的类名
	wprintf(L"%s", cls_name);      //将子窗口的类名打印到屏幕
	wchar_t* p = wcsstr(cls_name, (wchar_t*)lparam);  //判断查找到的子窗口是否是编辑区窗口
	if (p == NULL)
	{
		return TRUE;
	}
	else
	{
		/*像编辑区发送按键按下的消息，内容分别hello world*/
		PostMessage(hchild, WM_KEYDOWN, 0x48, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x45, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x4c, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x4c, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x4f, 0);
		PostMessage(hchild, WM_KEYDOWN, VK_SPACE, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x57, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x4f, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x52, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x4c, 0);
		PostMessage(hchild, WM_KEYDOWN, 0x44, 0);
		return TRUE;

	}
}

int main()
{
	HWND htext = FindWindow(NULL, L"无标题 - 记事本");  //找到记事本窗口的句柄
	if (!htext)
	{
		cout << "not find text!" << endl;
		return 0;
	}
	wchar_t class_name[] = { L"Edit" };   //设定要编辑区窗口的类名
	EnumChildWindows(htext, EnumChildProc, (LPARAM)class_name);  //枚举所有子窗口，在EnumChildProc函数中对这些窗口一一操作
	return 1;
}
```

以下是运行结果：
![在这里插入图片描述](https://img-bc.icode.best/2019121921484923.jpg)
可以看到也得到了正确的结果，另外通过命令行发现输出了记事本的编辑区窗口的类名是：Editmsctls_statusbar32。

# 四、后记

基于这种方法，可以编写一些软件的注册机。例如一些软件可能需要输入激活码，这时可以写一个注册机，通过穷举输入到窗口中，来暴力破解软件的激活码。