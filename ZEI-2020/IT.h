#pragma once
#include "Parm.h"
#include <fstream>
#define TI_TABLE_SIZE 100
#define ID_MAXSIZE 15					//макс кол-во символов в идентификаторе
#define TI_MAXSIZE 1024					//макс кол-во строк в таблице индентификаторов
#define TI_TINY_DEFAULT 0x00000000		//значение по умолчанию для типа инт
#define TI_SYMB_DEFAULT 0x00				//значение по умолчанию для типа стр
#define TI_NULLIDX 0xffffffff			//нет элемента таблицы идентификаторов

#define TI_STR_MAXSIZE 255
#define MAXPARMCOUNT 3


namespace IT
{

	enum IDDATATYPE
	{
		TINY = 1, SYMB, LGCL, UNDEF //типы данных идентификаторов
	};

	enum IDTYPE
	{
		V = 1, L, F, B, P, U //тип идентификатора(переменная, литерал), функция, библиотечная функция, параметр, не определено
	};

	struct Entry
	{
		short idxfirstLE;//индекс первой строки в таблице лексем
		char id[ID_MAXSIZE * 2] = "";//идентификатор(автоматически усекается до ID_MAXSIZE)
		char postfix[ID_MAXSIZE];
		IDDATATYPE iddatatype = IDDATATYPE::UNDEF;//тип данных
		IDTYPE idtype = IDTYPE::U;//тип идентификатора.
		union
		{
			char vlogical[6];
			int vtiny;//значение tiny
			struct
			{
				int len;//длина строки стр
				char str[TI_STR_MAXSIZE - 1];//строка
			}vsymb[TI_STR_MAXSIZE];//значение стр
		}value;//значение идентификатора
		struct
		{
			int count = 0; 
			IDDATATYPE typeofparameter[MAXPARMCOUNT];
		} parameters;
	};
	
	struct IdTable//экземпляр таблицы идентификаторов
	{
		int maxsize;//макс емкость таблицы идентификаторов( < TI_MAXSIZE)
		int size;//текущий размер таблицы идентификаторов ( < maxsize)
		Entry* table;//массив строк таблицы идентификаторов
	};

	IdTable Create(int size);	//емкость таблицы идентификаторов < TI_MAXSIZE
	void Add(IdTable& itable, Entry entry);
	Entry GetEntry(IdTable& itable, int n);
	int IsId(IdTable& idtable,	char id[ID_MAXSIZE]);
	int IsId(IdTable& idtable, char id[ID_MAXSIZE], char* postfix);
	void Delete(IdTable& itable);
}