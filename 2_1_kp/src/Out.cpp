#include <fstream>
#include "string.h"
#include "Utils.h"
#include "Out.h"
#include "Error.h"

using namespace Utils;
using namespace std;

namespace Out {
    // Используется для создания и открытия потокового вывода результирующего файла.
    OUT* createOut(Parm::PARM params) {
        string fileName	 = toChars(params.out);
        ofstream* stream = new ofstream();
        stream->open(fileName);
        if (!stream->is_open()) {
            throw ERROR_THROW(113);
        }

        // stream->imbue(locale("ru_RU.CP1251"));
        return new OUT(stream, params.logToConsole);
    }

    // закрыть файл
    void OUT::close() {
        if (stream) {
            stream->close();
            stream = nullptr;
        }
    }
}
