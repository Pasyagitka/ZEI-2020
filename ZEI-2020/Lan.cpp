#include "Lan.h"
#include "Log.h"
#include "LT.h"
#include "IT.h"
#include "FST.h"

#include "SEM.h"
#include <string>
#include "FSTExpr.h"
#define EMPTY_LITERAL "-"
//TODO: max длина строки
//TODO: получается номер и у H(16)
//TODO: проверить все ошибки
namespace Lan
{

	void Analysis(char inText[], Log::LOG, LT::LexTable& lextable, IT::IdTable& idtable)
	{
		int currentLine = 1, currentColumn = 0, tokenlen = 0;
		bool tokenIsCommited(false), proverka(false), newLineFlag(false), flag(false);
		bool quoteFlag(false);

		char postfix[10];
		char token[258];
		char anotherbuf[10];

		LT::LexTable* newLexTable = &lextable;
		IT::IdTable* newIDTable = &idtable;
		IT::IDDATATYPE dataType;
		IT::IDTYPE idType;

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
				|| inText[i] == LEX_POINT || inText[i] == LEX_COMMA || inText[i] == LEX_EXCLAMATION || inText[i] == LEX_LEFTHESIS || inText[i] == LEX_RIGHTHESIS || inText[i] == LEX_RIGHTBRACE || inText[i] == LEX_LEFTBRACE
				|| inText[i + 1] == LEX_POINT || inText[i + 1] == LEX_COMMA || inText[i +1 ] == LEX_EXCLAMATION || inText[i +1] == LEX_LEFTHESIS || inText[i+1] == LEX_RIGHTHESIS || inText[i+1] == LEX_RIGHTBRACE || inText[i+1] == LEX_LEFTBRACE
				|| inText[i + 1] == LEX_MINUS || inText[i + 1] == LEX_PLUS || inText[i + 1] == LEX_EQUALITY || inText[i + 1] == LEX_STAR || inText[i + 1] == LEX_SLASH
				|| inText[i] == LEX_MINUS || inText[i] == LEX_PLUS || inText[i] == LEX_EQUALITY || inText[i] == LEX_STAR || inText[i] == LEX_SLASH  
				)
			{
				if (quoteFlag) 	continue;
				if (inText[i] == LEX_ENDL)	newLineFlag = true;

				if (tokenlen == 1 || inText[i+1] == LEX_EXCLAMATION || inText[i+1] == LEX_POINT || inText[i+1] == LEX_LEFTHESIS || inText[i+1] == LEX_RIGHTHESIS ||  inText[i+1] == LEX_COMMA)
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
					LT::Entry newLTEntry = { LEX_EXCLAMATION, currentLine, LT_TI_NULLIDX };
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				FST::FST FSTPoint(token, FST_POINT);
				if (FST::execute(FSTPoint)) {
					LT::Entry newLTEntry = { LEX_POINT , currentLine, LT_TI_NULLIDX };
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				FST::FST FSTLefthesis(token, FST_LEFTHESIS);
				if (FST::execute(FSTLefthesis)) {
					LT::Entry newLTEntry = { LEX_LEFTHESIS , currentLine, LT_TI_NULLIDX };
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				FST::FST FSTRighthesis(token, FST_RIGHTHESIS);
				if (FST::execute(FSTRighthesis)) {
					LT::Entry newLTEntry = { LEX_RIGHTHESIS , currentLine, LT_TI_NULLIDX };
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				FST::FST FSTRightbrace(token, FST_RIGHTBRACE);
				if (FST::execute(FSTRightbrace)) {
					LT::Entry newLTEntry = { LEX_RIGHTBRACE , currentLine, LT_TI_NULLIDX };
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				FST::FST FSTLeftbrace(token, FST_LEFTBRACE);
				if (FST::execute(FSTLeftbrace)) {
					LT::Entry newLTEntry = { LEX_LEFTBRACE , currentLine, LT_TI_NULLIDX };
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				FST::FST FSTComma(token, FST_COMMA);
				if (FST::execute(FSTComma)) {
					LT::Entry newLTEntry = { LEX_COMMA, currentLine, LT_TI_NULLIDX };
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				FST::FST FSTTiny(token, FST_TINY);
				if (FST::execute(FSTTiny)) {
					dataType = IT::TINY;
					idType = IT::V;
					LT::Entry newLTEntry = { LEX_TINY , currentLine, IT::IsId(idtable, token) };
					strcpy_s(newLTEntry.buf, token);
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				FST::FST FSTSymbolic(token, FST_SYMBOLIC);
				if (FST::execute(FSTSymbolic)) {
					dataType = IT::SYMB;
					idType = IT::V;
					LT::Entry newLTEntry = { LEX_SYMBOLIC, currentLine, IT::IsId(idtable, token) };
					strcpy_s(newLTEntry.buf, token);
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				FST::FST FSTLogical(token, FST_LOGICAL);
				if (FST::execute(FSTLogical)) {
					dataType = IT::LGCL;
					idType = IT::V;
					LT::Entry newLTEntry = { LEX_LOGICAL, currentLine, IT::IsId(idtable, token) };
					strcpy_s(newLTEntry.buf, token);
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				FST::FST FSTFunc(token, FST_FUNC);
				if (FST::execute(FSTFunc)) {
					LT::Entry newLTEntry = { LEX_FUNCTION, currentLine, IT::IsId(idtable, token) };
					LT::Add(*newLexTable, newLTEntry);
					idType = IT::F;
					continue;
				}
				FST::FST FSTGiveback(token, FST_GIVEBACK);
				if (FST::execute(FSTGiveback)) {
					LT::Entry newLTEntry = { LEX_GIVEBACK, currentLine, IT::IsId(idtable, token) };
					LT::Add(*newLexTable, newLTEntry);
					idType = IT::V;
					continue;
				}
				FST::FST FSTSet(token, FST_SET);
				if (FST::execute(FSTSet)) {
					LT::Entry newLTEntry = { LEX_SET, currentLine, IT::IsId(idtable, token) };
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				FST::FST FSTShow(token, FST_SHOW);
				if (FST::execute(FSTShow)) {

					idType = IT::B;

					IT::Entry newIDEntry;
					strcpy_s(newIDEntry.id, token);
					newIDEntry.idtype = idType;
					newIDEntry.iddatatype = dataType;
					newIDEntry.value.vint = TI_INT_DEFAULT;
					newIDEntry.value.vstr->len = TI_STR_DEFAULT;
					strcpy_s(newIDEntry.value.vstr->str, "");
					newIDEntry.idxfirstLE = currentLine;
					IT::Add(*newIDTable, newIDEntry);

					LT::Entry newLTEntry = { LEX_SHOW, currentLine, IT::IsId(idtable, token) , 1 };
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				FST::FST FSTLib(token, FST_LIB);
				if (FST::execute(FSTLib)) {
					LT::Entry newLTEntry = { LEX_LIB, currentLine, IT::IsId(idtable, token) };
					LT::Add(*newLexTable, newLTEntry);
					strcpy_s(postfix, token);
					//SA::OneDvv(*ltable, flag);
					flag = true;
					continue;
				}
				FST::FST FSTWhen(token, FST_WHEN);
				if (FST::execute(FSTWhen)) {
					LT::Entry newLTEntry = { LEX_WHEN, currentLine, IT::IsId(idtable, token) };
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				FST::FST FSTOtherwise(token, FST_OTHERWISE);
				if (FST::execute(FSTOtherwise)) {
					LT::Entry newLTEntry = { LEX_OTHERWISE, currentLine, IT::IsId(idtable, token) };
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				FST::FST FSTSymblen(token, FST_SYMBLEN);
				if (FST::execute(FSTSymblen)) {
					idType = IT::B;
					dataType = IT::SYMB;
					IT::Entry newIDEntry;
					strcpy_s(newIDEntry.id, token);
					newIDEntry.idtype = idType;
					newIDEntry.iddatatype = dataType;
					newIDEntry.value.vint = TI_INT_DEFAULT;
					newIDEntry.value.vstr->len = TI_STR_DEFAULT;
					strcpy_s(newIDEntry.value.vstr->str, "");
					newIDEntry.idxfirstLE = currentLine;
					IT::Add(*newIDTable, newIDEntry);
					LT::Entry newLTEntry = { LEX_LIBFUNC, currentLine, IT::IsId(idtable, token) , 1 };
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				FST::FST FSTSymbtotiny(token, FST_SYMBTOTINY);
				if (FST::execute(FSTSymbtotiny)) {
					idType = IT::B;
					dataType = IT::SYMB;
					IT::Entry newIDEntry;
					strcpy_s(newIDEntry.id, token);
					newIDEntry.idtype = idType;
					newIDEntry.iddatatype = dataType;
					newIDEntry.value.vint = TI_INT_DEFAULT;
					newIDEntry.value.vstr->len = TI_STR_DEFAULT;
					strcpy_s(newIDEntry.value.vstr->str, "");
					newIDEntry.idxfirstLE = currentLine;
					IT::Add(*newIDTable, newIDEntry);

					LT::Entry newLTEntry = { LEX_LIBFUNC, currentLine, IT::IsId(idtable, token) , 1 };
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				FST::FST FSTLogicalLiteralTrue(token, FST_TRUE);
				FST::FST FSTLogicalLiteralFalse(token, FST_FALSE);
				if (FST::execute(FSTLogicalLiteralFalse) || FST::execute(FSTLogicalLiteralTrue)) {

					IT::Entry iEntry;
					strcpy_s(iEntry.id, EMPTY_LITERAL);
					iEntry.iddatatype = IT::LGCL;
					iEntry.idtype = IT::L;
					strcpy_s(iEntry.value.vstr->str, token);
					strcpy_s(iEntry.value.vbool, token);
					for (int i = 0; i < newIDTable->size; i++) {
						if (strcmp((*newIDTable).table[i].value.vbool, iEntry.value.vbool) == 0) {
							proverka = true;
							break;
						}
						else proverka = false;
					}
					iEntry.idxfirstLE = currentLine;
					if (!proverka) {
						IT::Add(*newIDTable, iEntry);
					}
					LT::Entry newLTEntry = { LEX_LITERAL, currentLine, IT::IsId(idtable, token) };
					newLTEntry.sign = -1;
					strcpy_s(newLTEntry.buf, token);
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				//HACK не понятно, правильно ли работает 0dec, 09hex
				FST::FST FSTTinyLiteral10(token, FST_TINYLITERAL10);
				FST::FST FSTTinyLiteral8(token, FST_TINYLITERAL8);
				if (FST::execute(FSTTinyLiteral10) || FST::execute(FSTTinyLiteral8)) {
					int bufNum = std::strtol(token, NULL, 0); //HACK перевод в 8-ричную 

					//SA::ZeroDivision(*ltable, buffer);
					IT::Entry iEntry;
					strcpy_s(iEntry.id, EMPTY_LITERAL);
					iEntry.iddatatype = IT::TINY;
					iEntry.idtype = IT::L;
					if (bufNum > MAXTINY && bufNum < MINTINY)	//TINY
						throw ERROR_THROW_IN(309, currentLine, currentColumn);
					iEntry.value.vint = (int)bufNum;
					strcpy_s(iEntry.value.vstr->str, token);
					for (int i = 0; i < newIDTable->size; i++) {
						if (iEntry.value.vint == (*newIDTable).table[i].value.vint) {
							proverka = true;
							break;
						}
						else  proverka = false;
					}
					iEntry.idxfirstLE = currentLine;
					if (!proverka)
						IT::Add(*newIDTable, iEntry);
					LT::Entry newLTEntry = { LEX_LITERAL, currentLine, IT::IsId(idtable, token) };
					newLTEntry.sign = bufNum;
					strcpy_s(newLTEntry.buf, token);
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				FST::FST FSTSymbolicLiteral(token, FST_SYMBOLICLITERAL);
				if (FST::execute(FSTSymbolicLiteral)) {

					IT::Entry iEntry;
					strcpy_s(iEntry.id, EMPTY_LITERAL);
					iEntry.iddatatype = IT::SYMB;
					iEntry.idtype = IT::L;
					if (strlen(token) > 128) //max длина строки будет
						throw ERROR_THROW_IN(310, currentLine, currentColumn);
					iEntry.value.vstr->len = strlen(token);
					strcpy_s(iEntry.value.vstr->str, token);
					for (int i = 0; i < newIDTable->size; i++)
					{
						if (strcmp(iEntry.value.vstr->str, (*newIDTable).table[i].value.vstr->str) == 0)
						{

							proverka = true;
							break;
						}
						else proverka = false;
					}
					iEntry.idxfirstLE = currentLine;
					if (!proverka)
					{
						IT::Add(*newIDTable, iEntry);
					}

					LT::Entry newLTEntry = { LEX_LITERAL, currentLine, IT::IsId(idtable, token) };
					newLTEntry.sign = -1;
					strcpy_s(newLTEntry.buf, token);
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				FST::FST FSTEquality(token, FST_EQUALITY);
				if (FST::execute(FSTEquality)) {
					LT::Entry newLTEntry = { LEX_EQUALITY, currentLine, LT_TI_NULLIDX };
					newLTEntry.sign = 2;
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				FST::FST FSTCompare(token, FST_COMPARE);
				if (FST::execute(FSTCompare)) {
					LT::Entry newLTEntry = { LEX_COMPARE, currentLine, LT_TI_NULLIDX };
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				FST::FST FSTPlus(token, FST_PLUS);
				if (FST::execute(FSTPlus)) {
					LT::Entry newLTEntry = { LEX_PLUS, currentLine, LT_TI_NULLIDX };
					newLTEntry.sign = 1;
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				FST::FST FSTMinus(token, FST_MINUS);
				if (FST::execute(FSTMinus)) {
					LT::Entry newLTEntry = { LEX_MINUS, currentLine, LT_TI_NULLIDX };
					newLTEntry.sign = 1;
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				FST::FST FSTStar(token, FST_STAR);
				if (FST::execute(FSTStar)) {
					LT::Entry newLTEntry = { LEX_STAR, currentLine, LT_TI_NULLIDX };
					newLTEntry.sign = 1;
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				FST::FST FSTSlash(token, FST_SLASH);
				if (FST::execute(FSTSlash)) {
					LT::Entry newLTEntry = { LEX_SLASH, currentLine, LT_TI_NULLIDX };
					newLTEntry.sign = 1;
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				FST::FST FSTLeftshift(token, FST_LEFTSHIFT);
				if (FST::execute(FSTLeftshift)) {
					LT::Entry newLTEntry = { LEX_LEFTSHIFT, currentLine, LT_TI_NULLIDX };
					newLTEntry.sign = 1;
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				FST::FST FSTRightshift(token, FST_RIGHTSHIFT);
				if (FST::execute(FSTRightshift)) {
					LT::Entry newLTEntry = { LEX_RIGHTSHIFT, currentLine, LT_TI_NULLIDX };
					newLTEntry.sign = 1;
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				FST::FST FSTIdentifier(token, FST_ID);
				if (FST::execute(FSTIdentifier)) {
					if (strlen(token) > ID_MAXSIZE)
						throw ERROR_THROW_IN(308, currentLine, currentColumn);
					IT::Entry iEntry;
					strcpy_s(anotherbuf, token);
					if (idType == IT::F)
						strcpy_s(postfix, token);
					strcpy_s(iEntry.postfix, postfix);
					bool isExecute = false;
					//SA::Proverka(*ltable, *itable);
					//SA::Pereobyavl(*ltable, *itable, buffer, postfix, line, col);
					for (int i = 0; i <= (*newIDTable).size; i++)
						if (strcmp((*newIDTable).table[i].id, token) == 0)
						{
							isExecute = true;
							if (newIDTable->table[i].idtype == IT::F)
								break;
							if (strcmp((*newIDTable).table[i].postfix, iEntry.postfix) != 0)
								isExecute = false;
						}
					if (!isExecute) { //если переменная не объявлена	
						strcpy_s(iEntry.id, token);
						iEntry.idtype = idType;
						iEntry.iddatatype = dataType;
						iEntry.value.vint = TI_INT_DEFAULT;
						iEntry.value.vstr->len = TI_STR_DEFAULT;
						strcpy_s(iEntry.value.vstr->str, "");
						iEntry.idxfirstLE = currentLine;
						IT::Add(*newIDTable, iEntry);
					}
					LT::Entry newLTEntry = { LEX_ID, currentLine, IT::IsId(idtable, token) };
					strcpy_s(newLTEntry.buf, token);
					LT::Add(*newLexTable, newLTEntry);
					continue;
				}
				throw ERROR_THROW_IN(311, currentLine, currentColumn);
			}
		}
	}
}