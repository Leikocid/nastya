#pragma once
#define PARM_IN L"-in:"						//ключ для файла исходника
#define PARM_OUT L"-out:"					//для объектного кода
#define PARM_LOG L"-log:"					//для файла журнала
#define PARM_MAX_SIZE 300					//максимальная длина строки параметра
#define PARM_OUT_DEFAULT_EXT L".out"		//расшириние файла объектного кода по умолчанию
#define PARM_LOG_DEFAULT_EXT L".log"		//расширение файла протокола по умолчанию

namespace Parm
{
	struct PARM
	{
		wchar_t in[PARM_MAX_SIZE];			//имена файлов
		wchar_t out[PARM_MAX_SIZE];
		wchar_t log[PARM_MAX_SIZE];
	};
	PARM getparm(int argc, _TCHAR* argv[]);			//формирование структуры PARM на основе параметров main
};