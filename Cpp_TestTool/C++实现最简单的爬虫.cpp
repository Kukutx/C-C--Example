#if 0
/*
ԭ��
�����ԭ�����������������Ƿ���http/https����+����htmlҳ�棬��ȡҳ���ϵ�Ŀ�����ݡ����۲��ú������ԣ�����Ҫ��server�������ɸ�TCP���ӣ��ٽ�http����д��TCP socket�У��ȴ�server�������ݡ�
�������Ͼ���һ���¼�ѭ����event loop������α���������������Ͼ���������
��ʼ��epoll����server����TCP���ӡ�
��������У�����Ҫ��ȡ����վ�б���ȡ��url��http����
��http����д�뵽���TCP socket�У��������socket����epoll�С�
����¼���epoll_wait����
���������¼�����htmlҳ�棩��Ȼ���ʣ��δ�������url��http�����Żض����й���һ����ȡ����
(�����д������ֻ�Ǽ򵥵ĵ��̴߳��п��Բ��÷Żأ���
�ص���2����
�����������������õ�һ��url����Ҫȥ���������url��Ӧ��ҳ�棬����������������Ҫ�����ݣ�
Ȼ����ܰ�������һ��url��������У�����һ�ֵ��͵��������򡣵���������������I/O�ܼ��ͳ���
������д�ɷ�����ʽ�Ķ��̳߳��򲢲���ʹ����Ч�ʲ�����Ծʽ���������෴�������ܻ����������еĵ��û��ң�
��ҲΪʲô����Ҫ�û����¼��ķ�����д��ԭ��
*/
#include<iostream>
#include <string.h>
#include <windows.h>
#include <winhttp.h>
#pragma comment(lib, "winhttp.lib")
using namespace std;

//�������ǽ�Ҫ�õľ��
HINTERNET hSession = NULL;
HINTERNET hConnect = NULL;
HINTERNET hRequest = NULL;

int main() {
	//1.��ʼ��һ��WinHTTP-session���������1Ϊ�˾�������ƣ��˴�������ΪWinHTTP
	hSession = WinHttpOpen(L"WinHTTP", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
	if (hSession == NULL) {
		cout << "Error:Open session failed: " << GetLastError() << endl;
		return -1;
	}

	//2.ͨ������������ӵ�����������Ҫָ��������IP�Ͷ˿ںš������ӳɹ������ص�hConnect�����ΪNULL
	LPCWSTR host = L"www.baidu.com";//�˴������԰ٶ�Ϊ��
	hConnect = WinHttpConnect(hSession, host, INTERNET_DEFAULT_HTTPS_PORT, 0);
	if (hConnect == NULL) {
		cout << "Error:Connect failed: " << GetLastError() << endl;
		return -1;
	}

	//3.ͨ��hConnect�������һ��hRequest��������ڷ����������ȡ�ӷ��������ص����ݡ�
	hRequest = WinHttpOpenRequest(hConnect, L"GET", NULL, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
	//���в���2��ʾ����ʽ���˴�ΪGET������3:����Post�ľ����ַ������L"getServiceInfo"ʱ�����ַΪhttp://192.168.50.112/getServiceInfo
	if (hRequest == NULL) {
		cout << "Error:OpenRequest failed: " << GetLastError() << endl;
		return -1;
	}

	//4.1.�����������post����
	//(1)ָ�����͵���������
	string data = "This is my data to be sent";
	const void* ss = (const char*)data.c_str();

	//(2)��������
	BOOL bResults;
	bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, const_cast<void*>(ss), data.length(), data.length(), 0);
	if (!bResults) {
		cout << "Error:SendRequest failed: " << GetLastError() << endl;
		return -1;
	}
	else {
		//��3����������ɹ���׼�����ܷ�������response��ע�⣺��ʹ�� WinHttpQueryDataAvailable��WinHttpReadDataǰ����ʹ��WinHttpReceiveResponse����access���������ص�����
		bResults = WinHttpReceiveResponse(hRequest, NULL);
	}
	//4.2.��ȡ�������������ݵ�header��Ϣ����һ����������ȡ�������ݵ��������͡�
	LPVOID lpHeaderBuffer = NULL;
	DWORD dwSize = 0;
	if (bResults) {
		//(1) ��ȡheader�ĳ���
		WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX, NULL, &dwSize, WINHTTP_NO_HEADER_INDEX);

		//(2) ����header�ĳ���Ϊbuffer�����ڴ�ռ�
		if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
			lpHeaderBuffer = new WCHAR[dwSize / sizeof(WCHAR)];

			//(3) ʹ��WinHttpQueryHeaders��ȡheader��Ϣ
			bResults = WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX, lpHeaderBuffer, &dwSize, WINHTTP_NO_HEADER_INDEX);
		}
	}
	printf("Header contents: \n%S", lpHeaderBuffer);

	/*��������header��Ϣ�ᷢ�ַ������������ݵ�charsetΪuft-8������ζ�ź�����Ҫ�Ի�ȡ����raw data���п��ַ�ת����һ��ʼ����û�н���ת�����Եõ������ݶ������롣
	���������ԭ���ǣ�HTTP�ڴ���������Ƕ�ֵ�ģ�����û��text������unicode�ĸ��HTTPʹ��7bit��ASCII����ΪHTTP headers����������������Ķ�ֵ���ݣ���Ҫ����header��ָ���ı��뷽ʽ����������ͨ����Content-Type header����
	��˵�����յ�ԭʼ��HTTP����ʱ�������Ƚ��䱣�浽char[] buffer�У�Ȼ������WinHttpQueryHearders()��ȡHTTPͷ���õ����ݵ�Content-Type,�������֪�����ݵ�����ɶ���͵��ˣ���ASCII����Unicode����������
	һ����֪���˾���ı��뷽ʽ���Ϳ���ͨ��MultiByteToWideChar()����ת���ɺ��ʱ�����ַ�������wchar_t[]�С�
	����4.4��ʾ��
	*/

	//4.3.��ȡ��������������
	LPSTR pszOutBuffer = NULL;
	DWORD dwDownloaded = 0;//ʵ����ȡ���ַ���
	if (bResults) {
		do {
			//(1)��ȡ�������ݵĴ�С�����ֽ�Ϊ��λ��
			dwSize = 0;
			if (!WinHttpQueryDataAvailable(hRequest, &dwSize)) {
				cout << "Error��WinHttpQueryDataAvailable failed��" << GetLastError() << endl;
				break;
			}
			if (!dwSize)
				break;//���ݴ�СΪ0ʱ����ѭ��

			//(2)���ݷ������ݵĳ���Ϊbuffer�������ڴ�ռ�
			pszOutBuffer = new char[dwSize + 1];
			if (!pszOutBuffer) {
				cout << "Out of memory." << endl;
				dwSize = 0;
				break;
			}
			else {
				//(3)ͨ��WinHttpReadData��ȡ�������ķ�������
				ZeroMemory(pszOutBuffer, dwSize + 1);//��buffer��0
				if (!WinHttpReadData(hRequest, pszOutBuffer, dwSize, &dwDownloaded)) {
					cout << "Error��WinHttpQueryDataAvailable failed��" << GetLastError() << endl;
				}
				else
					cout << pszOutBuffer;

				//4.4. ����������ת����UTF8
				wchar_t* pwText = NULL;
				DWORD dwNum = MultiByteToWideChar(CP_ACP, 0, pszOutBuffer, -1, NULL, 0);//����ԭʼASCII����ַ���Ŀ
				pwText = new wchar_t[dwNum];//����ASCII����ַ���������UTF8�Ŀռ�
				MultiByteToWideChar(CP_UTF8, 0, pszOutBuffer, -1, pwText, dwNum);//��ASCII��ת����UTF8
				printf("Received contents: \n%S", pwText);

				delete[] pszOutBuffer;//���������дC++�ĺ�ϰ��
			}
		} while (dwSize > 0);
	}

	//5.���ιر�request��connect��session���
	if (hRequest)
		WinHttpCloseHandle(hRequest);
	if (hConnect)
		WinHttpCloseHandle(hConnect);
	if (hSession)
		WinHttpCloseHandle(hSession);
	return 0;
}


/*
�ܽ�
ͨ�������������ľ���ʵ�֣����ǿ�����ϸ�Ŀ���C++��ȡ��ҳ�ĵײ��������ơ�����Ȼ���ӵ��־�Ȼ����
����������˵������ȡ���ݵĻ�¼���epoll_wait�������Ժ󣬽����ŵľ��Ƕ����ݵ���ϴ�������
����ʵ�ϳ��˶�ԭ����ĸ�����֪���⣬����ʱ������ǽ���ֻϣ���򵥿��ٵ����֣�������Ӱ�����ڱ��档
���ò�����ʱ���ķ�չ���Ǩʹ�õײ㱻Խ��Խ������Ŀ�ⲻ�ɼ�֮����
��ʱ��򵥵��ļ����������ǰ�˽ʾ���֭�����µ�˼�����������������ƽʱ����������ͬѧ����Ц�õ�ɫͼ��ȡ����
�򵥶��ָ�Ч���Ұ�����װ����һ��QQ�����˵��߼��ڲ�����ԾȺ�ġ����ҿ���������δ���Ĵ��뷢չ�����Ǻδ���
����һ������
*/

//#include <stdio.h>
//#include <tchar.h>
//#include <windows.h>
//#include<urlmon.h>
//#pragma comment(lib, "urlmon.lib")
//
//int main() {
//	TCHAR url[] = TEXT("https://img.paulzzh.tech/touhou/random?site=all&size=all");//һ����������Ķ���projectͼƬAPI
//	TCHAR filePath[] = L"�洫ɫͼ.jpg";
//	HRESULT res = URLDownloadToFile(NULL, url, filePath, 0, NULL);
//	if (res == S_OK) {
//		printf("ɫͼOk��������������˳���\n");
//		system("pause");
//	}
//	else if (res == E_OUTOFMEMORY) {
//		printf("��ĵ����ڴ治����\n");
//		system("pause");
//	}
//	else if (res == INET_E_DOWNLOAD_FAILURE) {
//		printf("ɫͼ������������\n");
//		system("pause");
//	}
//	else {
//		printf("Other error: %d\n", res);
//		system("pause");
//	}
//	return 0;
//}  
#endif // 0
