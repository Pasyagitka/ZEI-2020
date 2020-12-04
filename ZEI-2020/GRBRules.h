#pragma once
#include "GRB.h"
#define GRB_ERROR_SERIES 500

namespace GRB {
	/* Старый из лабы
		S -> m{NrE;}; | tfi(F){NrE;};S | m{NrE;};S
		N -> dti; | rE; | i=E; | dtfi(F); | dti;N | re;N | i=E;N | dtfi(F);N
		E -> i | l | (E) | i(W) | iM | lM | (E)M | i(W)M
		M -> vE | vEM
		F -> ti | ti,F
		W -> i | l | i,W | l,W
	*/

	/* Мой новый
		S -> ftiFBS | g{N} | ftiFB
		F -> [P] | []
		P -> ti | ti&P
		B -> {Nr[I].}
		I -> li
		U -> {N}
		N -> vti.N | vti=E.N | i=E.N | c[R]{X}N | c[R]{X}u{X}N | ~K.N | ^K.N | o[I].N | n.N | iK.N
			| vti. | vti= E.| i=E. |c[R]{X} | c[R]{X}u{X} | !K. | ~K. | ^K. | oK. | n. | iK.
		R -> i | ibi | lbi | lbl
		K -> [W] | []
		E -> i | l | (E) | iK | ~K | ^K| !K | iM | lM | (E)M | iKM | ~KM | ^KM | !KM
		W -> i | l | i&w | l&W
		M -> sE | seM
		X -> i=E.N | ~K.N | !K.N | o[I].N | c.N | iK.N | i=E. | ~K. | !K. | ^K. | oK. | c. | iK.
	*/

	/*
		S -> ftiFBS | g{N} | ftiFB
		F -> [P] | []
		P -> ti | ti&P
		B -> {Nr[I].}
		I -> li
		U -> {N}
		N -> vti.N | vti=E.N | i=E.N | c[R]{X}N | c[R]{X}u{X}N | ~K.N | ^K.N | o[I].N | n.N | iK.N
			| vti. | vti= E.| i=E. |c[R]{X} | c[R]{X}u{X} | !K. | ~K. | ^K. | oK. | n. | iK.
		R -> i | ibi | lbi | lbl
		K -> [W] | []
		E -> i | l | (E) | iK | ~K | ^K| !K | iM | lM | (E)M | iKM | ~KM | ^KM | !KM
		W -> i | l | i&w | l&W
		M -> sE | seM
		X -> i=E.N | ~K.N | !K.N | o[I].N | c.N | iK.N | i=E. | ~K. | !K. | ^K. | oK. | c. | iK.
	*/

	/*
		S -> tfi(Q)[Y]S | d[N]
		N ->ti:E.N | ti:E. | tO.N | tO. | ti:P.N | ti:P. | i:P.N | i:P. | i:E.N | i:E. | w(K)[N]e[N]N | w(K)[N]N | w(K)[N]e[N] | w(K)[N]
		| p(i).N | p(i). | p(l).N | p(l).
		Q -> ti | ti, Q
		O -> i | i,O
		Y -> ti:E.Y | ti:E. | tO.Y | tO. | ti:P.Y | ti:P. | i:P.Y | i:P. | i:E.Y | i:E. | w(K)[Y]e[Y]Y | w(K)[Y]Y | w(K)[Y]e[Y] | w(K)[Y] | 
		p(i).Y | p(i). | p(l).Y |  p(l). | ri. | rl.
		E -> i | l | s(i) | s(i,i) | s(l) | s(l, l) | i(O)
		P -> i | l | iP | lP | iMP | lMP | (P) | (P)MP | (P)N | (P)
		M -> + | - | * | /
		B -> > | < | =
		K -> i | l | iBi | iBl | lBi | lBl
	*/
	Greibach greibach(NS('S'), TS('$'), 10,
		Rule(NS('S'), GRB_ERROR_SERIES, 2,
			Rule::Chain(10, TS('t'), TS('f'), TS('i'), TS('('), NS('Q'), TS(')'), TS('['), NS('Y'), TS(']'), NS('S')),
			Rule::Chain(4, TS('d'), TS('['), NS('N'), TS(']'))
		),
		Rule(NS('N'), GRB_ERROR_SERIES + 1, 18,
			Rule::Chain(6, TS('t'), TS('i'), TS(':'), NS('E'), TS('.'), NS('N')),
			Rule::Chain(5, TS('t'), TS('i'), TS(':'), NS('E'), TS('.')),
			Rule::Chain(4, TS('t'), NS('O'), TS('.'), NS('N')),
			Rule::Chain(3, TS('t'), NS('O'), TS('.')),
			Rule::Chain(6, TS('t'), TS('i'), TS(':'), NS('P'), TS('.'), NS('N')),
			Rule::Chain(5, TS('t'), TS('i'), TS(':'), NS('P'), TS('.')),
			Rule::Chain(5, TS('i'), TS(':'), NS('P'), TS('.'), NS('N')),
			Rule::Chain(4, TS('i'), TS(':'), NS('P'), TS('.')),
			Rule::Chain(5, TS('i'), TS(':'), NS('E'), TS('.'), NS('N')),
			Rule::Chain(4, TS('i'), TS(':'), NS('E'), TS('.')),
			Rule::Chain(12, TS('w'), TS('('), NS('K'), TS(')'), TS('['), NS('N'), TS(']'), TS('e'), TS('['), NS('N'), TS(']'), NS('N')),
			Rule::Chain(8, TS('w'), TS('('), NS('K'), TS(')'), TS('['), NS('N'), TS(']'), NS('N')),
			Rule::Chain(11, TS('w'), TS('('), NS('K'), TS(')'), TS('['), NS('N'), TS(']'), TS('e'), TS('['), NS('N'), TS(']')),
			Rule::Chain(7, TS('w'), TS('('), NS('K'), TS(')'), TS('['), NS('N'), TS(']')),
			Rule::Chain(6, TS('p'), TS('('), TS('i'), TS(')'), TS('.'), NS('N')),
			Rule::Chain(5, TS('p'), TS('('), TS('i'), TS(')'), TS('.')),
			Rule::Chain(6, TS('p'), TS('('), TS('l'), TS(')'), TS('.'), NS('N')),
			Rule::Chain(5, TS('p'), TS('('), TS('l'), TS(')'), TS('.'))
		),
		Rule(NS('Q'), GRB_ERROR_SERIES + 8, 2,
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('Q'))
		),
		Rule(NS('O'), GRB_ERROR_SERIES + 7, 2,
			Rule::Chain(1, TS('i')),
			Rule::Chain(3, TS('i'), TS(','), NS('O'))
		),
		Rule(NS('Y'), GRB_ERROR_SERIES + 9, 20,
			Rule::Chain(6, TS('t'), TS('i'), TS(':'), NS('E'), TS('.'), NS('Y')),
			Rule::Chain(5, TS('t'), TS('i'), TS(':'), NS('E'), TS('.')),
			Rule::Chain(4, TS('t'), NS('O'), TS('.'), NS('Y')),
			Rule::Chain(3, TS('t'), NS('O'), TS('.')),
			Rule::Chain(6, TS('t'), TS('i'), TS(':'), NS('P'), TS('.'), NS('Y')),
			Rule::Chain(5, TS('t'), TS('i'), TS(':'), NS('P'), TS('.')),
			Rule::Chain(5, TS('i'), TS(':'), NS('P'), TS('.'), NS('Y')),
			Rule::Chain(4, TS('i'), TS(':'), NS('P'), TS('.')),
			Rule::Chain(5, TS('i'), TS(':'), NS('E'), TS('.'), NS('Y')),
			Rule::Chain(4, TS('i'), TS(':'), NS('E'), TS('.')),
			Rule::Chain(12, TS('w'), TS('('), NS('K'), TS(')'), TS('['), NS('Y'), TS(']'), TS('e'), TS('['), NS('Y'), TS(']'), NS('Y')),
			Rule::Chain(8, TS('w'), TS('('), NS('K'), TS(')'), TS('['), NS('Y'), TS(']'), NS('Y')),
			Rule::Chain(11, TS('w'), TS('('), NS('K'), TS(')'), TS('['), NS('Y'), TS(']'), TS('e'), TS('['), NS('Y'), TS(']')),
			Rule::Chain(7, TS('w'), TS('('), NS('K'), TS(')'), TS('['), NS('Y'), TS(']')),
			Rule::Chain(6, TS('p'), TS('('), TS('i'), TS(')'), TS('.'), NS('Y')),
			Rule::Chain(5, TS('p'), TS('('), TS('i'), TS(')'), TS('.')),
			Rule::Chain(6, TS('p'), TS('('), TS('l'), TS(')'), TS('.'), NS('Y')),
			Rule::Chain(5, TS('p'), TS('('), TS('l'), TS(')'), TS('.')),
			Rule::Chain(3, TS('r'), TS('i'), TS('.')),
			Rule::Chain(3, TS('r'), TS('l'), TS('.'))
		),
		Rule(NS('E'), GRB_ERROR_SERIES + 2, 7,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(4, TS('s'), TS('('), TS('i'), TS(')')),
			Rule::Chain(6, TS('s'), TS('('), TS('i'), TS(','), TS('i'), TS(')')),
			Rule::Chain(4, TS('s'), TS('('), TS('l'), TS(')')),
			Rule::Chain(6, TS('s'), TS('('), TS('l'), TS(','), TS('l'), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('O'), TS(')'))
		),
		Rule(NS('P'), GRB_ERROR_SERIES + 3, 10,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(2, TS('i'), NS('P')),
			Rule::Chain(2, TS('l'), NS('P')),
			Rule::Chain(3, TS('i'), NS('M'), NS('P')),
			Rule::Chain(3, TS('l'), NS('M'), NS('P')),
			Rule::Chain(3, TS('('), NS('P'), TS(')')),
			Rule::Chain(5, TS('('), NS('P'), TS(')'), NS('M'), NS('P')),
			Rule::Chain(4, TS('('), NS('P'), TS(')'), NS('N')),
			Rule::Chain(3, TS('('), NS('P'), TS(')'))
		),
		Rule(NS('M'), GRB_ERROR_SERIES + 4, 4,
			Rule::Chain(1, TS('+')),
			Rule::Chain(1, TS('-')),
			Rule::Chain(1, TS('*')),
			Rule::Chain(1, TS('/'))
		),
		Rule(NS('B'), GRB_ERROR_SERIES + 5, 3,
			Rule::Chain(1, TS('>')),
			Rule::Chain(1, TS('<')),
			Rule::Chain(1, TS('='))
		),
		Rule(NS('K'), GRB_ERROR_SERIES + 6, 6,
			Rule::Chain(1, TS('l')),
			Rule::Chain(1, TS('i')),
			Rule::Chain(3, TS('i'), NS('B'), TS('i')),
			Rule::Chain(3, TS('i'), NS('B'), TS('l')),
			Rule::Chain(3, TS('l'), NS('B'), TS('i')),
			Rule::Chain(3, TS('l'), NS('B'), TS('l'))
		)
	);
}