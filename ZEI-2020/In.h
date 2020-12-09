#pragma once
#define IN_MAX_LEN_TEXT 1024*1024	// ������������ ������ ��������� ���� = 1MB
#define SIZE 10000
#define IN_CODE_ENDL '\n'		//������ ����� ������
#define IN_CODE_N '\0'			//������ �����
#define IN_CODE_QUOTE			'"' 
#define IN_CODE_SPACE			' '
#define IN_CODE_COMPARE			':'
#define IN_CODE_COMMA			','
#define IN_CODE_LEFTBRACE		'{'
#define IN_CODE_RIGHTBRACE		'}'
#define IN_CODE_OPENBRACKET		'('
#define IN_CODE_CLOSEBRACKET	')'
#define IN_CODE_PLUS			'+' 
#define IN_CODE_MINUS			'-' 
#define	IN_CODE_STAR			'*' 
#define IN_CODE_DIVISION		'#' 
#define IN_CODE_EUALITY			'='
#define IN_CODE_COMMENT			'~'
#define IN_CODE_LEFTSHIFT       '<'
#define IN_CODE_RIGHTSHIFT      '>'


// ������� �������� ������� ����������, ������ = ��� (Windows-1251) �������
//���� 0 <= �������� < 256 - �� �������� ������ ��������
#define IN_CODE_TABLE {\
	     IN::F,      IN::F,      IN::F,	     IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,      IN::F, /*t*/IN::I, /*r*/IN::T,      IN::F,      IN::F,      IN::F,      IN::F,      IN::F, \
		 IN::F,		 IN::F,		 IN::F,      IN::F, 	 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,	     IN::F,      IN::F,      IN::F,		 IN::F,	     IN::F,	     IN::F, \
	/* */IN::T, /*!*/IN::T, /*"*/IN::T, /*#*/IN::T, /*$*/IN::F, /*%*/IN::F, /*&*/IN::F, /*'*/IN::T, /*(*/IN::T, /*)*/IN::T, /***/IN::T, /*+*/IN::T, /*,*/IN::T, /*-*/IN::T, /*.*/IN::T, /*/*/IN::T, \
	/*0*/IN::T, /*1*/IN::T, /*2*/IN::T, /*3*/IN::T, /*4*/IN::T, /*5*/IN::T, /*6*/IN::T, /*7*/IN::T, /*8*/IN::T, /*9*/IN::T, /*:*/IN::T, /*;*/IN::F, /*<*/IN::T, /*=*/IN::T, /*>*/IN::T, /*?*/IN::F, \
	/*@*/IN::F, /*A*/IN::T, /*B*/IN::T, /*C*/IN::T, /*D*/IN::T, /*E*/IN::T, /*F*/IN::T, /*G*/IN::T, /*H*/IN::T, /*I*/IN::T, /*J*/IN::T, /*K*/IN::T, /*L*/IN::T, /*M*/IN::T, /*N*/IN::T, /*O*/IN::T, \
	/*P*/IN::T, /*Q*/IN::T, /*R*/IN::T, /*S*/IN::T, /*T*/IN::T, /*U*/IN::T, /*V*/IN::T, /*W*/IN::T, /*X*/IN::T, /*Y*/IN::T, /*Z*/IN::T, /*[*/IN::T, /*\*/IN::F, /*]*/IN::T, /*^*/IN::T, /*_*/IN::F, \
	/*`*/IN::F, /*a*/IN::T, /*b*/IN::T, /*c*/IN::T, /*d*/IN::T, /*e*/IN::T, /*f*/IN::T, /*g*/IN::T, /*h*/IN::T, /*i*/IN::T, /*j*/IN::T, /*k*/IN::T, /*l*/IN::T, /*m*/IN::T, /*n*/IN::T, /*o*/IN::T, \
	/*p*/IN::T, /*q*/IN::T, /*r*/IN::T, /*s*/IN::T, /*t*/IN::T, /*u*/IN::T, /*v*/IN::T, /*w*/IN::T, /*x*/IN::T, /*y*/IN::T, /*z*/IN::T, /*{*/IN::T, /*|*/IN::F, /*}*/IN::T, /*~*/IN::F,      IN::F, \
	\
		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F, \
		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F, \
		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F, \
		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F,		 IN::F, \
	/*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, \
	/*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, \
	/*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, \
	/*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, /*�*/IN::F, \
			}

namespace In
{
	struct IN	//�������� ������
	{
		enum { T, F, I }; // � - ���������� ������, F - ������������, I - ������������, ����� ��������
		int size;		// ������ ��������� ����
		int lines;		// ���������� �����
		int ignor;		// ���������� ����������������� ��������
		unsigned char* text;// �������� ��� (Windows - 1251)
		int code[256] = IN_CODE_TABLE;// ������� ��������: T, F, I ����� ��������
	};
	IN getin(wchar_t infile[]);	// ������ � ��������� ������� �����
	void DeleteSpaces(In::IN in);
};