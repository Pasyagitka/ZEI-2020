#pragma once
#include "LT.h"
#include "IT.h"

namespace Pn {
	void ToPolish(LT::LexTable& lextable, IT::IdTable& idtable);
	int GetPriority(char c);
	bool PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable);
}