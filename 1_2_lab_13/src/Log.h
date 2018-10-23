#ifndef LOG_H
#define LOG_H

#include <fstream>
#include "In.h"
#include "Parm.h"
#include "Error.h"

using namespace std;
using namespace Parm;
using namespace Error;
using namespace In;

// Работа с протоколом
namespace Log {
    // протокол
    struct LOG {
        wchar_t	  logfile[PARM_MAX_SIZE];           // имя файла протокола
        ofstream* stream;                           // выходной поток пртокола
    };

    static const LOG INITLOG = { L"", NULL };       // начальная инициализация лога, который никуда не пишет

    LOG	 getLog(wchar_t logfile[]);                 // сформировать структуру LOG
    void logLine(LOG log, const char* с, ...);      // вывести в протокол конкатенацию строк
    void logLine(LOG log, const wchar_t* с, ...);   // вывести в протокол конкатенацию строк
    void logLog(LOG log);                           // вывести в протокол заголовок
    void logParm(LOG log, PARM parm);               // вывести в пртокол информацию о входных параметрах
    void logIn(LOG log, IN in);                     // вывести в протокол информацию o входном потоке
    void logError(LOG log, Error::ERROR error);     // вывести в протокол инфомацию об ошибке
    void closeLog(LOG log);                         // закрыть протокол
}

#endif // !LOG_H
