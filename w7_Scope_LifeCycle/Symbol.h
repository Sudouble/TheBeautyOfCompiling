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

	// 可见性, 如public或private
	size_t visibility = 0;

	antlr4::ParserRuleContext* ctx;
};

