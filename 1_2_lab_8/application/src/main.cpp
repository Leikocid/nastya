
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
        cout << "-in:" << parm.in << ", out:" << parm.out << ", -log:" << parm.log << endl << endl;
    } catch (ERROR e) {
        cout << "Ошибка " << e.id << ": " << e.message << endl << endl;
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "rus");
    locale::global(locale(locale(""), new codecvt_utf8<wchar_t>));

    testErrors();
    testParm(argc, argv);


    try {
        // обработка параметров
        // создание журнала
        // ввод исходного кода
    } catch (ERROR e) {
        cout << "Ошибка: " << e.id << endl << endl;
    }

    return 0;
}
