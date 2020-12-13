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
#include "Polish.h"
#include "MFST.h"
#include "Sem.h"
#include "CodeGen.h"
//#define AUTO
//TODO: добавить красоты в консоль
//TODO: добавить стандартных функций
//TODO: добавить несколько параметров функций

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	
	Log::LOG log = Log::INITLOG;
	Out::OUT out = Out::INITOUT;
	LT::LexTable lextable = LT::Create(LT_TABLE_SIZE);
	IT::IdTable idtable = IT::Create(TI_TABLE_SIZE);
	try
	{
		std::cout << "_________________ Входные параметры ________________________________________________" << std::endl << std::endl;
		Parm::PARM parm = Parm::getparm(argc, argv);
		std::wcout << " -in: " << parm.in << "\n-out: " << parm.out << "\n-log: " << parm.log << std::endl << std::endl;

		log = Log::getlog(parm.log);

		out = Out::getout(parm.out);
		In::IN in = In::getin(parm.in);

		std::cout << "_________________ Получено из файла ________________________________________________\n\n";
		std::cout << "Всего символов: " << in.size << std::endl;
		std::cout << "Всего строк   : " << in.lines << std::endl;
		std::cout << "Пропущено     : " << in.ignor << std::endl;

		//Out::WriteOut(out, in);
		

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
		
		CodeGeneration::StartGeneration(lextable, idtable, out);


		Out::Close(out);
		#ifdef AUTO
				std::cout << "Исполняемый файл создается..." << std::endl;
				system("C:\\Windows\\Microsoft.NET\\Framework\\v4.0.30319\\csc.exe -out:\"G:\\AAA.exe\" \"G:\\3 семестр\\ЯП курсовой проект\\ZEI-2020\\ZEI-CS\\OutputFile.cs\" \"G:\\3 семестр\\ЯП курсовой проект\\ZEI-2020\\ZEI2020stdlib\\StandartLibrary.cs\" -warn:0 ");
				std::cout << "Запуск исполняемого файла!" << std::endl;
				system("\"G:\\AAA.exe\"");
		#endif 

	
		Log::Close(log);
		//delete in.text;
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
