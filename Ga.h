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
 *           ��Ի��bug���ģ�����̱����
 */

#include<stdio.h>
#include<string>
#include <iostream>
#include<fstream>

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
	//cout << "�������������ʽ��" << endl;
	ifstream GAin("GAin.txt");
	GAin.getline(str, 50, '\0');
	len = strlen(str);
	str[len] = '#';
	str[len + 1] = '\0';
	cout << str << endl;
	E();
	cout << "��ȷ��䣡" << endl;
	strcpy(str, "");
	index = 0;

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
			cout << "F1����ʧ��!" << endl;
			exit(0);
		}
	}
	else 
	{
		cout << "F2����ʧ��!" << endl;
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
		cout << "Aerror" << endl;
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
		cout << "Merror" << endl;
}
