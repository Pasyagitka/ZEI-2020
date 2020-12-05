#include "Error.h"

namespace Error
{
	//TODO: проверить позиции ошибок
	//серии ошибок : 0 - 99 - системные ошибки
	//				100 - 109 - ошибки параметров
	//				110 - 119 - ошибки открытия и чтения файлов
	//				300 - 399 - Ошибки лексического анализа
	//				400 - 499 - Ошибки синтаксического анализа
	//				500 - 599 - Ошибки семантического анализа - диагностические сообщения подсистемы Error
	ERROR errors[ERROR_MAX_ENTRY] = //таблица ошибок
	{
		ERROR_ENTRY(0, "Недопустимый код ошибки"), // код ошибки вне диапазона 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1, "Системный сбой"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5), ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "[!] Параметр -in должен быть задан"),
		ERROR_ENTRY(101, "[!] Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103), ERROR_ENTRY_NODEF(104), ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107), ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "[!] Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111, "[!] Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112, "[!] Ошибка при создании файла протокола(-log)"),
		ERROR_ENTRY(113, "[!] Ошибка при создании файла с таблицей лексем(-lex)"),
		ERROR_ENTRY(114, "[!] Ошибка при создании файла с таблицей идентификаторов(-id)"),
		ERROR_ENTRY_NODEF(115), ERROR_ENTRY_NODEF(116),ERROR_ENTRY_NODEF(117),ERROR_ENTRY_NODEF(118),ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200),
		ERROR_ENTRY(300, "[LA] Превышен максимальный размер таблицы лексем"),
		ERROR_ENTRY(301, "[LA] Таблица лексем переполнена"),
		ERROR_ENTRY(302, "[LA] Таблица лексем, вероятно, ещё не создана"),
		ERROR_ENTRY(303, "[LA] Недопустимый номер строки таблицы лексем"),
		ERROR_ENTRY(304, "[LA] Превышен максимальный размер таблицы идентификаторов"),
		ERROR_ENTRY(305, "[LA] Таблица идентификаторов переполнена"),
		ERROR_ENTRY(306, "[LA] Таблица идентификаторов, вероятно, ещё не создана"),
		ERROR_ENTRY(307, "[LA] Недопустимый номер строки таблицы идентификаторов"),
		ERROR_ENTRY(308, "[LA] Превышена максимальная длина имени идентификатора"),	
		ERROR_ENTRY(309, "[LA] Значение вне диапазона для литерала типа tiny [-128; +127]"),
		ERROR_ENTRY(310, "[LA] Превышена максимальная длина литерала типа symbolic"),
		ERROR_ENTRY(311, "[LA] Ошибка лексического разбора"),	ERROR_ENTRY_NODEF(312),ERROR_ENTRY_NODEF(313),ERROR_ENTRY_NODEF(314),ERROR_ENTRY_NODEF(315),
		ERROR_ENTRY_NODEF(116),ERROR_ENTRY_NODEF(117),ERROR_ENTRY_NODEF(118),ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF10(320), ERROR_ENTRY_NODEF10(330), ERROR_ENTRY_NODEF10(340), ERROR_ENTRY_NODEF10(350),
		ERROR_ENTRY_NODEF10(360), ERROR_ENTRY_NODEF10(370), ERROR_ENTRY_NODEF10(380), ERROR_ENTRY_NODEF10(390),
		ERROR_ENTRY_NODEF100(400),
		ERROR_ENTRY(500, "[SX] Неверная структура программы"),
		ERROR_ENTRY(501, "[SX] Неверный список параметров функции"),
		ERROR_ENTRY(502, "[SX] Неверный список параметров функции при её объявлении"),
		ERROR_ENTRY(503, "[SX] Отсутствует тело функции"),
		ERROR_ENTRY(504, "[SX] Неверное выражение. Ожидаются только идентификаторы и литералы"),
		ERROR_ENTRY(505, "[SX] Ошибка в теле процедуры "),
		ERROR_ENTRY(505, "[SX] Неверная конструкция в теле функции"),
		ERROR_ENTRY(506, "[SX] Ошибка в условном выражении"),
		ERROR_ENTRY(507, "[SX] Ошибка в вызове функции"),
		ERROR_ENTRY(508, "[SX] Ошибка в вызове функции"),
		ERROR_ENTRY(509, "[SX] Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY(508, "[SX] Ошибка в арифметическом выражении"),
		ERROR_ENTRY(511, "[SX] Неверная конструкция в теле цикла/условного выражения"),





		//Семантика [SM]
		ERROR_ENTRY_NODEF100(600), ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	};
	ERROR geterror(int id)
	{
		ERROR newError{};
		(id < 0 && id > ERROR_MAX_ENTRY) ?	newError = errors[0] : newError = errors[id];
		return newError;
	}
	ERROR geterrorin(int id, short line = -1, short col = -1)
	{
		ERROR newError{};
		if (id < 0 && id > ERROR_MAX_ENTRY) {
			newError = errors[0];
		}
		else {
			newError = errors[id];
			newError.inext.line = line;
			newError.inext.col = col;
		}
		return newError;
	}
};