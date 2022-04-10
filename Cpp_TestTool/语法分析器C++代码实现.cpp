#if 0
#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
//���弸��ȫ�ֱ��� 
int syn;
char s[1000];
int p = 0;
int k = 0;// ���� k ��Ϊһ����Ƿ�����¼�Ƿ������ k=0 ����˵��û�г������������� 
char key[6][20] = { "begin","if","then","while","do","end" };//����һ����ά�����Źؼ��� 
char token[20];	//����ַ������ʣ� 
void expression();
//�жϹؼ��� 
int isKey(char s[])
{
	for (int i = 0; i < 6; i++)
	{
		if (strcmp(s, key[i]) == 0)
		{
			return i + 1;	//�ؼ��ֵ��ֱ�������Ϊ begin=1,if=2,then=3,while=4,do=5,end=6��Ϊ i+1 ��ֵ 
		}
	}
	return -1;
}
//�ж��ǲ�����ĸ 
bool isChar(char ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return true;
	else
		return false;
}
//�ж��ǲ������� 
bool isNum(char ch)
{
	if (ch >= '0' && ch <= '9')
		return true;
	else
		return false;
}
//�ʷ������� 
void scanner()
{
	int count = 0;
	if (s[p] == ' ') p++;
	//��ͷ����ĸ
	if (isChar(s[p]))
	{
		while (isNum(s[p]) || isChar(s[p]))
		{
			token[count++] = s[p];
			p++;
		}
		token[count] = '\0';	//'\0'��Ϊ������ ,�����ʷָ��� 
		syn = isKey(token);
		if (syn == -1)
		{
			syn = 10;	//��ʶ��letter(letter|digit) *
		}
	}

	//��ͷ������
	else if (isNum(s[p]))
	{
		while (isNum(s[p]))
		{
			token[count++] = s[p];
			p++;
		}
		token[count] = '\0';//������ʶ 
		syn = 11;	//����digit(digit) *
	}

	//�������������߽��
	else
	{
		//�ȴ���û��������ַ� 
		switch (s[p])
		{
		case '+': syn = 13; token[0] = s[p]; token[1] = '\0'; break;
		case '-': syn = 14; token[0] = s[p]; token[1] = '\0'; break;
		case '*': syn = 15; token[0] = s[p]; token[1] = '\0'; break;
		case '/': syn = 16; token[0] = s[p]; token[1] = '\0'; break;
		case '=': syn = 25; token[0] = s[p]; token[1] = '\0'; break;
		case ';': syn = 26; token[0] = s[p]; token[1] = '\0'; break;
		case '(': syn = 27; token[0] = s[p]; token[1] = '\0'; break;
		case ')': syn = 28; token[0] = s[p]; token[1] = '\0'; break;
		case '#': syn = 0; token[0] = s[p]; token[1] = '\0'; break;
		}


		//�����������
		//: :=
		if (s[p] == ':')
		{
			token[count++] = s[p];
			if (s[p + 1] == '=')
			{
				p++;
				token[count++] = s[p];
				syn = 18;
			}
			else
			{
				syn = 17;
			}
			token[count] = '\0';
		}

		//< <> <=
		if (s[p] == '<')
		{
			token[count++] = s[p];
			if (s[p + 1] == '>')
			{
				p++;
				token[count++] = s[p];
				syn = 21;
			}
			else if (s[p + 1] == '=')
			{
				p++;
				token[count++] = s[p];
				syn = 22;
			}
			else
			{
				syn = 20;
			}
			token[count] = '\0';
		}

		//> >=
		if (s[p] == '>')
		{
			token[count++] = s[p];
			if (s[p + 1] == '=')
			{
				p++;
				token[count++] = s[p];
				syn = 24;
			}
			else
			{
				syn = 23;
			}
			token[count] = '\0';
		}

		//���� 
		p++;	//�ж�������ͽ�����ⲿ������ָ�� p û�����ָ��������Ҫ��ָ�� p �����һλ 
	}

}

//���¸�������Ҫ�ȵ��� scanner()�������������Ȳ��� syn ��ֵ
//����-->��-->���ʽ-->��ֵ���-->���-->����
//��С��������װ���� 
void factor()	//���� ��<����> ��=ID | NUM | ��<���ʽ>�� 
{
	if (syn == 10 || syn == 11)	//��ɨ��������ֻ�����ĸʱ������ɨ��
	{
		scanner();
	}
	else if (syn == 27)	//��ɨ�赽 '('ʱ������Ӧ��Ϊһ�����ʽ������ɨ��
	{
		scanner();
		expression();
		if (syn == 28)		//��ɨ����� ')'ʱ������ɨ��
			scanner();
		else
		{
			k = 1;	//���� 
			cout << "ERROR!ȱ��'��'" << endl;	//���ʽȱ ')'������ 
		}
	}
	else
	{
		k = 1;
		cout << "ERROR!������ź��治�ǳ�����'('���ʶ��" << endl;	//ɨ����ʽ �����ʽ������ '('��ͷ 
	}
}

void term()//�� : <��> ��=<����>{*<����> | /<����> } 
{
	factor();
	while (syn == 15 || syn == 16)	//����ͷɨ����� '*' ���� '/'ʱ('*'����'/'����������)������ɨ��
	{
		scanner();
		factor();
	}
}

void expression()//���ʽ : <���ʽ> ��=<��>{+<��> | -<��>}
{
	term();
	while (syn == 13 || syn == 14)	//����ͷɨ����� '+' ���� '-'ʱ('+'����'-'��������)������ɨ��
	{
		scanner();
		term();
	}
}

void statement()//��ֵ��� : ID = <���ʽ>
{
	if (syn == 10)	//����ͷɨ�������ĸʱ������ɨ��
	{
		scanner();
		if (syn == 18)		//ɨ����� ':='ʱ������ɨ��
		{
			scanner();
			expression();
		}
		else
		{
			k = 1;
			cout << "ERROR!ȱ�� ':=' " << endl;
		}
	}
	else
	{
		k = 1;
		cout << "ERROR!��ͷ���Ǳ�ʶ����" << endl;
	}
}

void sens()//��䴮 ��<��䴮>��=<���>{��<���>}
{
	statement();
	while (syn == 26)	//����ʼɨ����� ';'ʱ������ɨ��
	{
		scanner();
		statement();
	}
}

//���� : <����> ��=begin<��䴮>end
void lrparser()
{
	if (syn == 1)	//����ͷɨ����� 'begin'ʱ������ɨ��
	{
		scanner();
		sens();
		if (syn == 6) //ɨ�赽 'end'ʱ������ɨ�� 
		{
			scanner();
			if (syn == 0 && k == 0)	//�����ִ����ɨ����� '#'�������޳��������ɹ�
				cout << "success!" << endl;
			else if (syn != 0 || k == 1)
				cout << "error!" << endl;
		}
		else
		{
			cout << "ERROR!û�� 'end'" << endl;
		}
	}
	else
	{
		cout << "ERROR!û�� 'begin'" << endl;
	}
}
int main()
{
	char ch;
	while (true)
	{
		cout << "Please input a string:  " << endl;
		cin.getline(s, 1000);//getline()����������ȥ�ո� 
		p = 0;
		scanner();
		lrparser();
	}
	return 0;
}
#endif // 0
