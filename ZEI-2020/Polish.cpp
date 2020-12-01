#pragma once
#include "LT.h"
#include "IT.h"
#include "Polish.h"
#include <stack>
#include <queue>
#include <string>
#include <iostream>

namespace Pn {

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

			if (temp.lexema == LEX_ID || temp.lexema == LEX_LITERAL)
			{
				if (LT::GetEntry(lextable, i + 1).lexema == LEX_LEFTHESIS) functionflag = true; //������������� ������� ���������
				else ResultingString += temp.lexema;
				continue;
			}

			if (temp.lexema == LEX_PLUS || temp.lexema == LEX_MINUS || temp.lexema == LEX_STAR || temp.lexema == LEX_SLASH) {
				if (stack.empty()) {
					stack.push(temp.lexema);
				}
				else { //�������� ����������� ��� �������� � ������� ��� ������	����������� � �������������� ������;  ������������ � ����, ���� ���� ���� ��� � ������� ����� ����� ���������� ������;
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

			if (temp.lexema == LEX_SEMICOLON) {
				isCompleted = true;
			}

			if (isCompleted) {
				while (!stack.empty()) {
					ResultingString += stack.top();
					stack.pop();
				}
				std::cout << ResultingString << std::endl; //������� ������
				int i = lextable_pos;
				for (int j = 0; lextable.table[i].lexema != LEX_SEMICOLON; i++, j++) {
					if (j < ResultingString.length())
						lextable.table[i].lexema = ResultingString[j];
					else if (j == ResultingString.length())
						lextable.table[i].lexema = LEX_SEMICOLON;
					else {
						for (int k = i; k > lextable_pos + ResultingString.length(); k--)
							lextable.table[k].lexema = LEX_FREE;
					}
				}
				lextable.table[i].lexema = LEX_FREE;
				return true;
			}
		}
		return false;
	}
}