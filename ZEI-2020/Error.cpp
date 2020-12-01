#include "Error.h"

namespace Error
{
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
		
		ERROR_ENTRY(100, "[!] Параметр -in должен быть задан"),
		ERROR_ENTRY(101, "[!] Превышена длина входного параметра"),

		ERROR_ENTRY(110, "[!] Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111, "[!] Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112, "[!] Ошибка при создании файла протокола(-log)"),
		ERROR_ENTRY(113, "[!] Ошибка при создании файла с таблицей лексем(-lex)"),
		ERROR_ENTRY(114, "[!] Ошибка при создании файла с таблицей идентификаторов(-id)"),

		ERROR_ENTRY(300, "[LA|L] Превышен максимальный размер таблицы лексем"),
		ERROR_ENTRY(301, "[LA|I] Таблица лексем переполнена"),
		ERROR_ENTRY(302, "[LA|L] Таблица лексем, вероятно, ещё не создана"),
		ERROR_ENTRY(303, "[LA|L] Недопустимый номер строки таблицы лексем"),
		ERROR_ENTRY(304, "[LA|I] Превышен максимальный размер таблицы идентификаторов"),
		ERROR_ENTRY(305, "[LA|I] Таблица идентификаторов переполнена"),
		ERROR_ENTRY(306, "[LA|I] Таблица идентификаторов, вероятно, ещё не создана"),
		ERROR_ENTRY(307, "[LA|I] Недопустимый номер строки таблицы идентификаторов"),

		ERROR_ENTRY(500, "[SEM] Неверная структура программы"),
		ERROR_ENTRY(501, "[SEM] Ошибочный оператор"),
		ERROR_ENTRY(502, "[SEM] Ошибка в выражении"),
		ERROR_ENTRY(503, "[SEM] Ошибка в параметрах функции"),
		ERROR_ENTRY(504, "[SEM] Ошибка в параметрах вызываемой фукнции"),
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