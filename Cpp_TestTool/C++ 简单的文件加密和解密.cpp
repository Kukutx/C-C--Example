#if 0
#include<stdio.h>   
#include<stdlib.h>   
#include<string.h>   
void encfile(char* in_filename, char* pwd, char* out_filename);/*���ļ����м��ܵľ��庯��*/
void decryptfile(char* in_filename, char* pwd, char* out_filename); /*���ļ����ܵľ��庯��*/
/*
*  ���ǰ��ֽ� �� ��λ ��ȡһ��Ҫ���ܵ��ļ��е����ݣ�Ȼ���������Լ������������һЩ �㷨������
*  ���µ�����д�뵽���ļ��У�������ļ��������ǵļ��ܺ���ļ���
*/
int main(int argc, char* argv[])/*����main()�����������в���*/
{
    int option; /*����ѡ��*/
    char in_filename[30];/*�û������Ҫ���ܵ��ļ��� ���� Ҫ���ܵ��ļ�*/
    char out_filename[30]; /*�û�������ܺ󱣴���ļ��� ���ǽ��ܱ�����ļ���*/
    char pwd[8];/*������������*/
    printf("                   thank you for using this program....../n");
    printf("1. Encrypt a file         2. Decrypt a file/n");
    printf("chose your option.....");
    scanf("%d", &option);
    getchar();
    if (argc != 4) {/*�ݴ���*/
        printf("/nPlease input In-filename:/n");
        gets_s(in_filename);/*�õ�Ҫ���ܵ��ļ���*/
        printf("Please input your Password:/n");
        gets_s(pwd);/*�õ�����*/
        printf("Please input Out-filename:/n");
        gets_s(out_filename);/*�õ����ܺ���Ҫ���ļ���*/

    }
    else {/*��������в�����ȷ,��ֱ�����г���*/
        strcpy(in_filename, argv[1]);
        strcpy(pwd, argv[2]);
        strcpy(out_filename, argv[3]);
    }

    switch (option) {
    case 1: //����      
        encfile(in_filename, pwd, out_filename);/*���ܺ�������*/
        break;
    case 2://����  
        decryptfile(in_filename, pwd, out_filename);/*���ܺ�������*/
        break;
    default:
        break;
    }

    system("pause");
    return 0;
}

/*�����Ӻ�����ʼ*/
void encfile(char* in_filename, char* pwd, char* out_file)
{
    FILE* fp1, * fp2;
    register char ch;
    int j = 0;
    int j0 = 0;
    fp1 = fopen(in_filename, "r");/*��Ҫ���ܵ��ļ�*/
    if (fp1 == NULL) {
        printf("cannot open in-file./n");
        exit(1);/*������ܴ�Ҫ���ܵ��ļ�,���˳�����*/
    }
    fp2 = fopen(out_file, "w");
    if (fp2 == NULL) {
        printf("cannot open or create out-file./n");
        exit(1);/*������ܽ������ܺ���ļ�,���˳�*/
    }

    while (pwd[++j0]);

    ch = fgetc(fp1);

    /*�����㷨��ʼ*/
    while (!feof(fp1)) {
        if (j0 > 7)
            j0 = 0;
        ch += pwd[j0++];
        fputc(ch, fp2);
        ch = fgetc(fp1);
    }
    fclose(fp1);/*�ر�Դ�ļ�*/
    fclose(fp2);/*�ر�Ŀ���ļ�*/
}

/*�����Ӻ�����ʼ*/
void decryptfile(char* in_filename, char* pwd, char* out_file)
{
    FILE* fp1, * fp2;
    register char ch;
    int j = 0;
    int j0 = 0;
    fp1 = fopen(in_filename, "r");/*��Ҫ���ܵ��ļ�*/
    if (fp1 == NULL) {
        printf("cannot open in-file./n");
        exit(1);/*������ܴ�Ҫ���ܵ��ļ�,���˳�����*/
    }
    fp2 = fopen(out_file, "w");
    if (fp2 == NULL) {
        printf("cannot open or create out-file./n");
        exit(1);/*������ܽ������ܺ���ļ�,���˳�*/
    }

    while (pwd[++j0]);
    ch = fgetc(fp1);
    /*�����㷨��ʼ*/
    while (!feof(fp1)) {
        if (j0 > 7)
            j0 = 0;
        ch -= pwd[j0++];
        fputc(ch, fp2);/*�ҵĽ����㷨*/
        ch = fgetc(fp1);
    }
    fclose(fp1);/*�ر�Դ�ļ�*/
    fclose(fp2);/*�ر�Ŀ���ļ�*/
}
#endif // 0
