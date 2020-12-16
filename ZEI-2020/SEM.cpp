#include "Sem.h"
#include "LT.h"
#include "Error.h"

//Сделано: значения литерала tiny, symbolic, не 1 perform, переопределение, не определено, нельзя свдвигать строку, параметры функций
namespace Sem
{
	bool Analysis(LT::LexTable lextable, IT::IdTable idtable, Log::LOG log) {
		for (int i = 0; i < lextable.size; i++) {
			switch (lextable.table[i].lexema) {
				case LEX_MORE:	case LEX_LESS: {	// Логические операции  < > можно производить только над типом tiny
					IT::IDDATATYPE lefttype = idtable.table[lextable.table[i - 1].indxTI].iddatatype;
					IT::IDDATATYPE righttype = idtable.table[lextable.table[i + 1].indxTI].iddatatype;
					if (lefttype != IT::IDDATATYPE::TINY || righttype != IT::IDDATATYPE::TINY)
						throw ERROR_THROW_IN(615, lextable.table[i].sn, 0); //Логические операции < > можно производить только над типом tiny
				}
				case LEX_EQUALITY: case LEX_INEQUALITY: { // Логические операции = ^ можно производить только над типами tiny или logical
					IT::IDDATATYPE lefttype = idtable.table[lextable.table[i - 1].indxTI].iddatatype;
					IT::IDDATATYPE righttype = idtable.table[lextable.table[i + 1].indxTI].iddatatype;
					if (!((lefttype == righttype) && (lefttype == IT::IDDATATYPE::TINY || lefttype == IT::IDDATATYPE::LGCL)))
						throw ERROR_THROW_IN(616, lextable.table[i].sn, 0); // Логические операции = ^ можно производить только над типами tiny или logical
					break;
				}
				case LEX_SET: { //set symbolic r : foo(r)!
					for (int y = i + 3; lextable.table[y].lexema != LEX_EXCLAMATION; y++) {
						if (idtable.table[lextable.table[i + 2].indxTI].id == idtable.table[lextable.table[y].indxTI].id)
							throw ERROR_THROW_IN(605, lextable.table[y].sn, 0); //Невозможно вызвать функцию с объявляемым идентификатором
					}
					break;
				}
				case LEX_ASSIGN:	{
					IT::IDDATATYPE lefttype = idtable.table[lextable.table[i - 1].indxTI].iddatatype;
					IT::IDDATATYPE righttype = lefttype;
					for (int j = i + 1; lextable.table[j].lexema != LEX_EXCLAMATION;) { //+-*#()\/
						if (lextable.table[j].lexema != LEX_PLUS && lextable.table[j].lexema != LEX_MINUS && lextable.table[j].lexema != LEX_STAR && lextable.table[j].lexema != LEX_DIVISION && lextable.table[j].lexema != LEX_LEFTHESIS && lextable.table[j].lexema != LEX_RIGHTHESIS && lextable.table[j].lexema != LEX_RIGHTSHIFT && lextable.table[j].lexema != LEX_LEFTSHIFT)	{	
							if (idtable.table[lextable.table[j].indxTI].idtype == IT::F) {	//определенная функция
								righttype = idtable.table[lextable.table[j].indxTI].iddatatype;
								while (lextable.table[j-1].lexema != LEX_RIGHTHESIS)	j++; //продвигаемся к кноцу параметров
								continue;
							}
							if (righttype != idtable.table[lextable.table[j].indxTI].iddatatype) { //tiny : tiny + symbolic!
								throw ERROR_THROW_IN(613, lextable.table[i].sn, 0); //Типы данных в выражении не совпадают
							}
							else if (lextable.table[j].lexema == LEX_LIBFUNC) {
								righttype = idtable.table[lextable.table[j].indxTI].iddatatype;
								if (idtable.table[lextable.table[j].indxTI].parameters.count == 1)	j = j + 4;// b(i)!
								else if (idtable.table[lextable.table[j].indxTI].parameters.count == 0) j = j + 3;	//b()!
							}
							else	{
								righttype = idtable.table[lextable.table[j].indxTI].iddatatype; //в ином случае присваиваем правый тип, чтоб потом сравнить
								j++;
							}
						}
						else
							j++;
					}
					if (lefttype != righttype)
						throw ERROR_THROW_IN(617, lextable.table[i].sn, 0); // tiny : symbolic!
					//Неверное выражение. Несовпадение типов слева и справа от знака присваивания
					break;
				}
				case LEX_FUNCTION:
				{
					IT::IDDATATYPE functionType = idtable.table[lextable.table[i + 1].indxTI].iddatatype;
					for (int j = i; j < lextable.size; j++) 	{
						if (lextable.table[j].lexema == LEX_GIVEBACK) 	{
							IT::IDDATATYPE givebackType = idtable.table[lextable.table[j + 1].indxTI].iddatatype;
							if (functionType != givebackType)	{
								throw ERROR_THROW_IN(608, lextable.table[i].sn, 0); //Несовпадение типа функции и типа возвращаемого значения
							}
							else break;
						}
					}
					break;
				}
				case LEX_ID: case LEX_LIBFUNC:  {
					if ((idtable.table[lextable.table[i].indxTI].idtype == IT::F || idtable.table[lextable.table[i].indxTI].idtype == IT::B)
						&& lextable.table[i - 1].lexema != LEX_FUNCTION) { 
						int paramCounter = 0;
						IT::Entry* ITEntry = new IT::Entry();
						*ITEntry = IT::GetEntry(idtable, lextable.table[i].indxTI);
						for (int j = i + 2; lextable.table[j].lexema != LEX_RIGHTHESIS; j++)	{
							if (lextable.table[j].lexema == LEX_ID || lextable.table[j].lexema == LEX_LITERAL)	{
								paramCounter++;
								if (paramCounter > ITEntry->parameters.count) {
									throw  ERROR_THROW_IN(611, lextable.table[i].sn, 0); //Слишком много аргументов в вызове функции
								}
								if (idtable.table[lextable.table[j].indxTI].iddatatype	!= ITEntry->parameters.typeofparameter[paramCounter - 1]) {
									throw  ERROR_THROW_IN(610, lextable.table[i].sn, 0); //Неверные параметры вызываемой функции
								}
							}
						}
						if (paramCounter < ITEntry->parameters.count)
							throw  ERROR_THROW_IN(612, lextable.table[i].sn, 0); //Слишком мало аргументов в вызове функции
						delete ITEntry;
					}
					if (idtable.table[lextable.table[i].indxTI].iddatatype != IT::TINY) { //например, symbolic : symbolic + symbolic!
						for (int j = i + 1; lextable.table[j].lexema != LEX_EXCLAMATION && lextable.table[j].lexema != LEX_RIGHTHESIS; j++) {
							if (lextable.table[j].lexema == LEX_PLUS || lextable.table[j].lexema == LEX_MINUS || lextable.table[j].lexema == LEX_STAR || lextable.table[j].lexema == LEX_DIVISION) {
								throw  ERROR_THROW_IN(614, lextable.table[i].sn, 0); //Арифметические операции можно производить только над типом tiny
							} 
						}
					}
					break;
				}

			}
		}
		return true;
	}
}