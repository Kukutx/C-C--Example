#if 0
#include <fstream> //fstream���ͷ�ļ�
using namespace std;
#pragma warning(disable : 4996)
int main()
{
	//1�����ļ�������
	fstream  srcFile;//�������ļ�
	fstream  dstFile;//���ܺ��ļ�

	//2���ļ�
	//����������ļ���������
	char srcFileName[256] = { 0 };
	//�������ļ���ָ��
	char dstFileName[256] = { 0 };
	printf("������������ļ���:");
	scanf("%s", srcFileName);
	printf("��������ܺ��ļ���:");
	scanf("%s", dstFileName);
	//�򿪴������ļ�  �ļ���  ����ʽ  ������
	srcFile.open(srcFileName, std::ios::in | std::ios::binary);
	//�򿪼����ļ�  �ļ���  ����ʽ  ������
	dstFile.open(dstFileName, std::ios::out | std::ios::binary);

	//3�õ��������ļ���С
	//3.1�����ļ�����ָ�뵽�ļ�ĩβ
	srcFile.seekg(0, std::ios::end);
	//3.2����ļ�ָ�뵽�ļ�ͷ�����ֽ���
	std::streamoff size = srcFile.tellg();
	//3.3�����ļ�����ָ�뵽�ļ�ͷ
	srcFile.seekg(0, std::ios::beg);
	for (std::streamoff i = 0; i < size; i++)
		dstFile.put(srcFile.get() ^ 0x66);

#if 0
	char temp;
	//4ѭ����ȡ ���� д��
	for (std::streamoff i = 0; i < size; i++) {
		//��ȡ
		temp = srcFile.get();
		//����
		temp ^= 0x66;
		//д��
		dstFile.put(temp);
}
#endif
	//5�ر��ļ�
	srcFile.close();
	dstFile.close();
	while (1);
	return 0;
}



#endif // 0
