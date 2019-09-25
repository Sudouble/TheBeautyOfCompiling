#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

enum STATE
{
	INIT = 0,
	ID,
	DIGIT,
	GT,
	GT_THAN
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

private:
	void parse();
	STATE InitToken(char ch);	

private:
	string str;
	TOKEN token;
	vector<TOKEN> vecResult;

	map<STATE, string> mapEnum2Name;
};
