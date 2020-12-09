#pragma once
#define IN_MAX_LEN_TEXT 1024*1024	// максимальный размер исходного кода = 1MB
#define SIZE 10000
#define IN_CODE_ENDL '\n'		//символ конца строки
#define IN_CODE_N '\0'			//символ конца
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


// таблица проверки входной информации, индекс = код (Windows-1251) символа
//если 0 <= значение < 256 - то вводится данное значение
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
	/*А*/IN::F, /*Б*/IN::F, /*В*/IN::F, /*Г*/IN::F, /*Д*/IN::F, /*Е*/IN::F, /*Ж*/IN::F, /*З*/IN::F, /*И*/IN::F, /*Й*/IN::F, /*К*/IN::F, /*Л*/IN::F, /*М*/IN::F, /*Н*/IN::F, /*О*/IN::F, /*П*/IN::F, \
	/*Р*/IN::F, /*С*/IN::F, /*Т*/IN::F, /*У*/IN::F, /*Ф*/IN::F, /*Х*/IN::F, /*Ц*/IN::F, /*Ч*/IN::F, /*Ш*/IN::F, /*Щ*/IN::F, /*Ъ*/IN::F, /*Ы*/IN::F, /*Ь*/IN::F, /*Э*/IN::F, /*Ю*/IN::F, /*Я*/IN::F, \
	/*а*/IN::F, /*б*/IN::F, /*в*/IN::F, /*г*/IN::F, /*д*/IN::F, /*е*/IN::F, /*ж*/IN::F, /*з*/IN::F, /*и*/IN::F, /*й*/IN::F, /*к*/IN::F, /*л*/IN::F, /*м*/IN::F, /*н*/IN::F, /*о*/IN::F, /*п*/IN::F, \
	/*р*/IN::F, /*с*/IN::F, /*т*/IN::F, /*у*/IN::F, /*ф*/IN::F, /*х*/IN::F, /*ц*/IN::F, /*ч*/IN::F, /*ш*/IN::F, /*щ*/IN::F, /*ъ*/IN::F, /*ы*/IN::F, /*ь*/IN::F, /*э*/IN::F, /*ю*/IN::F, /*я*/IN::F, \
			}

namespace In
{
	struct IN	//исходные данные
	{
		enum { T, F, I }; // Т - допустимый символ, F - недопустимый, I - игнорировать, иначе заменить
		int size;		// размер исходного кода
		int lines;		// количество строк
		int ignor;		// количество проигнорированных символов
		unsigned char* text;// исходный код (Windows - 1251)
		int code[256] = IN_CODE_TABLE;// таблица проверки: T, F, I новое значение
	};
	IN getin(wchar_t infile[]);	// ввести и проверить входной поток
	void DeleteSpaces(In::IN in);
};