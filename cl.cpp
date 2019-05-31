#include<iostream>

#include<string>

#include<fstream>

using namespace std;

struct WF       //定义一个产生式结构体

{

string left; //定义产生式的左部

string right; //定义产生式的右部

};

void Removing(WF * p, char * q, int n, int count)

{

	int count1 = n;

	int flag = 0;

	for (int i = 0; i  < n; i++)//判断第一个非终结符是否存在直接左递归 if(p[i].left[0]==q[0])

		if (p[i].left[0] == p[i].right[0])

			flag++;

	if (flag != 0)//如果存在直接左递归则消除直接左递归

	{

		for (int i = 0; i  < n; i++)

			if (p[i].left[0] == q[0])

				if (p[i].left[0] == p[i].right[0])

				{
					string str;

					str = p[i].right.substr(1, int (p[i].right.length()));//取右部第二位开始的字串赋给str

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

		p[count1].right = "ε";

	}

	for (int i = 0; i  <= count; i++)//对每一个非终结符    迭代

	{

		for (int j = 0; j  < i; j++)//对每一个小于i的非终结符

		{

			for (int g = 0; g  < n; g++) //对每一个产生式

				if (q[i] == p[g].left[0])   //i非终结符与第g产生式左边第一个字母相等

					if (p[g].right[0] == q[j])  //g产生式右边产生式第一个符号与第j个非终结符相等

					{

						for (int h = 0; h  < n * n; h++)

							if (p[h].left[0] == q[j] && int (p[h].left.length()) == 1)

							{

								string str;

								str = p[g].right.substr(1, int (p[g].right.length()));

								p[++count1].left = p[g].left;

								p[count1].right = p[h].right + str;

							}

						p[g].left = "";

						p[g].right = "";

					}

		}

	}

	for (int  i = 0; i  <= count; i++) // 去除间接递归产生式

	{

		flag = 0;

		for (int j = 0; j  < n * n; j++)

			if (p[j].left[0] == q[i])

				if (p[j].left[0] == p[j].right[0])

					flag++;

		if (flag != 0)

		{

			for (int j = 0; j  <= n * n; j++)

				if (p[j].left[0] == q[i])

					if (p[j].left[0] == p[j].right[0])

					{

						string str;

						str = p[j].right.substr(1, int (p[j].right.length()));

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

			p[++count1].left = q[i] + str;

			p[count1].right = "ε";

		}

	}

}

int Delete(WF * p, int n)

{

	return 0;

}

int main1()
{

	ofstream OutFile("jieguo.txt");

	int i, j, flag = 0, count = 1, n;

	cout << "请输入文法产生式个数n：" << endl;

	cin >> n;

	WF * p = new WF[50];

	cout << "请输入文法的个产生式：" << endl;

	for (i = 0; i < n; i++)//输入产生式

	{

		cin >> p[i].left;

		cout << "->" << endl;

		cin >> p[i].right;

		cout << endl;

	}

	cout << endl;

	OutFile << "即输入的文法产生式为：" << endl;

	//cout<<"即输入的文法产生式为："<<endl;

	for (i = 0; i  < n; i++)

		// cout<<p[i].left<<"-->"<<p[i].right<<endl;

		OutFile << p[i].left << "-->" << p[i].right << endl;

	OutFile << "*********************" << endl;

	//cout<<"*********************"<<endl;

	char q[20];         //对产生式的非终结符排序并存取在字符数组q

	q[0] = p[0].left[0];        //把产生式的第一个非终结符存入q中

	for (i = 1; i < n; i++)         //对非终结符排序并存取

	{

		flag = 0;

		for (j = 0; j < i; j++)

			if (p[i].left == p[j].left)            //根据j<i循环避免重复非终结符因此由标志位判断

				flag++;          //说明有重复的

		if (flag == 0)

			q[count++] = p[i].left[0];//没有重复加入q数组中

	}

	count--;

	Removing(p, q, n, count);//调用消除递归子函数

	Delete(p, n);//删除无用产生式

	OutFile << "消除递归后的文法产生式为：" << endl;

	//cout<<"消除递归后的文法产生式为："<<endl;

	for (i = 0; i  <= count; i++)

	{

		for (int j = 0; j  <= n * n; j++)

			if ((p[j].left[0] == q[i]) && int (p[j].left.length()) == 1)

				OutFile << p[j].left << "->" << p[j].right << endl;

		//  cout<<p[j].left<<"-->"<<p[j].right<<endl;

		else continue;

		for (j = 0; j  <= n * n; j++)
		
			if ((p[j].left[0] == q[i]) && int (p[j].left.length()) == 2)

				OutFile << p[j].left << "->" << p[j].right << endl;

		// cout<<p[j].left<<"-->"<<p[j].right<<endl;

		else continue;

	}

	return 0;

}