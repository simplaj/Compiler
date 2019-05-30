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
#pragma once

#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<stack>
#include<string>
#include<fstream>
using namespace std;

//表格数组
char LL1[50][50][100] = { {"->TX","null" ,"null","null" ,"null","->TX", "null", "null" },
						 {"->FY","null" ,"null","null" ,"null", "->FY", "null", "null"},
						 {"null","->+TX" ,"->-TX" ,"null","null","null" , "->$","->$" },
						 {"->i","null" ,"null" ,"null"  ,"null","->(E)","null","null" },
						 {"null" ,"->$","->$","->*FY" ,"->/FY","null","->$","->$" } };
char r[200] = "ETXFY";
char c[200] = "i+-*/()$";
stack<char>cmp;

int findr(char a)
{
	for (int i = 0; i < 5; i++)//找到对应行
	{
		if (a == r[i])
		{
			return i;
		}
	}
	return -1;
}
int findc(char b)
{
	for (int i = 0; i < 8; i++)//找到对应列
	{
		if (b == c[i])
		{
			return i;
		}
	}
	return -1;
}
int error(int i, int cnt, int len, char p[], char str[])
{
	printf("%d\t%s\t", cnt, p);
	for (int q = i; q < len; q++)
	{
		cout << str[q];
	}
	printf("\t报错\n");
	return len;
}
void analyze(char str[], int len)
{
	int cnt = 1;//输出Step专用
	int i = 0;
	char p[200] = "$E";//输出stack专用
	int pindex = 2;
	printf("Step\tStack\tString\tRule\n");
	while (i < len)
	{
		int x, y;
		char ch = cmp.top();
		if (ch >= 'A' && ch <= 'Z')
		{
			cmp.pop();
			x = findr(ch);
			y = findc(str[i]);
			if (x != -1 && y != -1)
			{
				int len2 = strlen(LL1[x][y]);
				if (strcmp(LL1[x][y], "null") == 0)
				{
					i = error(i, cnt, len, p, str);
					cout << '1';
					continue;
				}
				printf("%d\t%s\t", cnt, p);
				if (p[pindex - 1] != '$')
				{
					p[pindex] = '\0';
					pindex--;
				}
				if (LL1[x][y][2] != '$')
				{
					for (int q = len2 - 1; q > 1; q--)
					{
						p[pindex++] = LL1[x][y][q];
						cmp.push(LL1[x][y][q]);
					}
				}
				else
				{
					p[pindex] = '\0';
					pindex--;
				}
				for (int q = i; q < len; q++)
				{
					cout << str[q];
				}
				printf("\t%c%s\n", ch, LL1[x][y]);
			}
			else
			{
				i = error(i, cnt, len, p, str);
				cout << '2' << x;
				continue;
				///未找到，报错
			}

		}
		else
		{
			
			if (ch == str[i])
			{
				cmp.pop();
				printf("%d\t%s\t", cnt, p);
				if (ch == '$' && str[i] == '$')
				{
					printf("$\t接受\n");
					return;
				}
				for (int q = i; q < len; q++)
				{
					cout << str[q];
				}
				printf("\t%c匹配\n", ch);
				pindex--;
				p[pindex] = '\0';
				i++;
			}
			else
			{
				i = error(i, cnt, len, p, str);
				cout << '3';
				continue;
				///报错
			}
		}
		cnt++;
	}
}
void LL_1(string filename)
{
	//cout<<r[0]<<r[4]<<endl;
	//cout<<L[0]<<L[5]<<endl;
	/*for(int i = 0; i < 5; i++)
	{
		for(int j = 0 ; j < 6; j++)
			printf("%5s",LL1[i][j]);
			cout<<endl;
	}*/
	char str[200];
	//cin >> str;
	ifstream fin(filename);
	fin.getline(str, 200, '\0');
	int len = strlen(str);
	cmp.push('$');
	cmp.push('E');
	analyze(str, len + 1);
	//return 0;
}