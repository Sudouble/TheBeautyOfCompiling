// w3_basic_formula_calc.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include "TokenReader1.h"
#include "SimpleLexer.h"
using namespace std;

int main()
{
    std::cout << "Program Calculator!\n";

	string str2 = "2+3*5";
	TokenReader reader(str2);
	reader.Print();

	SimpleLexer lexer;	
	ASTNode* node = lexer.additive(reader);
	dumpTree(node, "\t");
	cout << str2 << " calc result:" << evaluate(node) << endl;


	cout << "===============================" << endl;
	string str3 = "2+3+4";
	TokenReader reader3(str3);
	reader3.Print();

	SimpleLexer lexer3;
	ASTNode* node3 = lexer3.additive(reader3);
	dumpTree(node3, "\t");
	cout << str3 << " calc result:" << evaluate(node3) << endl;
}
