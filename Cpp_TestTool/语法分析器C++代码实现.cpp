#if 0
#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
//定义几个全局变量 
int syn;
char s[1000];
int p = 0;
int k = 0;// 定义 k 作为一个标记符，记录是否出错，若 k=0 ，则说明没有出错，否则发生错误 
char key[6][20] = { "begin","if","then","while","do","end" };//定义一个二维数组存放关键字 
char token[20];	//存放字符（单词） 
void expression();
//判断关键字 
int isKey(char s[])
{
	for (int i = 0; i < 6; i++)
	{
		if (strcmp(s, key[i]) == 0)
		{
			return i + 1;	//关键字的种别码依次为 begin=1,if=2,then=3,while=4,do=5,end=6即为 i+1 的值 
		}
	}
	return -1;
}
//判断是不是字母 
bool isChar(char ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return true;
	else
		return false;
}
//判断是不是数字 
bool isNum(char ch)
{
	if (ch >= '0' && ch <= '9')
		return true;
	else
		return false;
}
//词法分析器 
void scanner()
{
	int count = 0;
	if (s[p] == ' ') p++;
	//开头是字母
	if (isChar(s[p]))
	{
		while (isNum(s[p]) || isChar(s[p]))
		{
			token[count++] = s[p];
			p++;
		}
		token[count] = '\0';	//'\0'作为结束符 ,将单词分隔开 
		syn = isKey(token);
		if (syn == -1)
		{
			syn = 10;	//标识符letter(letter|digit) *
		}
	}

	//开头是数字
	else if (isNum(s[p]))
	{
		while (isNum(s[p]))
		{
			token[count++] = s[p];
			p++;
		}
		token[count] = '\0';//结束标识 
		syn = 11;	//数字digit(digit) *
	}

	//如果是运算符或者界符
	else
	{
		//先处理没有争议的字符 
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


		//处理有争议的
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

		//后移 
		p++;	//判断运算符和界符的这部分由于指针 p 没有向后指，所以需要将指针 p 向后移一位 
	}

}

//以下各函数均要先调用 scanner()函数，用于首先产生 syn 的值
//因子-->项-->表达式-->赋值语句-->语句-->程序
//由小到大逐层封装函数 
void factor()	//因子 ：<因子> ：=ID | NUM | （<表达式>） 
{
	if (syn == 10 || syn == 11)	//当扫描的是数字或者字母时，继续扫描
	{
		scanner();
	}
	else if (syn == 27)	//当扫描到 '('时，后面应该为一个表达式，继续扫描
	{
		scanner();
		expression();
		if (syn == 28)		//当扫描的是 ')'时，继续扫描
			scanner();
		else
		{
			k = 1;	//出错 
			cout << "ERROR!缺少'）'" << endl;	//表达式缺 ')'，出错 
		}
	}
	else
	{
		k = 1;
		cout << "ERROR!运算符号后面不是常数或'('或标识符" << endl;	//扫描表达式 ，表达式不是以 '('开头 
	}
}

void term()//项 : <项> ：=<因子>{*<因子> | /<因子> } 
{
	factor();
	while (syn == 15 || syn == 16)	//当开头扫描的是 '*' 或者 '/'时('*'或者'/'后面是因子)，继续扫描
	{
		scanner();
		factor();
	}
}

void expression()//表达式 : <表达式> ：=<项>{+<项> | -<项>}
{
	term();
	while (syn == 13 || syn == 14)	//当开头扫描的是 '+' 或者 '-'时('+'或者'-'后面是项)，继续扫描
	{
		scanner();
		term();
	}
}

void statement()//赋值语句 : ID = <表达式>
{
	if (syn == 10)	//当开头扫描的是字母时，继续扫描
	{
		scanner();
		if (syn == 18)		//扫描的是 ':='时，继续扫描
		{
			scanner();
			expression();
		}
		else
		{
			k = 1;
			cout << "ERROR!缺少 ':=' " << endl;
		}
	}
	else
	{
		k = 1;
		cout << "ERROR!开头不是标识符！" << endl;
	}
}

void sens()//语句串 ：<语句串>：=<语句>{；<语句>}
{
	statement();
	while (syn == 26)	//当开始扫描的是 ';'时，继续扫描
	{
		scanner();
		statement();
	}
}

//程序 : <程序> ：=begin<语句串>end
void lrparser()
{
	if (syn == 1)	//当开头扫描的是 'begin'时，继续扫描
	{
		scanner();
		sens();
		if (syn == 6) //扫描到 'end'时，继续扫描 
		{
			scanner();
			if (syn == 0 && k == 0)	//当数字串最后扫描的是 '#'，而且无出错，分析成功
				cout << "success!" << endl;
			else if (syn != 0 || k == 1)
				cout << "error!" << endl;
		}
		else
		{
			cout << "ERROR!没有 'end'" << endl;
		}
	}
	else
	{
		cout << "ERROR!没有 'begin'" << endl;
	}
}
int main()
{
	char ch;
	while (true)
	{
		cout << "Please input a string:  " << endl;
		cin.getline(s, 1000);//getline()函数可以滤去空格 
		p = 0;
		scanner();
		lrparser();
	}
	return 0;
}
#endif // 0
