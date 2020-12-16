#pragma once
#include "GRB.h"
#define GRB_ERROR_SERIES 500

namespace GRB {
	Greibach greibach(
		NS('S'), TS('$'),                     // стартовый символ, дно стека
		13,									  // количество правил
		Rule( // неверная структура программы
			NS('S'), GRB_ERROR_SERIES + 0,   
			2,
			Rule::Chain(6, TS('t'), TS('f'), TS('i'), NS('F'), NS('B'), NS('S')),
			Rule::Chain(4, TS('p'), TS('['), NS('N'), TS(']'))
		),
		Rule( // отсутствует список параметров функции
			NS('F'), GRB_ERROR_SERIES + 1,   
			2,
			Rule::Chain(3, TS('('), NS('P'), TS(')')),
			Rule::Chain(2, TS('('), TS(')'))
		),
		Rule( // Ошибка в параметрах функции при её объявлении
			NS('P'), GRB_ERROR_SERIES + 2,   
			2,
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('P')),
			Rule::Chain(2, TS('t'), TS('i'))
		),
		Rule(// Отсутствует тело функции
			NS('B'), GRB_ERROR_SERIES + 3,    
			2,
			Rule::Chain(5, TS('['), TS('g'), NS('I'), TS('!'), TS(']')),
			Rule::Chain(6, TS('['), NS('N'), TS('g'), NS('I'), TS('!'), TS(']'))
		),
		Rule(// Недопустимое выражение. Ожидаются только литералы и идентификаторы
			NS('I'), GRB_ERROR_SERIES + 4,    
			2,
			Rule::Chain(1, TS('l')),
			Rule::Chain(1, TS('i'))
		),
		Rule(// Неверная конструкция в теле функции
			NS('N'), GRB_ERROR_SERIES + 6,    
			20,
			Rule::Chain(7, TS('s'), TS('t'), TS('i'), TS(':'), NS('E'), TS('!'), NS('N')),
			Rule::Chain(5, TS('s'), TS('t'), TS('i'), TS('!'), NS('N')),
			Rule::Chain(5, TS('i'), TS(':'), NS('E'), TS('!'), NS('N')),	
			Rule::Chain(5, TS('i'), TS(':'), NS('H'), TS('!'), NS('N')),
			Rule::Chain(8, TS('y'), TS('('), NS('R'), TS(')'), TS('['), NS('X'), TS(']'), NS('N')), 
			Rule::Chain(6, TS('h'), TS('('), NS('I'), TS(')'), TS('!'), NS('N')),
			Rule::Chain(8, TS('w'), TS('('), NS('R'), TS(')'), TS('['), NS('X'), TS(']'), NS('N')),
			Rule::Chain(12, TS('w'), TS('('), NS('R'), TS(')'), TS('['), NS('X'), TS(']'), TS('o'), TS('['), NS('X'), TS(']'), NS('N')),
			Rule::Chain(4, TS('b'), NS('K'), TS('!'),NS('N')),
			Rule::Chain(4, TS('i'), NS('K'), TS('!'), NS('N')),

			Rule::Chain(6, TS('s'), TS('t'), TS('i'), TS(':'), NS('E'), TS('!')),
			Rule::Chain(4, TS('s'), TS('t'), TS('i'), TS('!')),
			Rule::Chain(4, TS('i'), TS(':'), NS('E'), TS('!')),
			Rule::Chain(4, TS('i'), TS(':'), NS('H'), TS('!')),
			Rule::Chain(7, TS('y'), TS('('), NS('R'), TS(')'), TS('['), NS('X'), TS(']')),
			Rule::Chain(5, TS('h'), TS('('), NS('I'), TS(')'), TS('!')),
			Rule::Chain(7, TS('w'), TS('('), NS('R'), TS(')'), TS('['), NS('X'), TS(']')),
			Rule::Chain(11, TS('w'), TS('('), NS('R'), TS(')'), TS('['), NS('X'), TS(']'), TS('o'), TS('['), NS('X'), TS(']')),
			Rule::Chain(3, TS('b'), NS('K'), TS('!')),
			Rule::Chain(3, TS('i'), NS('K'), TS('!'))

		),
		Rule( // Ошибка в вызове функции
			NS('E'), GRB_ERROR_SERIES + 8,   
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
		Rule(// Ошибка в вызове функции
			NS('K'), GRB_ERROR_SERIES + 8,    
			2,
			Rule::Chain(3, TS('('), NS('W'), TS(')')),
			Rule::Chain(2, TS('('), TS(')'))
		),
		Rule(// ошибка в параметрах вызываемой функции 
			NS('W'), GRB_ERROR_SERIES + 9,    
			4,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		),
		Rule(//Ошибка в арифметических или сдвиговых операциях
			NS('M'), GRB_ERROR_SERIES + 10,   
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
		Rule( //Ошибка в арифметических или сдвиговых операциях
			NS('H'), GRB_ERROR_SERIES + 10,
			4,
			Rule::Chain(3, TS('i'), TS('\\'), NS('I')),
			Rule::Chain(3, TS('i'), TS('/'), NS('I')),
			Rule::Chain(3, TS('l'), TS('/'), NS('I')),
			Rule::Chain(3, TS('l'), TS('\\'), NS('I'))
		),
		Rule(// Ошибка в условном выражении или выражении цикла
			NS('R'), GRB_ERROR_SERIES + 7,
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
		Rule(// Неверная конструкция в теле цикла/условного выражения
			NS('X'), GRB_ERROR_SERIES + 11,    
			12,
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