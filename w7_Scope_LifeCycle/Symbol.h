#pragma once

#include <string>
#include "antlr4-runtime.h"

using std::string;

#include "Scope.h"

class Scope;

class Symbol
{
	string  strName;

	Scope* enclosingScope;

	// �ɼ���, ��public��private
	size_t visibility = 0;

	antlr4::ParserRuleContext* ctx;
};

