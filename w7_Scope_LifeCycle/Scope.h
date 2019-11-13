#pragma once

#include "Symbol.h"
#include <vector>
using std::vector;

class Symbol;

class Scope
{
	vector<Symbol> symbols;
};

