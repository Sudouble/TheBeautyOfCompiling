#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

enum STATE
{
	INIT = 0,
	
	Int,
	ID_Int1,
	ID_Int2,
	ID_Int3,

	Identify,  // 标识符
	INT_DIGIT, // 整型数字

	GT,
	GT_THAN,

	SemiColon, // ;
	LeftParen, // (
	RightParen,// )

	EQUAL, // =
	ADD,   // +
	MINUS, // - 
	MULTI, // *
};

typedef struct {
	string text = "";
	STATE state = INIT;
}TOKEN;

class TokenReader
{
public:
	TokenReader(string str_);
	~TokenReader() {}
	void Print();

	TOKEN read(); // next unit
	TOKEN peek();
	void unread();
	int GetCurrentToken();

private:
	void parse();
	void UpdateToken(STATE& lastState, char ch);
	STATE InitToken(char ch);	
	

private:
	string str;
	TOKEN token;
	vector<TOKEN> vecResult;

	map<STATE, string> mapEnum2Name;

	int currentPos;
};
