#pragma once

#include "ASTTress.h"
#include "TokenReader1.h"

class SimpleLexer
{
public:
	ASTNode* intDeclararion(TokenReader &reader);
	
	ASTNode* additive(TokenReader& reader);
	ASTNode* multiplyDeclaration(TokenReader& reader);
};

