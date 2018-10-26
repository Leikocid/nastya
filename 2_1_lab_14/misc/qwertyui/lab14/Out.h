#pragma once
namespace Out
{
	struct OUT
	{
		wchar_t outfile[PARM_MAX_SIZE];
		std::ofstream* stream;
	};

	OUT getEXE(wchar_t outfile[]);
	void writeCode(OUT, char* ch);
	void close(OUT);
};