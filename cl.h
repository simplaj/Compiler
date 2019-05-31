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

bool isNonterminal(char c) { // �ж�c�Ƿ�Ϊ���ս��
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
	//cout << "����Ĳ���ʽ�ĸ�����" << endl;
	//cin >> T;
	//cout << "����Ĳ���ʽ��" << endl;
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
	for (int index = 0; index < T; index++) {  // ����ÿһ������ʽ
		s = strVec[index];
		string temp = "";  // �洢ȥ���ո�Ĳ���ʽ
		for (int i = 0; i < s.length(); i++) {  // ȥ������ʽ�е�' '
			if (s[i] != ' ')
				temp += s[i];
		}
		p[index].left = temp[0];  // ����ʽ����
		for (int i = 3; i < temp.length(); i++) // ����ʽ���Ҳ�
			p[index].right += temp[i];

		for (int i = 0; i < temp.length(); i++) {  // �洢�����ս���ͷ��ս��
			if (i == 1 || i == 2) continue;  // ������������->
			if (isNonterminal(temp[i])) {  //����һ�����ս��
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
			else {                       //����һ���ս��
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

	for (int i = 0; i < n; i++)//�жϵ�һ�����ս���Ƿ����ֱ����ݹ� if(p[i].left[0]==nonterminal[0])

		if (p[i].left[0] == p[i].right[0])

			flag++;

	if (flag != 0)//�������ֱ����ݹ�������ֱ����ݹ�

	{

		for (int i = 0; i < n; i++)

			if (p[i].left[0] == nonterminal[0])

				if (p[i].left[0] == p[i].right[0])

				{
					string str;

					str = p[i].right.substr(1, int(p[i].right.length()));//ȡ�Ҳ��ڶ�λ��ʼ���ִ�����str

					string temp = p[i].left; //������E->E+T֮���ΪE'->+TE'

					string temp1 = "'";

					p[i].left = temp + temp1;

					p[i].right = str + p[i].left;

				}

				else

				{

					string temp = p[i].left; //������E->T֮���ΪE->TE'

					string temp1 = "'";

					temp = temp + temp1;

					p[i].right = p[i].right + temp;

				}

		string str = "'";

		p[count1].left = p[0].left[0] + str;

		p[count1].right = "$";

	}

	for (int i = 0; i <= count; i++)//��ÿһ�����ս��    ����

	{

		for (int j = 0; j < i; j++)//��ÿһ��С��i�ķ��ս��

		{

			for (int g = 0; g < n; g++) //��ÿһ������ʽ

				if (nonterminal[i] == p[g].left[0])   //i���ս�����g����ʽ��ߵ�һ����ĸ���

					if (p[g].right[0] == nonterminal[j])  //g����ʽ�ұ߲���ʽ��һ���������j�����ս�����

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

	for (int i = 0; i <= count; i++) // ȥ����ӵݹ����ʽ

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

	//OutFile << "��������ķ�����ʽΪ��" << endl;

	//cout<<"��������ķ�����ʽΪ��"<<endl;

	//for (i = 0; i < n; i++)

	//	// cout<<p[i].left<<"->"<<p[i].right<<endl;

	//	OutFile << p[i].left << "->" << p[i].right << endl;

	//OutFile << "*********************" << endl;

	//cout<<"*********************"<<endl;

	//Removing(p, nonterminal, T, nonterminal.size());//���������ݹ��Ӻ���

	Delete(p, T);//ɾ�����ò���ʽ

	//OutFile << "�����ݹ����ķ�����ʽΪ��" << endl;

	//cout<<"�����ݹ����ķ�����ʽΪ��"<<endl;

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
