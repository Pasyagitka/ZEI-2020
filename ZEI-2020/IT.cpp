#include "Error.h"
#include "IT.h"
#include <tchar.h>
#include <fstream>
#include <iomanip>
#include "Log.h"
#include "Lan.h"

namespace IT
{
	IdTable Create(int size)
	{
		if (size >= TI_MAXSIZE)
			throw ERROR_THROW(304); //превышена макс длина табл ид
		IdTable itable = { size, 0, new Entry[size] };
		return itable;
	}

	void Add(IdTable& itable, Entry istr)
	{
		if (itable.size >= itable.maxsize)
			throw ERROR_THROW(305); //таблица переполнена
		itable.table[itable.size++] = istr;
	}

	void Delete(IdTable& itable)
	{
		if (!&itable)
			throw ERROR_THROW(306); 
		delete itable.table;
		itable.table = nullptr;
	}

	Entry GetEntry(IdTable& itable, int nstr)
	{
		if (itable.size < nstr)
			throw ERROR_THROW(307); //недопустимый номер стрки
		return itable.table[nstr];
	}

	int IsId(IdTable& idtable, char id[ID_MAXSIZE]) {
		for (int i = 0; i < idtable.size; i++) {
			if (!strcmp(idtable.table[i].id, id))
				return i; //idtable.table[i].idxfirstLE;
		}
		return TI_NULLIDX;
	}	

	int IsId(IdTable& idtable, char id[ID_MAXSIZE], char *postfix) {
		for (int i = 0; i < idtable.size; i++) {
			if ( !strcmp(idtable.table[i].id, id) && (!strcmp(idtable.table[i].postfix, postfix) || !strcmp(idtable.table[i].postfix, POSTFIXGLOBAL)))
				return i; //idtable.table[i].idxfirstLE;
		}
		return TI_NULLIDX;
	}
}