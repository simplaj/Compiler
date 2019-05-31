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

#include<string>

#include<fstream>
#include<vector>
 //using namespace Base;

using namespace std;

struct pre_pro
{
	string left;
	string right;

};
struct pre_pro p[100];

vector <char> terminal, nonterminal;

bool isNonterminal(char c) { // 判断c是否为非终结符
	if (c >= 'A' && c <= 'Z')
		return true;
	return false;
}


int Delete(pre_pro* p, int n)

{

	return 0;

}

void Clear_Left()

{
	int i = 0, j, flag = 0, count = 1, n; 
	string s;
	//cout << "输入的产生式的个数：" << endl;
	//cin >> T;
	//cout << "输入的产生式：" << endl;
	ifstream fin("LL1in1.txt");
	string strVec[50];
	while (!fin.eof())
	{
		string inbuf;
		getline(fin, inbuf, '\n');
		strVec[i] = inbuf;
		i = i + 1;
	}
	fin.close();
	int T = i - 1;
	for (int index = 0; index < T; index++) {  // 处理每一个产生式
		s = strVec[index];
		string temp = "";  // 存储去掉空格的产生式
		for (int i = 0; i < s.length(); i++) {  // 去掉产生式中的' '
			if (s[i] != ' ')
				temp += s[i];
		}
		p[index].left = temp[0];  // 产生式的左部
		for (int i = 3; i < temp.length(); i++) // 产生式的右部
			p[index].right += temp[i];

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
	n = T;
	count = nonterminal.size()-1;
	int count1 = n;
	flag = 0;

	for (int i = 0; i < n; i++)//判断第一个非终结符是否存在直接左递归 if(p[i].left[0]==nonterminal[0])

		if (p[i].left[0] == p[i].right[0])

			flag++;

	if (flag != 0)//如果存在直接左递归则消除直接左递归

	{

		for (int i = 0; i < n; i++)

			if (p[i].left[0] == nonterminal[0])

				if (p[i].left[0] == p[i].right[0])

				{
					string str;

					str = p[i].right.substr(1, int(p[i].right.length()));//取右部第二位开始的字串赋给str

					string temp = p[i].left; //有形如E->E+T之后变为E'->+TE'

					string temp1 = "'";

					p[i].left = temp + temp1;

					p[i].right = str + p[i].left;

				}

				else

				{

					string temp = p[i].left; //有形如E->T之后变为E->TE'

					string temp1 = "'";

					temp = temp + temp1;

					p[i].right = p[i].right + temp;

				}

		string str = "'";

		p[count1].left = p[0].left[0] + str;

		p[count1].right = "$";

	}

	for (int i = 0; i <= count; i++)//对每一个非终结符    迭代

	{

		for (int j = 0; j < i; j++)//对每一个小于i的非终结符

		{

			for (int g = 0; g < n; g++) //对每一个产生式

				if (nonterminal[i] == p[g].left[0])   //i非终结符与第g产生式左边第一个字母相等

					if (p[g].right[0] == nonterminal[j])  //g产生式右边产生式第一个符号与第j个非终结符相等

					{

						for (int h = 0; h < n * n; h++)

							if (p[h].left[0] == nonterminal[j] && int(p[h].left.length()) == 1)

							{

								string str;

								str = p[g].right.substr(1, int(p[g].right.length()));

								p[++count1].left = p[g].left;

								p[count1].right = p[h].right + str;

							}

						p[g].left = "";

						p[g].right = "";

					}

		}

	}

	for (int i = 0; i <= count; i++) // 去除间接递归产生式

	{

		flag = 0;

		for (int j = 0; j < n * n; j++)

			if (p[j].left[0] == nonterminal[i])

				if (p[j].left[0] == p[j].right[0])

					flag++;

		if (flag != 0)

		{

			for (int j = 0; j <= n * n; j++)

				if (p[j].left[0] == nonterminal[i])

					if (p[j].left[0] == p[j].right[0])

					{

						string str;

						str = p[j].right.substr(1, int(p[j].right.length()));

						string temp = p[j].left;

						string temp1 = "'";

						p[j].left = temp + temp1;

						p[j].right = str + p[j].left;

					}

					else

					{

						string temp = p[j].left;

						string temp1 = "'";

						temp = temp + temp1;

						p[j].right = p[j].right + temp;

					}

			string str = "'";

			p[++count1].left = nonterminal[i] + str;

			p[count1].right = "$";

		}

	}

	ofstream OutFile("jieguo.txt");
	//cout << endl;

	//OutFile << "即输入的文法产生式为：" << endl;

	//cout<<"即输入的文法产生式为："<<endl;

	//for (i = 0; i < n; i++)

	//	// cout<<p[i].left<<"->"<<p[i].right<<endl;

	//	OutFile << p[i].left << "->" << p[i].right << endl;

	//OutFile << "*********************" << endl;

	//cout<<"*********************"<<endl;

	//Removing(p, nonterminal, T, nonterminal.size());//调用消除递归子函数

	Delete(p, T);//删除无用产生式

	//OutFile << "消除递归后的文法产生式为：" << endl;

	//cout<<"消除递归后的文法产生式为："<<endl;

	for (int i = 0; i <= count; i++)

	{

		for (int j = 0; j <= n * n; j++)

			if ((p[j].left[0] == nonterminal[i]) && int(p[j].left.length()) == 1)

			{
				OutFile << p[j].left << "->" << p[j].right << endl;

				cout << p[j].left << "->" << p[j].right << endl;
			}

			else continue;

		for (j = 0; j <= n * n; j++)

		
			if ((p[j].left[0] == nonterminal[i]) && int(p[j].left.length()) == 2)

			{
				OutFile << p[j].left << "->" << p[j].right << endl;

				cout << p[j].left << "->" << p[j].right << endl;
			}
		
			else 
				continue;
		
	}
}
