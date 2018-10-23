/**
 * @brief
 *
 *              Лексический анализатор
 *
 * • проверяет входной поток символов программы на исходном языке на допустимость, удаляет лишние пробелы и добавляет сепаратор для
 *        вычисления номера строки для каждой лексемы;
 * • для выбранной части входного потока выполняется функция распознавания лексемы;
 * • при успешном распознавании информация о выделенной лексеме заносится в таблицу лексем и таблицу идентификаторов, и алгоритм
 *        возвращается к первому этапу;
 * • формирует протокол работы;
 * • при неуспешном распознавании выдается сообщение об ошибке, а дальнейшие действия зависят от реализации сканера - либо его выполнение
 *        прекращается, либо делается попытка распознать следующую лексему (идет возврат к первому этапу алгоритма).
 *
 */

#include "LexicalAnalyzer.h"
#include "FST.h"

using namespace Fst;

namespace LA {
    void checkChain(TranslationContext &ctx, int begin, int end, int line, int col) {
        if (begin < end) {
            char* str = new char[end - begin + 2];
            memcpy(str, &ctx.in.text[begin], end - begin + 1);
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
                logLine(ctx.logger, "Цепочка \"", fst.string, "\" распознана", "");
            } else {
                logLine(ctx.logger, "Цепочка \"", fst.string,		   "\" не распознана", "");
                logLine(ctx.logger, "Строка: ",	  to_string(line).c_str(), ", позиция: ",
                        to_string(col + begin - end - 1 + fst.position).c_str(), "");
            }
        }
    }

    // лексический разбор входного файла ctx.in.txt и построение таблиц ctx.lt и ctx.it
    bool lexicalAnalysis(TranslationContext &ctx) {
        // TODO


        int begin = 0; // разбираем входящий файл по частям
        int i	  = 0;
        int line  = 0;
        int col	  = 0;
        while (i < strlen((char*)ctx.in.text)) {
            if (ctx.in.text[i] == '|') {
                checkChain(ctx, begin, i - 1, line, col);
                begin = i + 1;
            }
            if (ctx.in.text[i] == '\n') {
                line++;
                col = 0;
            } else {
                col++;
            }
            i++;
        }
        checkChain(ctx, begin, i - 1, line, col);


        return false;
    }
}
