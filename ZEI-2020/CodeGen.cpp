#include "Out.h"
#include "Parm.h"
#include "LT.h"
#include "IT.h"
#include "Log.h"
#include "CodeGen.h"

#define HEADER \
".586P\n\
.model flat, stdcall\n\
includelib libucrt.lib\n\
includelib kernel32.lib\n\
includelib ../Debug/ZEI.lib\n" 

#define PROTO	"ExitProcess PROTO :DWORD\n\
EXTRN show: PROC\n\
EXTRN symblen: PROC\n\
EXTRN symbtotiny: PROC\n"

#define STACK   ".STACK 4096\n"
#define CONST	".CONST\n"
#define DATA	".DATA\n"
#define CODE	".CODE\n"

//TODO: представление bool в asm?
namespace CG {
	void Generate(LT::LexTable lextable, IT::IdTable idtable, Log::LOG log, Out::OUT out) {
		*(out.stream) << HEADER << std::endl;
		*(out.stream) << PROTO << std::endl;
		*(out.stream) << STACK << std::endl;
		*(out.stream) << CONST << std::endl;
			ConstSegment(lextable, idtable, log, out);
		*(out.stream) << DATA << std::endl;
			/*DataSegment();*/
		*(out.stream) << CODE << std::endl;
			/*CodeSegment();*/
	}
	void ConstSegment(LT::LexTable lextable, IT::IdTable idtable, Log::LOG log, Out::OUT out) {
		for (int i = 0; i < idtable.size; i++)
		{
			if (idtable.table[i].idtype == IT::L)
			{
				*(out.stream) << "\t" << idtable.table[i].id;
				if (idtable.table[i].iddatatype == IT::SYMB)
					*(out.stream) << " BYTE " << idtable.table[i].value.vsymb->str << ", 0";
				if (idtable.table[i].iddatatype == IT::TINY || idtable.table[i].iddatatype == IT::LGCL)
					*(out.stream) << " SBYTE " << idtable.table[i].value.vtiny;
				*(out.stream) << '\n';
			}
		}
	}
	
}