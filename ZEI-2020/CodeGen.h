#pragma once
#include "IT.h"
#include "LT.h"
#include "Log.h"
#include "Out.h"

//TODO: ���� ����������, ������������ �� ��� � ����?

namespace CG {

	void Generate(LT::LexTable lextable, IT::IdTable idtable, Log::LOG log, Out::OUT out);
	void ConstSegment(LT::LexTable lextable, IT::IdTable idtable, Log::LOG log, Out::OUT out);
	//void DataSegment();
	//void CodeSegment();
}
