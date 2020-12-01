#include "Lan.h"
#include "Log.h"
#include "LT.h"
#include "IT.h"
#include "FST.h"
#include "Expr.h"
#include "SEM.h"
namespace Lan
{
	void Analysis(char inText[], Log::LOG, LT::LexTable& lextable, IT::IdTable& idtable)
	{
		int line = 0, col = 0, sizeofbuf = 0;
		bool linkflag(false), provsep(false), proverka(false), newflag(false), secondflag(false), flag(false);
		bool quoteFlag(false);
		char string[5] = "LTR";//еточо

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
			if (inText[i] == LEX_SPACE || inText[i] == LEX_ENDL || inText[i] == LEX_POINT || inText[i] == LEX_LEFTHESIS || inText[i] == LEX_RIGHTHESIS || inText[i] == LEX_RIGHTBRACE || inText[i] == LEX_LEFTBRACE || inText[i] == LEX_COMMA
				|| inText[i + 1] == LEX_MINUS || inText[i + 1] == LEX_PLUS || inText[i + 1] == LEX_EQUALLY || inText[i + 1] == LEX_STAR || inText[i + 1] == LEX_SLASH || inText[i + 1] == LEX_MORE || inText[i + 1]==  LEX_LESS
				|| inText[i] == LEX_MINUS || inText[i] == LEX_PLUS || inText[i] == LEX_EQUALLY || inText[i] == LEX_STAR || inText[i] == LEX_SLASH || inText[i] == LEX_MORE || inText[i] == LEX_LESS
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
				FST::FST fstint(buffer, FST_INTEGER);
				if (FST::execute(fstint))
				{
					LT::Entry lEntry = { LEX_INTEGER , line, col };
					strcpy_s(lEntry.buf, buffer);
					LT::Add(*ltable, lEntry);
					dataType = IT::INT;
					idType = IT::V;
					linkflag = true;
				}
				FST::FST fststr(buffer, FST_STRING);
				if (FST::execute(fststr))
				{
					LT::Entry lEntry = { LEX_STRING, line, col };
					strcpy_s(lEntry.buf, buffer);
					LT::Add(*ltable, lEntry);
					dataType = IT::STR;
					idType = IT::V;
					linkflag = true;
				}
				FST::FST fstbool(buffer, FST_BOOL);
				if (FST::execute(fstbool))
				{
					LT::Entry lEntry = { LEX_BOOL, line, col };
					strcpy_s(lEntry.buf, buffer);
					LT::Add(*ltable, lEntry);
					dataType = IT::BOOL;
					idType = IT::V;
					linkflag = true;
				}
				FST::FST fstfunc(buffer, FST_FUNC);
				if (FST::execute(fstfunc))
				{
					LT::Entry lEntry = { LEX_FUNCTION, line, col };
					LT::Add(*ltable, lEntry);
					idType = IT::F;
					linkflag = true;
				}
				FST::FST fstret(buffer, FST_RETURN);
				if (FST::execute(fstret))
				{
					LT::Entry lEntry = { LEX_RETURN, line, col };
					LT::Add(*ltable, lEntry);
					idType = IT::V;
					linkflag = true;
				}
				FST::FST fstprint(buffer, FST_PRINT);
				if (FST::execute(fstprint))
				{
					LT::Entry lEntry = { LEX_PRINT, line, col };
					LT::Add(*ltable, lEntry);
					idType = IT::V;
					linkflag = true;
				}
				FST::FST fstdvv(buffer, FST_DVV);
				if (FST::execute(fstdvv))
				{
					LT::Entry lEntry = { LEX_DVV, line, col };
					LT::Add(*ltable, lEntry);
					strcpy_s(postfix, buffer);
					//SA::OneDvv(*ltable, flag);
					flag = true;
					linkflag = true;
				}
				FST::FST fstif(buffer, FST_IF);
				if (FST::execute(fstif))
				{
					LT::Entry lEntry = { LEX_IF, line, col };
					LT::Add(*ltable, lEntry);
					linkflag = true;
				}
				FST::FST fstelse(buffer, FST_ELSE);
				if (FST::execute(fstelse))
				{
					LT::Entry lEntry = { LEX_ELSE, line, col };
					LT::Add(*ltable, lEntry);
					linkflag = true;
				}
				FST::FST fststrlen(buffer, FST_STRLEN);
				if (FST::execute(fststrlen))
				{
					LT::Entry lEntry = { LEX_LIBFUNC, line, col, 1 };
					LT::Add(*ltable, lEntry);
					linkflag = true;
				}
				FST::FST fstsubstr(buffer, FST_SUBSTR);
				if (FST::execute(fstsubstr))
				{
					LT::Entry lEntry = { LEX_LIBFUNC, line, col, 2 };
					LT::Add(*ltable, lEntry);
					linkflag = true;
				}
				FST::FST fstlitbool(buffer, FST_FALSE);
				FST::FST fstltbool(buffer, FST_TRUE);
				if (FST::execute(fstlitbool) || FST::execute(fstltbool))
				{
					LT::Entry lEntry = { LEX_LITERAL, line, col };
					lEntry.sign = -1;
					strcpy_s(lEntry.buf, buffer);
					LT::Add(*ltable, lEntry);
					IT::Entry iEntry;
					strcpy_s(iEntry.id, string);
					iEntry.iddatatype = IT::BOOL;
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
				FST::FST fstid(buffer, FST_ID);
				if (!linkflag)
					if (FST::execute(fstid))
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
					FST::FST fstintlit(buffer, FST_INTLIT);
					if (FST::execute(fstintlit))
					{
						long double bufNum = std::atoi(buffer);
						LT::Entry lEntry = { LEX_LITERAL, line, col };
						lEntry.sign = bufNum;
						strcpy_s(lEntry.buf, buffer);
						LT::Add(*ltable, lEntry);
						//SA::ZeroDivision(*ltable, buffer);
						IT::Entry iEntry;
						strcpy_s(iEntry.id, string);
						iEntry.iddatatype = IT::INT;
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
					FST::FST fststrlit(buffer, FST_STRLIT);
					if (FST::execute(fststrlit))
					{
						LT::Entry lEntry = { LEX_LITERAL, line, col };
						lEntry.sign = -1;
						strcpy_s(lEntry.buf, buffer);
						LT::Add(*ltable, lEntry);
						IT::Entry iEntry;
						strcpy_s(iEntry.id, string);
						iEntry.iddatatype = IT::STR;
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
					FST::FST fstpoint(buffer, FST_POINT);
					if (FST::execute(fstpoint))
					{
						LT::Entry lEntry = { LEX_POINT, line, col };
						LT::Add(*ltable, lEntry);
						continue;
					}
					FST::FST fstcomma(buffer, FST_COMMA);
					if (FST::execute(fstcomma))
					{
						LT::Entry lEntry = { LEX_COMMA, line, col };
						lEntry.priority = 1;
						LT::Add(*ltable, lEntry);
						continue;
					}
					FST::FST fstlbrace(buffer, FST_LEFTBRACE);
					if (FST::execute(fstlbrace))
					{
						LT::Entry lEntry = { LEX_LEFTBRACE, line, col };
						LT::Add(*ltable, lEntry);
						continue;
					}
					FST::FST fstrbrace(buffer, FST_RIGHTBRACE);
					if (FST::execute(fstrbrace))
					{
						LT::Entry lEntry = { LEX_RIGHTBRACE, line, col };
						LT::Add(*ltable, lEntry);
						continue;
					}
					FST::FST fstlthesis(buffer, FST_LEFTHESIS);
					if (FST::execute(fstlthesis))
					{
						LT::Entry lEntry = { LEX_LEFTHESIS, line, col };
						lEntry.priority = 0;
						LT::Add(*ltable, lEntry);
						continue;
					}
					FST::FST fstrthesis(buffer, FST_RIGHTHESIS);
					if (FST::execute(fstrthesis))
					{
						LT::Entry lEntry = { LEX_RIGHTHESIS, line, col };
						lEntry.priority = 0;
						LT::Add(*ltable, lEntry);
						continue;
					}
					FST::FST fstmore(buffer, FST_MORE);
					if (FST::execute(fstmore))
					{
						LT::Entry lEntry = { LEX_MORE, line, col };
						lEntry.sign = 2;
						LT::Add(*ltable, lEntry);
						linkflag = true;
					}
					FST::FST fstless(buffer, FST_LESS);
					if (FST::execute(fstless))
					{
						LT::Entry lEntry = { LEX_LESS, line, col };
						lEntry.sign = 2;
						LT::Add(*ltable, lEntry);
						linkflag = true;
					}
					FST::FST fstequally(buffer, FST_EQUALLY);
					if (FST::execute(fstequally))
					{
						LT::Entry lEntry = { LEX_EQUALLY, line, col };
						lEntry.sign = 2;
						LT::Add(*ltable, lEntry);
						linkflag = true;
					}
					FST::FST fstcompare(buffer, FST_COMPARE);
					if (FST::execute(fstcompare))
					{
						LT::Entry lEntry = { LEX_COMPARE, line, col };
						LT::Add(*ltable, lEntry);
						linkflag = true;
					}
					FST::FST fstplus(buffer, FST_PLUS);
					if (FST::execute(fstplus))
					{
						LT::Entry lEntry = { LEX_PLUS, line, col };
						lEntry.sign = 1;
						lEntry.priority = 2;
						LT::Add(*ltable, lEntry);
						linkflag = true;
					}
					FST::FST fstminus(buffer, FST_MINUS);
					if (FST::execute(fstminus))
					{
						LT::Entry lEntry = { LEX_MINUS, line, col };
						lEntry.sign = 1;
						lEntry.priority = 2;
						LT::Add(*ltable, lEntry);
						linkflag = true;
					}
					FST::FST fststar(buffer, FST_STAR);
					if (FST::execute(fststar))
					{
						LT::Entry lEntry = { LEX_STAR, line, col };
						lEntry.sign = 1;
						lEntry.priority = 3;
						LT::Add(*ltable, lEntry);
						linkflag = true;
					}
					FST::FST fstslash(buffer, FST_DIRSLASH);
					if (FST::execute(fstslash))
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
				FST::FST fstp(newbuf, FST_POINT);
				if (FST::execute(fstp))
				{
					LT::Entry lEntry = { LEX_POINT , line, col };
					LT::Add(*ltable, lEntry);
					continue;
				}
				FST::FST fstlft(newbuf, FST_LEFTHESIS);
				if (FST::execute(fstlft))
				{
					LT::Entry lEntry = { LEX_LEFTHESIS , line, col };
					LT::Add(*ltable, lEntry);
					continue;
				}
				FST::FST fstrft(newbuf, FST_RIGHTHESIS);
				if (FST::execute(fstrft))
				{
					LT::Entry lEntry = { LEX_RIGHTHESIS , line, col };
					LT::Add(*ltable, lEntry);
					continue;
				}
				FST::FST fstrb(newbuf, FST_RIGHTBRACE);
				if (FST::execute(fstrb))
				{
					LT::Entry lEntry = { LEX_RIGHTBRACE , line, col };
					LT::Add(*ltable, lEntry);
					continue;
				}
				FST::FST fstlb(newbuf, FST_LEFTBRACE);
				if (FST::execute(fstlb))
				{
					LT::Entry lEntry = { LEX_LEFTBRACE , line, col };
					LT::Add(*ltable, lEntry);
					continue;
				}
				FST::FST fstc(newbuf, FST_COMMA);
				if (FST::execute(fstc))
				{
					LT::Entry lEntry = { LEX_COMMA, line, col };
					LT::Add(*ltable, lEntry);
					continue;
				}
			}
		}
	}
}