#ifndef LOG_H
#define LOG_H

#include <fstream>
#include "In.h"
#include "Parm.h"
#include "Error.h"
#include "LT.h"
#include "IT.h"

using namespace std;
using namespace Parm;
using namespace Error;
using namespace In;

// Работа с протоколом
namespace Log {
    // протокол
    struct LOG {
        wchar_t	  logfile[PARM_MAX_SIZE];                                // имя файла протокола
        ofstream* stream;                                                // выходной поток пртокола

        void logLine(const char* с, ...);                                // вывести в протокол конкатенацию строк
        void logLine(const wchar_t* с, ...);                             // вывести в протокол конкатенацию строк
        void logLog();                                                   // вывести в протокол заголовок
        void logParm(PARM parm);                                         // вывести в пртокол информацию о входных параметрах
        void logIn(IN in);                                               // вывести в протокол информацию o входном потоке
        void logError(ERROR error);                                      // вывести в протокол инфомацию об ошибке
        void logLexemTables(LT::LexTable lextable, IT::IdTable idtable); // вывести в протокол таблице лексем и идентификаторов
        void closeLog();                                                 // закрыть протокол
        LOG  operator<<(const char* string);                             // вывести в лог строку
        LOG  operator<<(const wchar_t* wideString);                      // вывести в лог строку
    };

    static const LOG INITLOG = { L"", NULL };                            // начальная инициализация лога, который никуда не пишет

    LOG getLog(wchar_t logfile[]);                                       // сформировать структуру LOG
}

#endif // !LOG_H
