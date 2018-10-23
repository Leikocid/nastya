#include <wchar.h>
#include <string>
#include "Parm.h"
#include <iostream>

namespace Parm {
    // сформировать struct РАRM на основе параметров функции main
    PARM getparm(int argc, char* argv[]) {
        PARM p = *(new PARM);

        for (int i = 0; i < argc; i++) {
            char* c	       = argv[i];
            const size_t cSize = strlen(c) + 1;
            wchar_t*	 wc    = new wchar_t[cSize];
            mbstowcs(wc, c, cSize);


            std::wcout << *wc << std::endl;

            delete[] wc;
        }
        return p;
    }
}
