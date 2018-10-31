#include <wchar.h>
#include "Parm.h"
#include "Error.h"
#include "Utils.h"
#include <iostream>

using namespace std;
using namespace Utils;

namespace Parm {
    // сформировать struct РАRM на основе параметров функции main
    PARM getparm(int argc, char* argv[]) {
        wchar_t* inParam      = NULL;
        wchar_t* outParam     = NULL;
        wchar_t* logParam     = NULL;
        bool	 logToConsole = false;

        for (int i = 0; i < argc; i++) {
            wchar_t* arg = toWideChars(argv[i]);

            if (wcsncmp(arg, L"-in:", 4) == 0) {
                if (wcslen(arg) > 4) {
                    inParam = arg;
                }
            }
            if (wcsncmp(arg, L"-out:", 5) == 0) {
                if (wcslen(arg) > 5) {
                    outParam = arg;
                }
            }
            if (wcsncmp(arg, L"-log:", 5) == 0) {
                if (wcslen(arg) > 5) {
                    logParam = arg;
                }
            }
            if (wcsncmp(arg, L"-logToConsole", 13) == 0) {
                if (wcslen(arg)  == 13) {
                    logToConsole = true;
                }
            }
        }

        PARM p = *(new PARM);
        if (!inParam) {
            throw ERROR_THROW(100);
        }
        if (wcslen(inParam) - 4 > PARM_MAX_SIZE) {
            throw ERROR_THROW(104);
        } else {
            copyWideChars(p.in, &(inParam[4]));
        }
        if (outParam) {
            if (wcslen(outParam) - 5 > PARM_MAX_SIZE) {
                throw ERROR_THROW(104);
            } else {
                copyWideChars(p.out, &(outParam[5]));
            }
        } else {
            copyWideChars(p.out, p.in);
            appendWideChars(p.out, L".out");
        }
        if (logParam) {
            if (wcslen(logParam) - 5 > PARM_MAX_SIZE) {
                throw ERROR_THROW(104);
            } else {
                copyWideChars(p.log, &(logParam[5]));
            }
        } else {
            copyWideChars(p.log, p.in);
            appendWideChars(p.log, L".log");
        }
        p.logToConsole = logToConsole;
        return p;
    }
}
