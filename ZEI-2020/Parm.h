#pragma once
#include <tchar.h>

#define PARM_IN L"-in:"					// ключ для файла исходного кода
#define PARM_OUT L"-out:"		 
#define PARM_LOG L"-log:"				// ключ для файла журнала
#define PARM_MAX_SIZE 300				// максимальная длинна строки параметра
#define PARAM_OUT_DEFAULT_EXT L".cs"	
#define PARM_LOG_DEFAULT_EXC  L".log"	// расширение файла протокола по умолчанию

namespace Parm // обработка входных параметров
{
	struct PARM	//входные параметры
	{
		wchar_t in[PARM_MAX_SIZE];		// -in: имя файла исходного кода
		wchar_t out[PARM_MAX_SIZE];		// -out: имя файла исходного кода
		wchar_t log[PARM_MAX_SIZE];		// -log: имя файла исходного кода
	};
	PARM getparm(int argc, _TCHAR* argv[]);	//сформировать struct PARM на основе параметров функции main
};
