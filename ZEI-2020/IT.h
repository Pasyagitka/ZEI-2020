#pragma once
#include "Parm.h"
#include <fstream>
#define TI_TABLE_SIZE 100
#define ID_MAXSIZE 15					//���� ���-�� �������� � ��������������
#define TI_MAXSIZE 1024					//���� ���-�� ����� � ������� ����������������
#define TI_TINY_DEFAULT 0x00000000		//�������� �� ��������� ��� ���� ���
#define TI_SYMB_DEFAULT 0x00				//�������� �� ��������� ��� ���� ���
#define TI_NULLIDX 0xffffffff			//��� �������� ������� ���������������

#define TI_STR_MAXSIZE 255
#define MAXPARMCOUNT 3


namespace IT
{

	enum IDDATATYPE
	{
		TINY = 1, SYMB, LGCL, UNDEF //���� ������ ���������������
	};

	enum IDTYPE
	{
		V = 1, L, F, B, P, U //��� ��������������(����������, �������), �������, ������������ �������, ��������, �� ����������
	};

	struct Entry
	{
		short idxfirstLE;//������ ������ ������ � ������� ������
		char id[ID_MAXSIZE * 2] = "";//�������������(������������� ��������� �� ID_MAXSIZE)
		char postfix[ID_MAXSIZE];
		IDDATATYPE iddatatype = IDDATATYPE::UNDEF;//��� ������
		IDTYPE idtype = IDTYPE::U;//��� ��������������.
		union
		{
			char vlogical[6];
			int vtiny;//�������� tiny
			struct
			{
				int len;//����� ������ ���
				char str[TI_STR_MAXSIZE - 1];//������
			}vsymb[TI_STR_MAXSIZE];//�������� ���
		}value;//�������� ��������������
		struct
		{
			int count = 0; 
			IDDATATYPE typeofparameter[MAXPARMCOUNT];
		} parameters;
	};
	
	struct IdTable//��������� ������� ���������������
	{
		int maxsize;//���� ������� ������� ���������������( < TI_MAXSIZE)
		int size;//������� ������ ������� ��������������� ( < maxsize)
		Entry* table;//������ ����� ������� ���������������
	};

	IdTable Create(int size);	//������� ������� ��������������� < TI_MAXSIZE
	void Add(IdTable& itable, Entry entry);
	Entry GetEntry(IdTable& itable, int n);
	int IsId(IdTable& idtable,	char id[ID_MAXSIZE]);
	int IsId(IdTable& idtable, char id[ID_MAXSIZE], char* postfix);
	void Delete(IdTable& itable);
}