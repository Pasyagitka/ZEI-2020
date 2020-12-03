#pragma once
#include "Log.h"
#include "LT.h"
#include "IT.h"
#define MINTINY -128
#define MAXTINY 127

namespace Lan {
	void Analysis(char *inText, Log::LOG, LT::LexTable&, IT::IdTable&);
}