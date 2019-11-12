#pragma once

#include <vector>
#include <string>
#include <iostream>
using namespace std;

enum ASTNodeType {
	Program = 0,

	IntDeclaration,
	ExpressionStmt,
	AssignmentStmt,

	Primary,
	Multiplicative,
	Additive,

	Identifier,
	IntLiteral,
};

struct ASTNode {
	string txt;
	ASTNodeType type;

	ASTNode* parent;
	vector<ASTNode*> child;

	ASTNode()
	{
		txt = "";
		type = Program;

		parent = NULL;		
	}

	ASTNode(string txt_, ASTNodeType type_)
	{
		txt = txt_;
		type = type_;
		parent = NULL;
	}

	ASTNode* GetParent()
	{
		return parent;
	}

	vector<ASTNode*> GetChildren()
	{
		return child;
	}

	ASTNodeType getType()
	{
		return type;
	}
	string GetText()
	{
		return txt;
	}

	void addChild(string txt, ASTNodeType type)
	{
		ASTNode* node = new ASTNode(txt, type);

		child.push_back(node);
		node->parent = this;
	}

	void addChild(ASTNode *node)
	{
		child.push_back(node);
		node->parent = this;
	}
};

extern string GetEnumName(ASTNodeType type);
extern void dumpTree(ASTNode* node, string indent);
extern int evaluate(ASTNode* node);