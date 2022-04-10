#if 0
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <comdef.h>
#include <string>
#include <DShow.h>
#pragma   comment(lib,"Strmiids.lib")
//#include <uuids.h>
//#include <strmif.h>
int main()
{
	ICreateDevEnum* pDevEnum = NULL;
	IEnumMoniker* pEnum = NULL;
	HRESULT hr = NULL;
	CoInitialize(NULL);
	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, reinterpret_cast<void**>(&pDevEnum));
	if (SUCCEEDED(hr))
	{

		hr = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnum, 0);
		if (hr == S_OK)
		{
			//枚举捕获设备
			IMoniker* pMoniker = NULL;
			ULONG cFetched;
			while (pEnum->Next(1, &pMoniker, &cFetched) == S_OK)
			{
				IPropertyBag* pPropBag;
				hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, reinterpret_cast<void**>(&pPropBag));
				if (SUCCEEDED(hr))
				{

					//获取 vid 和 pid
					BSTR devicePath = NULL;
					hr = pMoniker->GetDisplayName(NULL, NULL, &devicePath);
					if (!SUCCEEDED(hr))
					{
						pMoniker->Release();
						continue;
					}
					wchar_t* lpszDevicePath = _bstr_t(devicePath);

					//获取设备名称
					VARIANT varName;
					varName.vt = VT_BSTR;
					VariantInit(&varName);
					hr = pPropBag->Read(L"FriendlyName", &varName, 0);
					if (SUCCEEDED(hr))
					{
						wchar_t* lpszBSTR = _bstr_t(varName.bstrVal);
						std::wcout << std::wstring(lpszDevicePath) << std::endl;
						std::wcout << std::wstring(lpszBSTR) << std::endl;
					}
					pPropBag->Release();
				}
				pMoniker->Release();
			}
		}
	}
	CoUninitialize();
	system("pause");
	return 0;
}

#endif // 0
