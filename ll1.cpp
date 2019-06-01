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
#include"LL1.h"
#include<fstream>
//using namespace LL1;

LL1::LL1() {
	memset(tableMap, -1, sizeof(tableMap));
}

void LL1::getTable() {
	for (int index = 0; index < T; index++) {                          // ����ÿ������ʽ(���index):A->��
		int row = getNIndex(p[index].left);
		int emptyCount = 0;
		for (int i = 0; i < p[index].right.size(); i++) { // 1) ��FIRST(��)�е�ÿ���ս����a,��index����(A, a)��
			char tmp = p[index].right[i];
			if (!isNonterminal(tmp)) { // tmp���ս��          
				if (tmp != '$')
					tableMap[row][getIndex(tmp)] = index;
				if (tmp == '$') {
					emptyCount++;
				}
				break;
			}
			else {  // tmp�Ƿ��ս��
				set<char>::iterator it;
				int tmpIndex = getNIndex(tmp);
				// ��FIRST(tmp)�е�ÿ���ս����a,��i����(A, a)��
				for (it = firstSet[tmpIndex].begin(); it != firstSet[tmpIndex].end(); it++) {
					tableMap[row][getIndex(*it)] = index;
				}
				if (firstSet[tmpIndex].count('$') != 0) {      // 2) �����$��FIRST(tmp)��,���������е���һ������
					emptyCount++;
				}
				else {
					break;
				}
			}
		}

		// 2) �����$��FIRST(��)��,��FOLLOW(A)�е�ÿ���ս���������b,��i����(A,b)��
		if (emptyCount == p[index].right.size()) {
			set<char>::iterator  it;
			for (it = followSet[row].begin(); it != followSet[row].end(); it++) {
				tableMap[row][getIndex(*it)] = index;
			}
		}
	}
}

void LL1::analyExpression(string s) {
	for (int i = 0; i < s.size(); i++)
		leftExpr.push_back(s[i]);
	leftExpr.push_back('#');

	analyStack.push_back('#');
	analyStack.push_back(nonterminal[0]);  // ���뿪ʼ����

	while (analyStack.size() > 0) {
		//cout<<"����ջ��";
		string outs = "";
		for (int i = 0; i < analyStack.size(); i++)
			outs += analyStack[i];
		cout << setw(15) << outs;

		//cout<<"ʣ�����봮��";
		outs = "";
		for (int i = 0; i < leftExpr.size(); i++)
			outs += leftExpr[i];
		cout << setw(15) << outs;

		// ƥ��
		char char1 = analyStack.back();
		char char2 = leftExpr.front();
		if (char1 == char2 && char1 == '#') {
			cout << setw(15) << "Accepted!" << endl;
			return;
		}
		if (char1 == char2) {
			analyStack.pop_back();
			leftExpr.erase(leftExpr.begin());
			cout << setw(15) << "ƥ�䣺" << char1 << endl;
		}
		else if (tableMap[getNIndex(char1)][getIndex(char2)] != -1) {  // Ԥ��������Ƶ���ɽ����Ƶ�
			int tg = tableMap[getNIndex(char1)][getIndex(char2)];
			analyStack.pop_back();

			if (p[tg].right != "$") {
				for (int i = p[tg].right.length() - 1; i >= 0; i--) // ����
					analyStack.push_back(p[tg].right[i]);
			}

			cout << setw(15) << "�Ƶ���" << p[tg].left << "->" << p[tg].right << endl;
		}
		else {  // ����
			cout << setw(15) << "error!" << endl;
			return;
		}
	}
}

void LL1::printPredictTable() {
	// ��ͷ
	for (int i = 0; i < terminalNoEmpty.size(); i++) {
		cout << setw(10) << terminalNoEmpty[i];
	}
	cout << endl;
	for (int i = 0; i < nonterminal.size(); i++) {
		cout << nonterminal[i] << ": ";
		for (int j = 0; j < terminalNoEmpty.size(); j++) {
			if (tableMap[i][j] == -1)
				cout << setw(10) << "   ";
			else
				cout << setw(10) << p[tableMap[i][j]].right;
		}
		cout << endl;
	}
	cout << endl;
}

void LL1::getResult() {
	inputAndSolve();
	displayFirstAndFollow();
	getTable();
	printPredictTable();
	//ջƥ��
	string ss;
	//cout << "��������Ŵ���" << endl;
	char sin[50];
	ifstream fin("�ʷ�������.txt");
	fin.getline(sin,50);
	ss = sin;
	cout << setw(15) << "����ջ" << setw(15) << "ʣ�����봮" << setw(15) << "�Ƶ�ʽ" << endl;
	analyExpression(ss);

}
