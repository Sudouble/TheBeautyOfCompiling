#include "ASTTress.h"

#include <map>
#include <string>

std::map<std::string, int> name2Value;

string GetEnumName(ASTNodeType type)
{
	switch (type)
	{
	case Program:
		return "Program";
		break;
	case IntDeclaration:
		return "IntDeclaration";
		break;
	case ExpressionStmt:
		return "ExpressionStmt";
		break;
	case AssignmentStmt:
		return "AssignmentStmt";
		break;
	case Primary:
		return "Primary";
		break;
	case Multiplicative:
		return "Multiplicative";
		break;
	case Additive:
		return "Additive";
		break;
	case Identifier:
		return "Identifier";
		break;
	case IntLiteral:
		return "IntLiteral";
		break;
	default:
		return "Not recognized...";
		break;
	}
}

void dumpTree(ASTNode* node, string indent)
{
	if (node == NULL)
		return;

	cout << indent << node->GetText() << " " << GetEnumName(node->getType()) << endl;
	for (ASTNode* child : node->GetChildren())
	{
		dumpTree(child, indent + "\t");
	}
}

int evaluate(ASTNode* node)
{
	if (node == NULL)
		return 0;

	vector<ASTNode*> vecNode = node->GetChildren();
	switch (node->getType())
	{
	case Program:
		return evaluate(vecNode[0]);
	case IntDeclaration:
	{
		name2Value[node->GetText()] = evaluate(vecNode[0]);
		return name2Value[node->GetText()];
	}
	case Identifier:
	{
		if (name2Value.find(node->GetText()) != name2Value.end())
		{
			return name2Value[node->GetText()];
		}
		else
		{
			throw "Unkown Identifier";
		}
	}
	case Additive:
	{
		if (vecNode.size() == 2)
			return evaluate(vecNode[0]) + evaluate(vecNode[1]);
		else
			throw "tree not with size 2";
	}
		break;
	case Multiplicative:
	{
		vector<ASTNode*> vecNode = node->GetChildren();
		if (vecNode.size() == 2)
			return evaluate(vecNode[0]) * evaluate(vecNode[1]);
		else
			throw "tree not with size 2";
	}
		break;
	case IntLiteral:
		return atoi(node->GetText().c_str());
	default:
		return 0;
		break;
	}
}