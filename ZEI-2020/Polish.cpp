#pragma once
#include "LT.h"
#include "IT.h"
#include "Polish.h"
#include <stack>
#include <queue>
#include <string>
#include <iostream>
//TODO: �������� ������� ��� {}
//TODO ������ ��������� ��������������? str
//TODO ��� �� ������, ��� ��� �� ������� ����?? b h - ��� ���-�� ������������� ���������
namespace Pn {
	void ToPolish(LT::LexTable& lextable, IT::IdTable& idtable) {
		for (int i = 0; i < lextable.size; i++) {
			if (lextable.table[i].lexema == ':')
				PolishNotation(i +1, lextable, idtable);
			/*if (lextable.table[i].lexema == 'h')
				PolishNotation(i, lextable, idtable);*/
		}
	}

	//switch
	int GetPriority(char c) {
		switch (c)
		{
		case LEX_LEFTHESIS: case LEX_RIGHTHESIS:		return 0;
		case LEX_COMMA:									return 1;
		case LEX_PLUS:  case LEX_MINUS:					return 2;
		case LEX_STAR: case LEX_DIVISION:					return 3;
		default:										return 0;
		}
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


			if (temp.lexema == LEX_ID || temp.lexema == LEX_LITERAL /*|| temp.lexema == LEX_LIBFUNC || temp.lexema == LEX_SHOW*/)
			{
				//if (lextable.table[i].indxTI != -1 && (idtable.table[lextable.table[i].indxTI].idtype== IT::F
				//	|| idtable.table[lextable.table[i].indxTI].idtype == IT::B))
				//	functionflag = true; //������������� ������� ��������� � ���???
				//else 
				ResultingString += temp.lexema;
				continue;
			}

			if (temp.lexema == LEX_PLUS || temp.lexema == LEX_MINUS || temp.lexema == LEX_STAR || temp.lexema == LEX_DIVISION) {
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
				//paramcounter++;
				while (stack.top() == LEX_PLUS || stack.top() == LEX_MINUS || stack.top() == LEX_STAR || stack.top() == LEX_DIVISION) {
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
				/*if (functionflag) {
					ResultingString += LEX_AT;
					ResultingString += std::to_string(paramcounter + 1);
					functionflag = false;
				}*/
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
				//std::cout << ResultingString << std::endl; //������� ������
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