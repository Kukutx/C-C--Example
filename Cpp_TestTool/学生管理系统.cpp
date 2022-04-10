#if 0
#include <stdio.h>
#include <conio.h>
#include <stdlib.h> 
#include <string>
//链表加文件操作
int numerofpeple = 0;//代表学生人数
struct StudentMesage { //学生信息
	int StudenNunmer; //学生的学号
	char StudenName[100];  //学生的姓名
	StudentMesage* pNext;
};
StudentMesage* pHead = NULL;//定义为头指针
StudentMesage* pEnd = NULL;//定义为尾
void RendFileMessageToMemory()//读取文件信息到内存中
{
	FILE* file = NULL;
	fopen_s(&file, "file.apk", "r");
	if (file == NULL) {//判断文件有木有打开成功
		printf("打开文件失败");
		return;
	}
	fread(&numerofpeple, sizeof(numerofpeple), 1, file);//读取总人数，根据人数执行循环次数
	for (int i = 0; i < numerofpeple; i++)
	{
		if (pHead == NULL) {
			pHead = new StudentMesage;
			memset(pHead->StudenName, 0, 100);
			pHead->pNext = NULL;
			pHead->StudenNunmer = 0;
			fread(&pHead->StudenNunmer, sizeof(pHead->StudenNunmer), 1, file);
			int len = 0;
			fread(&len, sizeof(len), 1, file);
			fread(pHead->StudenName, sizeof(char), len, file);
			pEnd = pHead;
		}
		else
		{
			pEnd->pNext = new StudentMesage;
			memset(pEnd->pNext->StudenName, 0, 100);
			pEnd->pNext->pNext = NULL;
			pEnd->pNext->StudenNunmer = 0;
			fread(&pEnd->pNext->StudenNunmer, sizeof(pEnd->pNext->StudenNunmer), 1, file);
			int len = 0;
			fread(&len, sizeof(len), 1, file);
			fread(pEnd->pNext->StudenName, sizeof(char), len, file);
			pEnd = pEnd->pNext;
		}
	}
	fclose(file);//写完之后要关闭文件
}
void WriteMessageToFile(StudentMesage* pHead) {//写入信息到文件中
	StudentMesage* Temp = pHead;
	FILE* file = NULL;
	fopen_s(&file, "file.apk", "w");
	if (file == NULL) {//判断文件有木有打开成功
		printf("打开文件失败");
		return;
	}
	fwrite(&numerofpeple, sizeof(numerofpeple), 1, file);//写入总人数
	while (Temp != NULL) {
		fwrite(&Temp->StudenNunmer, sizeof(Temp->StudenNunmer), 1, file);//写入学号
		int len = strlen(Temp->StudenName);//计算名字的长度
		fwrite(&len, sizeof(len), 1, file);//写入名字的长度
		fwrite(Temp->StudenName, sizeof(char), len, file);//写入名字
		Temp = Temp->pNext;//指向下一个节点
	}
	fclose(file);//写完之后要关闭文件
}
void AddStudent() {         //添加学员
	if (NULL == pHead) {
		//用头指针申请堆区内存
		pHead = (StudentMesage*)malloc(sizeof(StudentMesage));
		//去给这个内存赋初始值
		pHead->pNext = NULL;
		pHead->StudenNunmer = 0;
		//设置内存值的函数，第一个参数内存的首地址，第二个要设置的值，第三个要设置多少个字节
		memset(pHead->StudenName, 0, sizeof(pHead->StudenName));
		//表示指尾针也指向第一个节点
		pEnd = pHead;
	}
	else
	{   //用这个节点的pEnd申请一个节点
		pEnd->pNext = (StudentMesage*)malloc(sizeof(StudentMesage));
		//去给这个内存赋初始值
		pEnd->pNext->pNext = NULL;
		memset(pEnd->pNext->StudenName, 0, sizeof(pEnd->pNext->StudenName));
		pEnd->pNext->StudenNunmer = 0;

		//让pEnd指向新申请的节点
		pEnd = pEnd->pNext;
	}
	printf("请输入学生的学号：\n"); //获取用户输入的学号
	scanf_s("%d", &pEnd->StudenNunmer);
	fflush(stdin);//清除输入缓存区的信息
	printf("请输入学生的姓名：\n"); //获取用户输入的姓名
	gets_s(pEnd->StudenName);
	//scanf("%s", pEnd->StudenName);
	numerofpeple++;//表示添加了一个学员
}
void Show(StudentMesage* const pHead) {//显示学生的信息
	StudentMesage* pTemp = pHead;
	while (pTemp != NULL) {
		printf(" 学号:%d\n", pTemp->StudenNunmer);
		printf(" 姓名:%s\n", pTemp->StudenName);
		pTemp = pTemp->pNext;
	}
	getchar();
}
char SelectInterface() {
	//显示用户信息
	printf("1：添加学员\n");
	printf("2：浏览信息\n");
	printf("3：退出系统\n");
	char key = _getch(); //获取用户输入信息
	//_getch() //阻塞函数 获取按下的键
	if (key != '1' && key != '2' && key != '3') {
		key = '0';
	}
	return key;
}
int main() {
	RendFileMessageToMemory();
	char key = '0';
	while (key != '3') {
		system("cls");
		key = SelectInterface();
		switch (key) {
		case '1':
			AddStudent();
			break;
		case '2':
			Show(pHead);
			break;
		case '3':
			WriteMessageToFile(pHead);
			break;
		default:
			break;
		}
	}
	return 0;
}
#endif // 0
