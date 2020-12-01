#include "Lan.h"
#include "Log.h"
#include "LT.h"
#include "IT.h"
#include "FST.h"
#include "Expr.h"

#include "SEM.h"
#define EMPTY_LITERAL "-"
namespace Lan
{
	void Analysis(char inText[], Log::LOG, LT::LexTable& lextable, IT::IdTable& idtable)
	{
		int line = 0, col = 0, sizeofbuf = 0;
		bool linkflag(false), provsep(false), proverka(false), newflag(false), secondflag(false), flag(false);
		bool quoteFlag(false);

		char postfix[LT_MAXSIZE];
		char buffer[LT_MAXSIZE];
		char newbuf[LT_MAXSIZE];
		char anotherbuf[LT_MAXSIZE];

		LT::LexTable* ltable = &lextable;
		IT::IdTable* itable = &idtable;
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
			provsep = false;
			if (newflag)
			{
				line++;
				col = 0;
				newflag = false;
			}//TODO: добавить знаки,чтоб выражения х=х распознавались правильно +-=пробел*/<>
			if (inText[i] == LEX_SPACE || inText[i] == LEX_ENDL || inText[i] == LEX_POINT || inText[i] == LEX_COMMA || inText[i] == LEX_LEFTHESIS || inText[i] == LEX_RIGHTHESIS || inText[i] == LEX_RIGHTBRACE || inText[i] == LEX_LEFTBRACE || inText[i] == LEX_COMMA
				|| inText[i + 1] == LEX_MINUS || inText[i + 1] == LEX_PLUS || inText[i + 1] == LEX_EQUALITY || inText[i + 1] == LEX_STAR || inText[i + 1] == LEX_SLASH || inText[i + 1] == LEX_MORE || inText[i + 1] ==  LEX_LESS 
				|| inText[i] == LEX_MINUS || inText[i] == LEX_PLUS || inText[i] == LEX_EQUALITY || inText[i] == LEX_STAR || inText[i] == LEX_SLASH || inText[i] == LEX_MORE || inText[i] == LEX_LESS
				)
			{
				if (inText[i] == LEX_ENDL)
					newflag = true;

				if (quoteFlag) 
					continue;

				if (inText[i] == LEX_POINT || inText[i] == LEX_LEFTHESIS || inText[i] == LEX_RIGHTHESIS || inText[i] == LEX_RIGHTBRACE || inText[i] == LEX_LEFTBRACE || inText[i] == LEX_COMMA)	{
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
				provsep = true;
				if (buffer[sizeofbuf] == LEX_SPACE || buffer[sizeofbuf] == LEX_ENDL)
					continue;
			}
			col++;
			if (provsep)
			{
				FST::FST FSTTiny(buffer, FST_TINY);
				if (FST::execute(FSTTiny))
				{
					LT::Entry lEntry = { LEX_TINY , line, col };
					strcpy_s(lEntry.buf, buffer);
					LT::Add(*ltable, lEntry);
					dataType = IT::TINY;
					idType = IT::V;
					linkflag = true;
				}
				FST::FST FSTSymbolic(buffer, FST_SYMBOLIC);
				if (FST::execute(FSTSymbolic))
				{
					LT::Entry lEntry = { LEX_SYMBOLIC, line, col };
					strcpy_s(lEntry.buf, buffer);
					LT::Add(*ltable, lEntry);
					dataType = IT::SYMB;
					idType = IT::V;
					linkflag = true;
				}
				FST::FST FSTLogical(buffer, FST_LOGICAL);
				if (FST::execute(FSTLogical))
				{
					LT::Entry lEntry = { LEX_LOGICAL, line, col };
					strcpy_s(lEntry.buf, buffer);
					LT::Add(*ltable, lEntry);
					dataType = IT::LGCL;
					idType = IT::V;
					linkflag = true;
				}
				FST::FST FSTFunc(buffer, FST_FUNC);
				if (FST::execute(FSTFunc))
				{
					LT::Entry lEntry = { LEX_FUNCTION, line, col };
					LT::Add(*ltable, lEntry);
					idType = IT::F;
					linkflag = true;
				}
				FST::FST FSTGiveback(buffer, FST_GIVEBACK);
				if (FST::execute(FSTGiveback))
				{
					LT::Entry lEntry = { LEX_GIVEBACK, line, col };
					LT::Add(*ltable, lEntry);
					idType = IT::V;
					linkflag = true;
				}
				FST::FST FSTShow(buffer, FST_SHOW);
				if (FST::execute(FSTShow))
				{
					LT::Entry lEntry = { LEX_SHOW, line, col };
					LT::Add(*ltable, lEntry);
					idType = IT::V;
					linkflag = true;
				}
				FST::FST FSTLib(buffer, FST_LIB);
				if (FST::execute(FSTLib))
				{
					LT::Entry lEntry = { LEX_LIB, line, col };
					LT::Add(*ltable, lEntry);
					strcpy_s(postfix, buffer);
					//SA::OneDvv(*ltable, flag);
					flag = true;
					linkflag = true;
				}
				FST::FST FSTWhen(buffer, FST_WHEN);
				if (FST::execute(FSTWhen))
				{
					LT::Entry lEntry = { LEX_WHEN, line, col };
					LT::Add(*ltable, lEntry);
					linkflag = true;
				}
				FST::FST FSTOtherwise(buffer, FST_OTHERWISE);
				if (FST::execute(FSTOtherwise))
				{
					LT::Entry lEntry = { LEX_OTHERWISE, line, col };
					LT::Add(*ltable, lEntry);
					linkflag = true;
				}
				FST::FST FSTSymblen(buffer, FST_SYMBLEN);
				if (FST::execute(FSTSymblen))
				{
					LT::Entry lEntry = { LEX_LIBFUNC, line, col, 1 };
					LT::Add(*ltable, lEntry);
					linkflag = true;
				}
				FST::FST FSTSymbtotiny(buffer, FST_SYMBTOTINY);
				if (FST::execute(FSTSymbtotiny))
				{
					LT::Entry lEntry = { LEX_LIBFUNC, line, col, 2 };
					LT::Add(*ltable, lEntry);
					linkflag = true;
				}
				FST::FST FSTLogicalLiteralTrue(buffer, FST_TRUE);
				FST::FST FSTLogicalLiteralFalse(buffer, FST_FALSE);
				if (FST::execute(FSTLogicalLiteralFalse) || FST::execute(FSTLogicalLiteralTrue))
				{
					LT::Entry lEntry = { LEX_LITERAL, line, col };
					lEntry.sign = -1;
					strcpy_s(lEntry.buf, buffer);
					LT::Add(*ltable, lEntry);
					IT::Entry iEntry;
					strcpy_s(iEntry.id, EMPTY_LITERAL);
					iEntry.iddatatype = IT::LGCL;
					iEntry.idtype = IT::L;
					strcpy_s(iEntry.value.vstr->str, buffer);
					strcpy_s(iEntry.value.vbool, buffer);
					for (int i = 0; i < itable->size; i++)
					{
						if (strcmp((*itable).table[i].value.vbool, iEntry.value.vbool) == 0)
						{
							proverka = true;
							break;
						}
						else proverka = false;
					}
					iEntry.idxfirstLE = line;
					if (!proverka)
					{
						IT::Add(*itable, iEntry);
					}
					linkflag = true;
				}
				FST::FST FSTIdentifier(buffer, FST_ID);
				if (!linkflag)
					if (FST::execute(FSTIdentifier))
					{
						if (strlen(buffer) > 20)
							throw ERROR_THROW(122, line, col);
						LT::Entry lEntry = { LEX_ID, line, col };
						strcpy_s(lEntry.buf, buffer);
						LT::Add(*ltable, lEntry);
						IT::Entry iEntry;
						strcpy_s(anotherbuf, buffer);
						if (idType == IT::F)
						{
							strcpy_s(postfix, buffer);
						}
						strcpy_s(iEntry.postfix, postfix);
						bool isExecute = false;
						//SA::Proverka(*ltable, *itable);
						//SA::Pereobyavl(*ltable, *itable, buffer, postfix, line, col);
						for (int i = 0; i <= (*itable).size; i++)
						{
							if (strcmp((*itable).table[i].id, buffer) == 0)
							{
								isExecute = true;
								if (itable->table[i].idtype == IT::F)
								{
									break;
								}
								if (strcmp((*itable).table[i].postfix, iEntry.postfix) != 0)
								{
									isExecute = false;
								}

							}
						}
						if (!isExecute)						//если переменная не объявлена
						{
							strcpy_s(iEntry.id, buffer);
							iEntry.idtype = idType;
							iEntry.iddatatype = dataType;
							iEntry.value.vint = TI_INT_DEFAULT;
							iEntry.value.vstr->len = TI_STR_DEFAULT;
							strcpy_s(iEntry.value.vstr->str, "");
							iEntry.idxfirstLE = line;
							IT::Add(*itable, iEntry);
						}
						linkflag = true;
					}
					FST::FST FSTTinyLiteral(buffer, FST_TINYLITERAL);
					if (FST::execute(FSTTinyLiteral))
					{
						long double bufNum = std::atoi(buffer);
						LT::Entry lEntry = { LEX_LITERAL, line, col };
						lEntry.sign = bufNum;
						strcpy_s(lEntry.buf, buffer);
						LT::Add(*ltable, lEntry);
						//SA::ZeroDivision(*ltable, buffer);
						IT::Entry iEntry;
						strcpy_s(iEntry.id, EMPTY_LITERAL);
						iEntry.iddatatype = IT::TINY;
						iEntry.idtype = IT::L;
						if (bufNum >= INT_MAX)
						{
							throw ERROR_THROW(121, line, col);
						}
						iEntry.value.vint = (int)bufNum;
						strcpy_s(iEntry.value.vstr->str, buffer);
						for (int i = 0; i < itable->size; i++)
						{
							if (iEntry.value.vint == (*itable).table[i].value.vint)
							{
								proverka = true;
								break;
							}
							else  proverka = false;
						}
						iEntry.idxfirstLE = line;
						if (!proverka)
						{
							IT::Add(*itable, iEntry);
						}
						linkflag = true;
					}
					FST::FST FSTSymbolicLiteral(buffer, FST_SYMBOLICLITERAL);
					if (FST::execute(FSTSymbolicLiteral))
					{
						LT::Entry lEntry = { LEX_LITERAL, line, col };
						lEntry.sign = -1;
						strcpy_s(lEntry.buf, buffer);
						LT::Add(*ltable, lEntry);
						IT::Entry iEntry;
						strcpy_s(iEntry.id, EMPTY_LITERAL);
						iEntry.iddatatype = IT::SYMB;
						iEntry.idtype = IT::L;
						if (strlen(buffer) > 255)
							throw ERROR_THROW(120, line, col);
						iEntry.value.vstr->len = strlen(buffer);
						strcpy_s(iEntry.value.vstr->str, buffer);
						for (int i = 0; i < itable->size; i++)
						{
							if (strcmp(iEntry.value.vstr->str, (*itable).table[i].value.vstr->str) == 0)
							{

								proverka = true;
								break;
							}
							else proverka = false;
						}
						iEntry.idxfirstLE = line;
						if (!proverka)
						{
							IT::Add(*itable, iEntry);
						}
						linkflag = true;
					}
					FST::FST FSTPoint(buffer, FST_POINT);
					if (FST::execute(FSTPoint))
					{
						LT::Entry lEntry = { LEX_POINT, line, col };
						LT::Add(*ltable, lEntry);
						continue;
					}
					FST::FST FSTComma(buffer, FST_COMMA);
					if (FST::execute(FSTComma))
					{
						LT::Entry lEntry = { LEX_COMMA, line, col };
						lEntry.priority = 1;
						LT::Add(*ltable, lEntry);
						continue;
					}
					FST::FST FSTLeftBrace(buffer, FST_LEFTBRACE);
					if (FST::execute(FSTLeftBrace))
					{
						LT::Entry lEntry = { LEX_LEFTBRACE, line, col };
						LT::Add(*ltable, lEntry);
						continue;
					}
					FST::FST FSTRightBrace(buffer, FST_RIGHTBRACE);
					if (FST::execute(FSTRightBrace))
					{
						LT::Entry lEntry = { LEX_RIGHTBRACE, line, col };
						LT::Add(*ltable, lEntry);
						continue;
					}
					FST::FST FSTLeftThesis(buffer, FST_LEFTHESIS);
					if (FST::execute(FSTLeftThesis))
					{
						LT::Entry lEntry = { LEX_LEFTHESIS, line, col };
						lEntry.priority = 0;
						LT::Add(*ltable, lEntry);
						continue;
					}
					FST::FST FSTRightThesis(buffer, FST_RIGHTHESIS);
					if (FST::execute(FSTRightThesis))
					{
						LT::Entry lEntry = { LEX_RIGHTHESIS, line, col };
						lEntry.priority = 0;
						LT::Add(*ltable, lEntry);
						continue;
					}
					FST::FST FSTMore(buffer, FST_MORE);
					if (FST::execute(FSTMore))
					{
						LT::Entry lEntry = { LEX_MORE, line, col };
						lEntry.sign = 2;
						LT::Add(*ltable, lEntry);
						linkflag = true;
					}
					FST::FST FSTLess(buffer, FST_LESS);
					if (FST::execute(FSTLess))
					{
						LT::Entry lEntry = { LEX_LESS, line, col };
						lEntry.sign = 2;
						LT::Add(*ltable, lEntry);
						linkflag = true;
					}
					FST::FST FSTEquality(buffer, FST_EQUALITY);
					if (FST::execute(FSTEquality))
					{
						LT::Entry lEntry = { LEX_EQUALITY, line, col };
						lEntry.sign = 2;
						LT::Add(*ltable, lEntry);
						linkflag = true;
					}
					FST::FST FSTCompare(buffer, FST_COMPARE);
					if (FST::execute(FSTCompare))
					{
						LT::Entry lEntry = { LEX_COMPARE, line, col };
						LT::Add(*ltable, lEntry);
						linkflag = true;
					}
					FST::FST FSTPlus(buffer, FST_PLUS);
					if (FST::execute(FSTPlus))
					{
						LT::Entry lEntry = { LEX_PLUS, line, col };
						lEntry.sign = 1;
						lEntry.priority = 2;
						LT::Add(*ltable, lEntry);
						linkflag = true;
					}
					FST::FST FSTMinus(buffer, FST_MINUS);
					if (FST::execute(FSTMinus))
					{
						LT::Entry lEntry = { LEX_MINUS, line, col };
						lEntry.sign = 1;
						lEntry.priority = 2;
						LT::Add(*ltable, lEntry);
						linkflag = true;
					}
					FST::FST FSTStar(buffer, FST_STAR);
					if (FST::execute(FSTStar))
					{
						LT::Entry lEntry = { LEX_STAR, line, col };
						lEntry.sign = 1;
						lEntry.priority = 3;
						LT::Add(*ltable, lEntry);
						linkflag = true;
					}
					FST::FST FSTSlash(buffer, FST_SLASH);
					if (FST::execute(FSTSlash))
					{
						LT::Entry lEntry = { LEX_SLASH, line, col };
						lEntry.sign = 1;
						lEntry.priority = 3;
						LT::Add(*ltable, lEntry);
						linkflag = true;
					}
				}

		if (linkflag)
			if (secondflag)
			{
				FST::FST FSTPoint(newbuf, FST_POINT);
				if (FST::execute(FSTPoint))
				{
					LT::Entry lEntry = { LEX_POINT , line, col };
					LT::Add(*ltable, lEntry);
					continue;
				}
				FST::FST FSTLeftThesis(newbuf, FST_LEFTHESIS);
				if (FST::execute(FSTLeftThesis))
				{
					LT::Entry lEntry = { LEX_LEFTHESIS , line, col };
					LT::Add(*ltable, lEntry);
					continue;
				}
				FST::FST FSTRightThesis(newbuf, FST_RIGHTHESIS);
				if (FST::execute(FSTRightThesis))
				{
					LT::Entry lEntry = { LEX_RIGHTHESIS , line, col };
					LT::Add(*ltable, lEntry);
					continue;
				}
				FST::FST FSTRightbrace(newbuf, FST_RIGHTBRACE);
				if (FST::execute(FSTRightbrace))
				{
					LT::Entry lEntry = { LEX_RIGHTBRACE , line, col };
					LT::Add(*ltable, lEntry);
					continue;
				}
				FST::FST FSTLeftbrace(newbuf, FST_LEFTBRACE);
				if (FST::execute(FSTLeftbrace))
				{
					LT::Entry lEntry = { LEX_LEFTBRACE , line, col };
					LT::Add(*ltable, lEntry);
					continue;
				}
				FST::FST FSTComma(newbuf, FST_COMMA);
				if (FST::execute(FSTComma))
				{
					LT::Entry lEntry = { LEX_COMMA, line, col };
					LT::Add(*ltable, lEntry);
					continue;
				}
			}
		}
	}
}