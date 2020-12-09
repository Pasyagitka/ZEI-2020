#include "Log.h"
//#include "Lan.h"
#include "Error.h"
#include "Parm.h"
#include <ctime>
#include <iostream>
#include "LT.h"


namespace Log
{
	LOG getlog(wchar_t logfile[]) {
		LOG newLog{};
		newLog.stream = new std::ofstream;
		newLog.stream->open(logfile);		
		if (!newLog.stream->is_open())		throw ERROR_THROW(112);
		wcscpy_s(newLog.logfile, logfile);
		return newLog;
	}

	void WriteLine(LOG newLog, char* c, ...) {
		char** pointer = &c;
		while (*pointer != "") {
			*newLog.stream << *pointer;
			pointer++;
		}
		*newLog.stream << std::endl;
	}

	void WriteLine(LOG newLog, wchar_t* c, ...) {
		wchar_t** pointer = &c;
		while (*pointer != L"") {
			char buffer[SIZE];
			size_t n = 0;
			wcstombs_s(&n, buffer, *pointer, SIZE);
			*newLog.stream << buffer;
			pointer++;
		}
		*newLog.stream << std::endl;
	}

	void WriteLog(LOG newLog) {
		time_t t = time(0);
		tm currentTime;
		localtime_s(&currentTime, &t);
		char str[TIME_SIZE];
		strftime(str, TIME_SIZE, "%d.%m.%Y %H:%M:%S", &currentTime);
		*newLog.stream <<"------------ Протокол----------------------------------------------------------------" << str << "------------" << std::endl;
	}

	void WriteParm(LOG newLog, Parm::PARM parameter) {
		size_t n = 0;
		char buffer[PARM_MAX_SIZE];
		*newLog.stream << "\n--------- Параметры -------------------------------------------------------------------------------------" << std::endl;
		wcstombs_s(&n, buffer, parameter.log, PARM_MAX_SIZE);		*newLog.stream << "-log: " << buffer << std::endl;
		wcstombs_s(&n, buffer, parameter.out, PARM_MAX_SIZE);		*newLog.stream << "-out: " << buffer << std::endl;
		wcstombs_s(&n, buffer, parameter.in, PARM_MAX_SIZE);		*newLog.stream << " -in: " << buffer << std::endl;
	}

	void WriteIn(LOG newLog, In::IN in) {
		*newLog.stream << "\n--------- Исходные данные ----------------------------------------------------------------------------" << std::endl;
		*newLog.stream << "Количество символов: " << in.size << std::endl;
		*newLog.stream << "Проигнорировано    : " << in.ignor << std::endl;
		*newLog.stream << "Количество строк   : " << in.lines << std::endl;
	}

	void WriteError(LOG newLog, Error::ERROR newError) {
		if (newLog.stream == nullptr) {
			std::cout << "Ошибка " << newError.id << ": " << newError.message
				<< ", строка " << newError.inext.line << ", позиция " << newError.inext.col << std::endl;
		}
		else {
			*newLog.stream << "Ошибка " << newError.id << ": " << newError.message
				<< ", строка " << newError.inext.line << ", позиция " << newError.inext.col << std::endl;
		}
	}

	void WriteLexTable(LOG newLog, LT::LexTable& lextable)
	{
		*newLog.stream << "\n------------ Таблица лексем ----------------------------------------------------------------------------";
		unsigned int compLine = -1;
		for (unsigned int i = 0; i < (unsigned int)lextable.size; i++)
		{
			if (compLine != lextable.table[i].sn)
			{
				*newLog.stream << std::endl << lextable.table[i].sn << "\t";
				compLine = lextable.table[i].sn;
			}
			*newLog.stream << lextable.table[i].lexema;
			//if (ltable.table[i].indxTI != -1) *lx.stream << ltable.table[i].indxTI;
		}
	}

	void WriteIdTable(LOG newLog, IT::IdTable& idtable)
	{
		*newLog.stream << "\n\n------------ Таблица идентификаторов -----------------------------------------------------------------------" << std::endl;
		*newLog.stream << "Строка\tТип ID\t\tТип данных\tИмя\t\tВидимость\tЗначение\n";
		for (unsigned int i = 0; i < (unsigned int)idtable.size; i++)
		{
			*newLog.stream << idtable.table[i].idxfirstLE << "\t";

			if (idtable.table[i].idtype == IT::V)*newLog.stream << "variable";
			else if (idtable.table[i].idtype == IT::L)*newLog.stream << "literal";
			else if (idtable.table[i].idtype == IT::F)*newLog.stream << "function";
			else if (idtable.table[i].idtype == IT::B)*newLog.stream << "libfunc";
			else if (idtable.table[i].idtype == IT::P)*newLog.stream << "param";


			*newLog.stream << "\t\t";

			if (idtable.table[i].iddatatype == IT::TINY)*newLog.stream << "tiny";
			else if (idtable.table[i].iddatatype == IT::SYMB)*newLog.stream << "symbolic";
			else if (idtable.table[i].iddatatype == IT::LGCL)*newLog.stream << "logical";

			*newLog.stream << "\t\t" << idtable.table[i].id << "\t";

			*newLog.stream << "\t" << idtable.table[i].postfix << "\t\t";

			if (idtable.table[i].iddatatype == IT::TINY)			*newLog.stream << idtable.table[i].value.vtiny;
			else if (idtable.table[i].iddatatype == IT::SYMB)	*newLog.stream << idtable.table[i].value.vsymb->str;
			else if (idtable.table[i].iddatatype == IT::LGCL)	*newLog.stream << idtable.table[i].value.vlogical;

			*newLog.stream << std::endl;
		}
		*newLog.stream << "----------------------------------------------------------------------------------------------------------------------------" << std::endl;
	}


	void Close(LOG newLog) {
		if (newLog.stream != nullptr) {
			newLog.stream->close();
			delete newLog.stream;
		}
	}
};