#pragma once
/*
 * _ooOoo_
 * o8888888o
 * 88" . "88
 * (| -_- |)
 *  O\ = /O
 * ___/`---'\____
 * .   ' \\| |// `.
 * / \\||| : |||// \
 * / _||||| -:- |||||- \
 * | | \\\ - /// | |
 * | \_| ''\---/'' | |
 * \ .-\__ `-` ___/-. /
 * ___`. .' /--.--\ `. . __
 * ."" '< `.___\_<|>_/___.' >'"".
 * | | : `- \`.;`\ _ /`;.`/ - ` : | |
 * \ \ `-. \_ __\ /__ _/ .-` / /
 * ======`-.____`-.___\_____/___.-`____.-'======
 * `=---='
 *          .............................................
 *           佛曰：bug泛滥，我已瘫痪！
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<istream>
#include<fstream>
#pragma warning(disable:4996)

using namespace std;

//保留字表
static  char rsvWord[32][20] = {
	"auto", "break", "case", "char", "const", "continue",
	"default", "do", "double", "else", "enum", "extern",
	"float", "for", "goto", "if", "int", "long",
	"register", "return", "short", "signed", "sizeof", "static",
	"struct", "switch", "typedef", "union", "unsigned", "void",
	"volatile", "while"
};

//界符 运算符
static  char op_del[36][10] = {
	"+", "-", "*", "/", "<", "<=", ">", ">=", "=", "==",
	"!=", ";", "(", ")", "^", ",", "\"", "\'", "#", "&",
	"&&", "|", "||", "%", "~", "<<", ">>", "[", "]", "{",
	"}", "\\", ".", "\?", ":", "!"
};

//标识符
static char Idtbl[1000][50] = { "" };

int searchRsv(char rsvWord[][20], char s[])
{
	for (int i = 0; i < 32; i++)
	{
		if (strcmp(rsvWord[i], s) == 0)
		{
			return i + 1;
			//cout << "<" << s << "," << i + 1 << ">" << endl;
		}

	}
	return -1;
};

bool isLetter(char letter)
{
	if (letter >= 'a' && letter <= 'z' || letter >= 'A' && letter <= 'Z' || letter == '_')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isDigit(char digit)
{
	if (digit >= '0' && digit <= '9')
	{
		return true;
	}
	else
	{
		return false;
	}
}

void scan(int& syn, char repo[], char* read, int& p)
{

	int l, i, count = 0;
	char ch;
	char temp[10000];
	l = strlen(repo);
	for (int i = 0; i <= l; )
	{
		if (repo[i] == '/' && repo[i + 1] == '/')
		{
			while (repo[i] != '\n')
			{
				i++;
			}
		}
		if (repo[i] == '/' && repo[i + 1] == '*')
		{
			i += 2;
			while (repo[i] != '*' || repo[i + 1] != '/')
			{
				i++;
				if (repo[i] == '$')
				{
					printf("error\n");
					exit(0);
				}
			}
			i += 2;
		}
		if (repo[i] != '\n' && repo[i] != '\t' && repo[i] != '\v' && repo[i] != '\r')
		{
			temp[count++] = repo[i];
			i++;
		}
		else i++;

	}
	temp[count++] = '\0';
	strcpy(repo, temp);

	//cout << repo << endl;
	//cout << p;
	i = 0;
	count = 0;
	ch = repo[p];
	//cout << "ch :"<<ch<<endl;
	while (ch == ' ')
	{
		p++;
		//cout << "kongge" << endl;
		ch = repo[p];
	}

	for (i = 0; i < 50; i++)
	{
		read[i] = '\0';
	}
	//cout << repo[p];
	if (isLetter(repo[p]))
	{
		read[count++] = repo[p];
		p++;
		while (isLetter(repo[p]) || isDigit(repo[p]))
		{
			read[count++] = repo[p];
			p++;
		}
		read[count] = '\0';
		syn = searchRsv(rsvWord, read);
		if (syn == -1)
		{
			syn = 100;
			//cout << "<" << read << "," << syn << ">" << endl;
		}
		return;
	}
	else if (isDigit(repo[p]))
	{
		while (isDigit(repo[p]))
		{
			read[count++] = repo[p];
			p++;
		}
		read[count] = '\0';
		syn = 99;
		//cout << "<" << read << "," << syn << ">" << endl;
	}
	else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ';' || ch == '(' || ch == ')' || ch == '^'
		|| ch == ',' || ch == '\"' || ch == '\'' || ch == '~' || ch == '#' || ch == '%' || ch == '['
		|| ch == ']' || ch == '{' || ch == '}' || ch == '\\' || ch == '.' || ch == '\?' || ch == ':')
	{
		read[0] = repo[p];
		read[1] = '\0';
		for (i = 0; i < 36; i++)
		{
			if (strcmp(read, op_del[i]) == 0)
			{
				syn = 33 + i;
				break;
			}
		}
		p++;
		return;
	}
	else  if (repo[p] == '<')
	{//<,<=,<<
		p++;
		read[0] = '<';
		if (repo[p] == '=')
		{
			syn = 38;
			read[1] = '=';
		}
		else if (repo[p] == '<')
		{
			//p--;
			syn = 58;
			read[1] = '<';
		}
		else
		{
			p--;
			syn = 37;
		}
		p++;
		return;
	}
	else  if (repo[p] == '>')
	{//>,>=,>>
		p++;
		read[0] = '>';
		if (repo[p] == '=')
		{
			syn = 40;
			read[1] = '=';
		}
		else if (repo[p] == '>')
		{
			syn = 59;
			read[1] = '>';
		}
		else
		{
			p--;
			syn = 39;
		}
		p++;
		return;
	}
	else  if (repo[p] == '=')
	{//=.==
		p++;
		read[0] = '=';
		if (repo[p] == '=')
		{
			syn = 42;
			read[1] = '=';
		}
		else
		{
			p--;
			syn = 41;
		}
		p++;
		return;
	}
	else  if (repo[p] == '!')
	{//!,!=
		p++;
		read[0] = '!';
		if (repo[p] == '=')
		{
			syn = 43;
			read[1] = '=';
		}
		else
		{
			syn = 68;
			p--;
		}
		p++;
		return;
	}
	else  if (repo[p] == '&')
	{//&,&&
		p++;
		read[0] = '&';
		if (repo[p] == '&')
		{
			syn = 53;
			read[1] = '&';
		}
		else
		{
			p--;
			syn = 52;
		}
		p++;
		return;
	}
	else  if (repo[p] == '|')
	{//|,||
		p++;
		read[0] = '|';
		if (repo[p] == '|')
		{
			syn = 55;
			read[1] = '|';
		}
		else
		{
			p--;
			syn = 54;
		}
		p++;
		return;
	}
	else  if (repo[p] == '$')
	{//结束符
		syn = 0;
	}
	else
	{//出错
		cout << "error：there is no exist " << ch << endl;
		exit(0);
	}
}

void lex_ana(string filename)
{
	int syn = 1;
	int p = 0;
	int l = 0;
	char repo[9999], read[50];
	ifstream fin(filename);
	fin.getline(repo, 9999, '￥');
	l = strlen(repo);
	fin.close();
	ofstream fout("out.txt");
	ofstream GAout("GAin.txt");
	cout << "正在词法分析...";
	while (syn != 0)
	{
		scan(syn, &repo[0], &read[0], p);
		if (syn != 0)
		{
			cout << "...";
			fout << "<" << read << "," << syn << ">" << endl;
			if (syn != 99 && syn != 100)
			{
				GAout << read ;
			}
			else
				GAout << "i" ;
		}
	}
	fout.close();
	GAout.close();
	cout << endl;
	cout << "分析完成！" << endl;

}