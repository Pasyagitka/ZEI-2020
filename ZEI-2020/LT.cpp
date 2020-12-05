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
			throw ERROR_THROW(300); //�������� ������ ������� ������
		LexTable ltable = { size, 0, new Entry[size]};
		return ltable;
	}

	void Add(LexTable& ltable, Entry& lstr)
	{
		if (ltable.size >= ltable.maxsize)
			throw ERROR_THROW(113); //������� �����������
		ltable.table[ltable.size] = lstr;
		ltable.size++;
	}

	void Delete(LexTable& ltable)
	{
		if (!&ltable)
			throw ERROR_THROW(302); //������� ������, ��������, ��� �� �������
		delete ltable.table;
		ltable.table = nullptr;
	}

	Entry GetEntry(LexTable& ltable, int nstr)
	{
		if (ltable.size < nstr)
			throw ERROR_THROW(115); //����� ������������
		return ltable.table[nstr];
	}
}