#include "Sem.h"
#include "LT.h"
#include "Error.h"

//TODO сделать строку до 127 символов
//Сделано: значения литерала tiny, symbolic, не 1 perform, переопределение, не определено, нельзя свдвигать строку, параметры функций

//TODO: деление на 0

//Можно: округление слишком большого tiny литерала, усечение слишком длинного symbolic литерала
namespace Sem
{
	//TODO: не та строка в области видимости
	
	void Analysis(LT::LexTable lextable, IT::IdTable idtable, Log::LOG log) {
		for (int i = 0; i < lextable.size; i++) {
			switch (lextable.table[i].lexema) {
				case LEX_ASSIGN:	{
					int y = i + 1;
					IT::IDDATATYPE lefttype = idtable.table[lextable.table[i - 1].indxTI].iddatatype;
					IT::IDDATATYPE righttype = lefttype;
					for (; lextable.table[y].lexema != LEX_EXCLAMATION;) {
						if (lextable.table[y].lexema != LEX_PLUS && lextable.table[y].lexema != LEX_MINUS
							&& lextable.table[y].lexema != LEX_STAR && lextable.table[y].lexema != LEX_DIVISION
							&& lextable.table[y].lexema != LEX_LEFTHESIS && lextable.table[y].lexema != LEX_RIGHTHESIS 
							&& lextable.table[y].lexema != LEX_RIGHTSHIFT && lextable.table[y].lexema != LEX_LEFTSHIFT)
						{
							if (idtable.table[lextable.table[y].indxTI].idtype == IT::F) {
								righttype = idtable.table[lextable.table[y].indxTI].iddatatype;
								y++;
								while (lextable.table[y].lexema != LEX_RIGHTHESIS)
								{
									y++;
								}
								y++;
								continue;
							}
							if (righttype != idtable.table[lextable.table[y].indxTI].iddatatype) {
								throw ERROR_THROW_IN(613, lextable.table[i].sn, 0);
							}
							else if (lextable.table[y].lexema == LEX_LIBFUNC) {
								righttype = idtable.table[lextable.table[y].indxTI].iddatatype;
								y = y + 4;// b(i)
							}
							else	{
								righttype = idtable.table[lextable.table[y].indxTI].iddatatype;
								y++;
							}
						}
						else
							y++;
					}
					if (lefttype != righttype)
						throw ERROR_THROW_IN(617, lextable.table[i].sn, 0);
					break;
				}

				case LEX_MORE:	case LEX_LESS: case LEX_EQUALITY: case LEX_INEQUALITY: { // Логические операторы < > = ^
					IT::IDDATATYPE lefttype = idtable.table[lextable.table[i - 1].indxTI].iddatatype;
					IT::IDDATATYPE righttype = idtable.table[lextable.table[i + 1].indxTI].iddatatype;
					if (lefttype != IT::IDDATATYPE::TINY || righttype != IT::IDDATATYPE::TINY)
					{
						throw ERROR_THROW_IN(615, lextable.table[i].sn, 0);
					}
					break;
				}

				case LEX_LEFTSHIFT: case LEX_RIGHTSHIFT:	{		//Сдвиги
					IT::IDDATATYPE lefttype = idtable.table[lextable.table[i - 1].indxTI].iddatatype;
					IT::IDDATATYPE righttype = idtable.table[lextable.table[i + 1].indxTI].iddatatype;
					if (lefttype != IT::IDDATATYPE::TINY || righttype != IT::IDDATATYPE::TINY)
					{
						throw ERROR_THROW_IN(616, lextable.table[i].sn, 0);
					}
					break;
				}


				case LEX_FUNCTION:
				{
					IT::IDDATATYPE functionType = idtable.table[lextable.table[i + 1].indxTI].iddatatype;
					for (int y = i; y < lextable.size; y++)
					{
						if (lextable.table[y].lexema == LEX_GIVEBACK)
						{
							IT::IDDATATYPE givebackType = idtable.table[lextable.table[y + 1].indxTI].iddatatype;
							if (functionType != givebackType)
							{
								throw ERROR_THROW_IN(608, lextable.table[i].sn, 0);
							}
							else break;
						}
					}
					break;
				}
				
				//TODO: set symbolic r : foo(r)!
				case LEX_ID: case LEX_LIBFUNC: case LEX_SHOW: case LEX_SHOWSTR: { //параметры функции
					if ((idtable.table[lextable.table[i].indxTI].idtype == IT::F || idtable.table[lextable.table[i].indxTI].idtype == IT::B)//функция или библиотечная
						&& lextable.table[i - 1].lexema != LEX_FUNCTION) { //не объявление функции
						int paramCounter = 0;
						IT::Entry ITEntry = IT::GetEntry(idtable, lextable.table[i].indxTI);
						for (int j = i + 2; lextable.table[j].lexema != LEX_RIGHTHESIS; j++)
						{
							if (lextable.table[j].lexema == LEX_ID || lextable.table[j].lexema == LEX_LITERAL)
							{
								paramCounter++;
								if (paramCounter > ITEntry.parameters.count)
								{
									throw  ERROR_THROW_IN(611, lextable.table[i].sn, 0);
								}
								if (idtable.table[lextable.table[j].indxTI].iddatatype != ITEntry.parameters.typeofparameter)
								{
									throw  ERROR_THROW_IN(610, lextable.table[i].sn, 0);
								}
							}
						}
						if (paramCounter < ITEntry.parameters.count)
							throw  ERROR_THROW_IN(612, lextable.table[i].sn, 0);
					}
					break;
				}

						   //TODO: семантика
				//case LEX_SET: { //Не так работает
				//	int y = i + 2;
				//	IT::Entry DeclaringEntry = IT::GetEntry(idtable, lextable.table[y].indxTI);
				//	for (y = y+2; lextable.table[y].lexema != LEX_EXCLAMATION; y++) {
				//		if (DeclaringEntry.id == lextable.table[y].buf)
				//			throw ERROR_THROW_IN(605, lextable.table[y].sn, 0);
				//	}
				//	break;
				//}

			}
		}
	}
}
	
	//	
	//		//case LEX_CHECK:
	//		//{
	//		//	if (lex.lextable.table[i + 1].lexema == LEX_LEFTTHESIS && lex.lextable.table[i + 3].lexema == LEX_RIGHTTHESIS)
	//		//		if ((lex.lextable.table[i + 2].lexema == LEX_ID || lex.lextable.table[i + 2].lexema == LEX_LITERAL) && lex.idtable.table[lex.lextable.table[i + 2].idxTI].iddatatype != IT::BOOL)
	//		//			Log::WriteError(log, Error::geterrorin(301, lex.lextable.table[i].line, -1));
	//		//}
	//		
	//		}
	//	}
	//}
//}