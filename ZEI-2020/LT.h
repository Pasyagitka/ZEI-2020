#pragma once
#include "Parm.h"
#include <fstream>

#define LT_TABLE_SIZE 300
#define LT_MAXSIZE 4096					//������������ ���-�� ����� � ������� ������
#define LT_TI_NULLIDX  -1		//��� ��-�� ������� ����������������
#define LEX_TINY		't'
#define LEX_SYMBOLIC	't'
#define LEX_LOGICAL		't'
#define LEX_ID			'i'
#define LEX_LITERAL		'l'
#define LEX_LIB			'z'
#define LEX_WHEN		'w' //if
#define LEX_OTHERWISE	'o' // else
#define LEX_SHOW		'h'		//����� h
#define LEX_FUNCTION	'f'
#define LEX_LIBFUNC		'b'
#define LEX_GIVEBACK	'g'
#define LEX_PERFORM		'p'
#define LEX_LOOP		'y'
#define LEX_SET			's'
#define LEX_LEFTSHIFT   '\\'
#define LEX_RIGHTSHIFT	'/'

#define LEX_POINT		'.'
#define LEX_COMMA		','
#define LEX_LEFTBRACE	'['
#define LEX_RIGHTBRACE	']'
#define LEX_LEFTHESIS	'('
#define LEX_RIGHTHESIS	')'
#define LEX_RIGHTFIGUREBRACE '}'
#define LEX_LEFTFIGUREBRACE	'{'
#define LEX_MORE		'>'
#define LEX_LESS		'<'
#define LEX_EQUALITY	'='
#define LEX_INEQUALITY	'^'
#define LEX_COMPARE		':' //?
#define LEX_PLUS		'+'
#define LEX_MINUS		'-'
#define LEX_STAR		'*'
#define LEX_DIVISION	'#'
#define LEX_ENDL		'\n'
#define LEX_END			'\0'
#define LEX_SPACE		' '
#define LEX_APOS		'\''
#define LEX_SEMICOLON	';'
#define LEX_QUOTE		'"'
#define LEX_FREE		'%'	//��� ���������
#define LEX_AT			'@'
#define LEX_EXCLAMATION '!'


namespace LT
{
	struct Entry//������ ������� ������
	{
		char lexema;
		int sn;//����� ������ � ������
		int indxTI;//������ � ������� ��������������� ��� LT_TI_NULLIDX
		char buf[300]; // ������ ��� ����� � �������� ������
	};

	struct LexTable//�������� ������� ������
	{
		int maxsize;//������� ������� ������( < LT_MAXSIZE)
		int size;//������� ������ ������� ������ ( < maxsize)
		Entry* table;//������ ����� ������� ������
	};

	LexTable Create(int);//������� ������� ������(������� ������� ������ < LT_MAXSIZE)
	void Add(LexTable&, Entry&);//�������� ������ � ������� ������(lextable, entry)
	Entry GetEntry(LexTable&, int);	//�������� ������ ������� ������(lextable, '����� ���������� ������')
	void Delete(LexTable&);//������� ������� ������
}
