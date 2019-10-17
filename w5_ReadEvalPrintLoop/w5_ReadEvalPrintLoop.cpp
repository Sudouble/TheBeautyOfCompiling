// w5_ReadEvalPrintLoop.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "SimpleLexer.h"
using namespace std;

int main()
{
	string str1 = "int age=45*2+1;";

	TokenReader reader(str1);
	reader.Print();

	SimpleLexer lexer;
	ASTNode* node = lexer.intDeclararion(reader);
	dumpTree(node, "\t");
	cout << str1 << " calc result:" << evaluate(node) << endl;

	cout << "===============================" << endl;
	std::cout << "Program Calculator!\n";

	string str2 = "2+3*5*4";
	TokenReader reader2(str2);
	reader2.Print();

	SimpleLexer lexer2;
	ASTNode* node2 = lexer2.additive(reader2);
	dumpTree(node2, "\t");
	cout << str2 << " calc result:" << evaluate(node2) << endl;


	cout << "===============================" << endl;
	string str3 = "2+3+4";
	TokenReader reader3(str3);
	reader3.Print();

	SimpleLexer lexer3;
	ASTNode* node3 = lexer3.additive(reader3);
	dumpTree(node3, "\t");
	cout << str3 << " calc result:" << evaluate(node3) << endl;

	// REPL
	cout << "================ REPL =================" << endl;	
	cout << "支持的操作：" << endl;
	cout << "1. 整型变量声明" << endl;
	cout << "2. 整型数字加法" << endl;
	cout << "3. 变量赋值" << endl;

	while (true)
	{
		try
		{
			char str[200];
			cin.getline(str, 200);
			TokenReader reader(str);

			SimpleLexer lexer;
			ASTNode* node = lexer.prog(reader);
			cout << str << " calc result:" << evaluate(node) << endl;
		}
		catch (const std::exception& e)
		{
			cout << e.what();
		}		
	}
}
