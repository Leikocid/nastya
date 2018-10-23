
/**
 * @brief
 *
 */

#include "Error.h"
#include "Parm.h"
#include "Log.h"
#include "In.h"
#include "Out.h"
#include "FST.h"

using namespace std;
using namespace Error;
using namespace Parm;
using namespace In;
using namespace Out;
using namespace Log;
using namespace Fst;

LOG logger = INITLOG;
IN  in;

void checkChain(int begin, int end, int line, int col) {
    if (begin < end) {
        char* str = new char[end - begin + 2];
        memcpy(str, &in.text[begin], end - begin + 1);
        str[end - begin + 1] = '\0';

        // недетерминированный конечный автомат start( )+((send|wait|show)( )+)*( )+stop
        FST fst(str,
                24,
                N(R('s', 1)),
                N(R('t', 2)),
                N(R('a', 3)),
                N(R('r', 4)),
                N(R('t', 5)),
                N(R(' ', 5),  R(' ', 6)),
                N(R('s', 7),  R('w', 8), R(' ', 9)),
                N(R('e', 10), R('h', 11)),

                N(R('a', 17)),
                N(R(' ', 9),  R('s', 20)),
                N(R('n', 12)),
                N(R('o', 15)),
                N(R('d', 13)),
                N(R(' ', 14), R(' ', 6)),
                N(R(' ', 14), R(' ', 9)),
                N(R('w', 16)),

                N(R(' ', 14), R(' ', 6)),
                N(R('i', 18)),
                N(R('t', 19)),
                N(R(' ', 14), R(' ', 6)),
                N(R('t', 21)),
                N(R('o', 22)),
                N(R('p', 23)),
                N());
        if (execute(fst)) {
            logLine(logger, "Цепочка \"", fst.string, "\" распознана", "");
        } else {
            logLine(logger, "Цепочка \"", fst.string,		   "\" не распознана", "");
            logLine(logger, "Строка: ",	  to_string(line).c_str(), ", позиция: ",
                    to_string(col + begin - end - 1 + fst.position).c_str(), "");
        }
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "rus");

    try {
        PARM param = getparm(argc, argv); // разбираем параметры коммандной строки
        logger = getLog(param.log);       // инициализируем логирование
        logLog(logger);
        logParm(logger, param);
        in = getin(param.in);             // считываем входящий файл и проверям на допустимость символов
        logIn(logger, in);

        int begin = 0;                    // разбираем входящий файл по частям
        int i	  = 0;
        int line  = 0;
        int col	  = 0;
        while (i < strlen((char*)in.text)) {
            if (in.text[i] == '|') {
                checkChain(begin, i - 1, line, col);
                begin = i + 1;
            }
            if (in.text[i] == '\n') {
                line++;
                col = 0;
            } else {
                col++;
            }
            i++;
        }
        checkChain(begin, i - 1, line, col);

        writeResult(param.out, in.text);
    } catch (ERROR e) {
        logError(logger, e);
    }
    closeLog(logger);
    return 0;
}
