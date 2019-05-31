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

struct node {  // 产生式的数据结构
	char left;
	string right;
};

class Base {
protected:
	int T;
	node p[maxsize]; // 产生式集

	set<char> firstSet[maxsize];  // First集
	set<char> followSet[maxsize];  // Follow集
	vector<char> terminalNoEmpty; // 去$(空)的终结符
	vector<char> terminal;  // 终结符
	vector<char> nonterminal;  // 非终结符

	bool isNonterminal(char c);
	int getIndex(char target);  // 获得target在终结符集合中的下标
	int getNIndex(char target);  // 获得target在非终结符集合中的下标
	void getFirst(char target);  // 得到First(target)
	void getFollow(char target);  // 得到Follow(target)

public:
	Base() {};

	void inputAndSolve();  // 处理和求出First和Follow集
	void displayFirstAndFollow();  // 输出First和Follow集

};
#endif 