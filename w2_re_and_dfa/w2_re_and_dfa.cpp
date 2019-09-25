// w2_re_and_dfa.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "TokenReader1.h"

int main()
{
	string str = "age >= 45";
	string str1 = "int age = 40";
	string str2 = "2+3*5";

	TokenReader reader(str);
	reader.Print();
}
