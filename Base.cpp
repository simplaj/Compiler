#include "Base.h"

bool Base::isNonterminal(char c) { // �ж�c�Ƿ�Ϊ���ս��
	if (c >= 'A' && c <= 'Z')
		return true;
	return false;
}
int Base::getNIndex(char target) {  // ���target�ڷ��ս�������е��±�
	for (int i = 0; i < nonterminal.size(); i++) {
		if (target == nonterminal[i])
			return i;
	}
	return -1;
}
int Base::getIndex(char target) {  // ���target���ս�������е��±�
	for (int i = 0; i < terminalNoEmpty.size(); i++) {
		if (target == terminalNoEmpty[i])
			return i;
	}
	return -1;
}

void Base::getFirst(char target) {  // ��FIRST(target��
	int countEmpty = 0;  // ��������ж��Ƿ��п�
	int isEmpty = 0;
	int targetIndex = getNIndex(target);
	for (int i = 0; i < T; i++) {
		if (production[i].left == target) {  // ƥ�����ʽ��
			if (!isNonterminal(production[i].right[0])) {  // �����ս����ֱ�Ӽ���first
				firstSet[targetIndex].insert(production[i].right[0]);
			}
			else {
				for (int j = 0; j < production[i].right.length(); j++) { // X->Y1..Yj..Yk��һ������ʽ
					char Yj = production[i].right[j];
					if (!isNonterminal(Yj)) {  // Yj���ս��(���ܲ�����),FIRST(Yj)=Yj����FIRST(X),���ܼ�������,����
						firstSet[targetIndex].insert(Yj);
						break;
					}
					getFirst(Yj);// Yj�Ƿ��ս�����ݹ� �����FIRST(Yj)

					set<char>::iterator it;
					int YjIndex = getNIndex(Yj);
					for (it = firstSet[YjIndex].begin(); it != firstSet[YjIndex].end(); it++) {
						if (*it == '$')  // �����鿴FIRST(Yj)���Ƿ���'$'(�ܲ�����)
							isEmpty = 1;
						else
							firstSet[targetIndex].insert(*it);//��FIRST(Yj)�еķ�$�ͼ���FIRST(X)
					}
					if (isEmpty == 0)  // Yj���ܲ�����, ��������
						break;
					else {   //  Yj�ܲ�����
						countEmpty += isEmpty;
						isEmpty = 0;
					}
				}
				if (countEmpty == production[i].right.length())//�����Ҳ�first(Y)����$(��),��$����FIRST(X)��
					firstSet[getNIndex(target)].insert('$');
			}
		}
	}
}

void Base::getFollow(char target) {  // ��FOLLOW(target��
	int targetIndex = getNIndex(target);
	for (int i = 0; i < T; i++) {
		int index = -1;
		int len = production[i].right.length();
		for (int j = 0; j < len; j++) {  // Ѱ��target�ڲ���ʽ�е�λ��index
			if (production[i].right[j] == target) {
				index = j;
				break;
			}
		}
		if (index != -1 && index < len - 1) {  // �ҵ�target�ڲ���ʽ�е�λ��index
											   // ����A->��B��, ��FIRST(��)�г��˿�$֮������з���FOLLOW(B)��
											   // ����B��Ӧtarget, �¶�Ӧnxt
			char nxt = production[i].right[index + 1];
			if (!isNonterminal(nxt)) {  // �����ս�� FIRST(��)=�£�ֱ�Ӳ����
				followSet[targetIndex].insert(nxt);
			}
			else {  // ���Ƿ��ս��
				int hasEmpty = 0;
				set<char>::iterator it;
				int nxtIndex = getNIndex(nxt);  // ����FIRST(��)�г��˿�$֮�������
				for (it = firstSet[nxtIndex].begin(); it != firstSet[nxtIndex].end(); it++) {
					if (*it == '$')
						hasEmpty = 1;
					else
						followSet[targetIndex].insert(*it);
				}

				if (hasEmpty && production[i].left != target) { // ����A->��B����FIRST(��)->$
															 // FOLLOW(A)����FOLLOW(B)��
					getFollow(production[i].left);
					set<char>::iterator it;
					char tmp = production[i].left;
					int tmpIndex = getNIndex(tmp);
					for (it = followSet[tmpIndex].begin(); it != followSet[tmpIndex].end(); it++)
						followSet[targetIndex].insert(*it);
				}
			}
		}
		else if (index != -1 && index == len - 1 && target != production[i].left) {  // ����A->��B ,FOLLOW(A)����FOLLOW(B)��
			getFollow(production[i].left);
			set<char>::iterator it;
			char tmp = production[i].left;
			int tmpIndex = getNIndex(tmp);
			for (it = followSet[tmpIndex].begin(); it != followSet[tmpIndex].end(); it++)
				followSet[targetIndex].insert(*it);
		}
	}
}

void Base::inputAndSolve() {  // ��������First��Follow��
	string s;
	cout << "����Ĳ���ʽ�ĸ�����" << endl;
	cin >> T;
	cout << "����Ĳ���ʽ��" << endl;
	for (int index = 0; index < T; index++) {  // ����ÿһ������ʽ
		cin >> s;
		string temp = "";  // �洢ȥ���ո�Ĳ���ʽ
		for (int i = 0; i < s.length(); i++) {  // ȥ������ʽ�е�' '
			if (s[i] != ' ')
				temp += s[i];
		}
		production[index].left = temp[0];  // ����ʽ����
		for (int i = 3; i < temp.length(); i++) // ����ʽ���Ҳ�
			production[index].right += temp[i];

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
				if (!flag) nonterminal.push_back(temp[i]);
			}
			else {                       //����һ���ս��
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

	for (int i = 0; i < terminal.size(); i++) { // �洢û��$���ŵ��ս��
		if (terminal[i] != '$')
			terminalNoEmpty.push_back(terminal[i]);
	}

	// ���first��
	for (int i = 0; i < nonterminal.size(); i++) {
		getFirst(nonterminal[i]);
	}

	// ���follow��
	for (int i = 0; i < nonterminal.size(); i++) {
		if (i == 0)  // ��ʼ����, �ȼ����������
			followSet[0].insert('#');
		getFollow(nonterminal[i]);
	}
}

void Base::displayFirstAndFollow() {  // ���First��Follow��
	cout << "FIRST����" << endl;
	for (int i = 0; i < nonterminal.size(); i++) {
		cout << nonterminal[i] << ": ";
		set<char>::iterator it;
		for (it = firstSet[i].begin(); it != firstSet[i].end(); it++)
			cout << *it << "  ";
		cout << endl;
	}
	cout << endl;

	cout << "FOLLOW����" << endl;
	for (int i = 0; i < nonterminal.size(); i++) {
		cout << nonterminal[i] << ": ";
		set<char>::iterator it;
		for (it = followSet[i].begin(); it != followSet[i].end(); it++)
			cout << *it << "  ";
		cout << endl;
	}
	cout << endl;
}