#include "pch.h"
#include "stdafx.h"
#include <iostream>
#pragma warning(disable : 4996)
using namespace std;

namespace Log
{
	LOG getlog(wchar_t logfile[])
	{
		LOG log;
		wcscpy_s(log.logfile, logfile);
		ofstream *FILE = new ofstream;
		(*FILE).open(logfile, ios_base::out, ios_base::trunc);
		if (!(*FILE).is_open())
			throw ERROR_THROW(112);
		log.stream = FILE;
		return log;
	}

	void WriteLine(LOG log, char* txt, ...)
	{
		char** ptxt = &txt;
		char buf[PARM_MAX_SIZE];
		strcpy_s(buf, txt);
		*ptxt++;
		for (; (strcmp(*ptxt, "") != 0); *ptxt++)
			strcat_s(buf, *ptxt);
		*log.stream << buf << endl;

	}

	void WriteLine(LOG log, wchar_t* txt, ...)
	{
		wchar_t** ptxt = &txt;
		wchar_t buf[PARM_MAX_SIZE];
		char chBuf[PARM_MAX_SIZE];
		wcscpy_s(buf, txt);
		*ptxt++;
		for (; (wcscmp(*ptxt, L"") != 0); *ptxt++)
			wcscat_s(buf, *ptxt);
		wcstombs(chBuf, buf, PARM_MAX_SIZE);
		*log.stream << chBuf << endl;
	}

	void WriteLog(LOG log)
	{
		char Date[50];
		struct tm *date;
		const time_t timer = time(NULL);
		date = localtime(&timer);
		strftime(Date, 50, "%d.%m.%Y %H:%M:%S, %A", date);
		*log.stream << "----Протокол----" << "\t";
		*log.stream << "Дата: " << Date << endl;

	}

	void WriteParm(LOG log, Parm::PARM parm)
	{
		char in[PARM_MAX_SIZE], out[PARM_MAX_SIZE], logf[PARM_MAX_SIZE];
		wcstombs(in, parm.in, PARM_MAX_SIZE);
		wcstombs(out, parm.out, PARM_MAX_SIZE);
		wcstombs(logf, parm.log, PARM_MAX_SIZE);
		*log.stream << "----Параметры----" << endl;
		*log.stream << "-log: " << logf << endl;
		*log.stream << "-out: " << out << endl;
		*log.stream << "-in: " << in << endl << endl;
	}

	void WriteIn(LOG log, In::IN in)
	{
		*log.stream << "----Исходные данные----" << endl;
		*log.stream << "Количество символов: " << in.size << endl;
		*log.stream << "Количество строк: " << in.lines << endl;
		*log.stream << "Проигнорировано: " << in.ignor << endl;
	}

	void WriteError(LOG log, Error::ERROR e)
	{
		if (!log.stream)
			cout << "Ошибка " << e.id << ": " << e.message << endl << "Строка: " << e.inext.line << ", символ: " << e.inext.column << endl << endl;
		else
		{ 
			cout << "Ошибка " << e.id << ": " << e.message << endl << "Строка: " << e.inext.line << ", символ: " << e.inext.column << endl << endl;
			*log.stream << "Ошибка " << e.id << ": " << e.message << endl << "Строка: " << e.inext.line << ", символ: " << e.inext.column << endl;
		}
	}

	void Close(LOG log)
	{
		(*log.stream).close();
	}

	void WriteLex(LOG log, LT::LexTable& ltable)
	{
		*log.stream << "\tТаблица лексем:\n";
		unsigned int compLine = -1;
		for (unsigned int i = 0; i < (unsigned int)ltable.size; i++)
		{
			if(compLine != ltable.table[i].sn)
			{
				*log.stream << endl << ltable.table[i].sn << ".\t";
				compLine = ltable.table[i].sn;
			}
			*log.stream << ltable.table[i].lexema;
		}
		*log.stream << "\n\n";
	}

	void WriteId(LOG log, IT::IdTable& itable)
	{
		*log.stream << "\tТаблица идентификаторов:\n";
		*log.stream << "Строка\tТип Id\t\tТип переменной\tИмя\tЗначение\n";
		for (unsigned int i = 0; i < (unsigned int)itable.size; i++)
		{
			*log.stream << itable.table[i].idxfirstLE << "\t" << itable.table[i].idtype << "\t\t" << itable.table[i].iddatatype << "\t\t" << itable.table[i].id << "\t";
			if (itable.table[i].iddatatype == IT::INT)
				*log.stream << itable.table[i].value.vint;
			else if (itable.table[i].iddatatype == IT::STR)
				*log.stream << itable.table[i].value.vstr->str;
			else
				*log.stream << "ERROR ID";
			*log.stream << endl;
		}
		*log.stream << "\n\n";
	}
};