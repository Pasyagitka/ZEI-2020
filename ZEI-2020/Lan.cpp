#define _CRT_SECURE_NO_WARNINGS
#include "Lan.h"
#include "Log.h"
#include "LT.h"
#include "IT.h"
#include "FST.h"

#include <string>
#include "FSTExpr.h"
#include "Sem.h"

namespace Lan
{

	bool Analysis(char inText[], Log::LOG, LT::LexTable& lextable, IT::IdTable& idtable)
	{
		int currentLineLT = 1, currentColumn = 0, tokenlen = 0;
		bool tokenIsCommited(false), newLineFlag(false), quoteFlag(false);
		bool functiond(false);
		int entryPoint = 0;
		char postfix[10] = POSTFIXGLOBAL;
		char token[258]{};
		int literalCounter = 1;
		int lastfunctioni = 0;

		char* nLiteral = new char[3]{ "N" };
		char* literal_c = new char[10]{ "" }; // строковая запись счетчика

		LT::LexTable* newLexTable = &lextable;
		IT::IdTable* newIDTable = &idtable;
		IT::IDDATATYPE dataType = IT::IDDATATYPE::UNDEF;
		IT::IDTYPE idType = IT::IDTYPE::U;

		for (int i = 0; i < strlen(inText); i++)
		{
			token[tokenlen++] = inText[i];
			if (inText[i] == LEX_QUOTE)	quoteFlag = !quoteFlag;

			tokenIsCommited = false;
			strcpy(nLiteral, "N");

			if (newLineFlag)	{
				currentLineLT++;
				currentColumn = 0;
				newLineFlag = false;
			}

			if (inText[i] == LEX_SPACE || inText[i] == LEX_ENDL  || S || SNEXT || ARIFM || ARIFMNEXT || LOGIC || LOGICNEXT) {
				if (quoteFlag) 	continue;
				if (inText[i] == LEX_ENDL)	newLineFlag = true;

				if (tokenlen == 1 ||  inText[i + 1] == LEX_COMMA || inText[i+1] == LEX_ASSIGN ||inText[i+1] == LEX_EXCLAMATION || inText[i+1] == LEX_LEFTHESIS || inText[i+1] == LEX_RIGHTHESIS	 || inText[i+1] == LEX_RIGHTBRACE || inText[i+1] == LEX_LEFTBRACE || ARIFMNEXT || LOGICNEXT)
					token[tokenlen] = LEX_END;
				else
					if (!quoteFlag) token[tokenlen - 1] = LEX_END;
					

				tokenlen = 0;
				tokenIsCommited = true;
				if (token[tokenlen] == LEX_SPACE || token[tokenlen] == LEX_ENDL)	
					continue;
			}
			currentColumn++;

			if (tokenIsCommited) {
				FST::FST FSTExclamation(token, FST_EXCLAMATION);
				if (FST::execute(FSTExclamation)) {
					LT::Entry *newLTEntry = new LT::Entry{ LEX_EXCLAMATION, currentLineLT, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTLefthesis (token, FST_LEFTHESIS);
				if (FST::execute(FSTLefthesis)) {
					LT::Entry* newLTEntry = new LT::Entry{ LEX_LEFTHESIS, currentLineLT, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTRighthesis(token, FST_RIGHTHESIS);
				if (FST::execute(FSTRighthesis)) {
					if (idType == IT::P)
						idType = IT::U;
					functiond = false;
					LT::Entry* newLTEntry = new LT::Entry{ LEX_RIGHTHESIS, currentLineLT, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTRightbrace(token, FST_RIGHTBRACE);
				if (FST::execute(FSTRightbrace)) {
					LT::Entry* newLTEntry = new LT::Entry{ LEX_RIGHTBRACE, currentLineLT, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTLeftbrace(token, FST_LEFTBRACE);
				if (FST::execute(FSTLeftbrace)) {
					LT::Entry* newLTEntry = new LT::Entry{ LEX_LEFTBRACE, currentLineLT, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTTiny(token, FST_TINY);
				if (FST::execute(FSTTiny)) {
					dataType = IT::TINY;
					if (idType == IT::F || idType == IT::P) {
						idType = IT::P;
					}
					else
						idType = IT::V;
					LT::Entry* newLTEntry = new LT::Entry{ LEX_TINY, currentLineLT, LT_TI_NULLIDX };
					strcpy_s(newLTEntry->info, token);
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTSymbolic(token, FST_SYMBOLIC);
				if (FST::execute(FSTSymbolic)) {
					if (idType == IT::F || idType == IT::P)
						idType = IT::P;
					else 
						idType = IT::V;
					dataType = IT::SYMB;
					LT::Entry* newLTEntry = new LT::Entry{ LEX_SYMBOLIC, currentLineLT, LT_TI_NULLIDX };
					strcpy_s(newLTEntry->info, token);
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTLogical(token, FST_LOGICAL);
				if (FST::execute(FSTLogical)) {
					dataType = IT::LGCL;
					if (idType == IT::F || idType == IT::P)
						idType = IT::P;
					else
						idType = IT::V;
					LT::Entry* newLTEntry = new LT::Entry{ LEX_LOGICAL, currentLineLT, LT_TI_NULLIDX };
					strcpy_s(newLTEntry->info, token);
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTFunc(token, FST_FUNC);
				if (FST::execute(FSTFunc)) {
					for (int j = 0; j < i; j++) {
						if (lextable.table[j].lexema == LEX_PERFORM)
							throw ERROR_THROW_IN(607, currentLineLT, 0);
					}
					functiond = true;
					LT::Entry* newLTEntry = new LT::Entry{ LEX_FUNCTION, currentLineLT, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					idType = IT::F;
					delete newLTEntry;
					continue;
				}
				FST::FST FSTGiveback(token, FST_GIVEBACK);
				if (FST::execute(FSTGiveback)) {
					LT::Entry* newLTEntry = new LT::Entry{ LEX_GIVEBACK, currentLineLT, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					idType = IT::V;
					delete newLTEntry;
					continue;
				}
				FST::FST FSTPerform(token, FST_PERFORM);
				if (FST::execute(FSTPerform)) {
					entryPoint++;
					LT::Entry* newLTEntry = new LT::Entry{ LEX_PERFORM, currentLineLT, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					/*idType = IT::F;*/
					strcpy_s(postfix, "perform");
					delete newLTEntry;
					continue;
				}
				FST::FST FSTLoop(token, FST_LOOP);
				if (FST::execute(FSTLoop)) {
					LT::Entry* newLTEntry = new LT::Entry{ LEX_LOOP, currentLineLT, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTSet(token, FST_SET);
				if (FST::execute(FSTSet)) {
					LT::Entry* newLTEntry = new LT::Entry{ LEX_SET, currentLineLT, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTShow(token, FST_SHOW);
				if (FST::execute(FSTShow)) {;
					idType = IT::B;
					IT::Entry* newIDEntry = new IT::Entry{};
					if (IT::IsId(idtable, token) == TI_NULLIDX) {
						strcpy_s(newIDEntry->id, token);
						newIDEntry->idtype = idType;
						newIDEntry->iddatatype = IT::UNDEF;
						newIDEntry->parameters.count = 1;
						newIDEntry->parameters.typeofparameter[0] = IT::UNDEF;	//Только 1 параметр
						
						newIDEntry->idxfirstLE = currentLineLT;
						IT::Add(*newIDTable, *newIDEntry);
					}
					LT::Entry* newLTEntry = new LT::Entry{ LEX_SHOW, currentLineLT, IT::IsId(idtable, token) , 1};
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					delete newIDEntry;
					continue;
				}
				FST::FST FSTWhen(token, FST_WHEN);
				if (FST::execute(FSTWhen)) {
					LT::Entry* newLTEntry = new LT::Entry{ LEX_WHEN, currentLineLT, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTOtherwise(token, FST_OTHERWISE);
				if (FST::execute(FSTOtherwise)) {
					LT::Entry* newLTEntry = new LT::Entry{ LEX_OTHERWISE, currentLineLT, LT_TI_NULLIDX };
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
					newIDEntry->parameters.count = 1;
					newIDEntry->parameters.typeofparameter[0] = IT::SYMB; //Только 1 параметр
					newIDEntry->idxfirstLE = currentLineLT;
					strcpy_s(newIDEntry->postfix, POSTFIXGLOBAL);
					IT::Add(*newIDTable, *newIDEntry);

					LT::Entry* newLTEntry = new LT::Entry{ LEX_LIBFUNC, currentLineLT, IT::IsId(idtable, token) , 1 };
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
					newIDEntry->parameters.count = 1;
					newIDEntry->parameters.typeofparameter[0] = IT::SYMB; //Только 1 параметр
					newIDEntry->idxfirstLE = currentLineLT;
					strcpy_s(newIDEntry->postfix, POSTFIXGLOBAL);
					IT::Add(*newIDTable, *newIDEntry);

					LT::Entry *newLTEntry = new LT::Entry{ LEX_LIBFUNC, currentLineLT, IT::IsId(idtable, token) , 1 };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					delete newIDEntry;
					continue;
				}
				FST::FST FSTGettime(token, FST_GETTIME);
				if (FST::execute(FSTGettime)) {
					idType = IT::B;
					dataType = IT::SYMB;
					IT::Entry* newIDEntry = new IT::Entry{};
					strcpy_s(newIDEntry->id, token);
					newIDEntry->idtype = idType;
					newIDEntry->iddatatype = dataType;
					newIDEntry->parameters.count = 1;
					newIDEntry->parameters.typeofparameter[0] = IT::SYMB; //Только 1 параметр
					newIDEntry->idxfirstLE = currentLineLT;
					strcpy_s(newIDEntry->postfix, POSTFIXGLOBAL);
					IT::Add(*newIDTable, *newIDEntry);

					LT::Entry* newLTEntry = new LT::Entry{ LEX_LIBFUNC, currentLineLT, IT::IsId(idtable, token), 1 };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					delete newIDEntry;
					continue;
				}
				FST::FST FSTGetnertiny(token, FST_GENERTINY);
				if (FST::execute(FSTGetnertiny)) {
					idType = IT::B;
					dataType = IT::TINY;
					IT::Entry* newIDEntry = new IT::Entry{};
					strcpy_s(newIDEntry->id, token);
					newIDEntry->idtype = idType;
					newIDEntry->iddatatype = dataType;
					newIDEntry->parameters.count = 0;
					newIDEntry->idxfirstLE = currentLineLT;
					strcpy_s(newIDEntry->postfix, POSTFIXGLOBAL);
					IT::Add(*newIDTable, *newIDEntry);

					LT::Entry* newLTEntry = new LT::Entry{ LEX_LIBFUNC, currentLineLT, IT::IsId(idtable, token), 1 };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					delete newIDEntry;
					continue;
				}
				FST::FST FSTGenerlgcl(token, FST_GENERLGCL);
				if (FST::execute(FSTGenerlgcl)) {
					idType = IT::B;
					dataType = IT::LGCL;
					IT::Entry* newIDEntry = new IT::Entry{};
					strcpy_s(newIDEntry->id, token);
					newIDEntry->idtype = idType;
					newIDEntry->iddatatype = dataType;
					newIDEntry->parameters.count = 0;
					newIDEntry->idxfirstLE = currentLineLT;
					strcpy_s(newIDEntry->postfix, POSTFIXGLOBAL);
					IT::Add(*newIDTable, *newIDEntry);

					LT::Entry* newLTEntry = new LT::Entry{ LEX_LIBFUNC, currentLineLT, IT::IsId(idtable, token), 1 };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					delete newIDEntry;
					continue;
				}
				FST::FST FSTLogicalLiteralTrue(token, FST_TRUE);
				FST::FST FSTLogicalLiteralFalse(token, FST_FALSE);
				if (FST::execute(FSTLogicalLiteralFalse) || FST::execute(FSTLogicalLiteralTrue)) {
					IT::Entry* newIDEntry = new IT::Entry{};
					
					_itoa_s(literalCounter++, literal_c, sizeof(char) * 10, 10);
					strcpy(newIDEntry->id, strcat(nLiteral, literal_c));

					newIDEntry->iddatatype = IT::LGCL;
					newIDEntry->idtype = IT::L;
					strcpy_s(newIDEntry->value.vlogical, token);
			
					newIDEntry->idxfirstLE = currentLineLT;
				
					IT::Add(*newIDTable, *newIDEntry);
		
					LT::Entry *newLTEntry = new LT::Entry{ LEX_LITERAL, currentLineLT, idtable.size - 1 };
					strcpy_s(newLTEntry->info, token);
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					delete newIDEntry;
					continue;
				}
				FST::FST FSTTinyLiteral2(token, FST_TINYLITERAL2);
				FST::FST FSTTinyLiteral16(token, FST_TINYLITERAL16);
				FST::FST FSTTinyLiteral10(token, FST_TINYLITERAL10);
				FST::FST FSTTinyLiteral8(token, FST_TINYLITERAL8);
				if (FST::execute(FSTTinyLiteral10) || FST::execute(FSTTinyLiteral8) || FST::execute(FSTTinyLiteral16) || FST::execute(FSTTinyLiteral2)){
					int bufNum;
					if (token[0] == 'm') token[0] = '-';
				
					if (token[strlen(token) - 1] == 'q') {
						token[strlen(token) - 1] = LEX_END;
						bufNum = std::strtol(token, NULL, 8);
					}
					else if (token[strlen(token) - 1] == 'h') {
						token[strlen(token) - 1] = LEX_END;
						bufNum = std::strtol(token, NULL, 16);
					}
					else if (token[strlen(token) - 1] == 'b') {
						token[strlen(token) - 1] = LEX_END;
						bufNum = std::strtol(token, NULL, 2);
					}
					else 
						bufNum = std::strtol(token, NULL, 10);
					IT::Entry* newIDEntry = new IT::Entry{};

					_itoa_s(literalCounter++, literal_c, sizeof(char) * 10, 10);
					strcpy(newIDEntry->id, strcat(nLiteral, literal_c));

					newIDEntry->iddatatype = IT::TINY;
					newIDEntry->idtype = IT::L;
					if (bufNum > MAXTINY || bufNum < MINTINY)	//TINY
						throw ERROR_THROW_IN(309, currentLineLT, currentColumn);
					newIDEntry->value.vtiny = (int)bufNum;
					strcpy_s(newIDEntry->value.vsymb->str, token);

					newIDEntry->idxfirstLE = currentLineLT; //или индекс
			
					if (IT::IsId(idtable, token) == TI_NULLIDX)
						IT::Add(*newIDTable, *newIDEntry);


					LT::Entry *newLTEntry = new LT::Entry{ LEX_LITERAL, currentLineLT, idtable.size-1 };
					strcpy_s(newLTEntry->info, token);
					LT::Add(*newLexTable,* newLTEntry);
					delete newLTEntry;
					delete newIDEntry;
					continue;
				}
				FST::FST FSTSymbolicLiteral(token, FST_SYMBOLICLITERAL);
				if (FST::execute(FSTSymbolicLiteral)) {

					IT::Entry* newIDEntry = new IT::Entry{};

					_itoa_s(literalCounter++, literal_c, sizeof(char) * 10, 10);
				    strcpy(newIDEntry->id, strcat(nLiteral, literal_c));
	
					newIDEntry->iddatatype = IT::SYMB;
					newIDEntry->idtype = IT::L;
					if (strlen(token) > SYMBMAXLEN) //max длина строки будет
						throw ERROR_THROW_IN(310, currentLineLT, currentColumn);
					newIDEntry->value.vsymb->len = strlen(token);
					strcpy_s(newIDEntry->value.vsymb->str, token);
					newIDEntry->idxfirstLE = currentLineLT;
					IT::Add(*newIDTable, *newIDEntry);
					
					LT::Entry *newLTEntry = new  LT::Entry{ LEX_LITERAL, currentLineLT, idtable.size-1 };
					strcpy_s(newLTEntry->info, token);
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					delete newIDEntry;
					continue;
				}
				FST::FST FSTComma(token, FST_COMMA);
				if (FST::execute(FSTComma)) {
					idType = IT::P;
					LT::Entry* newLTEntry = new LT::Entry{ LEX_COMMA, currentLineLT, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTEquality(token, FST_EQUALITY);
				if (FST::execute(FSTEquality)) {
					LT::Entry *newLTEntry = new LT::Entry{ LEX_EQUALITY, currentLineLT, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTAssign(token, FST_ASSIGN);
				if (FST::execute(FSTAssign)) {
					LT::Entry *newLTEntry = new LT::Entry{ LEX_ASSIGN, currentLineLT, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTPlus(token, FST_PLUS);
				if (FST::execute(FSTPlus)) {
					LT::Entry* newLTEntry = new LT::Entry{ LEX_PLUS, currentLineLT, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTMinus(token, FST_MINUS);
				if (FST::execute(FSTMinus)) {
					LT::Entry* newLTEntry = new  LT::Entry{ LEX_MINUS, currentLineLT, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTStar(token, FST_STAR);
				if (FST::execute(FSTStar)) {
					LT::Entry *newLTEntry = new  LT::Entry{ LEX_STAR, currentLineLT, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTDivision(token, FST_DIVISION);
				if (FST::execute(FSTDivision)) {
					LT::Entry *newLTEntry = new  LT::Entry{ LEX_DIVISION, currentLineLT, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTMore(token, FST_MORE);
				if (FST::execute(FSTMore)) {
					LT::Entry* newLTEntry = new  LT::Entry{ LEX_MORE, currentLineLT, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTLess(token, FST_LESS);
				if (FST::execute(FSTLess)) {
					LT::Entry* newLTEntry = new  LT::Entry{ LEX_LESS, currentLineLT, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTInequality(token, FST_INEQUALITY);
				if (FST::execute(FSTInequality)) {
					LT::Entry* newLTEntry = new  LT::Entry{ LEX_INEQUALITY, currentLineLT, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTLeftshift(token, FST_LEFTSHIFT);
				if (FST::execute(FSTLeftshift)) {
					LT::Entry* newLTEntry = new  LT::Entry{ LEX_LEFTSHIFT, currentLineLT, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTRightshift(token, FST_RIGHTSHIFT);
				if (FST::execute(FSTRightshift)) {
					LT::Entry* newLTEntry = new  LT::Entry{ LEX_RIGHTSHIFT, currentLineLT, LT_TI_NULLIDX };
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					continue;
				}
				FST::FST FSTIdentifier(token, FST_ID);
				if (FST::execute(FSTIdentifier)) {
					if (strlen(token) > ID_MAXSIZE)
						throw ERROR_THROW_IN(308, currentLineLT, currentColumn);
					IT::Entry* newIDEntry = new IT::Entry{};
					if (idType == IT::F) {
						lastfunctioni = idtable.size;
						strcpy_s(postfix, token);
						strcpy_s(newIDEntry->postfix, POSTFIXGLOBAL);
					}
					else strcpy_s(newIDEntry->postfix, postfix);

					int idxID = IT::IsId(idtable, token, postfix); //такая переменная имя+постфикс определена

					if (lextable.table[lextable.size - 2].lexema == LEX_SET && idxID != TI_NULLIDX) //перед ней SET и она  определена? - нельзя, ошибка
						throw ERROR_THROW_IN(606, currentLineLT, currentColumn);
					

					if (idType == IT::P && functiond) { //functionid - определение функции
						if ((idtable.table[lastfunctioni]).parameters.count == MAXPARMCOUNT) //lastfunctioni запоминает индекс последней фукнции, которую как раз и определям
							throw ERROR_THROW_IN(609, currentLineLT, currentColumn);
						(idtable.table[lastfunctioni]).parameters.typeofparameter[(idtable.table[lastfunctioni]).parameters.count] = dataType;
						(idtable.table[lastfunctioni]).parameters.count++;
					}
					else 
					{
						if (idxID == TI_NULLIDX && lextable.table[lextable.size - 2].lexema != LEX_SET && lextable.table[lextable.size - 1].lexema != LEX_FUNCTION) //если не определена и мы сейчас не определяем то надо ошибку
							throw ERROR_THROW_IN(604, currentLineLT, currentColumn); //Идентификатор не объявлен
					}

					if (idxID == TI_NULLIDX) { //если переменная не объявлена, нужно занести в таблицу (только первый раз)	
						strcpy_s(newIDEntry->id, token);
						newIDEntry->idtype = idType;
						newIDEntry->iddatatype = dataType;
						newIDEntry->idxfirstLE = currentLineLT;
						IT::Add(*newIDTable, *newIDEntry);
					}
					LT::Entry *newLTEntry = new LT::Entry{ LEX_ID, currentLineLT, IT::IsId(idtable, token, postfix) };
					strcpy_s(newLTEntry->info, token);
					LT::Add(*newLexTable, *newLTEntry);
					delete newLTEntry;
					delete newIDEntry;
					continue;
				}
				throw ERROR_THROW_IN(311, currentLineLT, currentColumn);
			}
		}
		if (entryPoint == 0) 		throw  ERROR_THROW(602);
		if (entryPoint > 1) 		throw  ERROR_THROW(603);
		return true;
	}	
}