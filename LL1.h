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
#ifndef _LL1_H_
#define _LL1_H_

#include"Base.h"

class LL1 : public Base {
private:
	vector<char> analyStack; // ����ջ
	vector<char> leftExpr;  // ʣ�����봮
	int tableMap[100][100];  // Ԥ���

public:
	LL1();

	void getTable(); // ����Ԥ���
	void analyExpression(string s);  // �����������s
	void printPredictTable();  // ���Ԥ���
	void getResult(); // �ۺϴ���
};
#endif
