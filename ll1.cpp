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
#include"LL1.h"
#include<fstream>
//using namespace LL1;

LL1::LL1() {
	memset(tableMap, -1, sizeof(tableMap));
}

void LL1::getTable() {
	for (int index = 0; index < T; index++) {                          // 对于每个产生式(编号index):A->α
		int row = getNIndex(p[index].left);
		int emptyCount = 0;
		for (int i = 0; i < p[index].right.size(); i++) { // 1) 对FIRST(α)中的每个终结符号a,将index加入(A, a)中
			char tmp = p[index].right[i];
			if (!isNonterminal(tmp)) { // tmp是终结符          
				if (tmp != '$')
					tableMap[row][getIndex(tmp)] = index;
				if (tmp == '$') {
					emptyCount++;
				}
				break;
			}
			else {  // tmp是非终结符
				set<char>::iterator it;
				int tmpIndex = getNIndex(tmp);
				// 对FIRST(tmp)中的每个终结符号a,将i加入(A, a)中
				for (it = firstSet[tmpIndex].begin(); it != firstSet[tmpIndex].end(); it++) {
					tableMap[row][getIndex(*it)] = index;
				}
				if (firstSet[tmpIndex].count('$') != 0) {      // 2) 如果空$在FIRST(tmp)中,继续看α中的下一个符号
					emptyCount++;
				}
				else {
					break;
				}
			}
		}

		// 2) 如果空$在FIRST(α)中,对FOLLOW(A)中的每个终结符或结束符b,将i加入(A,b)中
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
	analyStack.push_back(nonterminal[0]);  // 加入开始符号

	while (analyStack.size() > 0) {
		//cout<<"分析栈：";
		string outs = "";
		for (int i = 0; i < analyStack.size(); i++)
			outs += analyStack[i];
		cout << setw(15) << outs;

		//cout<<"剩余输入串：";
		outs = "";
		for (int i = 0; i < leftExpr.size(); i++)
			outs += leftExpr[i];
		cout << setw(15) << outs;

		// 匹配
		char char1 = analyStack.back();
		char char2 = leftExpr.front();
		if (char1 == char2 && char1 == '#') {
			cout << setw(15) << "Accepted!" << endl;
			return;
		}
		if (char1 == char2) {
			analyStack.pop_back();
			leftExpr.erase(leftExpr.begin());
			cout << setw(15) << "匹配：" << char1 << endl;
		}
		else if (tableMap[getNIndex(char1)][getIndex(char2)] != -1) {  // 预测表中有推倒项，可进行推导
			int tg = tableMap[getNIndex(char1)][getIndex(char2)];
			analyStack.pop_back();

			if (p[tg].right != "$") {
				for (int i = p[tg].right.length() - 1; i >= 0; i--) // 反向
					analyStack.push_back(p[tg].right[i]);
			}

			cout << setw(15) << "推导：" << p[tg].left << "->" << p[tg].right << endl;
		}
		else {  // 错误
			cout << setw(15) << "error!" << endl;
			return;
		}
	}
}

void LL1::printPredictTable() {
	// 表头
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
	//栈匹配
	string ss;
	//cout << "请输入符号串：" << endl;
	char sin[50];
	ifstream fin("词法分析后.txt");
	fin.getline(sin,50);
	ss = sin;
	cout << setw(15) << "分析栈" << setw(15) << "剩余输入串" << setw(15) << "推导式" << endl;
	analyExpression(ss);

}
