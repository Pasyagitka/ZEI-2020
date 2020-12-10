#include "Lan.h"
#include "Log.h"
#include "LT.h"
#include "IT.h"
#include "FST.h"

#include <string>
#include "FSTExpr.h"
#include "Sem.h"
//Норм ли что библитечные функции записываются в id столько раз сколько вызываются

//TODO: получается номер и у H(16)
namespace Lan
{

	void Analysis(char inText[], Log::LOG, LT::LexTable& lextable, IT::IdTable& idtable)
	{
		int currentLine = 1, currentColumn = 0, tokenlen = 0;
		bool tokenIsCommited(false), check(false), newLineFlag(false), flag(false);
		bool quoteFlag(false);
		int entryPoint = 0;
		//TODO строка отнять кавычки
		char postfix[10];
		char token[258]{};
		char anotherbuf[10];

		int parameterscounter = 0;

		LT::LexTable* newLexTable = &lextable;
		IT::IdTable* newIDTable = &idtable;
		IT::IDDATATYPE dataType = IT::IDDATATYPE::UNDEF;
		IT::IDTYPE idType = IT::IDTYPE::U;

		for (int i = 0; i < strlen(inText); i++)
		{
			token[tokenlen++] = inText[i];
			if (inText[i] == LEX_QUOTE)	quoteFlag = !quoteFlag;

			tokenIsCommited = false;

			if (newLineFlag)
			{
				currentLine++;
				currentColumn = 0;
				newLineFlag = false;
			}//TODO: добавить знаки,чтоб выражения х=х распознавались правильно +-=пробел*/<>
			if (inText[i] == LEX_SPACE || inText[i] == LEX_ENDL 
				|| inText[i] == LEX_POINT || inText[i] == LEX_COMMA || inText[i] == LEX_EXCLAMATION || inText[i] == LEX_LEFTHESIS || inText[i] == LEX_RIGHTHESIS || inText[i] == LEX_RIGHTBRACE || inText[i] == LEX_LEFTBRACE || inText[i] == LEX_RIGHTFIGUREBRACE || inText[i] == LEX_LEFTFIGUREBRACE
				|| inText[i + 1] == LEX_POINT || inText[i + 1] == LEX_COMMA || inText[i +1 ] == LEX_EXCLAMATION || inText[i +1] == LEX_LEFTHESIS || inText[i+1] == LEX_RIGHTHESIS || inText[i+1] == LEX_RIGHTBRACE || inText[i+1] == LEX_LEFTBRACE || inText[i + 1] == LEX_RIGHTFIGUREBRACE || inText[i + 1] == LEX_LEFTFIGUREBRACE 
				|| inText[i + 1] == LEX_MINUS || inText[i + 1] == LEX_PLUS || inText[i + 1] == LEX_EQUALITY || inText[i + 1] == LEX_STAR || inText[i + 1] == LEX_DIVISION /*| inText[i + 1] == LEX_LESS || inText[i + 1] == LEX_MORE */ || inText[i + 1] == LEX_RIGHTSHIFT || inText[i + 1] == LEX_LEFTSHIFT
				|| inText[i] == LEX_MINUS || inText[i] == LEX_PLUS || inText[i] == LEX_EQUALITY || inText[i] == LEX_STAR || inText[i] == LEX_DIVISION /*|| inText[i] == LEX_LESS || inText[i] == LEX_MORE*/ || inText[i] == LEX_RIGHTSHIFT || inText[i] == LEX_LEFTSHIFT
				)
			{
				if (quoteFlag) 	continue;
				if (inText[i] == LEX_ENDL)	newLineFlag = true;

				if (tokenlen == 1 || inText[i+1] == LEX_EXCLAMATION || inText[i+1] == LEX_POINT || inText[i+1] == LEX_LEFTHESIS || inText[i+1] == LEX_RIGHTHESIS ||  inText[i+1] == LEX_COMMA || inText[i+1] == LEX_RIGHTFIGUREBRACE || inText[i+1] == LEX_LEFTFIGUREBRACE)
					token[tokenlen] = LEX_END;
				else
					if (!quoteFlag) token[tokenlen - 1] = LEX_END;
					

				tokenlen = 0;
				tokenIsCommited = true;
				if (token[tokenlen] == LEX_SPACE || token[tokenlen] == LEX_ENDL)	continue;
			}

			currentColumn++;
			if (tokenIsCommited) {
				FST::FST FSTExclamation(token, FST_EXCLAMATION);
				if (FST::execute(FSTExclamation)) {
					LT::Entry *newLTEntry = new LT::Entry{ LEX_EXCLAMATION, currentLine, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTPoint (token, FST_POINT);
				if (FST::execute(FSTPoint)) {
					LT::Entry* newLTEntry = new LT::Entry{ LEX_POINT, currentLine, IT::IsId(idtable, token) };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTLefthesis (token, FST_LEFTHESIS);
				if (FST::execute(FSTLefthesis)) {
					LT::Entry* newLTEntry = new LT::Entry{ LEX_LEFTHESIS, currentLine, IT::IsId(idtable, token) };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTRighthesis(token, FST_RIGHTHESIS);
				if (FST::execute(FSTRighthesis)) {
					LT::Entry* newLTEntry = new LT::Entry{ LEX_RIGHTHESIS, currentLine, IT::IsId(idtable, token) };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTRightbrace(token, FST_RIGHTBRACE);
				if (FST::execute(FSTRightbrace)) {
					LT::Entry* newLTEntry = new LT::Entry{ LEX_RIGHTBRACE, currentLine, IT::IsId(idtable, token) };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTLeftbrace(token, FST_LEFTBRACE);
				if (FST::execute(FSTLeftbrace)) {
					LT::Entry* newLTEntry = new LT::Entry{ LEX_LEFTBRACE, currentLine, IT::IsId(idtable, token) };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTRightfigurebrace(token, FST_RIGHTFIGUREBRACE);
				if (FST::execute(FSTRightfigurebrace)) {
					LT::Entry* newLTEntry = new LT::Entry{ LEX_RIGHTFIGUREBRACE, currentLine, IT::IsId(idtable, token) };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTLeftfigurebrace(token, FST_LEFTFIGUREBRACE);
				if (FST::execute(FSTLeftfigurebrace)) {
					LT::Entry* newLTEntry = new LT::Entry{ LEX_LEFTFIGUREBRACE, currentLine, IT::IsId(idtable, token) };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTComma(token, FST_COMMA);
				if (FST::execute(FSTComma)) {
					LT::Entry* newLTEntry = new LT::Entry{ LEX_COMMA, currentLine, IT::IsId(idtable, token) };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTTiny(token, FST_TINY);
				if (FST::execute(FSTTiny)) {
					dataType = IT::TINY;
					if (idType == IT::F)
						idType = IT::P;
					else
						idType = IT::V;
					LT::Entry* newLTEntry = new LT::Entry{ LEX_TINY, currentLine, IT::IsId(idtable, token) };
					strcpy_s(newLTEntry->buf, token);
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTSymbolic(token, FST_SYMBOLIC);
				if (FST::execute(FSTSymbolic)) {
					if (idType == IT::F)
						idType = IT::P;
					else 
						idType = IT::V;
					dataType = IT::SYMB;
					LT::Entry* newLTEntry = new LT::Entry{ LEX_SYMBOLIC, currentLine, IT::IsId(idtable, token) };
					strcpy_s(newLTEntry->buf, token);
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTLogical(token, FST_LOGICAL);
				if (FST::execute(FSTLogical)) {
					dataType = IT::LGCL;
					if (idType == IT::F)
						idType = IT::P;
					else
						idType = IT::V;
					LT::Entry* newLTEntry = new LT::Entry{ LEX_LOGICAL, currentLine, IT::IsId(idtable, token) };
					strcpy_s(newLTEntry->buf, token);
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTFunc(token, FST_FUNC);
				if (FST::execute(FSTFunc)) {
					LT::Entry* newLTEntry = new LT::Entry{ LEX_FUNCTION, currentLine, IT::IsId(idtable, token) };
					LT::Add(*newLexTable, *newLTEntry);
					idType = IT::F;
					delete newLTEntry;
					continue;
				}
				FST::FST FSTGiveback(token, FST_GIVEBACK);
				if (FST::execute(FSTGiveback)) {
					LT::Entry* newLTEntry = new LT::Entry{ LEX_GIVEBACK, currentLine, IT::IsId(idtable, token) };
					LT::Add(*newLexTable, *newLTEntry);
					idType = IT::V;
					delete newLTEntry;
					continue;
				}
				FST::FST FSTPerform(token, FST_PERFORM);
				if (FST::execute(FSTPerform)) {
					entryPoint++;
					LT::Entry* newLTEntry = new LT::Entry{ LEX_PERFORM, currentLine, IT::IsId(idtable, token) };
					LT::Add(*newLexTable, *newLTEntry);
					/*idType = IT::F;*/
					strcpy_s(postfix, "perform");
					delete newLTEntry;
					continue;
				}
				FST::FST FSTLoop(token, FST_LOOP);
				if (FST::execute(FSTLoop)) {
					LT::Entry* newLTEntry = new LT::Entry{ LEX_LOOP, currentLine, IT::IsId(idtable, token) };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTSet(token, FST_SET);
				if (FST::execute(FSTSet)) {
					LT::Entry* newLTEntry = new LT::Entry{ LEX_SET, currentLine, IT::IsId(idtable, token)  };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTShow(token, FST_SHOW);
				if (FST::execute(FSTShow)) {;
					idType = IT::B;

					IT::Entry *newIDEntry = new IT::Entry{};
					strcpy_s(newIDEntry->id, token);
					newIDEntry->idtype = idType;
					newIDEntry->iddatatype = dataType;
					newIDEntry->value.vtiny = TI_TINY_DEFAULT;
					newIDEntry->value.vsymb->len = TI_SYMB_DEFAULT;
					newIDEntry->parameters.count = 1;
					newIDEntry->parameters.typeofparameter = IT::SYMB;
					strcpy_s(newIDEntry->value.vsymb->str, "");
					newIDEntry->idxfirstLE = currentLine;
					IT::Add(*newIDTable, *newIDEntry);

					LT::Entry* newLTEntry = new LT::Entry{ LEX_SHOW, currentLine, IT::IsId(idtable, token) , 1};
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					delete newIDEntry;
					continue;
				}
				FST::FST FSTLib(token, FST_LIB);
				if (FST::execute(FSTLib)) {
					LT::Entry* newLTEntry = new LT::Entry{ LEX_LIB, currentLine, IT::IsId(idtable, token) };
					LT::Add(*newLexTable, *newLTEntry);
					strcpy_s(postfix, token);
					/*SA::OneLib(lextable, flag);*/
					flag = true;
					delete newLTEntry;
					continue;
				}
				FST::FST FSTWhen(token, FST_WHEN);
				if (FST::execute(FSTWhen)) {
					LT::Entry* newLTEntry = new LT::Entry{ LEX_WHEN, currentLine, IT::IsId(idtable, token) };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTOtherwise(token, FST_OTHERWISE);
				if (FST::execute(FSTOtherwise)) {
					LT::Entry* newLTEntry = new LT::Entry{ LEX_OTHERWISE, currentLine, IT::IsId(idtable, token) };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTSymblen(token, FST_SYMBLEN);
				if (FST::execute(FSTSymblen)) {
					IT::Entry* newIDEntry = new IT::Entry{};
					strcpy_s(newIDEntry->id, token);
					newIDEntry->idtype = IT::B;
					newIDEntry->iddatatype = IT::TINY;
					newIDEntry->value.vtiny = TI_TINY_DEFAULT;
					newIDEntry->value.vsymb->len = TI_SYMB_DEFAULT;
					newIDEntry->parameters.count = 1;
					newIDEntry->parameters.typeofparameter = IT::SYMB;
					strcpy_s(newIDEntry->value.vsymb->str, "");
					newIDEntry->idxfirstLE = currentLine;

					IT::Add(*newIDTable, *newIDEntry);

					LT::Entry* newLTEntry = new LT::Entry{ LEX_LIBFUNC, currentLine, IT::IsId(idtable, token) , 1 };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					delete newIDEntry;
					continue;
				}
				FST::FST FSTSymbtotiny(token, FST_SYMBTOTINY);
				if (FST::execute(FSTSymbtotiny)) {
					idType = IT::B;
					dataType = IT::TINY;
					IT::Entry* newIDEntry = new IT::Entry{};
					strcpy_s(newIDEntry->id, token);
					newIDEntry->idtype = idType;
					newIDEntry->iddatatype = dataType;
					newIDEntry->value.vtiny = TI_TINY_DEFAULT;
					newIDEntry->value.vsymb->len = TI_SYMB_DEFAULT;
					newIDEntry->parameters.count = 1;
					newIDEntry->parameters.typeofparameter = IT::SYMB;
					strcpy_s(newIDEntry->value.vsymb->str, "");
					newIDEntry->idxfirstLE = currentLine;
					IT::Add(*newIDTable, *newIDEntry);

					LT::Entry *newLTEntry = new LT::Entry{ LEX_LIBFUNC, currentLine, IT::IsId(idtable, token) , 1 };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					delete newIDEntry;
					continue;
				}
				FST::FST FSTLogicalLiteralTrue(token, FST_TRUE);
				FST::FST FSTLogicalLiteralFalse(token, FST_FALSE);
				if (FST::execute(FSTLogicalLiteralFalse) || FST::execute(FSTLogicalLiteralTrue)) {
					IT::Entry* newIDEntry = new IT::Entry{};
					strcpy_s(newIDEntry->id, EMPTY_LITERAL);
					newIDEntry->iddatatype = IT::LGCL;
					newIDEntry->idtype = IT::L;
					strcpy_s(newIDEntry->value.vlogical, token);
					for (int i = 0; i < newIDTable->size; i++) {
						if (strcmp((*newIDTable).table[i].value.vlogical, newIDEntry->value.vlogical) == 0) {
							check = true;
							break;
						}
						else check = false;
					}
					newIDEntry->idxfirstLE = currentLine;
					if (!check) {
						IT::Add(*newIDTable, *newIDEntry);
					}
					LT::Entry *newLTEntry = new LT::Entry{ LEX_LITERAL, currentLine, idtable.size - 1 };
					strcpy_s(newLTEntry->buf, token);
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					delete newIDEntry;
					continue;
				}
				//HACK проверить, правильно ли работает 0dec, 09hex
				FST::FST FSTTinyLiteral10(token, FST_TINYLITERAL10);
				FST::FST FSTTinyLiteral8(token, FST_TINYLITERAL8);
				if (FST::execute(FSTTinyLiteral10) || FST::execute(FSTTinyLiteral8)) {
					int bufNum = std::strtol(token, NULL, 0); //HACK перевод в 8-ричную 
					//Деление на 0 тут не проверить, так как может быть выражение
					IT::Entry* newIDEntry = new IT::Entry{};
					strcpy_s(newIDEntry->id, EMPTY_LITERAL);
					newIDEntry->iddatatype = IT::TINY;
					newIDEntry->idtype = IT::L;
					if (bufNum > MAXTINY || bufNum < MINTINY)	//TINY
						throw ERROR_THROW_IN(309, currentLine, currentColumn);
					newIDEntry->value.vtiny = (int)bufNum;
					strcpy_s(newIDEntry->value.vsymb->str, token);
					for (int i = 0; i < newIDTable->size; i++) { //не добавляем если уже встречался
						if (newIDEntry->value.vtiny == (*newIDTable).table[i].value.vtiny) {
							check = true;
							break;
						}
						else  check = false;
					}
					newIDEntry->idxfirstLE = currentLine;
					if (!check)
						IT::Add(*newIDTable, *newIDEntry);
					LT::Entry *newLTEntry = new LT::Entry{ LEX_LITERAL, currentLine, idtable.size-1 };
					strcpy_s(newLTEntry->buf, token);
					LT::Add(*newLexTable,* newLTEntry);
					delete newLTEntry;
					delete newIDEntry;
					continue;
				}
				FST::FST FSTSymbolicLiteral(token, FST_SYMBOLICLITERAL);
				if (FST::execute(FSTSymbolicLiteral)) {

					IT::Entry* newIDEntry = new IT::Entry{};
					strcpy_s(newIDEntry->id, EMPTY_LITERAL);
					newIDEntry->iddatatype = IT::SYMB;
					newIDEntry->idtype = IT::L;
					if (strlen(token) > SYMBMAXLEN) //max длина строки будет
						throw ERROR_THROW_IN(310, currentLine, currentColumn);
					newIDEntry->value.vsymb->len = strlen(token);
					strcpy_s(newIDEntry->value.vsymb->str, token);
					for (int i = 0; i < newIDTable->size; i++)
					{
						if (strcmp(newIDEntry->value.vsymb->str, (*newIDTable).table[i].value.vsymb->str) == 0)
						{

							check = true;
							break;
						}
						else check = false;
					}
					newIDEntry->idxfirstLE = currentLine;
					if (!check)
					{
						IT::Add(*newIDTable, *newIDEntry);
					}

					LT::Entry *newLTEntry = new  LT::Entry{ LEX_LITERAL, currentLine, idtable.size - 1 };
					strcpy_s(newLTEntry->buf, token);
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					delete newIDEntry;
					continue;
				}
				FST::FST FSTEquality(token, FST_EQUALITY);
				if (FST::execute(FSTEquality)) {
					LT::Entry *newLTEntry = new LT::Entry{ LEX_EQUALITY, currentLine, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTCompare(token, FST_COMPARE);
				if (FST::execute(FSTCompare)) {
					LT::Entry *newLTEntry = new LT::Entry{ LEX_COMPARE, currentLine, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTPlus(token, FST_PLUS);
				if (FST::execute(FSTPlus)) {
					LT::Entry* newLTEntry = new LT::Entry{ LEX_PLUS, currentLine, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTMinus(token, FST_MINUS);
				if (FST::execute(FSTMinus)) {
					LT::Entry* newLTEntry = new  LT::Entry{ LEX_MINUS, currentLine, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTStar(token, FST_STAR);
				if (FST::execute(FSTStar)) {
					LT::Entry *newLTEntry = new  LT::Entry{ LEX_STAR, currentLine, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTDivision(token, FST_DIVISION);
				if (FST::execute(FSTDivision)) {
					LT::Entry *newLTEntry = new  LT::Entry{ LEX_DIVISION, currentLine, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTMore(token, FST_MORE);
				if (FST::execute(FSTMore)) {
					LT::Entry* newLTEntry = new  LT::Entry{ LEX_MORE, currentLine, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTLess(token, FST_LESS);
				if (FST::execute(FSTLess)) {
					LT::Entry* newLTEntry = new  LT::Entry{ LEX_LESS, currentLine, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTInequality(token, FST_INEQUALITY);
				if (FST::execute(FSTInequality)) {
					LT::Entry* newLTEntry = new  LT::Entry{ LEX_INEQUALITY, currentLine, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTLeftshift(token, FST_LEFTSHIFT);
				if (FST::execute(FSTLeftshift)) {
					LT::Entry* newLTEntry = new  LT::Entry{ LEX_LEFTSHIFT, currentLine, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTRightshift(token, FST_RIGHTSHIFT);
				if (FST::execute(FSTRightshift)) {
					LT::Entry* newLTEntry = new  LT::Entry{ LEX_RIGHTSHIFT, currentLine, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTIdentifier(token, FST_ID);
				if (FST::execute(FSTIdentifier)) {
					if (strlen(token) > ID_MAXSIZE)
						throw ERROR_THROW_IN(308, currentLine, currentColumn);
					IT::Entry* newIDEntry = new IT::Entry{};
					strcpy_s(anotherbuf, token);
					if (idType == IT::F) {
						strcpy_s(postfix, token);
						strcpy_s(newIDEntry->postfix, POSTFIXGLOBAL);
					}
					else strcpy_s(newIDEntry->postfix, postfix);
					bool isExecute = false;

					int idx = IT::IsId(idtable, token, postfix); //такая переменная имя+постфикс определена

					if (lextable.table[lextable.size - 2].lexema == LEX_SET && idx != TI_NULLIDX) //перед ней SET и она  определена? - нельзя, ошибка
						throw ERROR_THROW_IN(606, currentLine, currentColumn);

					if (idType == IT::P) {
						(idtable.table[idtable.size-1]).parameters.count++;
						(idtable.table[idtable.size-1]).parameters.typeofparameter = dataType;
					}
					else 
					{
						if (idx == TI_NULLIDX && lextable.table[lextable.size - 2].lexema != LEX_SET && lextable.table[lextable.size - 1].lexema != LEX_FUNCTION) //если не определена и мы сейчас не определяем то надо ошибку
							throw ERROR_THROW_IN(604, currentLine, currentColumn);
					}

			
					for (int i = 0; i <= (*newIDTable).size; i++)
						if (strcmp((*newIDTable).table[i].id, token) == 0)
						{
							isExecute = true;
							if (newIDTable->table[i].idtype == IT::F)
								break;
							if (strcmp((*newIDTable).table[i].postfix, newIDEntry->postfix) != 0)
								isExecute = false;
						}
					if (!isExecute) { //если переменная не объявлена	
						strcpy_s(newIDEntry->id, token);
						newIDEntry->idtype = idType;
						newIDEntry->iddatatype = dataType;
						newIDEntry->value.vtiny = TI_TINY_DEFAULT;
						newIDEntry->value.vsymb->len = TI_SYMB_DEFAULT;
						strcpy_s(newIDEntry->value.vsymb->str, "");
						newIDEntry->idxfirstLE = currentLine;
						IT::Add(*newIDTable, *newIDEntry);
					}
					LT::Entry *newLTEntry = new LT::Entry{ LEX_ID, currentLine, IT::IsId(idtable, token) };
					strcpy_s(newLTEntry->buf, token);
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					delete newIDEntry;
					continue;
				}
				throw ERROR_THROW_IN(311, currentLine, currentColumn);
			}
		}
		if (entryPoint == 0) 		throw  ERROR_THROW(602);
		if (entryPoint > 1) 		throw  ERROR_THROW(603);
	}	
}