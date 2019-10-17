// w3_basic_formula_calc.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include "TokenReader1.h"
#include "SimpleLexer.h"
using namespace std;

typedef struct {

}SimpleASTNode;

SimpleASTNode additive();
SimpleASTNode multicative();

int main()
{
    std::cout << "Program Calculator!\n";

	string str2 = "2+3*5+3";

	TokenReader reader(str2);
	reader.Print();

	SimpleLexer lexer;
	
	ASTNode* node = lexer.additive(reader);
	dumpTree(node, "\t");
}
