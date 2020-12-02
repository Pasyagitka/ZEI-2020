#pragma once
#include "Parm.h"
#include <fstream>
#define TI_TABLE_SIZE 100
#define ID_MAXSIZE 15					//макс кол-во символов в идентификаторе
#define TI_MAXSIZE 1024					//макс кол-во строк в таблице индентификаторов
#define TI_INT_DEFAULT 0x00000000		//значение по умолчанию для типа инт
#define TI_STR_DEFAULT 0x00				//значение по умолчанию для типа стр
#define TI_NULLIDX 0xffffffff			//нет элемента таблицы идентификаторов
#define TI_STR_MAXSIZE 255

namespace IT
{

	enum IDDATATYPE
	{
		TINY = 1, SYMB, LGCL //типы данных идентификаторов
	};

	enum IDTYPE
	{
		V = 1, L, F, B //тип идентификатора(переменная, литерал), функция, библиотечная функция
	};
 
	struct Entry
	{
		short idxfirstLE;//индекс первой строки в таблице лексем
		char id[ID_MAXSIZE * 2];//идентификатор(автоматически усекается до ID_MAXSIZE)
		char postfix[ID_MAXSIZE];
		IDDATATYPE iddatatype;//тип данных
		IDTYPE idtype;//тип идентификатора.
		union
		{
			char vbool[6];
			int vint;//значение инт
			struct
			{
				int len;//длина строки стр
				char str[TI_STR_MAXSIZE - 1];//строка
			}vstr[TI_STR_MAXSIZE];//значение стр
		}value;//значение идентификатора
	};
	
	struct IdTable//экземпляр таблицы идентификаторов
	{
		int maxsize;//макс емкость таблицы идентификаторов( < TI_MAXSIZE)
		int size;//текущий размер таблицы идентификаторов ( < maxsize)
		Entry* table;//массив строк таблицы идентификаторов
	};

	struct ID
	{
		wchar_t idfile[PARM_MAX_SIZE];
		std::ofstream* stream;
	};

	static const ID INITID = { L"", NULL };//для начальной инициализации ID
	ID getid(wchar_t idfile[]);	//сформировать структуру ID
	IdTable Create(int size);	//емкость таблицы идентификаторов < TI_MAXSIZE
	void Add(IdTable& itable, Entry entry);
	Entry GetEntry(IdTable& itable, int n);
	int IsId(						//возврат: номер строки (если есть), TI_NULLIDX(если нет)
		IdTable& idtable,		//экземпляр таблицы идентификаторов
		char id[ID_MAXSIZE]		//идентификатор
	);
	void Delete(IdTable& itable);
	void WriteId(ID id, IT::IdTable& itable); 
	void Close(ID id); 
	void WriteIdHeading(ID id); 
}