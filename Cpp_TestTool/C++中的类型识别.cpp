#if 0
#include <type_traits>
#include <iostream>
using namespace std;
class CBase
{

};

class CDriverd : public CBase
{

};
int main() {
	cout << (is_base_of<CBase, CBase>::value ? "true" : "false");
	cout << "\n";
	cout << (is_base_of<CBase, CDriverd>::value ? "true" : "false");
	cout << "\n";
	cout << (is_base_of<CDriverd, CBase>::value ? "true" : "false");
	cout << "\n";
}
#endif // 0
