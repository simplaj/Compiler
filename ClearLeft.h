#pragma once
#include<iostream>

#include<string>

#include<fstream>

using namespace std;

struct WF       //����һ������ʽ�ṹ��

{

	string left; //�������ʽ����

	string right; //�������ʽ���Ҳ�

};

void Removing(WF* p, char* q, int n, int count)

{

	int count1 = n;

	int flag = 0;

	for (int i = 0; i < n; i++)//�жϵ�һ�����ս���Ƿ����ֱ����ݹ� if(p[i].left[0]==q[0])

		if (p[i].left[0] == p[i].right[0])

			flag++;

	if (flag != 0)//�������ֱ����ݹ�������ֱ����ݹ�

	{

		for (int i = 0; i < n; i++)

			if (p[i].left[0] == q[0])

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

		p[count1].right = "��";

	}

	for (int i = 0; i <= count; i++)//��ÿһ�����ս��    ����

	{

		for (int j = 0; j < i; j++)//��ÿһ��С��i�ķ��ս��

		{

			for (int g = 0; g < n; g++) //��ÿһ������ʽ

				if (q[i] == p[g].left[0])   //i���ս�����g����ʽ��ߵ�һ����ĸ���

					if (p[g].right[0] == q[j])  //g����ʽ�ұ߲���ʽ��һ���������j�����ս�����

					{

						for (int h = 0; h < n * n; h++)

							if (p[h].left[0] == q[j] && int(p[h].left.length()) == 1)

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

			if (p[j].left[0] == q[i])

				if (p[j].left[0] == p[j].right[0])

					flag++;

		if (flag != 0)

		{

			for (int j = 0; j <= n * n; j++)

				if (p[j].left[0] == q[i])

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

			p[++count1].left = q[i] + str;

			p[count1].right = "��";

		}

	}

}

int Delete(WF* p, int n)

{

	return 0;

}

int Clear_Left()
{

	ofstream OutFile("jieguo.txt");
	int i=0, j, flag = 0, count = 1;
	ifstream fin("LL1in1.txt");
	string strVec[50];
	string s;
	while (!fin.eof())
	{
		string inbuf;
		getline(fin, inbuf, '\n');
		strVec[i] = inbuf;
		i = i + 1;
	}
	fin.close();
	int T = i - 1;
	int n = T;
	WF* p = new WF[50];
	for (int index = 0; index < T; index++) 
	{  // ����ÿһ������ʽ
		s = strVec[index];
		string temp = "";  // �洢ȥ���ո�Ĳ���ʽ
		for (int i = 0; i < s.length(); i++) {  // ȥ������ʽ�е�' '
			if (s[i] != ' ')
				temp += s[i];
		}
		p[index].left = temp[0];  // ����ʽ����
		for (int i = 3; i < temp.length(); i++) // ����ʽ���Ҳ�
			p[index].right += temp[i];
	}

	//cout<<"*********************"<<endl;

	char q[20];         //�Բ���ʽ�ķ��ս�����򲢴�ȡ���ַ�����q

	q[0] = p[0].left[0];        //�Ѳ���ʽ�ĵ�һ�����ս������q��
	for (i = 1; i < n; i++)         //�Է��ս�����򲢴�ȡ

	{

		flag = 0;

		for (j = 0; j < i; j++)

			if (p[i].left == p[j].left)            //����j<iѭ�������ظ����ս������ɱ�־λ�ж�

				flag++;          //˵�����ظ���

		if (flag == 0)

			q[count++] = p[i].left[0];//û���ظ�����q������

	}

	count--;

	Removing(p, q, n, count);//���������ݹ��Ӻ���

	Delete(p, n);//ɾ�����ò���ʽ

	//OutFile << "�����ݹ����ķ�����ʽΪ��" << endl;

	//cout<<"�����ݹ����ķ�����ʽΪ��"<<endl;

	for (i = 0; i <= count; i++)

	{

		for (int j = 0; j <= n * n; j++)

			if ((p[j].left[0] == q[i]) && int(p[j].left.length()) == 1)

				OutFile << p[j].left << "->" << p[j].right << endl;

		//  cout<<p[j].left<<"-->"<<p[j].right<<endl;

			else continue;

		for (j = 0; j <= n * n; j++)

			if ((p[j].left[0] == q[i]) && int(p[j].left.length()) == 2)

				OutFile << p[j].left << "->" << p[j].right << endl;

		// cout<<p[j].left<<"-->"<<p[j].right<<endl;

			else continue;

	}

	return 0;

}