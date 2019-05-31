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
#include<fstream>
#include<stack>
#include <string>
#include<vector>
//using namespace Base;

using namespace std;

struct pre_pro
{
	string left;
	string right;
	int flag = 0;
	int flag2 = 0;

};
struct pre_pro production[100];

vector <char> terminal, nonterminal;

bool isNonterminal(char c) { // 判断c是否为非终结符
	if (c >= 'A' && c <= 'Z')
		return true;
	return false;
}

void ClearLeft()
{  // 处理和求出First和Follow集
	string s;
	//cout << "输入的产生式的个数：" << endl;
	//cin >> T;
	//cout << "输入的产生式：" << endl;
	ifstream fin("LL1in1.txt");
	string strVec[50];
	int i = 0;
	while (!fin.eof())
	{
		string inbuf;
		getline(fin, inbuf, '\n');
		strVec[i] = inbuf;
		i = i + 1;
	}
	fin.close();
	int T = i - 1;
	int cnt = T;
	for (int index = 0; index < T; index++) {  // 处理每一个产生式
		s = strVec[index];
		string temp = "";  // 存储去掉空格的产生式
		for (int i = 0; i < s.length(); i++) {  // 去掉产生式中的' '
			if (s[i] != ' ')
				temp += s[i];
		}
		production[index].left = temp[0];  // 产生式的左部
		for (int i = 3; i < temp.length(); i++) // 产生式的右部
			production[index].right += temp[i];

		for (int i = 0; i < temp.length(); i++) {  // 存储所有终结符和非终结符
			if (i == 1 || i == 2) continue;  // 跳过产生符号->
			if (isNonterminal(temp[i])) {  //插入一个非终结符
				int flag = 0;
				for (int j = 0; j < nonterminal.size(); j++) {
					if (nonterminal[j] == temp[i]) {
						flag = 1;
						break;
					}
				}
				if (!flag)
					nonterminal.push_back(temp[i]);
			}
			else {                       //插入一个终结符
				int flag = 0;
				for (int j = 0; j < terminal.size(); j++) {
					if (terminal[j] == temp[i]) {
						flag = 1;
						break;
					}
				}
				if (!flag)
					terminal.push_back(temp[i]);
			}
		}
	}

	for (int i = 0; i < nonterminal.size(); i++)
	{
		for (int j = 0; j < i; j++)
		{
			for (int k = 0; k < T; k++)
			{
				if (nonterminal[i] == production[k].left[0])
					if (nonterminal[j] == production[k].right[0])
					{
						for (int l = 0; l < T; l++)
						{
							if (nonterminal[j] == production[l].left[0] && int(production[l].left.length()) == 1)
							{
								string str;
								str.substr(1, production[k].left.size());
								production[k].left = production[l].left + str;
							}
						}
					}
			}
		}
		for (int j = 0; j < T; j++)
		{
			production[j].flag = 0;
			if (production[j].left[0] == production[j].right[0] && int(production[j].left.length()) == 1)
			{
				production[j].flag++;
			}
		}
		for (int j = 0; j < T; j++)
		{
			if (production[j].flag != 0)
			{
				if (production[i].left[0] == production[i].right[0])
				{
					string str;
					str = production[i].right.substr(1, production[i].right.size());
					production[i].left = production[i].left + "'";
					production[i].right = str + production[i].left;
					for (int k = 0; k < T; k++)
					{
						if (production[k].left == production[i].left && production[k].right != "$")
						{
							production[cnt].left == production[i].left;
							production[cnt++].right == "$";
						}
					}
				}
				else
				{
					production[i].right = production[i].right + production[i].left + "'";
				}
			}
		}
	}
	ofstream fout("LL1in2.txt");
	for(int i = 0;i<cnt;i++)
	{
		fout << production[i].left << "->" << production[i].right << endl;
	}
	fout.close();
}