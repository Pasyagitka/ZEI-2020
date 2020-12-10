#pragma once
#include "LT.h"
#include "IT.h"
#include "Polish.h"
#include <stack>
#include <queue>
#include <string>
#include <iostream>
//TODO первое вхождение идентификатора? str
//TODO: есл что сюда можно дописать предыдущую лексему функции - i d h а r

//TODO; входить в польскую когда надо и не трогать операторы сдвига и тп
namespace Pn {
	void ToPolish(LT::LexTable& lextable, IT::IdTable& idtable) {
		for (int i = 0; i < lextable.size; i++) {
			if (lextable.table[i].lexema == ':')
				PolishNotation(i +1, lextable, idtable);
		/*	if (lextable.table[i].lexema == 'h')
				PolishNotation(i, lextable, idtable);*/
		}
	}

	//switch
	int GetPriority(char c) {
		switch (c)
		{
		case LEX_LEFTHESIS: case LEX_RIGHTHESIS:		return 0;
		case LEX_PLUS:  case LEX_MINUS:					return 1;
		case LEX_STAR: case LEX_DIVISION:				return 2;
		default:										return 0;
		}
	}


	bool PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable) {
		std::stack<LT::Entry> stack;
		std::vector<LT::Entry>ResultingString;
		LT::Entry temp;
		bool isCompleted = false;
		bool functionflag = false;
		int paramcounter = 0;
		int currentLexTableLine;
		int functionIndexTI;

		for (int i = lextable_pos; ; i++)
		{
			temp = LT::GetEntry(lextable, i);
			currentLexTableLine = temp.sn;

			if (temp.lexema == LEX_ID || temp.lexema == LEX_LITERAL || temp.lexema == LEX_LIBFUNC || temp.lexema == LEX_SHOW)
			{
				if (lextable.table[i].indxTI != -1 && (idtable.table[lextable.table[i].indxTI].idtype == IT::F
					|| idtable.table[lextable.table[i].indxTI].idtype == IT::B)) {
					functionflag = true;
					functionIndexTI = lextable.table[i].indxTI;
				}
				else 
				ResultingString.push_back(temp);
				continue;
			}

			if (temp.lexema == LEX_PLUS || temp.lexema == LEX_MINUS || temp.lexema == LEX_STAR || temp.lexema == LEX_DIVISION) {
				if (stack.empty()) {
					stack.push(temp);
				}
				else { //операция выталкивает все операции с большим или равным	приоритетом в результирующую строку;  записывается в стек, если стек пуст или в вершине стека лежит отрывающая скобка;
					while (!stack.empty() && GetPriority(temp.lexema) <= GetPriority(stack.top().lexema)) {
						ResultingString.push_back(stack.top());
						stack.pop();
					}
					stack.push(temp);
					if (GetPriority(temp.lexema) > GetPriority(stack.top().lexema)) {
						stack.push(temp);
					}
				}
				continue;
			}
			//может быть только 1 параметр или 0 у меня
		/*	if (temp.lexema == LEX_COMMA) {
				paramcounter++;
				while (stack.top().lexema == LEX_PLUS || stack.top().lexema == LEX_MINUS || stack.top().lexema == LEX_STAR || stack.top().lexema == LEX_DIVISION) {
					ResultingString.push_back(stack.top());
					stack.pop();
				}
				continue;
			}*/

			if (temp.lexema == LEX_LEFTHESIS) {
				stack.push(temp);
				continue;
			}

			if (temp.lexema == LEX_RIGHTHESIS) {
				while (stack.top().lexema != LEX_LEFTHESIS) {
					ResultingString.push_back(stack.top());
					stack.pop();
				}
				stack.pop();
				if (functionflag) {
					ResultingString.push_back({ LEX_AT, currentLexTableLine, functionIndexTI });
					ResultingString.push_back(LT::Entry{ (char)(paramcounter + 1 + '0'), currentLexTableLine, -1 });//бред?
					functionflag = false;
				}
				continue;
			}

			if (temp.lexema == LEX_EXCLAMATION) {
				isCompleted = true;
			}

			if (isCompleted) {
				while (!stack.empty()) {
					ResultingString.push_back(stack.top());
					stack.pop();
				}
				//std::cout << ResultingString << std::endl; //таблица лексем
				int i = lextable_pos;
				int j = 0;
				for (; lextable.table[i].lexema != LEX_EXCLAMATION; i++, j++) {
					if (j < ResultingString.size())
						lextable.table[i] = ResultingString[j];
					else if (j == ResultingString.size()) {
						lextable.table[i] = { LEX_EXCLAMATION, lextable.table[i].sn, -1 };

					}
					else {
						for (int k = i; k > lextable_pos + ResultingString.size(); k--)
							lextable.table[k] = { LEX_FREE, lextable.table[k].sn , -1 };
					}
				}
				if (j != ResultingString.size()) 
					lextable.table[i] = { LEX_FREE, lextable.table[i].sn , -1 };
				return true;
			}
		}
		return false;
	}
}