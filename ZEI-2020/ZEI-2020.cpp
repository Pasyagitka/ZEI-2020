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
//TODO: цикл

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	wchar_t lexpath[] = L"../Lex.txt";
	wchar_t idpath[] = L"../Id.txt";
	
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

		Out::WriteOut(out, in);
		Out::Close(out);

		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		Log::WriteIn(log, in);
	
		
		Lan::Analysis((char*)in.text, log, lextable, idtable);


		//Pn::ToPolish(ltable, itable);
		Log::WriteLexTable(log, lextable);
		Log::WriteIdTable(log, idtable);

		MFST_TRACE_START //отладка
			MFST::Mfst synt = MFST::Mfst::Mfst(lextable, GRB::getGreibach()); //автомат
			//mfst.start();		//старт синтаксического анализа
		synt.start();
		synt.savededucation();
		synt.printrules();
		
	
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
