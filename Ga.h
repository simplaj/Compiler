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
#include<fstream>

using namespace std;

char str[50];
int index = 0;
void E();			//E->TE_P;
void E_P();			//E_P->-TE_P | +TE_P|e
void T();			//T->FT_P
void T_P();			//T_P->*FT_P | /FT_P|e
void F();			//F->(E) | i
void Gram_Anal(string filename)
{
	int len;
	//cout << "请输入算数表达式：" << endl;
	ifstream GAin(filename);
	GAin.getline(str, 50, '\0');
	len = strlen(str);
	str[len] = '#';
	str[len + 1] = '\0';
	//cout << str << endl;
	cout << "正在递归向下语法分析...";
	E();
	cout << endl;
	cout << "正确语句！" << endl;
	strcpy(str, "");
	index = 0;

}

void E()
{
	cout << "...";
	T();
	E_P();
}
void E_P()
{
	cout << "...";

	if (str[index] == '+'|| str[index] == '-')
	{
		index++;
		T();
		E_P();
	}
	else
	{
		index++;
		//cout << "EPerror" << endl;
		//exit(0);
	}
}
void T()
{
	cout << "...";

	F();
	T_P();
}
void T_P()
{
	cout << "...";

	if (str[index] == '*'|| str[index] == '/')
	{
		index++;
		F();
		T_P();

	}
	else
	{
		index++;
		//cout << "TPerror" << endl;

	}
}
void F()
{
	cout << "...";

	if (str[index] == 'i' )
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
			cout << endl;
			cout << "Error!" << endl;

			exit(0);
		}
	}
	else 
	{
		cout << endl;
		cout << "Error!" << endl;

		exit(0);
	}
}
//void A()
//{
//	if (str[index] == '+')
//	{
//		index++;
//	}
//	else if (str[index] == '-')
//	{
//		index++;
//	}
//	else
//		cout << "error" << index << endl;
//
//}
//
//void M()
//{
//	if (str[index] == '*')
//	{
//		index++;
//	}
//	else if (str[index] == '/')
//	{
//		index++;
//	}
//	else
//		cout << "error" << index << endl;
//
//}
