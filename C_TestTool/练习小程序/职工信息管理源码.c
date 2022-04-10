#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
struct worker
{
  char ID[20];       //工号
  char name[20];     //姓名
  char sex[5];       //性别
  char born[20];     //生日
  char edu[20];      //学历
  char position[20]; //职务
  char wage[10];     //工资
  char address[100]; //住址
  char tel[15];      //电话
} work[1000];
int n;

//文件读写模块
void read() //读入数据
{
  FILE *fp;
  int i = 0;
  if ((fp = fopen("d:\\date.txt", "r")) == NULL)
  {
    printf("请在D盘根目录下新建一个文本文件，文件名为date\n\n\n");
    system("pause");
    system("cls");
    return;
  }
  fscanf(fp, "%d\n", &n);
  while (i < n)
  {
    fscanf(fp, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", work[i].ID, work[i].name, work[i].sex, work[i].born, work[i].edu, work[i].position, work[i].wage, work[i].address, work[i].tel);
    i++;
  }
  fclose(fp);
}
void write() //写入数据
{
  FILE *fp;
  int i = 0;
  if ((fp = fopen("d:\\date.txt", "w")) == NULL)
  {
    printf("无法打开文件！\n");
    return;
  }
  fprintf(fp, "%d\n", n);
  while (i < n)
  {
    fprintf(fp, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", work[i].ID, work[i].name, work[i].sex, work[i].born, work[i].edu, work[i].position, work[i].wage, work[i].address, work[i].tel);
    i++;
  }
  fclose(fp);
}

//输入模块
void input() // 从键盘输入
{
  int i;
  int flag; //标记工号是否已存在
  char c;   //指令Y?N
  read();   //输入数据前先将文件中原有的数据读入
  do
  {
    flag = 0;
    printf("\t\t请输入职工的工号:               \n\t\t");
    scanf("%s", work[n].ID);
    for (i = 0; i < n; i++)
    {
      if (strcmp(work[i].ID, work[n].ID) == 0)
      {
        flag = 1;
        break;
      }
    }
    if (flag)
    {
      printf("该工号已存在！\n\n");
      printf("\t\t是否继续输入?(Y/N): ");
      scanf("%*c%c", &c);
      if (c == 'N' || c == 'n')
        break;
      continue;
    }
    printf("\t\t请输入职工的姓名:               \n\t\t");
    scanf("%s", work[n].name);
    printf("\t\t请输入职工的性别:               \n\t\t");
    scanf("%s", work[n].sex);
    printf("\t\t请输入职工的出生年月:             \n\t\t");
    scanf("%s", work[n].born);
    printf("\t\t请输入职工的学历:               \n\t\t");
    scanf("%s", work[n].edu);
    printf("\t\t请输入职工的职务:               \n\t\t");
    scanf("%s", work[n].position);
    printf("\t\t请输入职工的工资:               \n\t\t");
    scanf("%s", work[n].wage);
    printf("\t\t请输入职工的住址:               \n\t\t");
    scanf("%s", work[n].address);
    printf("\t\t请输入职工的电话:               \n\t\t");
    scanf("%s", work[n].tel);
    printf("\t\t是否继续输入?(Y/N): ");
    scanf("%*c%c", &c);
    n++;
  } while (c != 'N' && c != 'n');
  write();
  printf("\n\n数据已保存！\n\n");
}

//显示模块
void output_inf(int id)
{
  printf("\t\t  工号: %s\n", work[id].ID);
  printf("\t\t  姓名: %s\n", work[id].name);
  printf("\t\t  性别: %s\n", work[id].sex);
  printf("\t\t出生年月: %s\n", work[id].born);
  printf("\t\t  学历: %s\n", work[id].edu);
  printf("\t\t  职务: %s\n", work[id].position);
  printf("\t\t  工资: %s\n", work[id].wage);
  printf("\t\t  住址: %s\n", work[id].address);
  printf("\t\t  电话: %s\n", work[id].tel);
  printf("\n\n\n");
}
void show() //显示所有职工信息
{
  int i;
  read();
  if (n == 0)
    printf("无记录!\n\n");
  else
    for (i = 0; i < n; i++)
    {
      output_inf(i);
    }
}

//查询模块
void que() //查询信息
{
  char num;
  int flag, i;
  char q_id[20];       //查询工号
  char q_name[20];     //查询姓名
  char q_edu[20];      //查询学历
  char q_position[20]; //查询职位
  char c;              //指令Y?N
  read();              //打开程序后，要查询以前的数据，要先读入
  while (1)
  {
    system("cls");
    printf("\t\t******************查询********************\n");
    printf("\t\t*                    *\n");
    printf("\t\t*       1.按工号查询        *\n");
    printf("\t\t*                    *\n");
    printf("\t\t*       2.按姓名查询        *\n");
    printf("\t\t*                    *\n");
    printf("\t\t*       3.按学历查询        *\n");
    printf("\t\t*                    *\n");
    printf("\t\t*       4.按职务查询        *\n");
    printf("\t\t*                    *\n");
    printf("\t\t*    输入其他任意键退出本模块     *\n");
    printf("\t\t******************************************\n");
    printf("\t\t请输入指令(1-4):");
    scanf("%*c%c", &num);
    if (num < '1' || num > '4')
    {
      printf("错误指令！\n\n");
      system("pause");
      continue;
    }
    system("cls");
    flag = 0;       //用来标记职工信息是否存在
    if (num == '1') //按工号查询
    {
      printf("\t\t请输入您要查询职工的工号：");
      scanf("%s", q_id);
      for (i = 0; i < n; i++)
      {
        if (strcmp(work[i].ID, q_id) == 0)
        {
          output_inf(i);
          flag = 1; //标记
          break;
        }
      }
    }
    else if (num == '2') //按姓名查询
    {
      printf("\t\t请输入您要查询职工的姓名：");
      scanf("%s", q_name);
      for (i = 0; i < n; i++)
      {
        if (strcmp(work[i].name, q_name) == 0)
        {
          output_inf(i);
          flag = 1; //标记
        }
      }
    }
    else if (num == '3') //按学历查询
    {
      printf("\t\t请输入您要查询职工的学历：");

      scanf("%s", q_edu);
      for (i = 0; i < n; i++)
      {
        if (strcmp(work[i].edu, q_edu) == 0)
        {
          output_inf(i);
          flag = 1; //标记
        }
      }
    }
    else if (num == '4') //按职务查询
    {
      printf("\t\t请输入您要查询职工的职务：");
      scanf("%s", q_position);
      for (i = 0; i < n; i++)
      {
        if (strcmp(work[i].position, q_position) == 0)
        {
          output_inf(i);
          flag = 1; //标记
        }
      }
    }
    if (!flag) //判断是否有该职工信息
    {
      printf("\n\n无该职工信息!\n\n");
    }
    printf("\n\n是否继续查询(Y/N):");

    scanf("%*c%c", &c);
    if (c == 'N' || c == 'n')
      break;
  }
}

//修改信息模块
void mod() //修改职工信息
{
  char change_ID[20]; //需修改的职工的工号
  int number;         //职工信息在数据中的位置
  char num;           //指令
  char message[100];  //修改的信息
  char c;             //指令Y?N
  int flag;
  int i;
  read();
  while (1)
  {
    flag = 0;
    system("cls");
    printf("请输入需修改的职工的工号：");
    scanf("%s", change_ID);
    for (i = 0; i < n; i++)
    {
      if (strcmp(work[i].ID, change_ID) == 0)
      {
        number = i;
        flag = 1;
        break;
      }
    }
    if (!flag)
    {
      printf("\n\n无此员工信息！！\n\n");
      printf("\n\n是否继续修改(Y/N):");
      scanf("%*c%c", &c);
      if (c == 'N' || c == 'n')
        break;
      continue;
    }
    printf("\n\n\t\t******************修改********************\n");
    printf("\t\t*                    *\n");
    printf("\t\t*       1.修改姓名         *\n");
    printf("\t\t*                    *\n");
    printf("\t\t*       2.修改学历         *\n");
    printf("\t\t*                    *\n");
    printf("\t\t*       3.修改职务         *\n");
    printf("\t\t*                    *\n");
    printf("\t\t*       4.修改工资         *\n");
    printf("\t\t*                    *\n");
    printf("\t\t*       5.修改住址         *\n");
    printf("\t\t*                    *\n");
    printf("\t\t*       6.修改电话         *\n");
    printf("\t\t*                    *\n");
    printf("\t\t*    输入其他任意键退出本模块     *\n");
    printf("\t\t******************************************\n");
    printf("\t\t请输入指令(1-6):");
    scanf("%*c%c", &num);
    if (num < '1' || num > '6')
    {
      printf("错误指令！\n\n");
      system("pause");
      continue;
    }
    system("cls");
    printf("请输入修改后的信息：");
    scanf("%s", message);
    switch (num)
    {
    case '1':
      strcpy(work[number].name, message);
      break;
    case '2':
      strcpy(work[number].edu, message);
      break;
    case '3':
      strcpy(work[number].position, message);
      break;
    case '4':
      strcpy(work[number].wage, message);
      break;
    case '5':
      strcpy(work[number].address, message);
      break;
    case '6':
      strcpy(work[number].tel, message);
      break;
    }
    system("cls");
    printf("\n\n是否继续修改(Y/N):");
    scanf("%*c%c", &c);
    if (c == 'N' || c == 'n')
      break;
  }
  write();
}

//删除信息模块
void del() //删除职工信息
{
  char delete_ID[20]; //删除职工工号
  int i, j;
  int flag; //标记是否有该职工信息
  char c;
  read();
  while (1)
  {
    system("cls");
    flag = 0;
    printf("请输入需删除职工信息的工号：");
    scanf("%s", delete_ID);
    for (i = 0; i < n; i++)
    {
      if (strcmp(work[i].ID, delete_ID) == 0)
      {
        n--;
        flag = 1;
        for (j = i; j < n; j++)
        {
          work[j] = work[j + 1];
        }
        break;
      }
    }
    if (!flag)
      printf("\n\n无此员工信息！\n\n");
    else
      printf("\n\n删除成功！\n");
    printf("\n\n是否继续删除(Y/N):");
    scanf("%*c%c", &c);
    if (c == 'N' || c == 'n')
      break;
  }
  write();
}

//菜单模块
void menu() //菜单
{
  printf("\t\t************职工信息管理系统菜单**********\n");
  printf("\t\t*                    *\n");
  printf("\t\t*       1.录入职工信息      *\n");
  printf("\t\t*                    *\n");
  printf("\t\t*       2.显示职工信息      *\n");
  printf("\t\t*                    *\n");
  printf("\t\t*       3.查询职工信息      *\n");
  printf("\t\t*                    *\n");
  printf("\t\t*       4.修改职工信息      *\n");
  printf("\t\t*                    *\n");
  printf("\t\t*       5.删除职工信息      *\n");
  printf("\t\t*                    *\n");
  printf("\t\t*       0.退出          *\n");
  printf("\t\t*                    *\n");
  printf("\t\t******************************************\n");
  printf("\t\t请输入指令(0-5): ");
}

int main()
{
  int num;
  n = 0;
  system("color 0B");
  while (1)
  {
    menu();
    scanf("%d", &num);
    system("cls");
    switch (num)
    {
    case 1:
      input();
      break;
    case 2:
      show();
      break;
    case 3:
      que();
      break;
    case 4:
      mod();
      break;
    case 5:
      del();
      break;
    case 0:
      printf("谢谢使用！\n\n");
      return 0;
    default:
      printf("\n--->无效的指令!\n\n\n");
    }
    system("pause");
    system("cls");
  }
}