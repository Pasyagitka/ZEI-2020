#include "Sem.h"
#include "LT.h"
#include "Error.h"

//�������: �������� �������� tiny, symbolic, �� 1 perform, ���������������, �� ����������, ������ ��������� ������, ��������� �������
namespace Sem
{
	bool Analysis(LT::LexTable lextable, IT::IdTable idtable, Log::LOG log) {
		for (int i = 0; i < lextable.size; i++) {
			switch (lextable.table[i].lexema) {
				case LEX_MORE:	case LEX_LESS: {	// ���������� ��������  < > ����� ����������� ������ ��� ����� tiny
					IT::IDDATATYPE lefttype = idtable.table[lextable.table[i - 1].indxTI].iddatatype;
					IT::IDDATATYPE righttype = idtable.table[lextable.table[i + 1].indxTI].iddatatype;
					if (lefttype != IT::IDDATATYPE::TINY || righttype != IT::IDDATATYPE::TINY)
						throw ERROR_THROW_IN(615, lextable.table[i].sn, 0); //���������� �������� < > ����� ����������� ������ ��� ����� tiny
				}
				case LEX_EQUALITY: case LEX_INEQUALITY: { // ���������� �������� = ^ ����� ����������� ������ ��� ������ tiny ��� logical
					IT::IDDATATYPE lefttype = idtable.table[lextable.table[i - 1].indxTI].iddatatype;
					IT::IDDATATYPE righttype = idtable.table[lextable.table[i + 1].indxTI].iddatatype;
					if (!((lefttype == righttype) && (lefttype == IT::IDDATATYPE::TINY || lefttype == IT::IDDATATYPE::LGCL)))
						throw ERROR_THROW_IN(616, lextable.table[i].sn, 0); // ���������� �������� = ^ ����� ����������� ������ ��� ������ tiny ��� logical
					break;
				}
				case LEX_SET: { //set symbolic r : foo(r)!
					for (int y = i + 3; lextable.table[y].lexema != LEX_EXCLAMATION; y++) {
						if (idtable.table[lextable.table[i + 2].indxTI].id == idtable.table[lextable.table[y].indxTI].id)
							throw ERROR_THROW_IN(605, lextable.table[y].sn, 0); //���������� ������� ������� � ����������� ���������������
					}
					break;
				}
				case LEX_ASSIGN:	{
					IT::IDDATATYPE lefttype = idtable.table[lextable.table[i - 1].indxTI].iddatatype;
					IT::IDDATATYPE righttype = lefttype;
					for (int j = i + 1; lextable.table[j].lexema != LEX_EXCLAMATION;) { //+-*#()\/
						if (lextable.table[j].lexema != LEX_PLUS && lextable.table[j].lexema != LEX_MINUS && lextable.table[j].lexema != LEX_STAR && lextable.table[j].lexema != LEX_DIVISION && lextable.table[j].lexema != LEX_LEFTHESIS && lextable.table[j].lexema != LEX_RIGHTHESIS && lextable.table[j].lexema != LEX_RIGHTSHIFT && lextable.table[j].lexema != LEX_LEFTSHIFT)	{	
							if (idtable.table[lextable.table[j].indxTI].idtype == IT::F) {	//������������ �������
								righttype = idtable.table[lextable.table[j].indxTI].iddatatype;
								while (lextable.table[j-1].lexema != LEX_RIGHTHESIS)	j++; //������������ � ����� ����������
								continue;
							}
							if (righttype != idtable.table[lextable.table[j].indxTI].iddatatype) { //tiny : tiny + symbolic!
								throw ERROR_THROW_IN(613, lextable.table[i].sn, 0); //���� ������ � ��������� �� ���������
							}
							else if (lextable.table[j].lexema == LEX_LIBFUNC) {
								righttype = idtable.table[lextable.table[j].indxTI].iddatatype;
								if (idtable.table[lextable.table[j].indxTI].parameters.count == 1)	j = j + 4;// b(i)!
								else if (idtable.table[lextable.table[j].indxTI].parameters.count == 0) j = j + 3;	//b()!
							}
							else	{
								righttype = idtable.table[lextable.table[j].indxTI].iddatatype; //� ���� ������ ����������� ������ ���, ���� ����� ��������
								j++;
							}
						}
						else
							j++;
					}
					if (lefttype != righttype)
						throw ERROR_THROW_IN(617, lextable.table[i].sn, 0); // tiny : symbolic!
					//�������� ���������. ������������ ����� ����� � ������ �� ����� ������������
					break;
				}
				case LEX_FUNCTION:
				{
					IT::IDDATATYPE functionType = idtable.table[lextable.table[i + 1].indxTI].iddatatype;
					for (int j = i; j < lextable.size; j++) 	{
						if (lextable.table[j].lexema == LEX_GIVEBACK) 	{
							IT::IDDATATYPE givebackType = idtable.table[lextable.table[j + 1].indxTI].iddatatype;
							if (functionType != givebackType)	{
								throw ERROR_THROW_IN(608, lextable.table[i].sn, 0); //������������ ���� ������� � ���� ������������� ��������
							}
							else break;
						}
					}
					break;
				}
				case LEX_ID: case LEX_LIBFUNC:  {
					if ((idtable.table[lextable.table[i].indxTI].idtype == IT::F || idtable.table[lextable.table[i].indxTI].idtype == IT::B)
						&& lextable.table[i - 1].lexema != LEX_FUNCTION) { 
						int paramCounter = 0;
						IT::Entry* ITEntry = new IT::Entry();
						*ITEntry = IT::GetEntry(idtable, lextable.table[i].indxTI);
						for (int j = i + 2; lextable.table[j].lexema != LEX_RIGHTHESIS; j++)	{
							if (lextable.table[j].lexema == LEX_ID || lextable.table[j].lexema == LEX_LITERAL)	{
								paramCounter++;
								if (paramCounter > ITEntry->parameters.count) {
									throw  ERROR_THROW_IN(611, lextable.table[i].sn, 0); //������� ����� ���������� � ������ �������
								}
								if (idtable.table[lextable.table[j].indxTI].iddatatype	!= ITEntry->parameters.typeofparameter[paramCounter - 1]) {
									throw  ERROR_THROW_IN(610, lextable.table[i].sn, 0); //�������� ��������� ���������� �������
								}
							}
						}
						if (paramCounter < ITEntry->parameters.count)
							throw  ERROR_THROW_IN(612, lextable.table[i].sn, 0); //������� ���� ���������� � ������ �������
						delete ITEntry;
					}
					if (idtable.table[lextable.table[i].indxTI].iddatatype != IT::TINY) { //��������, symbolic : symbolic + symbolic!
						for (int j = i + 1; lextable.table[j].lexema != LEX_EXCLAMATION && lextable.table[j].lexema != LEX_RIGHTHESIS; j++) {
							if (lextable.table[j].lexema == LEX_PLUS || lextable.table[j].lexema == LEX_MINUS || lextable.table[j].lexema == LEX_STAR || lextable.table[j].lexema == LEX_DIVISION) {
								throw  ERROR_THROW_IN(614, lextable.table[i].sn, 0); //�������������� �������� ����� ����������� ������ ��� ����� tiny
							} 
						}
					}
					break;
				}

			}
		}
		return true;
	}
}