#pragma once

#define FST_INTEGER 8, \
	FST::NODE(1, FST::RELATION('i', 1)),\
	FST::NODE(1, FST::RELATION('n', 2)),\
	FST::NODE(1, FST::RELATION('t', 3)),\
	FST::NODE(1, FST::RELATION('e', 4)),\
	FST::NODE(1, FST::RELATION('g', 5)),\
	FST::NODE(1, FST::RELATION('e', 6)),\
	FST::NODE(1, FST::RELATION('r', 7)),\
	FST::NODE()

#define FST_STRING 7, \
	FST::NODE(1, FST::RELATION('s', 1)),\
	FST::NODE(1, FST::RELATION('t', 2)),\
	FST::NODE(1, FST::RELATION('r', 3)),\
	FST::NODE(1, FST::RELATION('i', 4)),\
	FST::NODE(1, FST::RELATION('n', 5)),\
	FST::NODE(1, FST::RELATION('g', 6)),\
	FST::NODE()

#define FST_BOOL 5, \
	FST::NODE(1, FST::RELATION('b', 1)),\
	FST::NODE(1, FST::RELATION('o', 2)),\
	FST::NODE(1, FST::RELATION('o', 3)),\
	FST::NODE(1, FST::RELATION('l', 4)),\
	FST::NODE()
#define FST_FUNC 5, \
    FST::NODE(1, FST::RELATION('f', 1)), \
    FST::NODE(1, FST::RELATION('u', 2)), \
    FST::NODE(1, FST::RELATION('n', 3)), \
    FST::NODE(1, FST::RELATION('c', 4)), \
    FST::NODE()

#define FST_RETURN 7, \
	FST::NODE(1, FST::RELATION('r', 1)),\
	FST::NODE(1, FST::RELATION('e', 2)),\
	FST::NODE(1, FST::RELATION('t', 3)),\
	FST::NODE(1, FST::RELATION('u', 4)),\
	FST::NODE(1, FST::RELATION('r', 5)),\
	FST::NODE(1, FST::RELATION('n', 6)),\
	FST::NODE()

#define FST_PRINT 6, \
	FST::NODE(1, FST::RELATION('p', 1)),\
	FST::NODE(1, FST::RELATION('r', 2)),\
	FST::NODE(1, FST::RELATION('i', 3)),\
	FST::NODE(1, FST::RELATION('n', 4)),\
	FST::NODE(1, FST::RELATION('t', 5)),\
	FST::NODE()

#define FST_DVV 4, \
	FST::NODE(1, FST::RELATION('d', 1)),\
	FST::NODE(1, FST::RELATION('v', 2)),\
	FST::NODE(1, FST::RELATION('v', 3)),\
	FST::NODE()

#define FST_IF 3, \
   FST::NODE(1, FST::RELATION('i',1)),\
   FST::NODE(1, FST::RELATION('f',2)),\
   FST::NODE()

#define FST_ELSE 5, \
	FST::NODE(1, FST::RELATION('e', 1)),\
	FST::NODE(1, FST::RELATION('l', 2)),\
	FST::NODE(1, FST::RELATION('s', 3)),\
	FST::NODE(1, FST::RELATION('e', 4)),\
	FST::NODE()

#define FST_STRLEN 7,\
    FST::NODE(1, FST::RELATION('s',1)),\
    FST::NODE(1, FST::RELATION('t',2)),\
    FST::NODE(1, FST::RELATION('r',3)),\
    FST::NODE(1, FST::RELATION('l',4)),\
    FST::NODE(1, FST::RELATION('e',5)),\
    FST::NODE(1, FST::RELATION('n',6)),\
    FST::NODE()

#define FST_SUBSTR 7,\
    FST::NODE(1, FST::RELATION('s',1)),\
    FST::NODE(1, FST::RELATION('u',2)),\
    FST::NODE(1, FST::RELATION('b',3)),\
    FST::NODE(1, FST::RELATION('s',4)),\
    FST::NODE(1, FST::RELATION('t',5)),\
    FST::NODE(1, FST::RELATION('r',6)),\
    FST::NODE()

#define FST_ID 2, \
	FST::NODE(52, \
	FST::RELATION('a', 0), FST::RELATION('b', 0), FST::RELATION('c', 0), FST::RELATION('d', 0), FST::RELATION('e', 0), FST::RELATION('f', 0),\
	FST::RELATION('g', 0), FST::RELATION('h', 0), FST::RELATION('i', 0), FST::RELATION('j', 0), FST::RELATION('k', 0), FST::RELATION('l', 0),\
	FST::RELATION('m', 0), FST::RELATION('n', 0), FST::RELATION('o', 0), FST::RELATION('p', 0), FST::RELATION('q', 0), FST::RELATION('r', 0),\
	FST::RELATION('s', 0), FST::RELATION('t', 0), FST::RELATION('u', 0), FST::RELATION('v', 0), FST::RELATION('w', 0), FST::RELATION('x', 0),\
	FST::RELATION('y', 0), FST::RELATION('z', 0),\
	\
	FST::RELATION('a', 1), FST::RELATION('b', 1), FST::RELATION('c', 1), FST::RELATION('d', 1), FST::RELATION('e', 1), FST::RELATION('f', 1),\
	FST::RELATION('g', 1), FST::RELATION('h', 1), FST::RELATION('i', 1), FST::RELATION('j', 1), FST::RELATION('k', 1), FST::RELATION('l', 1),\
	FST::RELATION('m', 1), FST::RELATION('n', 1), FST::RELATION('o', 1), FST::RELATION('p', 1), FST::RELATION('q', 1), FST::RELATION('r', 1),\
	FST::RELATION('s', 1), FST::RELATION('t', 1), FST::RELATION('u', 1), FST::RELATION('v', 1), FST::RELATION('w', 1), FST::RELATION('x', 1),\
	FST::RELATION('y', 1), FST::RELATION('z', 1)),\
    FST::NODE()

#define FST_INTLIT 2, \
	FST::NODE(20, \
	FST::RELATION('1', 0), FST::RELATION('2', 0), FST::RELATION('3', 0), FST::RELATION('4', 0), FST::RELATION('5', 0), FST::RELATION('6', 0),\
	FST::RELATION('7', 0), FST::RELATION('8', 0), FST::RELATION('9', 0), FST::RELATION('0', 0),\
	\
	FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1), FST::RELATION('6', 1),\
	FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1), FST::RELATION('0', 1)),\
	FST::NODE()

//TODO Нужна ли литералу лексема?
#define FST_STRLIT 4, \
	FST::NODE(1, FST::RELATION('"', 1)),\
	FST::NODE(154, \
	FST::RELATION('a', 1), FST::RELATION('b', 1), FST::RELATION('c', 1), FST::RELATION('d', 1), FST::RELATION('e', 1), FST::RELATION('f', 1),\
	FST::RELATION('g', 1), FST::RELATION('h', 1), FST::RELATION('i', 1), FST::RELATION('j', 1), FST::RELATION('k', 1), FST::RELATION('l', 1),\
	FST::RELATION('m', 1), FST::RELATION('n', 1), FST::RELATION('o', 1), FST::RELATION('p', 1), FST::RELATION('q', 1), FST::RELATION('r', 1),\
	FST::RELATION('s', 1), FST::RELATION('t', 1), FST::RELATION('u', 1), FST::RELATION('v', 1), FST::RELATION('w', 1), FST::RELATION('x', 1),\
	FST::RELATION('y', 1), FST::RELATION('z', 1), FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1),\
	FST::RELATION('5', 1), FST::RELATION('6', 1), FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1), FST::RELATION('0', 1),\
	\
	FST::RELATION('а', 1), FST::RELATION('б', 1), FST::RELATION('в', 1), FST::RELATION('г', 1), FST::RELATION('д', 1), FST::RELATION('е', 1),\
	FST::RELATION('ё', 1), FST::RELATION('ж', 1), FST::RELATION('з', 1), FST::RELATION('и', 1), FST::RELATION('й', 1), FST::RELATION('к', 1),\
	FST::RELATION('л', 1), FST::RELATION('м', 1), FST::RELATION('н', 1), FST::RELATION('о', 1), FST::RELATION('п', 1), FST::RELATION('р', 1),\
	FST::RELATION('с', 1), FST::RELATION('т', 1), FST::RELATION('у', 1), FST::RELATION('ф', 1), FST::RELATION('х', 1), FST::RELATION('ц', 1),\
	FST::RELATION('ч', 1), FST::RELATION('ш', 1), FST::RELATION('щ', 1), FST::RELATION('ъ', 1), FST::RELATION('ы', 1), FST::RELATION('ь', 1),\
	FST::RELATION('э', 1), FST::RELATION('ю', 1), FST::RELATION('я', 1), FST::RELATION(' ', 1), FST::RELATION('.', 1), FST::RELATION(',', 1),\
	FST::RELATION('?', 1), FST::RELATION('!', 1), FST::RELATION(';', 1), FST::RELATION(':', 1), FST::RELATION('-', 1), \
	\
	FST::RELATION('a', 2), FST::RELATION('b', 2), FST::RELATION('c', 2), FST::RELATION('d', 2), FST::RELATION('e', 2), FST::RELATION('f', 2),\
	FST::RELATION('g', 2), FST::RELATION('h', 2), FST::RELATION('i', 2), FST::RELATION('j', 2), FST::RELATION('k', 2), FST::RELATION('l', 2),\
	FST::RELATION('m', 2), FST::RELATION('n', 2), FST::RELATION('o', 2), FST::RELATION('p', 2), FST::RELATION('q', 2), FST::RELATION('r', 2),\
	FST::RELATION('s', 2), FST::RELATION('t', 2), FST::RELATION('u', 2), FST::RELATION('v', 2), FST::RELATION('w', 2), FST::RELATION('x', 2),\
	FST::RELATION('y', 2), FST::RELATION('z', 2), FST::RELATION('1', 2), FST::RELATION('2', 2), FST::RELATION('3', 2), FST::RELATION('4', 2),\
	FST::RELATION('5', 2), FST::RELATION('6', 2), FST::RELATION('7', 2), FST::RELATION('8', 2), FST::RELATION('9', 2), FST::RELATION('0', 2),\
	\
	FST::RELATION('а', 2), FST::RELATION('б', 2), FST::RELATION('в', 2), FST::RELATION('г', 2), FST::RELATION('д', 2), FST::RELATION('е', 2),\
	FST::RELATION('ё', 2), FST::RELATION('ж', 2), FST::RELATION('з', 2), FST::RELATION('и', 2), FST::RELATION('й', 2), FST::RELATION('к', 2),\
	FST::RELATION('л', 2), FST::RELATION('м', 2), FST::RELATION('н', 2), FST::RELATION('о', 2), FST::RELATION('п', 2), FST::RELATION('р', 2),\
	FST::RELATION('с', 2), FST::RELATION('т', 2), FST::RELATION('у', 2), FST::RELATION('ф', 2), FST::RELATION('х', 2), FST::RELATION('ц', 2),\
	FST::RELATION('ч', 2), FST::RELATION('ш', 2), FST::RELATION('щ', 2), FST::RELATION('ъ', 2), FST::RELATION('ы', 2), FST::RELATION('ь', 2),\
	FST::RELATION('э', 2), FST::RELATION('ю', 2), FST::RELATION('я', 2), FST::RELATION(' ', 2), FST::RELATION('.', 2), FST::RELATION(',', 2),\
	FST::RELATION('?', 2), FST::RELATION('!', 2), FST::RELATION(';', 2), FST::RELATION(':', 2), FST::RELATION('-', 2)),\
    \
	FST::NODE(1, FST::RELATION('"', 3)),\
	FST::NODE()

#define FST_TRUE 5,\
    FST::NODE(1, FST::RELATION('t',1)),\
    FST::NODE(1, FST::RELATION('r',2)),\
    FST::NODE(1, FST::RELATION('u',3)),\
    FST::NODE(1, FST::RELATION('e',4)),\
    FST::NODE()

#define FST_FALSE 6,\
    FST::NODE(1, FST::RELATION('f',1)),\
    FST::NODE(1, FST::RELATION('a',2)),\
    FST::NODE(1, FST::RELATION('l',3)),\
    FST::NODE(1, FST::RELATION('s',4)),\
    FST::NODE(1, FST::RELATION('e',5)),\
    FST::NODE()


#define FST_POINT 2,\
    FST::NODE(1, FST::RELATION('.',1)),\
    FST::NODE()

#define FST_COMMA 2,\
    FST::NODE(1, FST::RELATION(',',1)),\
    FST::NODE()

#define FST_LEFTBRACE 2,\
    FST::NODE(1, FST::RELATION('[',1)),\
    FST::NODE()

#define FST_RIGHTBRACE 2,\
    FST::NODE(1, FST::RELATION(']',1)),\
    FST::NODE()

#define FST_LEFTHESIS 2,	\
	FST::NODE(1, FST::RELATION('(', 1)),\
	FST::NODE()

#define FST_RIGHTHESIS 2,	\
	FST::NODE(1, FST::RELATION(')', 1)),\
	FST::NODE()

#define FST_MORE 2, \
   FST::NODE(1, FST::RELATION('>', 1)),\
   FST::NODE()

#define FST_LESS 2, \
   FST::NODE(1, FST::RELATION('<', 1)),\
   FST::NODE()

#define FST_EQUALLY 2, \
   FST::NODE(1, FST::RELATION('=', 1)),\
   FST::NODE()

#define FST_COMPARE 2, \
   FST::NODE(1, FST::RELATION(':', 1)),\
   FST::NODE()

#define FST_PLUS 2, \
   FST::NODE(1, FST::RELATION('+', 1)),\
   FST::NODE()

#define FST_MINUS 2, \
  FST::NODE(1, FST::RELATION('-', 1)),\
  FST::NODE()

#define FST_STAR 2, \
  FST::NODE(1, FST::RELATION('*', 1)),\
  FST::NODE()

#define FST_DIRSLASH 2, \
  FST::NODE(1, FST::RELATION('/', 1)),\
  FST::NODE()

