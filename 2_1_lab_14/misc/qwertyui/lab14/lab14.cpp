#include "pch.h"
#include "stdafx.h"
#include <iostream>
#include <locale>
#include <cwchar>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;
	char q1[] = "Тест: ", q2[] = "без ошибок ", q3[] = "";
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, q1, q2, q3);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		Out::OUT out = Out::getEXE(parm.out);
		In::IN in = In::getin(parm.in);
		LA::LexAnalizator((char*)in.text, log);
		Out::writeCode(out, (char*)in.text);
		Out::close(out);
		cout << "Выходной файл создан" << endl;
		Log::WriteIn(log, in);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	};
	Log::Close(log);
	cout << "Протокол создан" << endl;
	return 0;
}

