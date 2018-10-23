#include "pch.h"
#include "stdafx.h"
#include "Parm.h"
#include <iostream>
#pragma warning(disable : 4996)

namespace Parm
{
	PARM getparm(int argc, _TCHAR* argv[])									//argc - ïî óìîë÷àíèþ åäèíèöà
	{
		PARM parm;
		switch (argc)
		{
		case 1: throw ERROR_THROW(100);
		case 2:
		{
			wchar_t *inpar = argv[1], *buf;
			if (wcslen(inpar) - 4 > PARM_MAX_SIZE)
				throw ERROR_THROW(104);
			buf = wcsstr(inpar, PARM_IN);												//ÂÎÇÂÐÀÒÈÒ ÓÊÀÇÀÒÅËÜ ÍÀ ÏÅÐÂÛÉ ÑÈÌÂÎË "-in:", ÅÑËÈ ÎÍ ÍÀÉÄÅÒÑß
			if (!buf)
				throw ERROR_THROW(100);
			inpar = &buf[4];
			wcscpy_s(parm.in, inpar);

			wcscpy_s(parm.out, inpar);
			wcscat_s(parm.out, PARM_OUT_DEFAULT_EXT);

			wcscpy_s(parm.log, inpar);
			wcscat_s(parm.log, PARM_LOG_DEFAULT_EXT);
			break;
		}
		case 3:
		{
			wchar_t *inpar = argv[1], *buf;
			if (wcslen(inpar) - 4 > PARM_MAX_SIZE)
				throw ERROR_THROW(104);
			buf = wcsstr(inpar, PARM_IN);
			if (!buf)
				throw ERROR_THROW(100);
			inpar = &buf[4];
			wcscpy_s(parm.in, inpar);

			wchar_t *outpar = argv[2];
			if (wcslen(outpar) - 4 > PARM_MAX_SIZE)
				throw ERROR_THROW(104);
			buf = wcsstr(outpar, PARM_OUT);
			if (!buf)
			{
				buf = wcsstr(outpar, PARM_LOG);
				if (!buf)
				{
					wcscpy_s(parm.log, inpar);
					wcscat_s(parm.log, PARM_LOG_DEFAULT_EXT);

					wcscpy_s(parm.out, inpar);
					wcscat_s(parm.out, PARM_OUT_DEFAULT_EXT);
				}
				else
				{
					wchar_t *logpar = argv[3];
					logpar = &buf[5];
					wcscpy_s(parm.log, logpar);

					wcscpy_s(parm.out, inpar);
					wcscat_s(parm.out, PARM_OUT_DEFAULT_EXT);
				}
			}
			else
			{
				outpar = &buf[5];
				wcscpy_s(parm.out, outpar);
			}
			break;
		}
		case 4:
		{
			wchar_t *inpar = argv[1], *buf;
			if (wcslen(inpar) - 4 > PARM_MAX_SIZE)
				throw ERROR_THROW(104);
			buf = wcsstr(inpar, PARM_IN);
			if (!buf)
				throw ERROR_THROW(100);
			inpar = &buf[4];
			wcscpy_s(parm.in, inpar);

			wchar_t *outpar = argv[2];
			if (wcslen(outpar) - 4 > PARM_MAX_SIZE)
				throw ERROR_THROW(104);
			buf = wcsstr(outpar, PARM_OUT);
			if (!buf)
			{
				wcscpy_s(parm.out, inpar);
				wcscat_s(parm.out, PARM_OUT_DEFAULT_EXT);
			}
			else
			{
				outpar = &buf[5];
				wcscpy_s(parm.out, outpar);
			}

			wchar_t *logpar = argv[3];
			if (wcslen(logpar) - 4 > PARM_MAX_SIZE)
				throw ERROR_THROW(104);
			buf = wcsstr(logpar, PARM_LOG);
			if (!buf)
			{
				wcscpy_s(parm.log, inpar);
				wcscat_s(parm.log, PARM_LOG_DEFAULT_EXT);
			}
			else
			{
				logpar = &buf[5];
				wcscpy_s(parm.log, logpar);
			}
			break;
		}
		default:
		{
			wchar_t *inpar = argv[1], *buf;
			if (wcslen(inpar) - 4 > PARM_MAX_SIZE)
				throw ERROR_THROW(104);
			buf = wcsstr(inpar, PARM_IN);
			if (!buf)
				throw ERROR_THROW(100);
			inpar = &buf[4];
			wcscpy_s(parm.in, inpar);

			wchar_t *outpar = argv[2];
			if (wcslen(outpar) - 4 > PARM_MAX_SIZE)
				throw ERROR_THROW(104);
			buf = wcsstr(outpar, PARM_OUT);
			if (!buf)
			{
				wcscpy_s(parm.out, inpar);
				wcscat_s(parm.out, PARM_OUT_DEFAULT_EXT);
			}
			else
			{
				outpar = &buf[5];
				wcscpy_s(parm.out, outpar);
			}

			wchar_t *logpar = argv[3];
			if (wcslen(logpar) - 4 > PARM_MAX_SIZE)
				throw ERROR_THROW(104);
			buf = wcsstr(logpar, PARM_LOG);
			if (!buf)
			{
				wcscpy_s(parm.log, inpar);
				wcscat_s(parm.log, PARM_LOG_DEFAULT_EXT);
			}
			else
			{
				logpar = &buf[5];
				wcscpy_s(parm.log, logpar);
			}
			break;
		}
		}
		return parm;
	}
};