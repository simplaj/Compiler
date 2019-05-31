#pragma once
#ifndef _BASE_H_
#define _BASE_H_
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>

#define maxsize 100

using namespace std;

struct node {  // ����ʽ�����ݽṹ
	char left;
	string right;
};

class Base {
protected:
	int T;
	node p[maxsize]; // ����ʽ��

	set<char> firstSet[maxsize];  // First��
	set<char> followSet[maxsize];  // Follow��
	vector<char> terminalNoEmpty; // ȥ$(��)���ս��
	vector<char> terminal;  // �ս��
	vector<char> nonterminal;  // ���ս��

	bool isNonterminal(char c);
	int getIndex(char target);  // ���target���ս�������е��±�
	int getNIndex(char target);  // ���target�ڷ��ս�������е��±�
	void getFirst(char target);  // �õ�First(target)
	void getFollow(char target);  // �õ�Follow(target)

public:
	Base() {};

	void inputAndSolve();  // ��������First��Follow��
	void displayFirstAndFollow();  // ���First��Follow��

};
#endif 