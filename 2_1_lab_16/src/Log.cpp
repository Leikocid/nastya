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
    // вывести в лог строку
    LOG LOG::operator<<(const char* string) {
        if (stream) {
            *stream << string;
        }
        return *this;
    }

    // вывести в лог строку
    LOG LOG::operator<<(const wchar_t* wideString) {
        if (stream) {
            char* string = toChars(wideString);
            *stream << string;
        }
        return *this;
    }

    // Используется для создания и открытия потокового вывода протокола.
    LOG getLog(wchar_t logfile[]) {
        LOG log = *(new LOG());
        copyWideChars(log.logfile, logfile);

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
    void LOG::closeLog() {
        if (stream) {
            stream->close();
            stream = NULL;
        }
    }

    // вывести в протокол конкатенацию строк
    void LOG::logLine(const char* c, ...) {
        if (stream) {
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
            s[0] = 0;
            va_start(p, c);
            cp = c;
            while (strcmp(cp, "")) {
                appendChars(s, cp);
                cp = va_arg(p, char*);
            }
            va_end(p);

            *stream << s << endl;
        }
    }

    // вывести в протокол конкатенацию строк
    void LOG::logLine(const wchar_t* c, ...) {
        if (stream) {
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
                appendWideChars(ws, cp);
                cp = va_arg(p, wchar_t*);
            }
            va_end(p);

            char* s = toChars(ws);
            *stream << s << endl;
            delete s;
        }
    }

    // вывести в протокол заголовок: ---- Протокол -----  Дата: 21.04.2015 22:18:04 ---------
    void LOG::logLog() {
        if (stream) {
            *stream << "----- Протокол -----  Дата: ";
            tm tm;
            getCurrentTime(tm);
            char timeString[80];
            strftime(timeString, 80, "%d.%m.%Y %H:%M:%S", &tm);
            *stream << timeString;
            *stream << " ----- " << endl;
        }
    }

    // вывести в пртокол информацию о входных параметрах
    void LOG::logParm(PARM parm) {
        if (stream) {
            *stream << "-log: ";
            char* str = toChars(parm.log);
            *stream << str << endl;
            delete str;
            *stream << "-out: ";
            str = toChars(parm.out);
            *stream << str << endl;
            delete str;
            *stream << "-in: ";
            str = toChars(parm.in);
            *stream << str << endl;
            delete str;
        }
    }

    // вывести в протокол информацию o входном потоке
    void LOG::logIn(IN in) {
        if (stream) {
            *stream << "----- Исходные данные -----" << endl;
            *stream << "Количество символов: " << in.size << endl;
            *stream << "Проигнорировано:     " << in.ignor << endl;
            *stream << "Количество строк:    " << in.lines << endl;
        }
    }

    // вывести в протокол инфомацию об ошибке
    void LOG::logError(ERROR error) {
        if (stream) {
            *stream << "Ошибка " << error.id << ": " << error.message;
            if (error.hasInext) {
                *stream << ", строка "  << error.inext.line << ", позиция " << error.inext.col << endl << endl;
            }
            *stream << endl;
        }
    }

    void LOG::logLexemTables(LT::LexTable lextable, IT::IdTable idtable) {
        *stream << "\nТаблица лексем:\n";
        for (int i = 0; i < lextable.table.size(); i++) {
            LT::Entry e	 = lextable.table[i];
            int prevLine = 0;
            if (i > 0) {
                prevLine = lextable.table[i - 1].line;
            }
            if (e.line != prevLine) {
                for (int l = prevLine + 1; l <= e.line; l++) {
                    *stream << std::endl;
                    if (l < 10) {
                        *stream << "0";
                    }
                    *stream << l << ": ";
                }
            }
            *stream << e.lexema;
            if (e.lexema == 'i') {
                *stream << "[" << e.idxTI << "]";
            }
        }
        *stream << "\n\nТаблица идентификаторов:\n\n";
        for (int i = 0; i < idtable.table.size(); i++) {
            if (i < 10) {
                *stream << "0";
            }
            *stream << i << ": ";

            switch (idtable.table[i].idtype) {
                case IT::T_F: {
                    *stream << "f ";
                    break;
                }
                case IT::T_P: {
                    *stream << "p ";
                    break;
                }
                case IT::T_V: {
                    *stream << "v ";
                    break;
                }
                case IT::T_L: {
                    *stream << "l ";
                    break;
                }
            }

            switch (idtable.table[i].iddatatype) {
                case IT::DT_STR: {
                    *stream << "str";
                    break;
                }; case IT::DT_INT: {
                    *stream << "int";
                    break;
                }; case IT::DT_UNKNOWN: {
                    *stream << "<unknown>";
                    break;
                };
            }
            *stream << " " << idtable.table[i].id << " [" << idtable.table[i].idxfirstLE << "] ";

            switch (idtable.table[i].idtype) {
                case IT::T_F: {
                    break;
                }
                case IT::T_P:
                case IT::T_V:
                case IT::T_L: {
                    if (idtable.table[i].iddatatype == IT::DT_STR) {
                        *stream << "= <" << idtable.table[i].value.vstr.str << "> lenght = " << (int)idtable.table[i].value.vstr.len;
                    } else if (idtable.table[i].iddatatype == IT::DT_INT) {
                        *stream << "= <" << (int)idtable.table[i].value.vint << ">";
                    }
                    break;
                }
            }
            *stream << endl;
        }
    }
}
