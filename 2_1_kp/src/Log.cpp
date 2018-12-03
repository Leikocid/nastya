#include <wchar.h>
#include <fstream>
#include <iostream>
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
    LOG* getLog(Parm::PARM params) {
        string fileName	 = toChars(params.log);
        ofstream* stream = new ofstream();
        stream->open(fileName);
        if (!stream->is_open()) {
            throw ERROR_THROW(112);
        }

        // stream->imbue(locale("ru_RU.CP1251"));
        return new LOG(stream, params.logToConsole);
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

            *this << s << endl;
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
            *this << s << endl;
            delete s;
        }
    }

    // вывести в протокол заголовок: ---- Протокол -----  Дата: 21.04.2015 22:18:04 ---------
    void LOG::logLog() {
        if (stream) {
            *this << "----- Протокол -----  Дата: ";
            tm tm;
            getCurrentTime(tm);
            char timeString[80];
            strftime(timeString, 80, "%d.%m.%Y %H:%M:%S", &tm);
            *this << timeString;
            *this << " ----- " << endl;
        }
    }

    // вывести в пртокол информацию о входных параметрах
    void LOG::logParm(PARM parm) {
        if (stream) {
            *this << "-log: ";
            char* str = toChars(parm.log);
            *this << str << endl;
            delete str;
            *this << "-out: ";
            str = toChars(parm.out);
            *this << str << endl;
            delete str;
            *this << "-in: ";
            str = toChars(parm.in);
            *this << str << endl;
            delete str;
        }
    }

    // вывести в протокол информацию o входном потоке
    void LOG::logIn(IN in) {
        if (stream) {
            *this << "----- Исходные данные -----" << endl;
            *this << "Количество символов: " << in.size << endl;
            *this << "Проигнорировано:     " << in.ignor << endl;
            *this << "Количество строк:    " << in.lines << endl;
        }
    }

    // вывести в протокол инфомацию об ошибке
    void LOG::logError(ERROR error) {
        if (stream) {
            *this << "Ошибка " << error.id << ": " << error.message;
            if (error.hasInext) {
                *this << ", строка "  << error.inext.line << ", позиция " << error.inext.col << endl << endl;
            }
            *this << endl;
        }
    }

    void LOG::logLexemTables(LT::LexTable lextable, IT::IdTable idtable) {
        if (stream) {
            *this << "\nТаблица лексем:\n";
            for (int i = 0; i < lextable.table.size(); i++) {
                LT::Entry e  = lextable.table[i];
                int prevLine = 0;
                if (i > 0) {
                    prevLine = lextable.table[i - 1].line;
                }
                if (e.line != prevLine) {
                    for (int l = prevLine + 1; l <= e.line; l++) {
                        *this << std::endl;
                        if (l < 10) {
                            *this << "0";
                        }
                        *this << l << ": ";
                    }
                }
                *this << e.lexema;
                if (e.lexema == 'i') {
                    *this << "[" << e.idxTI << "]";
                }
            }
            *this << "\n\nТаблица идентификаторов:\n\n";
            for (int i = 0; i < idtable.table.size(); i++) {
                if (i < 10) {
                    *this << "0";
                }
                *this << i << ": ";

                switch (idtable.table[i].idtype) {
                    case IT::T_F: {
                        *this << "f ";
                        break;
                    }
                    case IT::T_P: {
                        *this << "p ";
                        break;
                    }
                    case IT::T_V: {
                        *this << "v ";
                        break;
                    }
                    case IT::T_L: {
                        *this << "l ";
                        break;
                    }
                }

                switch (idtable.table[i].iddatatype) {
                    case IT::DT_STR: {
                        *this << "str";
                        break;
                    }; case IT::DT_INT: {
                        *this << "int";
                        break;
                    }; case IT::DT_UNKNOWN: {
                        *this << "<unknown>";
                        break;
                    };
                }
                *this << " " << idtable.table[i].id << " [" << idtable.table[i].idxfirstLE << "] ";

                switch (idtable.table[i].idtype) {
                    case IT::T_F: {
                        break;
                    }
                    case IT::T_P:
                    case IT::T_V:
                    case IT::T_L: {
                        if (idtable.table[i].iddatatype == IT::DT_STR) {
                            *this << "= <" << idtable.table[i].value.vstr.str << "> lenght = " << (int)idtable.table[i].value.vstr.len;
                        } else if (idtable.table[i].iddatatype == IT::DT_INT) {
                            *this << "= <" << (int)idtable.table[i].value.vint << ">";
                        }
                        break;
                    }
                }
                *this << endl;
            }
        }
    }
}
