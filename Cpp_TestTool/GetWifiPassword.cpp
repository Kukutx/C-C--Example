#if 0
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#pragma warning(disable : 4996)
using namespace std;
class Wifi {
private:
	string name;
public:
	Wifi(string _name) :name(_name)
	{

	}
	string getName()
	{
		return this->name;
	}

};

void showWifiPassword(Wifi wifi)
{
	string cmd = "netsh wlan show profiles " + wifi.getName() + " key=clear >>1.tmp";
	system(cmd.c_str());
	FILE* fp = nullptr;
	if ((fp = fopen("1.tmp", "r")) == NULL)
	{
		cout << "file open error" << endl;
	}
	char lineTxt[1024];
	for (int i = 0; i < 33; i++)
	{
		fgets(lineTxt, 1024, fp);
	}

	string passwd = lineTxt;
	int c = passwd.find(':');
	passwd.erase(passwd.begin(), passwd.begin() + c + 2);
	cout << "Wifi Name:     " << wifi.getName() << endl;
	cout << "Wifi Password: " << passwd;
}
int main()
{
	Wifi w("DailyTelecom_F17B");  //填入wifi名称
	showWifiPassword(w);
	system("pause");
	return 0;
}
#endif // 0
