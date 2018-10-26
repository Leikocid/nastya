#include "pch.h"
#include "stdafx.h"
#include <iostream>
using namespace std;

namespace Out
{
	OUT getEXE(wchar_t outfile[])
	{
		OUT rc;
		wcscpy_s(rc.outfile, outfile);
		ofstream *FILE = new ofstream;
		(*FILE).open(rc.outfile, ios_base::out, ios_base::trunc);
		rc.stream = FILE;
		return rc;
	}

	void writeCode(OUT rc, char* ch)
	{
		(*rc.stream) << ch;
	}

	void close(OUT rc)
	{
		(*rc.stream).close();
	}
};