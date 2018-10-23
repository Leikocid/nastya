#include <wchar.h>
#include <fstream>
#include "Log.h"
#include "Parm.h"
#include "Error.h"
#include "Utils.h"
#include <stdarg.h>

using namespace std;
using namespace Parm;
using namespace Error;

using namespace Utils;

// Работа с протоколом
namespace Log {
    // Используется для создания и открытия потокового вывода протокола.
    LOG getLog(wchar_t logfile[]) {
        LOG log = *(new LOG());
        wcscpy(log.logfile, logfile);

        string fileName	 = toChars(logfile);
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
    void logLine(LOG log, const char* c, ...) {
        if (log.stream) {
            va_list p;
            va_start(p, c);

            int len	   = 0;
            const char* cp = c;
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

    // вывести в протокол конкатенацию строк
    void logLine(LOG log, const wchar_t* c, ...) {
        if (log.stream) {
            va_list p;
            va_start(p, c);

            int len	      = 0;
            const wchar_t* cp = c;
            while (wcscmp(cp, L"")) {
                len += wcslen(cp);
                cp   = va_arg(p, wchar_t*);
            }
            va_end(p);

            wchar_t* ws = new wchar_t[len + 1];
            ws[0] = 0;
            va_start(p, c);
            cp = c;
            while (wcscmp(cp, L"")) {
                wcsncat(ws, cp, wcslen(cp));
                cp = va_arg(p, wchar_t*);
            }
            va_end(p);

            char* s = toChars(ws);
            *(log.stream) << s << endl;
            delete s;
        }
    }

    // вывести в протокол заголовок: ---- Протокол -----  Дата: 21.04.2015 22:18:04 ---------
    void logLog(LOG log) {
        if (log.stream) {
            *(log.stream) << "----- Протокол -----  Дата: ";
            time_t t  = time(NULL);
            tm*	   tm = localtime(&t);
            char   timeString[80];
            strftime(timeString, 80, "%d.%m.%Y %H:%M:%S", tm);
            *(log.stream) << timeString;
            *(log.stream) << " ----- " << endl;
        }
    }

    // вывести в пртокол информацию о входных параметрах
    void logParm(LOG log, PARM parm) {
        if (log.stream) {
            *(log.stream) << "-log: ";
            char* str = toChars(parm.log);
            *(log.stream) << str << endl;
            delete str;
            *(log.stream) << "-out: ";
            str = toChars(parm.out);
            *(log.stream) << str << endl;
            delete str;
            *(log.stream) << "-in: ";
            str = toChars(parm.in);
            *(log.stream) << str << endl;
            delete str;
        }
    }

    // вывести в протокол информацию o входном потоке
    void logIn(LOG log, IN in) {
        if (log.stream) {
            *(log.stream) << "----- Исходные данные -----" << endl;
            *(log.stream) << "Количество символов: " << in.size << endl;
            *(log.stream) << "Проигнорировано:     " << in.ignor << endl;
            *(log.stream) << "Количество строк:    " << in.lines << endl;
        }
    }

    // вывести в протокол инфомацию об ошибке
    void logError(LOG log, ERROR error) {
        if (log.stream) {
            *(log.stream) << "Ошибка " << error.id << ": " << error.message;
            if (error.hasInext) {
                *(log.stream) << ", строка "  << error.inext.line << ", позиция " << error.inext.col << endl << endl;
            }
            *(log.stream) << endl;
        }
    }
}
