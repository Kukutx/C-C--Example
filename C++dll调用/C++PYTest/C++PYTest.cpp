#include <iostream>
#include "include\Python.h"
#pragma comment(lib,"python39.lib")
using namespace std;
bool callpytest() {
	Py_Initialize();//加载Python解释器
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('Dlls/')");
	PyObject* pModule = NULL;
	PyObject* pFunc = NULL;
	PyObject* pArgs = NULL;
	PyObject* pResult = NULL;
	pModule = PyImport_ImportModule("ExternalPythonTool");//Python py文件名
	if (pModule == nullptr)
		return true;
	pFunc = PyObject_GetAttrString(pModule, "add_func");//py文件内函数名
	//传入参数
	pArgs = Py_BuildValue("ii", 1, 24);
	//执行函数
	pResult = PyObject_CallObject(pFunc, pArgs);
	//返回值为C++
	double a = PyLong_AsDouble(pResult);
	cout << a << std::endl;
	Py_Finalize();//卸载Python解释器
}
int main()
{
	if (!callpytest()) {
		cout << "失败";
	}
	system("pause");
}
