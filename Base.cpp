#include "Base.h"

bool Base::isNonterminal(char c) { // 判断c是否为非终结符
	if (c >= 'A' && c <= 'Z')
		return true;
	return false;
}
int Base::getNIndex(char target) {  // 获得target在非终结符集合中的下标
	for (int i = 0; i < nonterminal.size(); i++) {
		if (target == nonterminal[i])
			return i;
	}
	return -1;
}
int Base::getIndex(char target) {  // 获得target在终结符集合中的下标
	for (int i = 0; i < terminalNoEmpty.size(); i++) {
		if (target == terminalNoEmpty[i])
			return i;
	}
	return -1;
}

void Base::getFirst(char target) {  // 求FIRST(target）
	int countEmpty = 0;  // 用于最后判断是否有空
	int isEmpty = 0;
	int targetIndex = getNIndex(target);
	for (int i = 0; i < T; i++) {
		if (production[i].left == target) {  // 匹配产生式左部
			if (!isNonterminal(production[i].right[0])) {  // 对于终结符，直接加入first
				firstSet[targetIndex].insert(production[i].right[0]);
			}
			else {
				for (int j = 0; j < production[i].right.length(); j++) { // X->Y1..Yj..Yk是一个产生式
					char Yj = production[i].right[j];
					if (!isNonterminal(Yj)) {  // Yj是终结符(不能产生空),FIRST(Yj)=Yj加入FIRST(X),不能继续迭代,结束
						firstSet[targetIndex].insert(Yj);
						break;
					}
					getFirst(Yj);// Yj是非终结符，递归 先求出FIRST(Yj)

					set<char>::iterator it;
					int YjIndex = getNIndex(Yj);
					for (it = firstSet[YjIndex].begin(); it != firstSet[YjIndex].end(); it++) {
						if (*it == '$')  // 遍历查看FIRST(Yj)中是否含有'$'(能产生空)
							isEmpty = 1;
						else
							firstSet[targetIndex].insert(*it);//将FIRST(Yj)中的非$就加入FIRST(X)
					}
					if (isEmpty == 0)  // Yj不能产生空, 迭代结束
						break;
					else {   //  Yj能产生空
						countEmpty += isEmpty;
						isEmpty = 0;
					}
				}
				if (countEmpty == production[i].right.length())//所有右部first(Y)都有$(空),将$加入FIRST(X)中
					firstSet[getNIndex(target)].insert('$');
			}
		}
	}
}

void Base::getFollow(char target) {  // 求FOLLOW(target）
	int targetIndex = getNIndex(target);
	for (int i = 0; i < T; i++) {
		int index = -1;
		int len = production[i].right.length();
		for (int j = 0; j < len; j++) {  // 寻找target在产生式中的位置index
			if (production[i].right[j] == target) {
				index = j;
				break;
			}
		}
		if (index != -1 && index < len - 1) {  // 找到target在产生式中的位置index
											   // 存在A->αBβ, 将FIRST(β)中除了空$之外的所有放入FOLLOW(B)中
											   // 这里B对应target, β对应nxt
			char nxt = production[i].right[index + 1];
			if (!isNonterminal(nxt)) {  // β是终结符 FIRST(β)=β，直接插入β
				followSet[targetIndex].insert(nxt);
			}
			else {  // β是非终结符
				int hasEmpty = 0;
				set<char>::iterator it;
				int nxtIndex = getNIndex(nxt);  // 插入FIRST(β)中除了空$之外的所有
				for (it = firstSet[nxtIndex].begin(); it != firstSet[nxtIndex].end(); it++) {
					if (*it == '$')
						hasEmpty = 1;
					else
						followSet[targetIndex].insert(*it);
				}

				if (hasEmpty && production[i].left != target) { // 存在A->αBβ且FIRST(β)->$
															 // FOLLOW(A)放在FOLLOW(B)中
					getFollow(production[i].left);
					set<char>::iterator it;
					char tmp = production[i].left;
					int tmpIndex = getNIndex(tmp);
					for (it = followSet[tmpIndex].begin(); it != followSet[tmpIndex].end(); it++)
						followSet[targetIndex].insert(*it);
				}
			}
		}
		else if (index != -1 && index == len - 1 && target != production[i].left) {  // 存在A->αB ,FOLLOW(A)放在FOLLOW(B)中
			getFollow(production[i].left);
			set<char>::iterator it;
			char tmp = production[i].left;
			int tmpIndex = getNIndex(tmp);
			for (it = followSet[tmpIndex].begin(); it != followSet[tmpIndex].end(); it++)
				followSet[targetIndex].insert(*it);
		}
	}
}

void Base::inputAndSolve() {  // 处理和求出First和Follow集
	string s;
	cout << "输入的产生式的个数：" << endl;
	cin >> T;
	cout << "输入的产生式：" << endl;
	for (int index = 0; index < T; index++) {  // 处理每一个产生式
		cin >> s;
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
				if (!flag) nonterminal.push_back(temp[i]);
			}
			else {                       //插入一个终结符
				int flag = 0;
				for (int j = 0; j < terminal.size(); j++) {
					if (terminal[j] == temp[i]) {
						flag = 1;
						break;
					}
				}
				if (!flag) terminal.push_back(temp[i]);
			}
		}
	}
	terminal.push_back('#');

	for (int i = 0; i < terminal.size(); i++) { // 存储没有$符号的终结符
		if (terminal[i] != '$')
			terminalNoEmpty.push_back(terminal[i]);
	}

	// 获得first集
	for (int i = 0; i < nonterminal.size(); i++) {
		getFirst(nonterminal[i]);
	}

	// 获得follow集
	for (int i = 0; i < nonterminal.size(); i++) {
		if (i == 0)  // 开始符号, 先加入结束符号
			followSet[0].insert('#');
		getFollow(nonterminal[i]);
	}
}

void Base::displayFirstAndFollow() {  // 输出First和Follow集
	cout << "FIRST集合" << endl;
	for (int i = 0; i < nonterminal.size(); i++) {
		cout << nonterminal[i] << ": ";
		set<char>::iterator it;
		for (it = firstSet[i].begin(); it != firstSet[i].end(); it++)
			cout << *it << "  ";
		cout << endl;
	}
	cout << endl;

	cout << "FOLLOW集合" << endl;
	for (int i = 0; i < nonterminal.size(); i++) {
		cout << nonterminal[i] << ": ";
		set<char>::iterator it;
		for (it = followSet[i].begin(); it != followSet[i].end(); it++)
			cout << *it << "  ";
		cout << endl;
	}
	cout << endl;
}