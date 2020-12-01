#pragma once
#include "Parm.h"
#include <fstream>

#define LT_TABLE_SIZE 300
#define LT_MAXSIZE 4096					//������������ ���-�� ����� � ������� ������
#define LT_TI_NULLIDX 0xffffffff		//��� ��-�� ������� ����������������
#define LEX_INTEGER 't'
#define LEX_STRING 't'
#define LEX_BOOL 't'
#define LEX_ID 'i'
#define LEX_LITERAL 'l'
#define LEX_DVV 'd'
#define LEX_IF 'w'
#define LEX_ELSE 'e'
#define LEX_PRINT 'p'
#define LEX_FUNCTION 'f'
#define LEX_LIBFUNC 's'
#define LEX_RETURN 'r'
#define LEX_POINT '.'
#define LEX_COMMA ','
#define LEX_LEFTBRACE '['
#define LEX_RIGHTBRACE ']'
#define LEX_LEFTHESIS '('
#define LEX_RIGHTHESIS ')'
#define LEX_MORE '>'
#define LEX_LESS '<'
#define LEX_EQUALLY '='
#define LEX_COMPARE ':'
#define LEX_PLUS '+'
#define LEX_MINUS '-'
#define LEX_STAR '*'
#define LEX_SLASH '/'
#define LEX_ENDL '\n'
#define LEX_END '\0'
#define LEX_SPACE ' '
#define LEX_APOS '\''
#define LEX_SEMICOLON ';'
#define LEX_QUOTE '"'
#define LEX_FREE		'%'	//��� ���������
#define LEX_AT			'@'


namespace LT
{
	struct Entry//������ ������� ������
	{
		char lexema;
		int sn;//����� ������ � ������
		int indxTI;//������ � ������� ��������������� ��� LT_TI_NULLIDX
		int parm; // ���������� ���������� � �������
		char buf[LT_MAXSIZE * 2]; // ������ ��� ����� � �������� ������
		int sign;
		int priority;
	};

	struct LexTable//�������� ������� ������
	{
		int maxsize;//������� ������� ������( < LT_MAXSIZE)
		int size;//������� ������ ������� ������ ( < maxsize)
		Entry* table;//������ ����� ������� ������
	};

	struct LEX
	{
		wchar_t lexfile[PARM_MAX_SIZE];
		std::ofstream* stream;
	};

	static const LEX INITLEX = { L"", NULL };	//��� ��������� ������������� Lex
	LexTable Create(int);//������� ������� ������(������� ������� ������ < LT_MAXSIZE)
	void Add(LexTable&, Entry&);//�������� ������ � ������� ������(lextable, entry)
	Entry GetEntry(LexTable&, int);	//�������� ������ ������� ������(lextable, '����� ���������� ������')
	void Delete(LexTable&);//������� ������� ������
	LEX getlex(wchar_t lexfile[]);
	void Close(LEX lx);
	void WriteLex(LEX lx, LT::LexTable& ltable); 
	void WriteLexHeading(LEX lx); 
}
