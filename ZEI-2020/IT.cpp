#include "Error.h"
#include "IT.h"
#include <tchar.h>
#include <fstream>
#include <iomanip>
#include "Log.h"

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
		itable.table[itable.size] = istr;
		itable.size++;
		if (itable.size >= itable.maxsize)
			throw ERROR_THROW(305);//таблица переполнена
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
		if (itable.size > nstr)
			throw ERROR_THROW(307); //недопустимый номер стрки
		return itable.table[nstr];
	}

	ID getid(wchar_t idfile[])
	{
		ID id;
		wcscpy_s(id.idfile, idfile);
		std::ofstream* FILE = new std::ofstream;
		(*FILE).open(idfile);
		if (!(*FILE).is_open())
			throw ERROR_THROW(114);
		id.stream = FILE;
		return id;
	}
	void Close(ID id)
	{
		if (id.stream != nullptr) {
			id.stream->close();
			delete id.stream;
		}
	}
	void WriteId(ID id, IT::IdTable& itable)
	{
		WriteIdHeading(id);
		*id.stream << "Строка\tТип ID\t\tТип данных\tИмя\tЗначение\n";
		for (unsigned int i = 0; i < (unsigned int)itable.size; i++)
		{
			*id.stream << itable.table[i].idxfirstLE + 1 << "\t";

			if (itable.table[i].idtype == IT::TINY)*id.stream << "variable";
			else if (itable.table[i].idtype == IT::SYMB)*id.stream << "literal";
			else if (itable.table[i].idtype == IT::LGCL)*id.stream << "function";

			*id.stream << "\t\t";

			if (itable.table[i].iddatatype == IT::TINY)*id.stream << "tiny";
			else if (itable.table[i].iddatatype == IT::SYMB)*id.stream << "symbolic";
			else if (itable.table[i].iddatatype == IT::LGCL)*id.stream << "logical";

			*id.stream << "\t\t" << itable.table[i].id << "\t";

			if (itable.table[i].iddatatype == IT::TINY)			*id.stream << itable.table[i].value.vint;
			else if (itable.table[i].iddatatype == IT::SYMB)		*id.stream << itable.table[i].value.vstr->str;
			else if (itable.table[i].iddatatype == IT::LGCL)	*id.stream << itable.table[i].value.vbool;
			*id.stream << std::endl;
		}
	}
	void WriteIdHeading(ID id)
	{
		time_t t = time(0);
		tm currentTime;
		localtime_s(&currentTime, &t);
		char str[TIME_SIZE];
		strftime(str, TIME_SIZE, "%d.%m.%Y %H:%M:%S", &currentTime);
		*id.stream << "------------ Таблица идентификаторов--------------------------- " << str << " ---------" << std::endl;
	}
	
}