#if 0
#include <stdio.h>
#include <conio.h>
#include <stdlib.h> 
#include <string>
//������ļ�����
int numerofpeple = 0;//����ѧ������
struct StudentMesage { //ѧ����Ϣ
	int StudenNunmer; //ѧ����ѧ��
	char StudenName[100];  //ѧ��������
	StudentMesage* pNext;
};
StudentMesage* pHead = NULL;//����Ϊͷָ��
StudentMesage* pEnd = NULL;//����Ϊβ
void RendFileMessageToMemory()//��ȡ�ļ���Ϣ���ڴ���
{
	FILE* file = NULL;
	fopen_s(&file, "file.apk", "r");
	if (file == NULL) {//�ж��ļ���ľ�д򿪳ɹ�
		printf("���ļ�ʧ��");
		return;
	}
	fread(&numerofpeple, sizeof(numerofpeple), 1, file);//��ȡ����������������ִ��ѭ������
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
	fclose(file);//д��֮��Ҫ�ر��ļ�
}
void WriteMessageToFile(StudentMesage* pHead) {//д����Ϣ���ļ���
	StudentMesage* Temp = pHead;
	FILE* file = NULL;
	fopen_s(&file, "file.apk", "w");
	if (file == NULL) {//�ж��ļ���ľ�д򿪳ɹ�
		printf("���ļ�ʧ��");
		return;
	}
	fwrite(&numerofpeple, sizeof(numerofpeple), 1, file);//д��������
	while (Temp != NULL) {
		fwrite(&Temp->StudenNunmer, sizeof(Temp->StudenNunmer), 1, file);//д��ѧ��
		int len = strlen(Temp->StudenName);//�������ֵĳ���
		fwrite(&len, sizeof(len), 1, file);//д�����ֵĳ���
		fwrite(Temp->StudenName, sizeof(char), len, file);//д������
		Temp = Temp->pNext;//ָ����һ���ڵ�
	}
	fclose(file);//д��֮��Ҫ�ر��ļ�
}
void AddStudent() {         //���ѧԱ
	if (NULL == pHead) {
		//��ͷָ����������ڴ�
		pHead = (StudentMesage*)malloc(sizeof(StudentMesage));
		//ȥ������ڴ渳��ʼֵ
		pHead->pNext = NULL;
		pHead->StudenNunmer = 0;
		//�����ڴ�ֵ�ĺ�������һ�������ڴ���׵�ַ���ڶ���Ҫ���õ�ֵ��������Ҫ���ö��ٸ��ֽ�
		memset(pHead->StudenName, 0, sizeof(pHead->StudenName));
		//��ʾָβ��Ҳָ���һ���ڵ�
		pEnd = pHead;
	}
	else
	{   //������ڵ��pEnd����һ���ڵ�
		pEnd->pNext = (StudentMesage*)malloc(sizeof(StudentMesage));
		//ȥ������ڴ渳��ʼֵ
		pEnd->pNext->pNext = NULL;
		memset(pEnd->pNext->StudenName, 0, sizeof(pEnd->pNext->StudenName));
		pEnd->pNext->StudenNunmer = 0;

		//��pEndָ��������Ľڵ�
		pEnd = pEnd->pNext;
	}
	printf("������ѧ����ѧ�ţ�\n"); //��ȡ�û������ѧ��
	scanf_s("%d", &pEnd->StudenNunmer);
	fflush(stdin);//������뻺��������Ϣ
	printf("������ѧ����������\n"); //��ȡ�û����������
	gets_s(pEnd->StudenName);
	//scanf("%s", pEnd->StudenName);
	numerofpeple++;//��ʾ�����һ��ѧԱ
}
void Show(StudentMesage* const pHead) {//��ʾѧ������Ϣ
	StudentMesage* pTemp = pHead;
	while (pTemp != NULL) {
		printf(" ѧ��:%d\n", pTemp->StudenNunmer);
		printf(" ����:%s\n", pTemp->StudenName);
		pTemp = pTemp->pNext;
	}
	getchar();
}
char SelectInterface() {
	//��ʾ�û���Ϣ
	printf("1�����ѧԱ\n");
	printf("2�������Ϣ\n");
	printf("3���˳�ϵͳ\n");
	char key = _getch(); //��ȡ�û�������Ϣ
	//_getch() //�������� ��ȡ���µļ�
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
