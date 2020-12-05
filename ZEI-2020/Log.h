#pragma once
#include "In.h"
#include "Error.h"
#include "LT.h"
#include "IT.h"
#include "Parm.h"
#include <fstream>
#define TIME_SIZE 25

namespace Log // –абота с протоколом
{
	struct LOG	// протокол
	{
		wchar_t logfile[PARM_MAX_SIZE]; // им€ файла протокола
		std::ofstream* stream;			// выходной поток протокола
	};

	static const LOG INITLOG = { L"", NULL };		//структура дл€ начальной инициализации LOG
	LOG getlog(wchar_t logfile[]);					//сформировать структуру LOG
	void WriteLine(LOG log, char* c, ...);			// вывести в протокол конкатенацию строк
	void WriteLine(LOG log, wchar_t* c, ...);		// вывести в протокол конкатенацию строк
	void WriteLog(LOG log);							//вывести в протокол заголовок
	void WriteParm(LOG log, Parm::PARM parm);		// вывести в пртокол информацию о входных параметрах
	void WriteIn(LOG log, In::IN in);				//вывести в протокол информацию о входном потоке
	void WriteError(LOG log, Error::ERROR error);	// вывести в протокол инфомацию об ошибке
	void WriteLexTable(LOG log, LT::LexTable& ltable);
	void WriteIdTable(LOG log, IT::IdTable& itable);
	void Close(LOG log);							// закрыть протокол
};
