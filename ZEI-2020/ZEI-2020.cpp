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
//#define AUTO

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	
	Log::LOG log = Log::INITLOG;
	Out::OUT out = Out::INITOUT;
	LT::LexTable lextable = LT::Create(LT_TABLE_SIZE);
	IT::IdTable idtable = IT::Create(TI_TABLE_SIZE);
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);

		log = Log::getlog(parm.log);
		out = Out::getout(parm.out);

		In::IN in = In::getin(parm.in);

		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		Log::WriteIn(log, in);

		Lan::Analysis((char*)in.text, log, lextable, idtable);

		Log::WriteLexTable(log, lextable);
		Log::WriteIdTable(log, idtable);

		MFST_TRACE_START(log);
		MFST::Mfst mfst(lextable, GRB::getGreibach());
		mfst.start(log);
		mfst.savededucation();
		mfst.printrules(log);

		Sem::Analysis(lextable, idtable, log);
	
		//Pn::ToPolish(lextable, idtable);
		
		CG::Generation(lextable, idtable, out);

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
					std::cout << "Исполняемый файл создается..." << std::endl;
					system(path);
					std::cout << "Запуск исполняемого файла!" << std::endl;
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
