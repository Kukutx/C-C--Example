#if 0
#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <conio.h>
#include <vector>
#include <string>
#include <map>
using namespace std;
#pragma warning(disable:4996)
// ���ű�
enum eType
{
	Symbol
};
map<string, eType> g_mapSymbol;

enum eCharFlag
{
	noFlag,
	explain
};

eCharFlag g_charFlag = noFlag;

int main()
{
	// ���볣�ñ�ʶ��
	g_mapSymbol["if"] = Symbol;

	// ��ȡ����
	int i = 0, j = 0, k = 0;
	char oneChar;
	char fname[200];
	memset(fname, 0, 200);
	printf("������Ҫ�򿪵��ļ���:\n");
	scanf("%s", fname);

	// for ����
	//strcpy(fname, "d:\\1.cpp");

	// ���ļ�
	FILE* fp;
	if ((fp = fopen(fname, "r")) == NULL)
	{
		printf("Cannot open infile.\n");
		exit(0);
	}

	//int 0i;

	// �����ļ�
	oneChar = fgetc(fp);
	char oneWord[256] = { 0 };
	int nBuf = 0;
	vector<string> vecWords;
	while (oneChar != EOF)
	{
		if (nBuf == 0)
		{
			if (oneChar == ' ' || oneChar == '\n' || oneChar == '\t')
			{

			}
			else if (oneChar == '(' || oneChar == '{')
			{
				oneWord[nBuf++] = oneChar;
				string strWord = oneWord;
				vecWords.push_back(strWord);
				nBuf = 0;
				g_charFlag = noFlag;
				memset(oneWord, 0, 256);
				//continue;
			}
			else if (oneChar == ')' || oneChar == '}')
			{
				oneWord[nBuf++] = oneChar;
				string strWord = oneWord;
				vecWords.push_back(strWord);
				nBuf = 0;
				g_charFlag = noFlag;
				memset(oneWord, 0, 256);
				//continue;
			}
			else if (oneChar >= '0' && oneChar <= '9')
			{
				/*printf("error, ���������ִ�ͷ");
				return -1;*/
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar >= 'a' && oneChar <= 'z')
			{
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar >= 'A' && oneChar <= 'Z')
			{
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar == '#')
			{
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar == ':')
			{
				// ���޷���
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar == '/')
			{
				// ע�͵Ŀ�ʼ���ҵڶ�������
				// ������·������
				oneWord[nBuf++] = oneChar;
				g_charFlag = explain;
			}
			else if (oneChar == '(')
			{
				// �����Ŀ�ʼ���ҵڶ�������
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar == ')')
			{
				// �����Ľ���
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar == '{')
			{
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar == '}')
			{
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar == ';')
			{
				// ��������
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar == '~')
			{
				// ����������
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar == '\"')
			{
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar == '=')
			{
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar == '_')
			{
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar == '?')
			{
				oneWord[nBuf++] = oneChar;
			}
			else
			{
				//printf("δ���������%c", oneChar);
				oneWord[nBuf++] = oneChar;
			}
		}
		else
		{
			if (oneChar == ' ' || oneChar == '\t' || oneChar == '\n')
			{
				if (g_charFlag != explain)
				{
					string strWord = oneWord;
					vecWords.push_back(strWord);
					nBuf = 0;
					g_charFlag = noFlag;
					memset(oneWord, 0, 256);
				}
				else if (g_charFlag == explain && oneChar == '\n')
				{
					// �����ע��״̬,�������س��Žض�
					string strWord = oneWord;
					vecWords.push_back(strWord);
					nBuf = 0;
					g_charFlag = noFlag;
					memset(oneWord, 0, 256);
				}
			}
			else if (oneChar == '(' || oneChar == '{')
			{
				//oneWord[nBuf++]	= oneChar;
				string strWord = oneWord;
				vecWords.push_back(strWord);
				nBuf = 0;
				g_charFlag = noFlag;
				memset(oneWord, 0, 256);
				continue;
			}
			else if (oneChar == ')' || oneChar == '}')
			{
				//oneWord[nBuf++]	= oneChar;
				string strWord = oneWord;
				vecWords.push_back(strWord);
				nBuf = 0;
				g_charFlag = noFlag;
				memset(oneWord, 0, 256);
				continue;
			}
			//else if(oneChar == '\n')
			//{
			//	// ��ĩ, ����һЩ���, ����ע�͵�
			//}
			else if (oneChar >= '0' && oneChar <= '9')
			{
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar >= 'a' && oneChar <= 'z')
			{
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar >= 'A' && oneChar <= 'Z')
			{
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar == '_')
			{
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar == ':')
			{
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar == '(')
			{
				// �����Ŀ�ʼ���ҵڶ�������
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar == ')')
			{
				// �����Ľ���
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar == '{')
			{
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar == '}')
			{
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar == ';')
			{
				// ��������
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar == '~')
			{
				// ����������
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar == '\"')
			{
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar == '*')
			{
				// ����ָ��
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar == '.')
			{
				// .h
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar == '=')
			{
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar == '/')
			{
				// �����ע��״̬, �ȴ�һ�н���
				//if(g_charFlag == explain)
				{
					//oneWord[nBuf++]	= oneChar;
					//string strWord = oneWord;
					//vecWords.push_back(strWord);
					//nBuf = 0;
					g_charFlag = noFlag;
					//memset(oneWord, 0, 256);
					//oneWord[nBuf++]	= oneChar;
				}
				//else
				{
					oneWord[nBuf++] = oneChar;
				}
			}
			else if (oneChar == ',')
			{
				oneWord[nBuf++] = oneChar;
			}
			else if (oneChar == '?')
			{
				oneWord[nBuf++] = oneChar;
			}
			else
			{
				oneWord[nBuf++] = oneChar;
				//printf("δ���������%c", oneChar);

				//string strWord = "δ���������%s";
				//printf("error, δ�������.");
				//return -1;
			}
		}
		oneChar = fgetc(fp);
	}
	fclose(fp);

	// д���ļ�
	FILE* fpIn;
	if ((fpIn = fopen("d:\\words.txt", "w+")) == NULL)
	{
		printf("Cannot open infile.\n");
		exit(0);
	}

	for (int i = 0; i < vecWords.size(); i++)
	{
		char szBuf[300];
		memset(szBuf, 0, 300);
		sprintf(szBuf, "%d. %s\n", i, vecWords[i].c_str());
		fwrite(szBuf, strlen(szBuf), 1, fpIn);
		//printf("%d. %s\n", i, vecWords[i].c_str());
	}
	fclose(fpIn);

	// �﷨����
	// ����Ҫ�����Ž���ƥ��,��֤�﷨��
	vector<string> vecClass;	// ��������
	vector<string> vecHeader;	// ������ͷ�ļ�
	typedef struct
	{
		string funcName;
		string paramList;
	}stFunc;
	vector<stFunc> vecFunc;		// ����������
	for (int i = 0; i < vecWords.size(); i++)
	{
		if (vecWords[i] == "#include")
		{
			// �﷨���������Ŵʷ�����������仯

			//if(i > 0)
			//{
			//	// û��ע�͵���ͷ�ļ�
			//	if(vecWords[i-1] != "//")
			//	{
			//		vecHeader.push_back(vecWords[i+1]);
			//	}
			//}	

			vecHeader.push_back(vecWords[i + 1]);
		}
		else if (vecWords[i] == "(")
		{
			// ǰ���Ǻ�����, �����ǲ���
			if (i > 0)
			{
				if (g_mapSymbol.find(vecWords[i - 1]) != g_mapSymbol.end())
				{
					//  ˵���Ǳ�׼��ʾ��,���Ǻ���
					continue;
				}
				stFunc f;
				f.funcName = vecWords[i - 1];
				string strParamList = "(";
				while (vecWords[i++] != ")")
				{
					if (vecWords[i] == "(")
					{
						strParamList += "(";
						while (vecWords[i++] != ")")
						{
							strParamList += " ";
							strParamList += vecWords[i];
						}
					}
					strParamList += " ";
					strParamList += vecWords[i];
				}
				f.paramList = strParamList;
				vecFunc.push_back(f);
			}
		}
		else if (vecWords[i] == "()")
		{
			// ǰ���Ǻ�����, �м��޲���
			if (i > 0)
			{
				stFunc f;
				f.funcName = vecWords[i - 1];
				f.paramList = "";
				vecFunc.push_back(f);
			}
		}
		else if (vecWords[i] == "class")
		{
			// ��һ��������
			string strClass = vecWords[i + 1];
			vecClass.push_back(strClass);
		}
	}

	// Grammar д���ļ�
	if ((fpIn = fopen("d:\\grammar.txt", "w+")) == NULL)
	{
		printf("Cannot open infile.\n");
		exit(0);
	}

	// ͷ�ļ�
	for (int i = 0; i < vecHeader.size(); i++)
	{
		char szBuf[500];
		memset(szBuf, 0, 500);
		sprintf(szBuf, "%d. %s \n", i, vecHeader[i].c_str());
		fwrite(szBuf, strlen(szBuf), 1, fpIn);
	}

	fwrite("\n\n\n", 2, 1, fpIn);

	// ����
	for (int i = 0; i < vecClass.size(); i++)
	{
		char szBuf[500];
		memset(szBuf, 0, 500);
		sprintf(szBuf, "%d. %s \n", i, vecClass[i].c_str());
		fwrite(szBuf, strlen(szBuf), 1, fpIn);
	}
	fwrite("\n\n\n", 2, 1, fpIn);
	// ����
	for (int i = 0; i < vecFunc.size(); i++)
	{
		char szBuf[500];
		memset(szBuf, 0, 500);
		sprintf(szBuf, "%d. %s %s \n", i, vecFunc[i].funcName.c_str(), vecFunc[i].paramList.c_str());
		fwrite(szBuf, strlen(szBuf), 1, fpIn);
		//printf("%d. %s\n", i, vecWords[i].c_str());
	}
	fclose(fpIn);
	// �������
	printf("�������...\n");
	printf("�ʷ��������: d:\\words.txt  �﷨�������: d:\\grammar.txt, �������κμ�����...\n");
	getch();
	return 0;
}
#endif // 0
