#include <wchar.h>
#include <fstream>
#include "Log.h"
#include "Parm.h"
#include "Error.h"
#include <stdarg.h>

using namespace std;
using namespace Parm;
using namespace Error;

// Работа с протоколом
namespace Log {
    // Используется для создания и открытия потокового вывода протокола.
    LOG getLog(wchar_t logfile[]) {
        LOG log = *(new LOG);
        wcscpy(log.logfile, logfile);

        wstring wideFileName(logfile);
        string	fileName(wideFileName.begin(), wideFileName.end());

        ofstream* stream = new ofstream();
        stream->open(fileName);
        if (!stream->is_open()) {
            throw ERROR_THROW(112);
        }

        // stream->imbue(locale("ru_RU.CP1251"));
        log.stream = stream;
        return log;
    }

    // закрыть протокол
    void closeLog(LOG log) {
        if (log.stream) {
            log.stream->close();
            log.stream = NULL;
        }
    }

    // вывести в протокол конкатенацию строк
    void logLine(LOG log, char* c, ...) {
        if (log.stream) {
            va_list p;
            va_start(p, c);

            int	  len = 0;
            char* cp  = c;
            while (strcmp(cp, "")) {
                len += strlen(cp);
                cp   = va_arg(p, char*);
            }
            va_end(p);

            char* s = new char[len + 1];
            va_start(p, c);
            cp = c;
            while (strcmp(cp, "")) {
                strcat(s, cp);
                cp = va_arg(p, char*);
            }
            va_end(p);

            *(log.stream) << s << endl;
        }
    }

    void logLine(LOG log, wchar_t* с, ...);     // вывести в протокол конкатенацию строк
    void logLog(LOG log);                       // вывести в протокол заголовок: ---- Протокол ----- Дата: 21.04.2015 22:18:04 ------------
    void logParm(LOG log, PARM parm);           // вывести в пртокол информацию о входных параметрах
    void logIn(LOG log, IN in);                 // вывести в протокол информацию o входном потоке
    void logError(LOG log, Error::ERROR error); // вывести в протокол инфомацию об ошибке
}
