#if 0
/*
原理
爬虫从原理上来，简单来讲就是发送http/https请求+解析html页面，获取页面上的目标数据。无论采用何种语言，都需要和server建立若干个TCP连接，再将http请求写入TCP socket中，等待server返回数据。
它本质上就是一个事件循环（event loop），用伪代码来描述基本上就是这样：
初始化epoll，与server建立TCP连接。
从请求队列（如你要爬取的网站列表）中取出url和http请求。
将http请求写入到这个TCP socket中，并把这个socket加入epoll中。
检查活动事件（epoll_wait）。
分析处理事件（如html页面），然后把剩余未处理过的url和http继续放回队列中供下一次爬取调用
(如果你写的爬虫只是简单的单线程串行可以不用放回）。
回到第2步。
当程序从请求队列里拿到一个url后，需要去下载与这个url对应的页面，进而解析出真正需要的数据，
然后才能把它的下一层url加入队列中，这是一种典型的阻塞程序。但由于爬虫是网络I/O密集型程序，
将代码写成非阻塞式的多线程程序并不会使运行效率产生飞跃式的提升，相反甚至可能会造成请求队列的调用混乱，
这也为什么爬虫要用基于事件的方法来写的原因。
*/
#include<iostream>
#include <string.h>
#include <windows.h>
#include <winhttp.h>
#pragma comment(lib, "winhttp.lib")
using namespace std;

//定义我们将要用的句柄
HINTERNET hSession = NULL;
HINTERNET hConnect = NULL;
HINTERNET hRequest = NULL;

int main() {
	//1.初始化一个WinHTTP-session句柄，参数1为此句柄的名称，此处我命名为WinHTTP
	hSession = WinHttpOpen(L"WinHTTP", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
	if (hSession == NULL) {
		cout << "Error:Open session failed: " << GetLastError() << endl;
		return -1;
	}

	//2.通过上述句柄连接到服务器，需要指定服务器IP和端口号。若连接成功，返回的hConnect句柄不为NULL
	LPCWSTR host = L"www.baidu.com";//此处我们以百度为例
	hConnect = WinHttpConnect(hSession, host, INTERNET_DEFAULT_HTTPS_PORT, 0);
	if (hConnect == NULL) {
		cout << "Error:Connect failed: " << GetLastError() << endl;
		return -1;
	}

	//3.通过hConnect句柄创建一个hRequest句柄，用于发送数据与读取从服务器返回的数据。
	hRequest = WinHttpOpenRequest(hConnect, L"GET", NULL, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
	//其中参数2表示请求方式，此处为GET；参数3:给定Post的具体地址，如填L"getServiceInfo"时具体地址为http://192.168.50.112/getServiceInfo
	if (hRequest == NULL) {
		cout << "Error:OpenRequest failed: " << GetLastError() << endl;
		return -1;
	}

	//4.1.向服务器发送post数据
	//(1)指定发送的数据内容
	string data = "This is my data to be sent";
	const void* ss = (const char*)data.c_str();

	//(2)发送请求
	BOOL bResults;
	bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, const_cast<void*>(ss), data.length(), data.length(), 0);
	if (!bResults) {
		cout << "Error:SendRequest failed: " << GetLastError() << endl;
		return -1;
	}
	else {
		//（3）发送请求成功则准备接受服务器的response。注意：在使用 WinHttpQueryDataAvailable和WinHttpReadData前必须使用WinHttpReceiveResponse才能access服务器返回的数据
		bResults = WinHttpReceiveResponse(hRequest, NULL);
	}
	//4.2.获取服务器返回数据的header信息。这一步我用来获取返回数据的数据类型。
	LPVOID lpHeaderBuffer = NULL;
	DWORD dwSize = 0;
	if (bResults) {
		//(1) 获取header的长度
		WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX, NULL, &dwSize, WINHTTP_NO_HEADER_INDEX);

		//(2) 根据header的长度为buffer申请内存空间
		if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
			lpHeaderBuffer = new WCHAR[dwSize / sizeof(WCHAR)];

			//(3) 使用WinHttpQueryHeaders获取header信息
			bResults = WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX, lpHeaderBuffer, &dwSize, WINHTTP_NO_HEADER_INDEX);
		}
	}
	printf("Header contents: \n%S", lpHeaderBuffer);

	/*解析上述header信息会发现服务器返回数据的charset为uft-8。这意味着后面需要对获取到的raw data进行宽字符转换。一开始由于没有进行转换所以得到的数据都是乱码。
	出现乱码的原因是：HTTP在传输过程中是二值的，它并没有text或者是unicode的概念。HTTP使用7bit的ASCII码作为HTTP headers，但是内容是任意的二值数据，需要根据header中指定的编码方式来描述它（通常是Content-Type header）。
	因此当你接收到原始的HTTP数据时，可以先将其保存到char[] buffer中，然后利用WinHttpQueryHearders()获取HTTP头，得到内容的Content-Type,这样你就知道数据到底是啥类型的了，是ASCII还是Unicode或者其他。
	一旦你知道了具体的编码方式，就可以通过MultiByteToWideChar()将其转换成合适编码的字符，存入wchar_t[]中。
	如下4.4所示。
	*/

	//4.3.获取服务器返回数据
	LPSTR pszOutBuffer = NULL;
	DWORD dwDownloaded = 0;//实际收取的字符数
	if (bResults) {
		do {
			//(1)获取返回数据的大小（以字节为单位）
			dwSize = 0;
			if (!WinHttpQueryDataAvailable(hRequest, &dwSize)) {
				cout << "Error：WinHttpQueryDataAvailable failed：" << GetLastError() << endl;
				break;
			}
			if (!dwSize)
				break;//数据大小为0时跳出循环

			//(2)根据返回数据的长度为buffer来申请内存空间
			pszOutBuffer = new char[dwSize + 1];
			if (!pszOutBuffer) {
				cout << "Out of memory." << endl;
				dwSize = 0;
				break;
			}
			else {
				//(3)通过WinHttpReadData读取服务器的返回数据
				ZeroMemory(pszOutBuffer, dwSize + 1);//将buffer置0
				if (!WinHttpReadData(hRequest, pszOutBuffer, dwSize, &dwDownloaded)) {
					cout << "Error：WinHttpQueryDataAvailable failed：" << GetLastError() << endl;
				}
				else
					cout << pszOutBuffer;

				//4.4. 将返回数据转换成UTF8
				wchar_t* pwText = NULL;
				DWORD dwNum = MultiByteToWideChar(CP_ACP, 0, pszOutBuffer, -1, NULL, 0);//返回原始ASCII码的字符数目
				pwText = new wchar_t[dwNum];//根据ASCII码的字符数来分配UTF8的空间
				MultiByteToWideChar(CP_UTF8, 0, pszOutBuffer, -1, pwText, dwNum);//将ASCII码转换成UTF8
				printf("Received contents: \n%S", pwText);

				delete[] pszOutBuffer;//用完回收是写C++的好习惯
			}
		} while (dwSize > 0);
	}

	//5.依次关闭request，connect，session句柄
	if (hRequest)
		WinHttpCloseHandle(hRequest);
	if (hConnect)
		WinHttpCloseHandle(hConnect);
	if (hSession)
		WinHttpCloseHandle(hSession);
	return 0;
}


/*
总结
通过对这五个步骤的具体实现，我们可以详细的看到C++爬取网页的底层运作机制——虽然复杂但又井然有序。
正如上文所说，当爬取数据的活动事件（epoll_wait）结束以后，紧接着的就是对数据的清洗与分析。
但事实上除了对原理本身的格物致知以外，更多时候的我们仅仅只希望简单快速的上手，浮光掠影，流于表面。
不得不承认时代的发展与变迁使得底层被越来越尘封于目光不可及之处，
有时简简单单的几步就能完成前人绞尽脑汁几个月的思考。就像下面这个我平时经常用来和同学开玩笑用的色图爬取代码
简单而又高效，我把它封装到了一个QQ机器人的逻辑内部来活跃群聊。在我看来，无论未来的代码发展方向是何处，
都是一种美。
*/

//#include <stdio.h>
//#include <tchar.h>
//#include <windows.h>
//#include<urlmon.h>
//#pragma comment(lib, "urlmon.lib")
//
//int main() {
//	TCHAR url[] = TEXT("https://img.paulzzh.tech/touhou/random?site=all&size=all");//一个很正常向的东方project图片API
//	TCHAR filePath[] = L"祖传色图.jpg";
//	HRESULT res = URLDownloadToFile(NULL, url, filePath, 0, NULL);
//	if (res == S_OK) {
//		printf("色图Ok，单击任意键以退出喵\n");
//		system("pause");
//	}
//	else if (res == E_OUTOFMEMORY) {
//		printf("你的电脑内存不足喵\n");
//		system("pause");
//	}
//	else if (res == INET_E_DOWNLOAD_FAILURE) {
//		printf("色图服务器挂了喵\n");
//		system("pause");
//	}
//	else {
//		printf("Other error: %d\n", res);
//		system("pause");
//	}
//	return 0;
//}  
#endif // 0
