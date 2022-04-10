#if 0
#include <fstream> //fstream类的头文件
using namespace std;
#pragma warning(disable : 4996)
int main()
{
	//1创建文件流对象
	fstream  srcFile;//待加密文件
	fstream  dstFile;//加密后文件

	//2打开文件
	//保存待加密文件名的数组
	char srcFileName[256] = { 0 };
	//待加密文件的指针
	char dstFileName[256] = { 0 };
	printf("请输入待加密文件名:");
	scanf("%s", srcFileName);
	printf("请输入加密后文件名:");
	scanf("%s", dstFileName);
	//打开待加密文件  文件名  读方式  二进制
	srcFile.open(srcFileName, std::ios::in | std::ios::binary);
	//打开加密文件  文件名  读方式  二进制
	dstFile.open(dstFileName, std::ios::out | std::ios::binary);

	//3得到待加密文件大小
	//3.1设置文件内容指针到文件末尾
	srcFile.seekg(0, std::ios::end);
	//3.2获得文件指针到文件头都的字节数
	std::streamoff size = srcFile.tellg();
	//3.3设置文件内容指针到文件头
	srcFile.seekg(0, std::ios::beg);
	for (std::streamoff i = 0; i < size; i++)
		dstFile.put(srcFile.get() ^ 0x66);

#if 0
	char temp;
	//4循环读取 加密 写入
	for (std::streamoff i = 0; i < size; i++) {
		//读取
		temp = srcFile.get();
		//加密
		temp ^= 0x66;
		//写入
		dstFile.put(temp);
}
#endif
	//5关闭文件
	srcFile.close();
	dstFile.close();
	while (1);
	return 0;
}



#endif // 0
