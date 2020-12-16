#include "CodeGen.h"
#include <iostream>

namespace CG
{
	bool Generation(LT::LexTable& lextable, IT::IdTable& idtable, Out::OUT out)
	{
		int shift = 0; //переменная для создания отступов
		bool typeCastingFlag = false;
		*(out.stream) << "using System;\n\nnamespace CourseProject\n{\n\tclass ZEI2020\n\t{\n\t\t";

		for (int i = 0; i < lextable.size; i++)
		{
			if (typeCastingFlag && lextable.table[i].lexema == LEX_EXCLAMATION) {
				typeCastingFlag = false;
				*(out.stream) << ")";
			}

			switch (lextable.table[i].lexema) {
				case LEX_TINY: 	{ //LEX_SYMBOLIC LEX_LOGICAL
					if (lextable.table[i + 1].lexema == LEX_FUNCTION)
						*(out.stream) << "static ";
					if (!strcmp(lextable.table[i].info, "tiny"))
						*(out.stream) << "sbyte ";								
					if (!strcmp(lextable.table[i].info, "symbolic"))
						*(out.stream) << "string ";
					if (!strcmp(lextable.table[i].info, "logical"))
						*(out.stream) << "bool ";
					break;
				}
				case LEX_LITERAL: {
					if (idtable.table[lextable.table[i].indxTI].iddatatype == IT::TINY)
						*(out.stream) << idtable.table[lextable.table[i].indxTI].value.vtiny;
					if (idtable.table[lextable.table[i].indxTI].iddatatype == IT::SYMB)
						*(out.stream) << idtable.table[lextable.table[i].indxTI].value.vsymb->str;
					if (idtable.table[lextable.table[i].indxTI].iddatatype == IT::LGCL)
						*(out.stream) << idtable.table[lextable.table[i].indxTI].value.vlogical;
					break;
				}
				case LEX_LIBFUNC: {
					*(out.stream) << "ZEI2020stdlib.StandartLibrary."; 
					if (!strcmp(idtable.table[lextable.table[i].indxTI].id,"symblen"))
					{
						*(out.stream) << "Symblen";
					}
					if (!strcmp(idtable.table[lextable.table[i].indxTI].id, "symbtotiny"))
					{
						*(out.stream) << "SymbToTiny";
					}
					if (!strcmp(idtable.table[lextable.table[i].indxTI].id, "gettime"))
					{
						*(out.stream) << "GetTime";
					}
					if (!strcmp(idtable.table[lextable.table[i].indxTI].id, "genertiny"))
					{
						*(out.stream) << "GenerTiny";
					}
					if (!strcmp(idtable.table[lextable.table[i].indxTI].id, "generlgcl"))
					{
						*(out.stream) << "GenerLogical";
					}
					break;
				}
				case LEX_ID: {
					*(out.stream) << idtable.table[lextable.table[i].indxTI].id;
					if (lextable.table[i - 2].lexema == LEX_SET && lextable.table[i+1].lexema == LEX_EXCLAMATION) {	//Инициализация по умолчанию
						if (idtable.table[lextable.table[i].indxTI].iddatatype == IT::TINY)
							*(out.stream) << " = 0";
						if (idtable.table[lextable.table[i].indxTI].iddatatype == IT::SYMB)
							*(out.stream) << " = \"\"";
						if (idtable.table[lextable.table[i].indxTI].iddatatype == IT::LGCL)
							*(out.stream) << " = false";
					}
					break;
				}

				case LEX_ASSIGN: {					//в присваивании литерала не надо приведение типов
					*(out.stream) << " = ";	
					if (idtable.table[lextable.table[i - 1].indxTI].iddatatype == IT::TINY && lextable.table[i+2].lexema != LEX_EXCLAMATION) {
						typeCastingFlag = true;
						*(out.stream) << "(sbyte)(";
					}
					break;
				}
				case LEX_GIVEBACK: {   
					*(out.stream) << "return ";
					if (idtable.table[lextable.table[i + 1].indxTI].iddatatype == IT::TINY) {
						typeCastingFlag = true;
						*(out.stream) << "(sbyte)(";
					}
					break;	
				}

				case LEX_PERFORM: {	*(out.stream) << "static void Main(string[] args)";		break;	}
				case LEX_SHOW:			{	*(out.stream) << "Console.WriteLine";	break;	}	
				case LEX_WHEN:			{	*(out.stream) << "if";		break;	}
				case LEX_OTHERWISE:		{	*(out.stream) << "else";	break;	}
				case LEX_LOOP:			{	*(out.stream) << "while";	break;	}

				case LEX_PLUS:			{	*(out.stream) << " + ";		break;	}
				case LEX_MINUS:			{	*(out.stream) << " - ";		break;	}
				case LEX_STAR:			{	*(out.stream) << " * ";		break;	}
				case LEX_DIVISION:		{	*(out.stream) << " / ";		break;	}
		
				case LEX_EQUALITY:		{	*(out.stream) << " == ";	break;	}
				case LEX_INEQUALITY:	{	*(out.stream) << " != ";	break;	}
				case LEX_MORE:			{	*(out.stream) << " > ";		break;	}
				case LEX_LESS:			{	*(out.stream) << " < ";		break;	}

				case LEX_COMMA:			{	*(out.stream) << ", ";		break;	}
				case LEX_LEFTHESIS:		{	*(out.stream) << "(";		break;	}
				case LEX_EXCLAMATION:	{	*(out.stream) << ";";		break;  }
				case LEX_RIGHTSHIFT:	{	*(out.stream) << " >> ";	break;	}
				case LEX_LEFTSHIFT:		{	*(out.stream) << " << ";    break;	}
				case LEX_RIGHTHESIS:	{	*(out.stream) << ")";		break;  }
				case LEX_LEFTBRACE:		{	*(out.stream) << "{";	shift++;	break;	}
				case LEX_RIGHTBRACE:	{
					if (i + 2 > lextable.size)	{
						*(out.stream) /*<< "\tConsole.ReadKey();" */<< std::endl << "\t" << "\t" << "}";
					}
					else {
						shift--;
						*(out.stream) << "}";
					}
					break;
				}
			}
				
			if (lextable.table[i].sn != lextable.table[i + 1].sn)
			{
				*(out.stream) << std::endl << "\t" << "\t";
				if (lextable.table[i + 1].lexema != LEX_RIGHTBRACE)
					for (int k = 0; k < shift; k++)  //генерация отступов
							*(out.stream) << "\t";
				else
					for (int k = 0; k+1 < shift; k++) //генерация отступов
						*(out.stream) << "\t";
			}
		}
		*(out.stream) << std::endl << "\t" << "}" << std::endl << "}";
		return true;
	}
}

