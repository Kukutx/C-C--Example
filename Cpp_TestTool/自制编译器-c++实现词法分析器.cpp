#if 0
#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <string>
using namespace std;
#pragma warning(disable:4996)
#define NTOKEN 1000
/*����һ��ʷ���Ԫ*/
//����ʷ���Ԫֵ
enum TokenValue {
    TOK_COMMA,          //����
    TOK_DIV,
    TOK_END,
    TOK_EQUAL,
    TOK_FOR,
    TOK_ID,
    TOK_IF,
    TOK_INTEGER,
    TOK_MINUS,
    TOK_MULT,
    TOK_PLUS,
    TOK_SEMICOLON,
    TOK_UNDEFINED,
    TOK_WHILE,
};
string TOKEN_VALUE_DESCRIPTION[] =
{
    "TOK_COMMA",
    "TOK_DIV",
    "TOK_END",
    "TOK_EQUAL",
    "TOK_FOR",
    "TOK_ID",
    "TOK_IF",
    "TOK_INTEGER",
    "TOK_MINUS",
    "TOK_MULT",
    "TOK_PLUS",
    "TOK_SEMICOLON",
    "TOK_UNDEFINED",
    "TOK_WHILE",
};
//��ǩ�ͱ�ǩ��ֵ
typedef struct _Token {
    int  type;
    string str;
} Token;
Token token[NTOKEN];
//�������Ϊ·��
int lexer(char* path) {
    FILE* fin;
    int  ch;
    char buf[256], * p;
    int n = 0;

    if ((fin = fopen(path, "r")) == NULL) {
        fprintf(stderr, "Cant' open the file... :(\n");
    }
    while ((ch = fgetc(fin)) != EOF) {
        if (ch <= ' ') continue;                  // [\n\t ]
        p = buf;
        switch (ch)
        {
        case '+':
            token[n].type = TOK_PLUS;
            token[n++].str = '+';
            break;
        case '-':
            token[n].type = TOK_MINUS;
            token[n++].str = '-';
            break;
        case '*':
            token[n].type = TOK_MINUS;
            token[n++].str = '*';
            break;
        case ';':
            token[n].type = TOK_SEMICOLON;
            token[n++].str = ';';
            break;
        case '=':
            token[n].type = TOK_EQUAL;
            token[n++].str = '=';
            break;
        case ',':
            token[n].type = TOK_COMMA;
            token[n++].str = ',';
            break;
        default:
            break;
        }
        if (isalpha(ch)) {                        // [A-Za-z][A-Za-z0-9],����ĸ��ͷΪ��
            token[n].type = TOK_ID;               //��һ����ʶ��
            *p++ = ch;
            while (isalnum(ch = fgetc(fin))) *p++ = ch;  //�Ƿ�Ϊ��ĸ������
            ungetc(ch, fin);
            *p++ = '\0';
            token[n++].str = buf;
        }
        if (isdigit(ch)) {                 // [0-9]+
            token[n].type = TOK_INTEGER;
            *p++ = ch;
            while (isdigit(ch = fgetc(fin))) *p++ = ch;
            ungetc(ch, fin);
            *p++ = '\0';
            token[n++].str = buf;
        }
    }
    fclose(fin);
    return n;
}
/*************************************************************************************
CMD�����еĽ����
void main(int argc, char* argv[]) {
    int n;
    int nToken = lexer(argv[1]);
    for (n = 0; n < nToken; n++) {
        //printf("%s: %s\n", TOKEN_VALUE_DESCRIPTION[token[n].type], token[n].str);
        cout << TOKEN_VALUE_DESCRIPTION[token[n].type] << ": " << token[n].str << endl;
    }
}
***************************************************************************************/
//vs�ϵ��Խ��

/* �������н��е��ʵķָ� */
void main(int argc, char* argv[]) {
    int n;
    const char* input = "aa.txt";
    int nToken = lexer((char*)input);
    for (n = 0; n < nToken; n++) {
        cout << TOKEN_VALUE_DESCRIPTION[token[n].type] << ": " << token[n].str << endl;
    }
}
#endif // 0
