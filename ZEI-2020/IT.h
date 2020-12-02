#pragma once
#include "Parm.h"
#include <fstream>
#define TI_TABLE_SIZE 100
#define ID_MAXSIZE 15					//���� ���-�� �������� � ��������������
#define TI_MAXSIZE 1024					//���� ���-�� ����� � ������� ����������������
#define TI_INT_DEFAULT 0x00000000		//�������� �� ��������� ��� ���� ���
#define TI_STR_DEFAULT 0x00				//�������� �� ��������� ��� ���� ���
#define TI_NULLIDX 0xffffffff			//��� �������� ������� ���������������
#define TI_STR_MAXSIZE 255

namespace IT
{

	enum IDDATATYPE
	{
		TINY = 1, SYMB, LGCL //���� ������ ���������������
	};

	enum IDTYPE
	{
		V = 1, L, F //��� ��������������(����������, �������)
	};
 
	struct Entry
	{
		short idxfirstLE;//������ ������ ������ � ������� ������
		char id[ID_MAXSIZE * 2];//�������������(������������� ��������� �� ID_MAXSIZE)
		char postfix[ID_MAXSIZE];
		IDDATATYPE iddatatype;//��� ������
		IDTYPE idtype;//��� ��������������.
		union
		{
			char vbool[6];
			int vint;//�������� ���
			struct
			{
				int len;//����� ������ ���
				char str[TI_STR_MAXSIZE - 1];//������
			}vstr[TI_STR_MAXSIZE];//�������� ���
		}value;//�������� ��������������
	};
	
	struct IdTable//��������� ������� ���������������
	{
		int maxsize;//���� ������� ������� ���������������( < TI_MAXSIZE)
		int size;//������� ������ ������� ��������������� ( < maxsize)
		Entry* table;//������ ����� ������� ���������������
	};

	struct ID
	{
		wchar_t idfile[PARM_MAX_SIZE];
		std::ofstream* stream;
	};

	static const ID INITID = { L"", NULL };//��� ��������� ������������� ID
	ID getid(wchar_t idfile[]);	//������������ ��������� ID
	IdTable Create(int size);	//������� ������� ��������������� < TI_MAXSIZE
	void Add(IdTable& itable, Entry entry);
	Entry GetEntry(IdTable& itable, int n);
	void Delete(IdTable& itable);
	void WriteId(ID id, IT::IdTable& itable); 
	void Close(ID id); 
	void WriteIdHeading(ID id); 
}