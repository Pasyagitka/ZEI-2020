 #include <iostream>
#include <locale>
#include <cwchar>
#include <iomanip>

#include "Parm.h"
#include "Error.h"
#include "In.h"
#include "Log.h"
#include "Lan.h"
#include "Out.h"
#include "MFST.h"
#include "Sem.h"
#include "CodeGen.h"
#define AUTO

int _tmain(int argc, _TCHAR* argv[])
{
	int phase = 0;
	setlocale(LC_ALL, "Russian");
	Log::LOG log = Log::INITLOG;
	Out::OUT out = Out::INITOUT;
	try
	{
		LT::LexTable lextable = LT::Create(LT_TABLE_SIZE);
		IT::IdTable idtable = IT::Create(TI_TABLE_SIZE);

		Parm::PARM parm = Parm::getparm(argc, argv);

		log = Log::getlog(parm.log);
		out = Out::getout(parm.out);

		In::IN in = In::getin(parm.in);

		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		Log::WriteIn(log, in);

		if (Lan::Analysis((char*)in.text, log, lextable, idtable)) {
			std::cout << "Лексический анализ завершен" << std::endl;
			phase++;
		}

		Log::WriteLexTable(log, lextable);
		Log::WriteIdTable(log, idtable);

		MFST_TRACE_START(log);
		MFST::Mfst mfst(lextable, GRB::getGreibach());
		if (mfst.start(log)) {
			std::cout << "Синтаксический анализ завершен" << std::endl;
			phase++;
		}
		mfst.savededucation();
		mfst.printrules(log);

		if (Sem::Analysis(lextable, idtable, log)) {
			std::cout << "Семантический анализ завершен" << std::endl;
			phase++;
		}
		
		if (CG::Generation(lextable, idtable, out)) {
			std::cout << "Генерация кода завершена" << std::endl;
			phase++;
		}
	
		LT::Delete(lextable);
		IT::Delete(idtable);

		Log::Close(log);
		Out::Close(out);

		std::cout << "Транслятор завершил работу без ошибок" << std::endl;

		#ifdef AUTO
			size_t n = 0;
			char path[PARM_MAX_SIZE];
			char cs[PARM_MAX_SIZE];
			char csc[] = "C:\\Windows\\Microsoft.NET\\Framework\\v4.0.30319\\csc.exe";
			char exe[] = "..\\Debug\\OutputFile.exe";
			char stdlib[] = "..\\ZEI2020stdlib\\StandartLibrary.cs";
			wcstombs_s(&n, cs, parm.out, PARM_MAX_SIZE);

			sprintf_s(path, PARM_MAX_SIZE, "%s -out:\"%s\" \"%s\" \"%s\" -warn:0", csc, exe, cs, stdlib);
					std::cout << "Исполняемый файл создается на основе файла " << cs << std::endl;
					system(path);
					std::cout << "Запуск исполняемого файла! " << exe << std::endl;
				system(exe);
		#endif 
	}

	catch (Error::ERROR e)
	{
		if (e.inext.line == -1 || e.inext.col == -1)
			std::cout << "Ошибка " << e.id << ": " << e.message << std::endl << std::endl;
		else {
			std::cout << "Ошибка " << e.id << ": " << e.message << std::endl;
			std::cout << "строка " << e.inext.line << " позиция " << e.inext.col << std::endl << std::endl;
		}
		Log::WriteError(log, e);
	};
	system("pause");
	return 0;
}
