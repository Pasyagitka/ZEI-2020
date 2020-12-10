#pragma once
#include "GRB.h"
#define GRB_ERROR_SERIES 500

namespace GRB {
	//TODO пишет ошибку если нет !
	/*
		S-> tfiFBS	|	p[N]	|	tfiFB??			//неверная структура программы
		F-> (P)		|   ()							//список параметров функции
		P-> ti		|  ti,P							//параметры функции при её объявлении
		B-> [NgI!]									//отсутствует тело функции
		I-> l       |   i							//Недопустимое выражение. Ожидаются только литералы и идентификаторы
		U-> {N}	??									// Ошибка в теле процедуры
		N-> sti:E!N |   sti:E!   |  sti!N | irl!N |      sti! | w(E)[N]o[N]N  | w(E)[N]o[N]  | i=E!N | h(i)! | h(i)!N |
			h(l)!   |   h(l)!N   |  w(E)[N]N | w(E)[N] | 
		R-> i | ibi | ibl | lbi | lbl				//Ошибка в условном выражении
		K->(W)  | ()								 //Ошибка в вызове функции
		E-> bK | i | l | (E) | iK | pK | SK| !K	| iM | lM | (E)M | iKM | bKM | !KM  // Ошибка в вызове функции
		W-> i | l | i,W | l&W
		M-> +E | =E| *E| /E | -E | +EM | =EM | -EM | *EM | /EM    // ошибка в арифметическом выражении 
		X->										     // Неверная конструкция в теле цикла/условного выражения
			
	*/

	Greibach greibach(
		NS('S'), TS('$'),                     // стартовый символ, дно стека
		14,									  // количество правил
		Rule(
			NS('S'), GRB_ERROR_SERIES + 0,    // неверная структура программы
			3,
			Rule::Chain(6, TS('t'), TS('f'), TS('i'), NS('F'), NS('B'), NS('S')),
			Rule::Chain(4, TS('p'), TS('['), NS('N'), TS(']')),
			Rule::Chain(5, TS('t'), TS('f'), TS('i'), NS('F'), NS('B'))//??
		),
		Rule(
			NS('F'), GRB_ERROR_SERIES + 1,    // Отсутствует список параметров функции
			2,
			Rule::Chain(3, TS('('), NS('P'), TS(')')),
			Rule::Chain(2, TS('('), TS(')'))
		),
		Rule(
			NS('P'), GRB_ERROR_SERIES + 2,    // Ошибка в параметрах функции при её объявлении
			2,
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('P'))
		),
		Rule(
			NS('B'), GRB_ERROR_SERIES + 3,    // Отсутствует тело функции
			1,
			Rule::Chain(6, TS('['), NS('N'), TS('g'), NS('I'), TS('!'), TS(']'))
		),
		Rule(
			NS('I'), GRB_ERROR_SERIES + 4,    // Недопустимое выражение. Ожидаются только литералы и идентификаторы
			2,
			Rule::Chain(1, TS('l')),
			Rule::Chain(1, TS('i'))
		),
		Rule(
			NS('U'), GRB_ERROR_SERIES + 5,    // Ошибка в теле процедуры
			1,
			Rule::Chain(3, TS('{'), NS('N'), TS('}'))//??
		),
		Rule(
			NS('N'), GRB_ERROR_SERIES + 6,    // Неверная конструкция в теле функции
			23,
			Rule::Chain(7, TS('s'), TS('t'), TS('i'), TS(':'), NS('E'), TS('!'), NS('N')),//need
			Rule::Chain(6, TS('s'), TS('t'), TS('i'), TS(':'), NS('E'), TS('!')),//need
			Rule::Chain(5, TS('s'), TS('t'), TS('i'), TS('!'), NS('N')),//need

			Rule::Chain(5, TS('i'), TS(':'), NS('E'), TS('!'), NS('N')),//need	
			Rule::Chain(4, TS('i'), TS(':'), NS('E'), TS('!')),//need

			Rule::Chain(5, TS('i'), TS(':'), NS('H'), TS('!'), NS('N')),//need
			Rule::Chain(4, TS('i'), TS(':'), NS('H'), TS('!')),//need



			Rule::Chain(8, TS('y'), TS('('), NS('R'), TS(')'), TS('['), NS('N'), TS(']'), NS('N')),//need
			Rule::Chain(7, TS('y'), TS('('), NS('R'), TS(')'), TS('['), NS('N'), TS(']')),//need

			Rule::Chain(4, TS('s'), TS('t'), TS('i'), TS('!')),//need
			Rule::Chain(12, TS('w'), TS('('), NS('R'), TS(')'), TS('['), NS('X'), TS(']'),TS('o'), TS('['), NS('X'), TS(']'), NS('N')),//need
			Rule::Chain(11, TS('w'), TS('('), NS('R'), TS(')'), TS('['), NS('X'), TS(']'),TS('o'), TS('['), NS('X'), TS(']')),//need
			Rule::Chain(5, TS('i'), TS(':'), NS('E'), TS('!'), NS('N')),//need тут было =
			Rule::Chain(5, TS('h'), TS('('), TS('i'), TS(')'), TS('!')),//need
			Rule::Chain(6, TS('h'), TS('('), TS('i'), TS(')'), TS('!'), NS('N')),//need
			Rule::Chain(5, TS('h'), TS('('), TS('l'), TS(')'), TS('!')),//need
			Rule::Chain(6, TS('h'), TS('('), TS('l'), TS(')'), TS('!'), NS('N')),//need
			Rule::Chain(8, TS('w'), TS('('), NS('R'), TS(')'), TS('['), NS('X'), TS(']'), NS('N')),//need
			Rule::Chain(7, TS('w'), TS('('), NS('R'), TS(')'), TS('['), NS('X'), TS(']')),//need

			Rule::Chain(5, TS('r'), TS('('), TS('i'), TS(')'), TS('!')),//need
			Rule::Chain(6, TS('r'), TS('('), TS('i'), TS(')'), TS('!'), NS('N')),//need
			Rule::Chain(5, TS('r'), TS('('), TS('l'), TS(')'), TS('!')),//need
			Rule::Chain(6, TS('r'), TS('('), TS('l'), TS(')'), TS('!'), NS('N'))//need
			//Rule::Chain(4, TS('i'), TS('='), NS('E'), TS('!')),
			//Rule::Chain(7, TS('c'), TS('['), NS('R'), TS(']'), TS('{'), NS('X'), TS('}')),
			//Rule::Chain(6, TS('S'), NS('K'), TS('.'), NS('N')),
			//Rule::Chain(6, TS('!'), NS('K'), TS('.'), NS('N')),
			//Rule::Chain(6, TS('o'), TS('['), NS('I'), TS(']'), TS('.'), NS('N')),
			//Rule::Chain(3, TS('n'), TS('.'), NS('N')),
			//Rule::Chain(4, TS('i'), NS('K'), TS('.'), NS('N')),
			//Rule::Chain(12, TS('c'), TS('['), NS('R'), TS(']'), TS('{'), NS('X'), TS('}'), TS('u'), TS('{'), NS('X'), TS('}'), NS('N')),//?
			//Rule::Chain(6, TS('P'), NS('K'), TS('.'), NS('N')),//?
			//Rule::Chain(11, TS('c'), TS('['), NS('R'), TS(']'), TS('{'), NS('X'), TS('}'), TS('u'), TS('{'), NS('X'), TS('}')),
			//Rule::Chain(3, TS('h'), NS('K'), TS('!')),
			//Rule::Chain(3, TS('i'), NS('K'), TS('!'))
		),
		Rule(
			NS('R'), GRB_ERROR_SERIES + 7,    // Ошибка в условном выражении или выражении цикла
			9,
			Rule::Chain(1, TS('i')),
			Rule::Chain(3, TS('i'), TS('<'), NS('I')),
			Rule::Chain(3, TS('l'), TS('<'), NS('I')),
			Rule::Chain(3, TS('i'), TS('>'), NS('I')),
			Rule::Chain(3, TS('l'), TS('>'), NS('I')),
			Rule::Chain(3, TS('i'), TS('='), NS('I')),
			Rule::Chain(3, TS('l'), TS('='), NS('I')),
			Rule::Chain(3, TS('i'), TS('^'), NS('I')),
			Rule::Chain(3, TS('l'), TS('^'), NS('I'))
		),
		Rule(
			NS('H'), GRB_ERROR_SERIES + 10,    //Ошибка в арифметических или сдвиговых операциях
			8,
			Rule::Chain(3, TS('i'), TS('/'), TS('l')),
			Rule::Chain(3, TS('i'), TS('\\'), TS('l')),
			Rule::Chain(3, TS('i'), TS('/'), TS('l')),
			Rule::Chain(3, TS('i'), TS('\\'), TS('l')),
			Rule::Chain(3, TS('l'), TS('/'), TS('l')),
			Rule::Chain(3, TS('l'), TS('\\'), TS('l')),
			Rule::Chain(3, TS('l'), TS('/'), TS('l')),
			Rule::Chain(3, TS('l'), TS('\\'), TS('l'))
		),
		Rule(
			NS('K'), GRB_ERROR_SERIES + 8,    // Ошибка в вызове функции
			2,
			Rule::Chain(3, TS('('), NS('W'), TS(')')),
			Rule::Chain(2, TS('('), TS(')'))
		),
		Rule(
			NS('E'), GRB_ERROR_SERIES + 8,    // Ошибка в вызове функции
			14,
			Rule::Chain(2, TS('b'), NS('K')),
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(2, TS('i'), NS('K')),
			Rule::Chain(2, TS('P'), NS('K')),
			Rule::Chain(2, TS('S'), NS('K')),
			Rule::Chain(2, TS('!'), NS('K')),
			
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(3, TS('i'), NS('K'), NS('M')),
			Rule::Chain(3, TS('b'), NS('K'), NS('M')),
			Rule::Chain(3, TS('!'), NS('K'), NS('M'))
		),
		Rule(
			NS('W'), GRB_ERROR_SERIES + 9,    // ошибка в параметрах вызываемой функции 
			4,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		),
		Rule(
			NS('M'), GRB_ERROR_SERIES + 10,    //Ошибка в арифметических или сдвиговых операциях
			8,
			Rule::Chain(2, TS('+'), NS('E')),
			//Rule::Chain(2, TS('='), NS('E')),
			Rule::Chain(2, TS('*'), NS('E')),
			Rule::Chain(2, TS('#'), NS('E')),
			Rule::Chain(2, TS('-'), NS('E')),
			Rule::Chain(3, TS('+'), NS('E'), NS('M')),
			//Rule::Chain(3, TS('='), NS('E'), NS('M')),
			Rule::Chain(3, TS('-'), NS('E'), NS('M')),
			Rule::Chain(3, TS('*'), NS('E'), NS('M')),
			Rule::Chain(3, TS('#'), NS('E'), NS('M'))
		),
				//TODO доабвить операци
		Rule(
			NS('X'), GRB_ERROR_SERIES + 11,    // Неверная конструкция в теле цикла/условного выражения
			14,
			Rule::Chain(4, TS('i'), TS(':'), NS('I'), TS('!'), NS('N')),
			Rule::Chain(5, TS('i'), TS(':'), NS('E'), TS('!'), NS('N')),
			Rule::Chain(5, TS('i'), TS(':'), NS('H'), TS('!'), NS('N')),
			Rule::Chain(6, TS('h'), TS('('), TS('i'), TS(')'), TS('!'), NS('N')),
			Rule::Chain(6, TS('h'), TS('('), TS('l'), TS(')'), TS('!'), NS('N')),
			Rule::Chain(6, TS('r'), TS('('), TS('i'), TS(')'), TS('!'), NS('N')),
			Rule::Chain(6, TS('r'), TS('('), TS('l'), TS(')'), TS('!'), NS('N')),

			Rule::Chain(4, TS('i'), TS(':'), NS('I'), TS('!')),
			Rule::Chain(4, TS('i'), TS(':'), NS('E'), TS('!')),
			Rule::Chain(4, TS('i'), TS(':'), NS('H'), TS('!')),
			Rule::Chain(5, TS('h'), TS('('), TS('i'), TS(')'), TS('!')),
			Rule::Chain(5, TS('h'), TS('('), TS('l'), TS(')'), TS('!')),
			Rule::Chain(5, TS('r'), TS('('), TS('i'), TS(')'), TS('!')),
			Rule::Chain(5, TS('r'), TS('('), TS('l'), TS(')'), TS('!'))

			/*Rule::Chain(5, TS('i'), TS('='), NS('E'), TS('.'), NS('N')),
			Rule::Chain(6, TS('P'), NS('K'), TS('.'), NS('N')),
			Rule::Chain(6, TS('S'), NS('K'), TS('.'), NS('N')),
			Rule::Chain(6, TS('!'), NS('K'), TS('.'), NS('N')),
			Rule::Chain(6, TS('o'), TS('['), NS('I'), TS(']'), TS('.'), NS('N')),
			Rule::Chain(3, TS('c'), TS('.'), NS('N')),
			Rule::Chain(4, TS('i'), NS('K'), TS('.'), NS('N')),

			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS('.')),
			Rule::Chain(3, TS('!'), NS('K'), TS('.')),
			Rule::Chain(3, TS('P'), NS('K'), TS('.')),
			Rule::Chain(3, TS('S'), NS('K'), TS('.')),
			Rule::Chain(3, TS('o'), NS('K'), TS('.')),
			Rule::Chain(2, TS('c'), TS('.')),
			Rule::Chain(3, TS('i'), NS('K'), TS('.'))*/
		)
	);
}