
/**
 * @brief
 *
 */

#include <iostream>
#include <fstream>
#include <codecvt>

#include "Error.h"
#include "Parm.h"
#include "Log.h"
#include "In.h"


using namespace std;
using namespace Error;
using namespace Parm;
using namespace In;
using namespace Log;

void testErrors() {
    cout << "---- тест Error::geterror ----" << endl << endl;
    try {
        throw ERROR_THROW(100);
    } catch (ERROR e) {
        cout << "Ошибка " << e.id << ": " << e.message << endl << endl;
    }

    cout << "---- тест Error::geterrorin ----" << endl << endl;
    try {
        throw ERROR_THROW_IN(111, 7, 7);
    } catch (ERROR e) {
        cout << "Ошибка " << e.id << ": " << e.message
             << ", строка " << e.inext.line
             << ", позиция " << e.inext.col  << endl << endl;
    }
}

void testParm(int argc, char* argv[]) {
    cout << "---- тест Parm::getparm ----" << endl << endl;

    try {
        PARM parm = getparm(argc, argv);
        wcout << "-in:" << parm.in << ", out:" << parm.out << ", -log:" << parm.log << endl << endl;
    } catch (ERROR e) {
        cout << "Ошибка " << e.id << ": " << e.message << endl << endl;
    }
}

void testIn(int argc, char* argv[]) {
    cout << "---- тест In::getin ----" << endl << endl;
    try {
        PARM parm = getparm(argc, argv);
        IN   in	  = getin(parm.in);

        cout << in.text << endl;
        cout << "Bcero символов: " << in.size << endl;
        cout << "Bcero строк: " << in.lines << endl;
        cout << "Пponyщeнo: " << in.ignor << endl;
    } catch (ERROR e) {
        cout << "Ошибка " << e.id << ": " << e.message
             << ", строка " << e.inext.line
             << ", позиция " << e.inext.col  << endl << endl;
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "rus");

    // locale::global(locale(locale(""), new codecvt_utf8<wchar_t>));

    testErrors();
    testParm(argc, argv);
    testIn(argc, argv);

    LOG log = INITLOG;
    try {
        PARM parm = getparm(argc, argv);
        log = getLog(parm.log);
        logLine(log, (char*)"Текст:", (char*)"без ошибок", (char*)"");

        // создание журнала
        // ввод исходного кода
    } catch (ERROR e) {
        cout << "Ошибка: " << e.id << endl << endl;
    }
    closeLog(log);

    return 0;
}
