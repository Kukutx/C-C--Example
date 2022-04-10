#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include<conio.h>
#include<windows.h>
struct stu{
	int id[10];	//学号 
	char name[20]; //姓名 
	int score; //分数 
};

struct STU
{
	//int data;
	struct stu data;
	struct STU*  next;
};
//创建结构体表头 
struct STU* creatlist()//创建链表
{
	struct STU* head = (struct STU*)malloc(sizeof(struct STU));
	head->next = NULL;
	return head;
}
//创建结点
struct STU* createNode(struct stu data)
{
	struct STU* newNode = (struct STU*)malloc(sizeof(struct STU));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}
//插入结点
void insertNodeByhead(struct STU* head, struct stu data)
{
	struct STU* newNode = createNode(data);
	newNode->data = data;
	head->next = newNode;
}
//指定位置删除
void deleteNode(struct STU* head, char* name)
{
	struct STU* posNode = head->next;
	struct STU* posFrontNode = head;
	if (posNode == NULL)
	{
		printf("数据为空，无法删除！\n");
		return;
	}
	while (strcmp(posNode->data.name, name))
	{
		posFrontNode = posNode;
		posNode = posFrontNode->next;
		if (posNode == NULL)
		{
			printf("未找到指定位置，无法删除！\n");
			return;
		}
	}
	posFrontNode->next = posNode->next;
	free(posNode);
}
//查找
struct STU* searchData(struct STU* head, char *name)
{
	struct STU* p = head->next;
	if (p == NULL)
		return NULL;
	while (strcmp(p->data.name, name))
	{
		p = p->next;
	}
	return p;
}
//文件读操作
void readFile(struct STU* head, char *fileName)
{
	FILE *fp;
	struct stu data;
	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		fp = fopen(fileName, "w+");
	}
	while (fscanf(fp, "%d\t%s\t%d\n", &data.id, data.name, &data.score) != EOF)
	{
		insertNodeByhead(head, data);
	}
	fclose(fp);
}
//文件写操作
void writeFile(struct STU* head, char *FileName)
{
	FILE  *fp;
	fp = fopen(FileName, "w");
	struct STU* p = head->next;
	while (p)
	{
		fprintf(fp, "%d\t%s\t%d\n", p->data.id, p->data.name, p->data.score);
		p = p->next;
	}
	fclose(fp);
}

//打印链表
void printlist(struct STU* head)
{
	struct STU* p = head->next;
	printf("学号\t姓名\t分数\n");
	while (p)
	{
		printf("%d\t%s\t%d\n", p->data.id, p->data.name, p->data.score);
		p = p->next;
	}
	printf("\n");
}


void menu()
{

	system("cls");//清屏
	system("color b");//修改字体颜色 
	printf("\n\n\n\n");
	printf("\t************************************\n");
	printf("\t|     欢迎来到学生信息管理系统     |\n");
	printf("\t|**********************************|\n");
	printf("\t|**        1:录入学生信息        **|\n");
	printf("\t|**        2:显示学生信息        **|\n");
	printf("\t|**        3:增加学生信息        **|\n");
	printf("\t|**        4:删除学生信息        **|\n");
	printf("\t|**        5:查询学生信息        **|\n");
	printf("\t|**        6:修改学生信息        **|\n");
	printf("\t|**        7:退出学生系统        **|\n");
	printf("\t************************************\n");
	printf("\n  \t请输入您要进行的操作（1~~7）：");

}


struct STU* List = creatlist();

void  keydown()
{
	int n = 0;
	struct stu data;
	struct STU*p = NULL;
	scanf("%d", &n);
	switch (n)
	{
		//增加一个学生信息 
	case 1:
		printf("******录入学生信息******\n");
		printf("请输入你要添加的学生学号,姓名，分数：");
		fflush(stdin);//清空缓冲区 
		scanf("%d\t%s\t%d\n", &data.id, data.name, &data.score);
		insertNodeByhead(List, data);
		break;
	case 2:
		printf("******显示学生信息******\n");
		printlist(List);
		break;
	case 3:
		printf("******增加学生信息******\n");
		printf("请输入你要添加的学生学号,姓名，分数：");
		fflush(stdin);//清空缓冲区 
		scanf("%d\t%s\t%d\n", &data.id, data.name, &data.score);
		insertNodeByhead(List, data);
		break;
	case 4:
		printf("******删除学生信息******\n");
		printf("请输删除的学生姓名:");
		scanf("%s", data.name);
		deleteNode(List, data.name);
		break;
	case 5:
		printf("******查询学生信息******\n");
		printf("请输入要查找的学生姓名：");
		scanf("%s", data.name);
		p = searchData(List, data.name);
		if (p == NULL)
		{
			printf("未找到相关信息，无法删除！\n");
			system("pause");
		}
		else
		{
			printf("学号\t姓名\t分数\n");
			printf("%d\t%s\t%d\n", p->data.id, p->data.name, p->data.score);
		}
		break;
	case 6:
		printf("******修改学生信息******\n");
		printf("请输入要修改的学生姓名：");
		scanf("%s", data.name);

		break;
	case 7:
		printf("已经安安全退出！");
		system("pause");//防止闪屏 
		exit(7);
		break;

	default:
		printf("输入有误,请重新入！");
		system("pause");//防止闪屏
		break;


	}
	writeFile(List, "1.txt");
}

int main()
{
	readFile(List, "1.txt");
	while (1)
	{
		menu();
		keydown();
	}
	return 0;
}




