#pragma once
#ifndef _LL1_H_
#define _LL1_H_

#include"Base.h"

class LL1 : public Base {
private:
	vector<char> analyStack; // 分析栈
	vector<char> leftExpr;  // 剩余输入串
	int tableMap[100][100];  // 预测表

public:
	LL1();

	void getTable(); // 生成预测表
	void analyExpression(string s);  // 分析输入语句s
	void printPredictTable();  // 输出预测表
	void getResult(); // 综合处理
};
#endif
