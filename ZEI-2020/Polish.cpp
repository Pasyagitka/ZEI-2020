#pragma once
#include "LT.h"
#include "IT.h"
#include "Polish.h"
#include <stack>
#include <queue>
#include <string>
#include <iostream>
//TODO первое вхождение идентификатора?
//TODO как он узнает, что это за функция была?? b h - там где-то идентификатор удаляется
namespace Pn {
	void ToPolish(LT::LexTable& lextable, IT::IdTable& idtable) {
		for (int i = 0; i < lextable.size; i++) {
			if (lextable.table[i].lexema == ':')
				PolishNotation(i +1, lextable, idtable);
			if (lextable.table[i].lexema == 'h')
				PolishNotation(i, lextable, idtable);
		}
	}

	//switch
	int GetPriority(char c) {
		if (c == LEX_LEFTHESIS || c == LEX_RIGHTHESIS) return 0;
		if (c == LEX_COMMA) return 1;
		if (c == LEX_PLUS || c == LEX_MINUS) return 2;
		if (c == LEX_STAR || c == LEX_SLASH) return 3;
		return 0;
	}


	bool PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable) {
		std::stack<char> stack;
		std::string ResultingString;
		LT::Entry temp;
		bool isCompleted = false;
		bool functionflag = false;
		int paramcounter = 0;

		for (int i = lextable_pos; ; i++)
		{
			temp = LT::GetEntry(lextable, i);


			if (temp.lexema == LEX_ID || temp.lexema == LEX_LITERAL || temp.lexema == LEX_LIBFUNC || temp.lexema == LEX_SHOW)
			{
				if (idtable.table[lextable.table[i].indxTI].idtype== IT::F || idtable.table[lextable.table[i].indxTI].idtype == IT::B) functionflag = true; //идентификатор функции удаляется А ТИП???
				else ResultingString += temp.lexema;
				continue;
			}

			if (temp.lexema == LEX_PLUS || temp.lexema == LEX_MINUS || temp.lexema == LEX_STAR || temp.lexema == LEX_SLASH) {
				if (stack.empty()) {
					stack.push(temp.lexema);
				}
				else { //операция выталкивает все операции с большим или равным	приоритетом в результирующую строку;  записывается в стек, если стек пуст или в вершине стека лежит отрывающая скобка;
					while (!stack.empty() && GetPriority(temp.lexema) <= GetPriority(stack.top())) {
						ResultingString += stack.top();
						stack.pop();
					}
					stack.push(temp.lexema);
					if (GetPriority(temp.lexema) > GetPriority(stack.top())) {
						stack.push(temp.lexema);
					}
				}
				continue;
			}
			if (temp.lexema == LEX_COMMA) {
				paramcounter++;
				while (stack.top() == LEX_PLUS || stack.top() == LEX_MINUS || stack.top() == LEX_STAR || stack.top() == LEX_SLASH) {
					ResultingString += stack.top();
					stack.pop();
				}
				continue;
			}

			if (temp.lexema == LEX_LEFTHESIS) {
				stack.push(temp.lexema);
				continue;
			}

			if (temp.lexema == LEX_RIGHTHESIS) {
				while (stack.top() != LEX_LEFTHESIS) {
					ResultingString += stack.top();
					stack.pop();
				}
				stack.pop();
				if (functionflag) {
					ResultingString += LEX_AT;
					ResultingString += std::to_string(paramcounter + 1);
					functionflag = false;
				}
				continue;
			}

			if (temp.lexema == LEX_EXCLAMATION) {
				isCompleted = true;
			}

			if (isCompleted) {
				while (!stack.empty()) {
					ResultingString += stack.top();
					stack.pop();
				}
				std::cout << ResultingString << std::endl; //таблица лексем
				int i = lextable_pos;
				int j = 0;
				for (; lextable.table[i].lexema != LEX_EXCLAMATION; i++, j++) {
					if (j < ResultingString.length())
						lextable.table[i].lexema = ResultingString[j];
					else if (j == ResultingString.length())
						lextable.table[i].lexema = LEX_EXCLAMATION;
					else {
						for (int k = i; k > lextable_pos + ResultingString.length(); k--)
							lextable.table[k].lexema = LEX_FREE;
					}
				}
				if (j != ResultingString.length()) lextable.table[i].lexema = LEX_FREE;
				return true;
			}
		}
		return false;
	}
}