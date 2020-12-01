#pragma once
#include "Parm.h"
#include <fstream>

#define LT_TABLE_SIZE 300
#define LT_MAXSIZE 4096					//максимальнео кол-во строк в таблице лексем
#define LT_TI_NULLIDX 0xffffffff		//нет эл-та таблицы индентификаторов
#define LEX_TINY		't'
#define LEX_SYMBOLIC	't'
#define LEX_LOGICAL		't'
#define LEX_ID			'i'
#define LEX_LITERAL		'l'
#define LEX_LIB			'z'
#define LEX_WHEN		'w' //if
#define LEX_OTHERWISE	'o' // else
#define LEX_SHOW		'h'		//вывод h
#define LEX_FUNCTION	'f'
#define LEX_LIBFUNC		'b'
#define LEX_GIVEBACK	'g'
#define LEX_PERFORM		'p'
#define LEX_LOOP		'y'

#define LEX_POINT		'.'
#define LEX_COMMA		','
#define LEX_LEFTBRACE	'['
#define LEX_RIGHTBRACE	']'
#define LEX_LEFTHESIS	'('
#define LEX_RIGHTHESIS	')'
#define LEX_MORE		'>'
#define LEX_LESS		'<'
#define LEX_EQUALITY	'='
#define LEX_COMPARE		':' //?
#define LEX_PLUS		'+'
#define LEX_MINUS		'-'
#define LEX_STAR		'*'
#define LEX_SLASH		'/'
#define LEX_ENDL		'\n'
#define LEX_END			'\0'
#define LEX_SPACE		' '
#define LEX_APOS		'\''
#define LEX_SEMICOLON	';'
#define LEX_QUOTE		'"'
#define LEX_FREE		'%'	//дл€ удаленных
#define LEX_AT			'@'
#define LEX_EXCLAMATION '!'

namespace LT
{
	struct Entry//строка таблицы лексем
	{
		char lexema;
		int sn;//номер строки в тексте
		int indxTI;//индекс в таблице идентификаторов или LT_TI_NULLIDX
		int parm; // количество параметров в функции
		char buf[LT_MAXSIZE * 2]; // буффер дл€ св€зи с таблицей лексем
		int sign;
		int priority;
	};

	struct LexTable//экземп€р таблицы лексем
	{
		int maxsize;//емкость таблицы лексем( < LT_MAXSIZE)
		int size;//текущий размер таблицы лексем ( < maxsize)
		Entry* table;//массив строк таблицы лексем
	};

	struct LEX
	{
		wchar_t lexfile[PARM_MAX_SIZE];
		std::ofstream* stream;
	};

	static const LEX INITLEX = { L"", NULL };	//дл€ начальной инициализации Lex
	LexTable Create(int);//создать таблицу лексем(емкость таблицы лексем < LT_MAXSIZE)
	void Add(LexTable&, Entry&);//добавить строку в таблицу лексем(lextable, entry)
	Entry GetEntry(LexTable&, int);	//получить строку таблицы лексем(lextable, 'номер получаемой строки')
	void Delete(LexTable&);//удалить таблицу лексем
	LEX getlex(wchar_t lexfile[]);
	void Close(LEX lx);
	void WriteLex(LEX lx, LT::LexTable& ltable); 
	void WriteLexHeading(LEX lx); 
}
