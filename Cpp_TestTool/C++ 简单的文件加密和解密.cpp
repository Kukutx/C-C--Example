#if 0
#include<stdio.h>   
#include<stdlib.h>   
#include<string.h>   
void encfile(char* in_filename, char* pwd, char* out_filename);/*对文件进行加密的具体函数*/
void decryptfile(char* in_filename, char* pwd, char* out_filename); /*对文件解密的具体函数*/
/*
*  即是按字节 或 按位 读取一个要加密的文件中的数据，然后与我们自己输入的密码做一些 算法操作，
*  将新的数据写入到新文件中，这个新文件就是我们的加密后的文件。
*/
int main(int argc, char* argv[])/*定义main()函数的命令行参数*/
{
    int option; /*功能选择*/
    char in_filename[30];/*用户输入的要加密的文件名 或是 要解密的文件*/
    char out_filename[30]; /*用户输入加密后保存的文件名 或是解密保存的文件名*/
    char pwd[8];/*用来保存密码*/
    printf("                   thank you for using this program....../n");
    printf("1. Encrypt a file         2. Decrypt a file/n");
    printf("chose your option.....");
    scanf("%d", &option);
    getchar();
    if (argc != 4) {/*容错处理*/
        printf("/nPlease input In-filename:/n");
        gets_s(in_filename);/*得到要加密的文件名*/
        printf("Please input your Password:/n");
        gets_s(pwd);/*得到密码*/
        printf("Please input Out-filename:/n");
        gets_s(out_filename);/*得到加密后你要的文件名*/

    }
    else {/*如果命令行参数正确,便直接运行程序*/
        strcpy(in_filename, argv[1]);
        strcpy(pwd, argv[2]);
        strcpy(out_filename, argv[3]);
    }

    switch (option) {
    case 1: //加密      
        encfile(in_filename, pwd, out_filename);/*加密函数调用*/
        break;
    case 2://解密  
        decryptfile(in_filename, pwd, out_filename);/*解密函数调用*/
        break;
    default:
        break;
    }

    system("pause");
    return 0;
}

/*加密子函数开始*/
void encfile(char* in_filename, char* pwd, char* out_file)
{
    FILE* fp1, * fp2;
    register char ch;
    int j = 0;
    int j0 = 0;
    fp1 = fopen(in_filename, "r");/*打开要加密的文件*/
    if (fp1 == NULL) {
        printf("cannot open in-file./n");
        exit(1);/*如果不能打开要加密的文件,便退出程序*/
    }
    fp2 = fopen(out_file, "w");
    if (fp2 == NULL) {
        printf("cannot open or create out-file./n");
        exit(1);/*如果不能建立加密后的文件,便退出*/
    }

    while (pwd[++j0]);

    ch = fgetc(fp1);

    /*加密算法开始*/
    while (!feof(fp1)) {
        if (j0 > 7)
            j0 = 0;
        ch += pwd[j0++];
        fputc(ch, fp2);
        ch = fgetc(fp1);
    }
    fclose(fp1);/*关闭源文件*/
    fclose(fp2);/*关闭目标文件*/
}

/*解密子函数开始*/
void decryptfile(char* in_filename, char* pwd, char* out_file)
{
    FILE* fp1, * fp2;
    register char ch;
    int j = 0;
    int j0 = 0;
    fp1 = fopen(in_filename, "r");/*打开要解密的文件*/
    if (fp1 == NULL) {
        printf("cannot open in-file./n");
        exit(1);/*如果不能打开要解密的文件,便退出程序*/
    }
    fp2 = fopen(out_file, "w");
    if (fp2 == NULL) {
        printf("cannot open or create out-file./n");
        exit(1);/*如果不能建立解密后的文件,便退出*/
    }

    while (pwd[++j0]);
    ch = fgetc(fp1);
    /*解密算法开始*/
    while (!feof(fp1)) {
        if (j0 > 7)
            j0 = 0;
        ch -= pwd[j0++];
        fputc(ch, fp2);/*我的解密算法*/
        ch = fgetc(fp1);
    }
    fclose(fp1);/*关闭源文件*/
    fclose(fp2);/*关闭目标文件*/
}
#endif // 0
