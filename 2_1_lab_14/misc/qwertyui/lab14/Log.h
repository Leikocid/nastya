#pragma once
#include <fstream>
#include <ctime>
#include "In.h"
#include "Parm.h"

namespace Log
{
	struct LOG
	{
		wchar_t logfile[PARM_MAX_SIZE];
		std::ofstream* stream;
	};

	static const LOG INITLOG = { L"", NULL };			//для начальной инициализации LOG
	LOG getlog(wchar_t logfile[]);						//сформировать структуру LOG
	void WriteLine(LOG log, char* c, ...);					//вывести в протокол конкатенацию строк
	void WriteLine(LOG log, wchar_t* c, ...);
	void WriteLog(LOG);									//вывеси заголовок	
	void WriteParm(LOG, Parm::PARM);					//вывести инфу о входных параметрах
	void WriteIn(LOG, In::IN);							//инфу о потоке
	void WriteError(LOG, Error::ERROR);					//инфу о ошибке
	void Close(LOG);									//закрыть прогу

	void WriteLex(LOG, LT::LexTable&);
	void WriteId(LOG, IT::IdTable&);
};