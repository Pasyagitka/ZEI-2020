#include "Lan.h"
#include "Log.h"
#include "LT.h"
#include "IT.h"
#include "FST.h"
#include "Expr.h"

#include "SEM.h"
#define EMPTY_LITERAL "-"
//TODO: сделать всё в одном стиле
//TODO: проверить все ошибки
namespace Lan
{
	void Analysis(char inText[], Log::LOG, LT::LexTable& lextable, IT::IdTable& idtable)
	{
		int IDindex = 0;
		int currentLine = 1, currentColumn = 1, sizeofbuf = 0;
		bool linkflag(false), TokenIsCommited(false), doubleid(false), newflag(false), secondflag(false), flag(false);
		bool quoteFlag(false);

		char postfix[LT_MAXSIZE];
		char buffer[LT_MAXSIZE];
		char newbuf[LT_MAXSIZE];
		char anotherbuf[LT_MAXSIZE];

		LT::LexTable* newLexTable = &lextable;
		IT::IdTable* newIDTable = &idtable;
		IT::IDDATATYPE dataType;
		IT::IDTYPE idType;

		for (int i = 0; i < strlen(inText); i++)
		{
			buffer[sizeofbuf] = inText[i];
			if (inText[i] == LEX_QUOTE)
				quoteFlag = !quoteFlag;

			sizeofbuf++;
			linkflag = false;
			secondflag = false;
			TokenIsCommited = false;
			if (newflag)
			{
				currentLine++;
				currentColumn = 1;
				newflag = false;
			}//TODO: добавить знаки,чтоб выражения х=х распознавались правильно +-=пробел*/<>
			if (inText[i] == LEX_SPACE || inText[i] == LEX_ENDL || inText[i] == LEX_POINT || inText[i] == LEX_COMMA || inText[i] == LEX_EXCLAMATION || inText[i] == LEX_LEFTHESIS || inText[i] == LEX_RIGHTHESIS || inText[i] == LEX_RIGHTBRACE || inText[i] == LEX_LEFTBRACE || inText[i] == LEX_COMMA
				|| inText[i + 1] == LEX_MINUS || inText[i + 1] == LEX_PLUS || inText[i + 1] == LEX_EQUALITY || inText[i + 1] == LEX_STAR || inText[i + 1] == LEX_SLASH || inText[i + 1] == LEX_MORE || inText[i + 1] ==  LEX_LESS
				|| inText[i] == LEX_MINUS || inText[i] == LEX_PLUS || inText[i] == LEX_EQUALITY || inText[i] == LEX_STAR || inText[i] == LEX_SLASH || inText[i] == LEX_MORE || inText[i] == LEX_LESS
				)
			{
				if (inText[i] == LEX_ENDL)	newflag = true;

				if (quoteFlag) 	continue;

				if (inText[i] == LEX_EXCLAMATION || inText[i] == LEX_POINT || inText[i] == LEX_LEFTHESIS || inText[i] == LEX_RIGHTHESIS || inText[i] == LEX_RIGHTBRACE || inText[i] == LEX_LEFTBRACE || inText[i] == LEX_COMMA)	{
					newbuf[0] = buffer[sizeofbuf - 1];
					newbuf[1] = LEX_END;
					secondflag = true;
				}
				if (sizeofbuf == 1)	{
					buffer[sizeofbuf] = LEX_END;
				}
				else
					if (!quoteFlag) buffer[sizeofbuf - 1] = LEX_END;

				sizeofbuf = 0;
				TokenIsCommited = true;
				if (buffer[sizeofbuf] == LEX_SPACE || buffer[sizeofbuf] == LEX_ENDL)
					continue;
			}
			currentColumn++;
			if (TokenIsCommited)	{
				FST::FST FSTTiny(buffer, FST_TINY);
					if (FST::execute(FSTTiny))	{
						LT::Entry newLTEntry = { LEX_TINY , currentLine };
						strcpy_s(newLTEntry.buf, buffer);
						LT::Add(*newLexTable, newLTEntry);
						dataType = IT::TINY;
						idType = IT::V;
						linkflag = true;
					}
				FST::FST FSTSymbolic(buffer, FST_SYMBOLIC);
					if (FST::execute(FSTSymbolic)) 	{
						LT::Entry newLTEntry = { LEX_SYMBOLIC, currentLine };
						strcpy_s(newLTEntry.buf, buffer);
						LT::Add(*newLexTable, newLTEntry);
						dataType = IT::SYMB;
						idType = IT::V;
						linkflag = true;
					}
				FST::FST FSTLogical(buffer, FST_LOGICAL);
					if (FST::execute(FSTLogical))	{
						LT::Entry newLTEntry = { LEX_LOGICAL, currentLine };
						strcpy_s(newLTEntry.buf, buffer);
						LT::Add(*newLexTable, newLTEntry);
						dataType = IT::LGCL;
						idType = IT::V;
						linkflag = true;
					}
				FST::FST FSTFunc(buffer, FST_FUNC);
					if (FST::execute(FSTFunc)) {
						LT::Entry newLTEntry = { LEX_FUNCTION, currentLine };
						LT::Add(*newLexTable, newLTEntry);
						idType = IT::F;
						linkflag = true;
					}
				FST::FST FSTGiveback(buffer, FST_GIVEBACK);
					if (FST::execute(FSTGiveback)) {
						LT::Entry newLTEntry = { LEX_GIVEBACK, currentLine };
						LT::Add(*newLexTable, newLTEntry);
						idType = IT::V;
						linkflag = true;
					}
				FST::FST FSTSet(buffer, FST_SET);
					if (FST::execute(FSTSet)) {
						LT::Entry newLTEntry = { LEX_SET, currentLine };
						LT::Add(*newLexTable, newLTEntry);
						linkflag = true;
					}
				FST::FST FSTShow(buffer, FST_SHOW);
					if (FST::execute(FSTShow))	{
						LT::Entry newLTEntry = { LEX_SHOW, currentLine, IDindex, 1 };
						LT::Add(*newLexTable, newLTEntry);
						idType = IT::B;

						IT::Entry newIDEntry;
						strcpy_s(newIDEntry.id, buffer);
						newIDEntry.idtype = idType;
						newIDEntry.iddatatype = dataType;
						newIDEntry.value.vint = TI_INT_DEFAULT;
						newIDEntry.value.vstr->len = TI_STR_DEFAULT;
						strcpy_s(newIDEntry.value.vstr->str, "");
						newIDEntry.idxfirstLE = currentLine;
						IT::Add(*newIDTable, newIDEntry);
						linkflag = true;
					}
				FST::FST FSTLib(buffer, FST_LIB);
					if (FST::execute(FSTLib))	{
						LT::Entry newLTEntry = { LEX_LIB, currentLine };
						LT::Add(*newLexTable, newLTEntry);
						strcpy_s(postfix, buffer);
						//SA::OneDvv(*ltable, flag);
						flag = true;
						linkflag = true;
					}
				FST::FST FSTWhen(buffer, FST_WHEN);
					if (FST::execute(FSTWhen))	{
						LT::Entry newLTEntry = { LEX_WHEN, currentLine };
						LT::Add(*newLexTable, newLTEntry);
						linkflag = true;
					}
				FST::FST FSTOtherwise(buffer, FST_OTHERWISE);
					if (FST::execute(FSTOtherwise)) {
						LT::Entry newLTEntry = { LEX_OTHERWISE, currentLine };
						LT::Add(*newLexTable, newLTEntry);
						linkflag = true;
					}
					//TODO: библиотечные функции в таблицу ID
				FST::FST FSTSymblen(buffer, FST_SYMBLEN);
					if (FST::execute(FSTSymblen))	{
						LT::Entry newLTEntry = { LEX_LIBFUNC, currentLine, IDindex, 1 };
						LT::Add(*newLexTable, newLTEntry);
						idType = IT::B;
						dataType = IT::SYMB;
						IT::Entry newIDEntry;
						strcpy_s(newIDEntry.id, buffer);
						newIDEntry.idtype = idType;
						newIDEntry.iddatatype = dataType;
						newIDEntry.value.vint = TI_INT_DEFAULT;
						newIDEntry.value.vstr->len = TI_STR_DEFAULT;
						strcpy_s(newIDEntry.value.vstr->str, "");
						newIDEntry.idxfirstLE = currentLine;
						IT::Add(*newIDTable, newIDEntry);
						linkflag = true;
					}
				FST::FST FSTSymbtotiny(buffer, FST_SYMBTOTINY);
					if (FST::execute(FSTSymbtotiny))	{
						LT::Entry newLTEntry = { LEX_LIBFUNC, currentLine,  IDindex, 1 };
						LT::Add(*newLexTable, newLTEntry);
						idType = IT::B;
						dataType = IT::SYMB;
						IT::Entry newIDEntry;
						strcpy_s(newIDEntry.id, buffer);
						newIDEntry.idtype = idType;
						newIDEntry.iddatatype = dataType;
						newIDEntry.value.vint = TI_INT_DEFAULT;
						newIDEntry.value.vstr->len = TI_STR_DEFAULT;
						strcpy_s(newIDEntry.value.vstr->str, "");
						newIDEntry.idxfirstLE = currentLine;
						IT::Add(*newIDTable, newIDEntry);
						linkflag = true;
					}
					//TODO: добавление правильного индекса в таблицу лекс
				FST::FST FSTLogicalLiteralTrue(buffer, FST_TRUE);
				FST::FST FSTLogicalLiteralFalse(buffer, FST_FALSE);
					if (FST::execute(FSTLogicalLiteralFalse) || FST::execute(FSTLogicalLiteralTrue))	{
						IT::Entry iEntry;
						strcpy_s(iEntry.id, EMPTY_LITERAL);
						iEntry.iddatatype = IT::LGCL;
						iEntry.idtype = IT::L;
						strcpy_s(iEntry.value.vstr->str, buffer);
						strcpy_s(iEntry.value.vbool, buffer);
						for (int i = 0; i < newIDTable->size; i++)	{
							if (strcmp((*newIDTable).table[i].value.vbool, iEntry.value.vbool) == 0)	{
								doubleid = true;
								break;
							}
							else doubleid = false;
						}
						if (doubleid) continue;
						LT::Entry newLTEntry = { LEX_LITERAL, currentLine, IDindex };
						newLTEntry.sign = -1;
						iEntry.idxfirstLE = currentLine;
						strcpy_s(newLTEntry.buf, buffer);
						LT::Add(*newLexTable, newLTEntry);
						linkflag = true;
					}
				//TODO: лексемы сдвига

				FST::FST FSTIdentifier(buffer, FST_ID);
					if (!linkflag)
						if (FST::execute(FSTIdentifier))	{
							if (strlen(buffer) > ID_MAXSIZE)	throw ERROR_THROW_IN(308, currentLine, currentColumn);

							int idx = IT::IsId(idtable, buffer);
							if (idx != TI_NULLIDX)
							{
								LT::Entry newLTEntry = { LEX_ID, currentLine, idx };
								strcpy_s(newLTEntry.buf, buffer);
								LT::Add(*newLexTable, newLTEntry);
							}
							else {
								LT::Entry newLTEntry = { LEX_ID, IDindex, idx };
								strcpy_s(newLTEntry.buf, buffer);
								LT::Add(*newLexTable, newLTEntry);
							}

							IT::Entry iEntry;
							strcpy_s(anotherbuf, buffer);
							if (idType == IT::F)
								strcpy_s(postfix, buffer);
							strcpy_s(iEntry.postfix, postfix);
							bool isExecute = false;
							//SA::Proverka(*ltable, *itable);
							//SA::Pereobyavl(*ltable, *itable, buffer, postfix, line, col);
							for (int i = 0; i <= (*newIDTable).size; i++)
								if (strcmp((*newIDTable).table[i].id, buffer) == 0)
								{
									isExecute = true;
									if (newIDTable->table[i].idtype == IT::F)
										break;
									if (strcmp((*newIDTable).table[i].postfix, iEntry.postfix) != 0)
										isExecute = false;
								}
							if (!isExecute)			{ //если переменная не объявлена	
								strcpy_s(iEntry.id, buffer);
								iEntry.idtype = idType;
								iEntry.iddatatype = dataType;
								iEntry.value.vint = TI_INT_DEFAULT;
								iEntry.value.vstr->len = TI_STR_DEFAULT;
								strcpy_s(iEntry.value.vstr->str, "");
								iEntry.idxfirstLE = currentLine;
								IT::Add(*newIDTable, iEntry);
							}
							linkflag = true;
						}
				FST::FST FSTTinyLiteral(buffer, FST_TINYLITERAL);
						if (FST::execute(FSTTinyLiteral))	{
							long double bufNum = std::atoi(buffer);
							
							//SA::ZeroDivision(*ltable, buffer);
							IT::Entry iEntry;
							strcpy_s(iEntry.id, EMPTY_LITERAL);
							iEntry.iddatatype = IT::TINY;
							iEntry.idtype = IT::L;
							if (bufNum >= INT_MAX)	//TINY
								throw ERROR_THROW_IN(309, currentLine, currentColumn);
							iEntry.value.vint = (int)bufNum;
							strcpy_s(iEntry.value.vstr->str, buffer);
							for (int i = 0; i < newIDTable->size; i++)	{
								if (iEntry.value.vint == (*newIDTable).table[i].value.vint) {
									doubleid = true;
									break;
								}
								else  doubleid = false;
							}
							iEntry.idxfirstLE = currentLine;
							if (doubleid) continue;

							LT::Entry newLTEntry = { LEX_LITERAL, currentLine, IDindex };
							newLTEntry.sign = bufNum;
							strcpy_s(newLTEntry.buf, buffer);
							LT::Add(*newLexTable, newLTEntry);
							IT::Add(*newIDTable, iEntry); 
							linkflag = true;
						}
				FST::FST FSTSymbolicLiteral(buffer, FST_SYMBOLICLITERAL);
					if (FST::execute(FSTSymbolicLiteral))	{
						
						IT::Entry iEntry;
						strcpy_s(iEntry.id, EMPTY_LITERAL);
						iEntry.iddatatype = IT::SYMB;
						iEntry.idtype = IT::L;
						if (strlen(buffer) > 128) //max длина строки будет
							throw ERROR_THROW_IN(310, currentLine, currentColumn);
						iEntry.value.vstr->len = strlen(buffer);
						strcpy_s(iEntry.value.vstr->str, buffer);
						for (int i = 0; i < newIDTable->size; i++)
						{
							if (strcmp(iEntry.value.vstr->str, (*newIDTable).table[i].value.vstr->str) == 0)
							{

								doubleid = true;
								break;
							}
							else doubleid = false;
						}
						iEntry.idxfirstLE = currentLine;
						if (doubleid) continue;
					
						LT::Entry newLTEntry = { LEX_LITERAL, currentLine, IDindex };
						newLTEntry.sign = -1;
						strcpy_s(newLTEntry.buf, buffer);
						LT::Add(*newLexTable, newLTEntry);
						IT::Add(*newIDTable, iEntry);
						
						linkflag = true;
					}

					FST::FST FSTExclamation(buffer, FST_EXCLAMATION);
					if (FST::execute(FSTExclamation)) {
						LT::Entry newLTEntry = { LEX_EXCLAMATION, currentLine };
						LT::Add(*newLexTable, newLTEntry);
						continue;
					}
					FST::FST FSTPoint(buffer, FST_POINT);
					if (FST::execute(FSTPoint)) {
						LT::Entry newLTEntry = { LEX_POINT , currentLine };
						LT::Add(*newLexTable, newLTEntry);
						continue;
					}
					FST::FST FSTLefthesis(buffer, FST_LEFTHESIS);
					if (FST::execute(FSTLefthesis)) {
						LT::Entry newLTEntry = { LEX_LEFTHESIS , currentLine };
						LT::Add(*newLexTable, newLTEntry);
						continue;
					}
					FST::FST FSTRighthesis(buffer, FST_RIGHTHESIS);
					if (FST::execute(FSTRighthesis)) {
						LT::Entry newLTEntry = { LEX_RIGHTHESIS , currentLine };
						LT::Add(*newLexTable, newLTEntry);
						continue;
					}
					FST::FST FSTRightbrace(buffer, FST_RIGHTBRACE);
					if (FST::execute(FSTRightbrace)) {
						LT::Entry newLTEntry = { LEX_RIGHTBRACE , currentLine };
						LT::Add(*newLexTable, newLTEntry);
						continue;
					}
					FST::FST FSTLeftbrace(buffer, FST_LEFTBRACE);
					if (FST::execute(FSTLeftbrace)) {
						LT::Entry newLTEntry = { LEX_LEFTBRACE , currentLine };
						LT::Add(*newLexTable, newLTEntry);
						continue;
					}
					FST::FST FSTComma(buffer, FST_COMMA);
					if (FST::execute(FSTComma)) {
						LT::Entry newLTEntry = { LEX_COMMA, currentLine };
						LT::Add(*newLexTable, newLTEntry);
						continue;
					}
					FST::FST FSTMore(buffer, FST_MORE);
					if (FST::execute(FSTMore)) {
						LT::Entry newLTEntry = { LEX_MORE, currentLine };
						newLTEntry.sign = 2;
						LT::Add(*newLexTable, newLTEntry);
						linkflag = true;
					}
					FST::FST FSTLess(buffer, FST_LESS);
					if (FST::execute(FSTLess)) {
						LT::Entry newLTEntry = { LEX_LESS, currentLine };
						newLTEntry.sign = 2;
						LT::Add(*newLexTable, newLTEntry);
						linkflag = true;
					}
					FST::FST FSTEquality(buffer, FST_EQUALITY);
					if (FST::execute(FSTEquality)) {
						LT::Entry newLTEntry = { LEX_EQUALITY, currentLine };
						newLTEntry.sign = 2;
						LT::Add(*newLexTable, newLTEntry);
						linkflag = true;
					}
					FST::FST FSTCompare(buffer, FST_COMPARE);
					if (FST::execute(FSTCompare)) {
						LT::Entry newLTEntry = { LEX_COMPARE, currentLine };
						LT::Add(*newLexTable, newLTEntry);
						linkflag = true;
					}
					FST::FST FSTPlus(buffer, FST_PLUS);
					if (FST::execute(FSTPlus)) {
						LT::Entry newLTEntry = { LEX_PLUS, currentLine };
						newLTEntry.sign = 1;
						LT::Add(*newLexTable, newLTEntry);
						linkflag = true;
					}
					FST::FST FSTMinus(buffer, FST_MINUS);
					if (FST::execute(FSTMinus)) {
						LT::Entry newLTEntry = { LEX_MINUS, currentLine };
						newLTEntry.sign = 1;
						LT::Add(*newLexTable, newLTEntry);
						linkflag = true;
					}
					FST::FST FSTStar(buffer, FST_STAR);
					if (FST::execute(FSTStar)) {
						LT::Entry newLTEntry = { LEX_STAR, currentLine };
						newLTEntry.sign = 1;
						LT::Add(*newLexTable, newLTEntry);
						linkflag = true;
					}
					FST::FST FSTSlash(buffer, FST_SLASH);
					if (FST::execute(FSTSlash)) {
						LT::Entry newLTEntry = { LEX_SLASH, currentLine };
						newLTEntry.sign = 1;
						LT::Add(*newLexTable, newLTEntry);
						linkflag = true;
					}
			}

		if (linkflag)
			if (secondflag)
			{
				FST::FST FSTExclamation(newbuf, FST_EXCLAMATION);
					if (FST::execute(FSTExclamation)) {
						LT::Entry newLTEntry = { LEX_EXCLAMATION, currentLine };
						LT::Add(*newLexTable, newLTEntry);
						continue;
					}
				FST::FST FSTPoint(newbuf, FST_POINT);
					if (FST::execute(FSTPoint)) {
						LT::Entry newLTEntry = { LEX_POINT , currentLine };
						LT::Add(*newLexTable, newLTEntry);
						continue;
					}
				FST::FST FSTLefthesis(newbuf, FST_LEFTHESIS);
					if (FST::execute(FSTLefthesis)) 	{
						LT::Entry newLTEntry = { LEX_LEFTHESIS , currentLine };
						LT::Add(*newLexTable, newLTEntry);
						continue;
					}
				FST::FST FSTRighthesis(newbuf, FST_RIGHTHESIS);
					if (FST::execute(FSTRighthesis)) 	{
						LT::Entry newLTEntry = { LEX_RIGHTHESIS , currentLine };
						LT::Add(*newLexTable, newLTEntry);
						continue;
					}
				FST::FST FSTRightbrace(newbuf, FST_RIGHTBRACE);
					if (FST::execute(FSTRightbrace)) {
						LT::Entry newLTEntry = { LEX_RIGHTBRACE , currentLine };
						LT::Add(*newLexTable, newLTEntry);
						continue;
					}
				FST::FST FSTLeftbrace(newbuf, FST_LEFTBRACE);
					if (FST::execute(FSTLeftbrace)) {
						LT::Entry newLTEntry = { LEX_LEFTBRACE , currentLine };
						LT::Add(*newLexTable, newLTEntry);
						continue;
					}
				FST::FST FSTComma(newbuf, FST_COMMA);
					if (FST::execute(FSTComma)) {
						LT::Entry newLTEntry = { LEX_COMMA, currentLine };
						LT::Add(*newLexTable, newLTEntry);
						continue;
					}
			}
		}
	}
}