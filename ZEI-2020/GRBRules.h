#pragma once
#include "GRB.h"
#define GRB_ERROR_SERIES 500

namespace GRB {
	Greibach greibach(
		NS('S'), TS('$'),                     // стартовый символ, дно стека
		13,									  // количество правил
		Rule(
			NS('S'), GRB_ERROR_SERIES + 0,    // неверная структура программы
			2,
			Rule::Chain(6, TS('t'), TS('f'), TS('i'), NS('F'), NS('B'), NS('S')),
			Rule::Chain(4, TS('p'), TS('['), NS('N'), TS(']'))
		),
		Rule(
			NS('F'), GRB_ERROR_SERIES + 1,    // отсутствует список параметров функции
			2,
			Rule::Chain(3, TS('('), NS('P'), TS(')')),
			Rule::Chain(2, TS('('), TS(')'))
		),
		Rule(
			NS('P'), GRB_ERROR_SERIES + 2,    // Ошибка в параметрах функции при её объявлении
			2,
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('P')),
			Rule::Chain(2, TS('t'), TS('i'))
		),
		Rule(
			NS('B'), GRB_ERROR_SERIES + 3,    // Отсутствует тело функции
			2,
			Rule::Chain(5, TS('['), TS('g'), NS('I'), TS('!'), TS(']')),
			Rule::Chain(6, TS('['), NS('N'), TS('g'), NS('I'), TS('!'), TS(']'))
		),
		Rule(
			NS('I'), GRB_ERROR_SERIES + 4,    // Недопустимое выражение. Ожидаются только литералы и идентификаторы
			2,
			Rule::Chain(1, TS('l')),
			Rule::Chain(1, TS('i'))
		),
		Rule(
			NS('N'), GRB_ERROR_SERIES + 6,    // Неверная конструкция в теле функции
			22,
			Rule::Chain(7, TS('s'), TS('t'), TS('i'), TS(':'), NS('E'), TS('!'), NS('N')),
			Rule::Chain(5, TS('s'), TS('t'), TS('i'), TS('!'), NS('N')),
			Rule::Chain(5, TS('i'), TS(':'), NS('E'), TS('!'), NS('N')),	
			Rule::Chain(5, TS('i'), TS(':'), NS('H'), TS('!'), NS('N')),
			Rule::Chain(8, TS('y'), TS('('), NS('R'), TS(')'), TS('['), NS('X'), TS(']'), NS('N')), 
			Rule::Chain(6, TS('h'), TS('('), TS('i'), TS(')'), TS('!'), NS('N')),
			Rule::Chain(6, TS('h'), TS('('), TS('l'), TS(')'), TS('!'), NS('N')),
			Rule::Chain(8, TS('w'), TS('('), NS('R'), TS(')'), TS('['), NS('X'), TS(']'), NS('N')),
			Rule::Chain(12, TS('w'), TS('('), NS('R'), TS(')'), TS('['), NS('X'), TS(']'), TS('o'), TS('['), NS('X'), TS(']'), NS('N')),
			Rule::Chain(4, TS('b'), NS('K'), TS('!'),NS('N')),
			Rule::Chain(4, TS('i'), NS('K'), TS('!'), NS('N')),

			Rule::Chain(6, TS('s'), TS('t'), TS('i'), TS(':'), NS('E'), TS('!')),
			Rule::Chain(4, TS('s'), TS('t'), TS('i'), TS('!')),
			Rule::Chain(4, TS('i'), TS(':'), NS('E'), TS('!')),
			Rule::Chain(4, TS('i'), TS(':'), NS('H'), TS('!')),
			Rule::Chain(7, TS('y'), TS('('), NS('R'), TS(')'), TS('['), NS('X'), TS(']')),
			Rule::Chain(5, TS('h'), TS('('), TS('i'), TS(')'), TS('!')),
			Rule::Chain(5, TS('h'), TS('('), TS('l'), TS(')'), TS('!')),
			Rule::Chain(7, TS('w'), TS('('), NS('R'), TS(')'), TS('['), NS('X'), TS(']')),
			Rule::Chain(11, TS('w'), TS('('), NS('R'), TS(')'), TS('['), NS('X'), TS(']'), TS('o'), TS('['), NS('X'), TS(']')),
			Rule::Chain(3, TS('b'), NS('K'), TS('!')),
			Rule::Chain(3, TS('i'), NS('K'), TS('!'))

		),
		Rule(
			NS('R'), GRB_ERROR_SERIES + 7,    // Ошибка в условном выражении или выражении цикла
			8,
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
			Rule::Chain(3, TS('i'), TS('/'),  TS('l')),
			Rule::Chain(3, TS('i'), TS('\\'), TS('l')),
			Rule::Chain(3, TS('i'), TS('/'),  TS('l')),
			Rule::Chain(3, TS('i'), TS('\\'), TS('l')),
			Rule::Chain(3, TS('l'), TS('/'),  TS('l')),
			Rule::Chain(3, TS('l'), TS('\\'), TS('l')),
			Rule::Chain(3, TS('l'), TS('/'),  TS('l')),
			Rule::Chain(3, TS('l'), TS('\\'), TS('l'))
		),
		Rule(
			NS('E'), GRB_ERROR_SERIES + 8,    // Ошибка в вызове функции
			10,
			Rule::Chain(2, TS('b'), NS('K')),
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(2, TS('i'), NS('K')),
			
			Rule::Chain(2, TS('i'), NS('M')), 
			Rule::Chain(2, TS('l'), NS('M')), 
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')), 
			Rule::Chain(3, TS('i'), NS('K'), NS('M')),
			Rule::Chain(3, TS('b'), NS('K'), NS('M'))
		),
		Rule(
			NS('K'), GRB_ERROR_SERIES + 8,    // Ошибка в вызове функции
			2,
			Rule::Chain(3, TS('('), NS('W'), TS(')')),
			Rule::Chain(2, TS('('), TS(')'))
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
			Rule::Chain(3, TS('+'), NS('E'), NS('M')),
			Rule::Chain(3, TS('-'), NS('E'), NS('M')),
			Rule::Chain(3, TS('*'), NS('E'), NS('M')),
			Rule::Chain(3, TS('#'), NS('E'), NS('M')),

			Rule::Chain(2, TS('+'), NS('E')),
			Rule::Chain(2, TS('*'), NS('E')),
			Rule::Chain(2, TS('#'), NS('E')),
			Rule::Chain(2, TS('-'), NS('E'))
		),
		Rule(
			NS('X'), GRB_ERROR_SERIES + 11,    // Неверная конструкция в теле цикла/условного выражения
			14,
			Rule::Chain(5, TS('i'), TS(':'), NS('I'), TS('!'), NS('X')),
			Rule::Chain(5, TS('i'), TS(':'), NS('E'), TS('!'), NS('X')),
			Rule::Chain(5, TS('i'), TS(':'), NS('H'), TS('!'), NS('X')),
			Rule::Chain(6, TS('h'), TS('('), TS('i'), TS(')'), TS('!'), NS('X')),
			Rule::Chain(6, TS('h'), TS('('), TS('l'), TS(')'), TS('!'), NS('X')),
			Rule::Chain(4, TS('b'), NS('K'), TS('!'), NS('X')),
			Rule::Chain(4, TS('i'), NS('K'), TS('!'), NS('X')),

			Rule::Chain(4, TS('i'), TS(':'), NS('I'), TS('!')),
			Rule::Chain(4, TS('i'), TS(':'), NS('E'), TS('!')),
			Rule::Chain(4, TS('i'), TS(':'), NS('H'), TS('!')),
			Rule::Chain(5, TS('h'), TS('('), TS('i'), TS(')'), TS('!')),
			Rule::Chain(5, TS('h'), TS('('), TS('l'), TS(')'), TS('!')),
			Rule::Chain(3, TS('b'), NS('K'), TS('!')),
			Rule::Chain(3, TS('i'), NS('K'), TS('!'))
		)
	);
}