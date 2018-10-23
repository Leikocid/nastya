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

	static const LOG INITLOG = { L"", NULL };			//��� ��������� ������������� LOG
	LOG getlog(wchar_t logfile[]);						//������������ ��������� LOG
	void WriteLine(LOG log, char* c, ...);					//������� � �������� ������������ �����
	void WriteLine(LOG log, wchar_t* c, ...);
	void WriteLog(LOG);									//������ ���������	
	void WriteParm(LOG, Parm::PARM);					//������� ���� � ������� ����������
	void WriteIn(LOG, In::IN);							//���� � ������
	void WriteError(LOG, Error::ERROR);					//���� � ������
	void Close(LOG);									//������� �����

	void WriteLex(LOG, LT::LexTable&);
	void WriteId(LOG, IT::IdTable&);
};