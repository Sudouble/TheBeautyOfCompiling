// w2_re_and_dfa.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
using namespace std;

enum STATE
{
	INIT = 0,
	ID,
	DIGIT,
	GT,
	GT_THAN
};

string tokenText = "";

void InitToken(ch)
{

}

void ReadOne(char ch)
{
	STATE newState = INIT;
	if (isalpha(ch))
	{
		newState = ID;
		tokenText += ch;
	}
	else if (isdigit(ch))
	{
		newState = DIGIT;
		tokenText += ch;
	}
	else if (ch == '>')
	{
		newState = GT;
		tokenText += ch;
	}
}

int main()
{
    
}
