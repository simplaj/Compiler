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
#include<string>
#include <iostream>

using namespace std;

char str[50];
int index = 0;
void E();			//E->TE_P;
void E_P();			//E_P->ATE_P | e
void T();			//T->FT_P
void T_P();			//T_P->MFT_P | e
void F();			//F->(E) | i
void A();			//A->+|-
void M();			//M->*|/
void Gram_Anal()
{
	int len;
	int m;
	cout << "请输入要测试的次数：";
	cin >> m;
	while (m--)
	{
		cout << "请输入算数表达式：" << endl;
		len = strlen(str);
		str[len] = '#';
		str[len + 1] = '\0';
		E();
		cout << "正确语句！" << endl;
		strcpy(str, "");
		index = 0;
	}
}

void E()
{
	T();
	E_P();
}
void E_P()
{
	A();
	T();
	E_P();
}
void T()
{
	F();
	T_P();
}
void T_P()
{
	M();
	F();
	T_P();
}
void F()
{
	if (str[index] == '99' || str[index] == '100')
	{
		index++;
	}
	else if (str[index] == '(')
	{
		index++;
		E();
		if (str[index] == ')')
		{
			index++;
		}
		else {
			cout << "分析失败!" << endl;
			exit(0);
		}
	}
	else {
		cout << "分析失败!" << endl;
		exit(0);
	}
}
void A()
{
	if (str[index] == '+')
	{
		index++;
	}
	else if (str[index] == '-')
	{
		index++;
	}
	else
		cout << "error" << endl;
}

void M()
{
	if (str[index] == '*')
	{
		index++;
	}
	else if (str[index] == '/')
	{
		index++;
	}
	else
		cout << "error" << endl;
}
