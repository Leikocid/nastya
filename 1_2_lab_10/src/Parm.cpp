#include <wchar.h>
#include "Parm.h"
#include "Error.h"
#include <iostream>

using namespace std;

namespace Parm {
    // сформировать struct РАRM на основе параметров функции main
    PARM getparm(int argc, char* argv[]) {
        wchar_t* inParam  = NULL;
        wchar_t* outParam = NULL;
        wchar_t* logParam = NULL;

        for (int i = 0; i < argc; i++) {
            char* c	       = argv[i];
            const size_t cSize = strlen(c) + 1;
            wchar_t*	 arg   = new wchar_t[cSize];
            mbstowcs(arg, c, cSize);

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
        }

        PARM p = *(new PARM);
        if (!inParam) {
            throw ERROR_THROW(100);
        }
        if (wcslen(inParam) - 4 > PARM_MAX_SIZE) {
            throw ERROR_THROW(104);
        } else {
            wcscpy(p.in, &(inParam[4]));
        }
        if (outParam) {
            if (wcslen(outParam) - 5 > PARM_MAX_SIZE) {
                throw ERROR_THROW(104);
            } else {
                wcscpy(p.out, &(outParam[5]));
            }
        } else {
            wcscpy(p.out, p.in);
            wcsncat(p.out, L".out", 4);
        }
        if (logParam) {
            if (wcslen(logParam) - 5 > PARM_MAX_SIZE) {
                throw ERROR_THROW(104);
            } else {
                wcscpy(p.log, &(logParam[5]));
            }
        } else {
            wcscpy(p.log, p.in);
            wcsncat(p.log, L".log", 4);
        }
        return p;
    }
}
