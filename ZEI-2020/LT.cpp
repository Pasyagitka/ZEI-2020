#include "LT.h"
#include "Error.h"
#include <fstream>
#include <time.h>
#include "Log.h"
using namespace std;

namespace LT
{
	LexTable Create(int size)
	{
		if (size >= LT_MAXSIZE)
			throw ERROR_THROW(300); //превышен размер таблицы лексем
		LexTable ltable = { size, 0, new Entry[size]};
		return ltable;
	}

	void Add(LexTable& ltable, Entry& lstr)
	{
		if (ltable.size >= ltable.maxsize)
			throw ERROR_THROW(113); //таблица переполнена
		ltable.table[ltable.size] = lstr;
		ltable.size++;
	}

	void Delete(LexTable& ltable)
	{
		if (!&ltable)
			throw ERROR_THROW(302); //таблица лексем, веро€тно, ещЄ не создана
		delete ltable.table;
		ltable.table = nullptr;
	}

	Entry GetEntry(LexTable& ltable, int nstr)
	{
		if (ltable.size < nstr)
			throw ERROR_THROW(115); //номер недопустимый
		return ltable.table[nstr];
	}

	LEX getlex(wchar_t lexfile[])
	{
		LEX lx;
		wcscpy_s(lx.lexfile, lexfile);
		ofstream* FILE = new ofstream;
		(*FILE).open(lexfile);
		if (!(*FILE).is_open())
			throw ERROR_THROW(113); //ошибка файла lex
		lx.stream = FILE;
		return lx;
	}

	void Close(LEX lex)
	{
		if (lex.stream != nullptr) {
			lex.stream->close();
			delete lex.stream;
		}
	}

	void WriteLex(LEX lx, LT::LexTable& ltable)
	{
		WriteLexHeading(lx);
		unsigned int compLine = -1;
		for (unsigned int i = 0; i < (unsigned int)ltable.size; i++)
		{
			if (compLine != ltable.table[i].sn)
			{
				*lx.stream << endl << ltable.table[i].sn << "\t" ;
				compLine = ltable.table[i].sn;
			}
			*lx.stream << ltable.table[i].lexema;
			//if (ltable.table[i].indxTI != -1) *lx.stream << ltable.table[i].indxTI;
		}
	}
	void WriteLexHeading(LEX lx)
	{
		time_t t = time(0);
		tm currentTime;
		localtime_s(&currentTime, &t);
		char str[TIME_SIZE];
		strftime(str, TIME_SIZE, "%d.%m.%Y %H:%M:%S", &currentTime);
		*lx.stream << "------------ “аблица лексем --------------------------- " << str << " ---------";
	}
}