#pragma once
#include "Log.h"
#include "LT.h"
#include "IT.h"


namespace Lan {
	void Analysis(char inText[], Log::LOG, LT::LexTable&, IT::IdTable&);
}