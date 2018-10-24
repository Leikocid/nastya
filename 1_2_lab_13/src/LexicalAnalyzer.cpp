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
#include "LT.h"
#include "IT.h"

#include "FST.h"

#include <iostream>

using namespace LT;
using namespace IT;

using namespace Fst;

namespace LA {
    void analyzeFragment(const TranslationContext &ctx, const int begin, const int end, const int line, const int col);
    void addLexema(const TranslationContext &ctx, const int begin, const int end, const int line, const int col, const char lexema);
    bool isTerminalSymbol(const char c);

    // лексический разбор входного файла ctx.in.txt и построение таблиц ctx.lt и ctx.it
    void lexicalAnalysis(TranslationContext &ctx) {
        // создаем пустые таблицы
        ctx.lexTable = CreateLexTable(LT_MAXSIZE);
        ctx.idTable  = CreateIdTable(IT_MAXSIZE);

        // разбираем входящий файл по частям
        int  i		= 0;     // инщекс текущего символа
        int  begin	= 0;     // индекс начала фрагмента текста
        int  beginLine	= 0;     // номер строки начала фрагмента
        int  line	= 1;     // номер текущей строки
        int  col	= 1;     // номер текущей колонки
        bool stringMode = false; // это специальный режим когда мы ждем только закрывающейся кавычки '

        // проходим последовательно символы исходного текста, отделяя фрагменты текста с помощью
        // терминальных символов: space ; , . { } ( ) + - * / \n \t ' =
        // в случае если мы определяем границу строкового литерала то терминальный символ это одинарная кавычка: ’
        while (i < strlen((char*)ctx.in.text)) {
            char c = ctx.in.text[i];

            if (stringMode) { // режим строкового литерала
                if (c == '\'') {
                    addLexema(ctx, begin, i, beginLine, col, LEX_LITERAL);
                    stringMode = false;
                    begin      = i + 1;
                    beginLine  = line;
                }
            } else { // обычный режим обработки
                if (isTerminalSymbol(c)) {
                    analyzeFragment(ctx, begin, i - 1, beginLine, col);
                    begin     = i + 1;
                    beginLine = line;
                }

                switch (c) {
                    case '\'': {
                        stringMode = true;
                        begin	   = i;
                        beginLine  = line;
                        break;
                    }
                    case LEX_PLUS:
                    case LEX_MINUS:
                    case LEX_STAR:
                    case LEX_DIRSLASH:
                    case LEX_COMPARE:
                    case LEX_SEMICOLON:
                    case LEX_COMMA:
                    case LEX_LEFTBRACE:
                    case LEX_RIGTHBRACE:
                    case LEX_LEFTHESIS:
                    case LEX_RIGHTHESIS: {
                        addLexema(ctx, begin - 1, i, beginLine, col, c);
                        break;
                    }
                }
            }

            if (c == '\n') {
                line++;
                col = 1;
            } else {
                col++;
            }
            i++;
        }
        if (stringMode) {
            // TODO - кинуть ошибку - строковый литерал открыт и не закрыт
        }
        analyzeFragment(ctx, begin, i - 1, line, col); // обработать последний фрагмент текста
    }

    void analyzeFragment(const TranslationContext &ctx, const int begin, const int end, const int line, const int col) {
        if (begin <= end) {
            char* str = new char[end - begin + 2];
            memcpy(str, &ctx.in.text[begin], end - begin + 1);
            str[end - begin + 1] = '\0';
            std::cout << line << ": фрагмент [" << str << "]" << endl;

            // TODO


            // недетерминированный конечный автомат start( )+((send|wait|show)( )+)*( )+stop
            // FST fst(str,
            //         24,
            //         N(R('s', 1)),
            //         N(R('t', 2)),
            //         N(R('a', 3)),
            //         N(R('r', 4)),
            //         N(R('t', 5)),
            //         N(R(' ', 5),  R(' ', 6)),
            //         N(R('s', 7),  R('w', 8), R(' ', 9)),
            //         N(R('e', 10), R('h', 11)),

            //         N(R('a', 17)),
            //         N(R(' ', 9),  R('s', 20)),
            //         N(R('n', 12)),
            //         N(R('o', 15)),
            //         N(R('d', 13)),
            //         N(R(' ', 14), R(' ', 6)),
            //         N(R(' ', 14), R(' ', 9)),
            //         N(R('w', 16)),

            //         N(R(' ', 14), R(' ', 6)),
            //         N(R('i', 18)),
            //         N(R('t', 19)),
            //         N(R(' ', 14), R(' ', 6)),
            //         N(R('t', 21)),
            //         N(R('o', 22)),
            //         N(R('p', 23)),
            //         N());
            // if (execute(fst)) {
            //     logLine(ctx.logger, "Цепочка \"", fst.string, "\" распознана", "");
            // } else {
            //     logLine(ctx.logger, "Цепочка \"", fst.string,		   "\" не распознана", "");
            //     logLine(ctx.logger, "Строка: ",	  to_string(line).c_str(), ", позиция: ",
            //             to_string(col + begin - end - 1 + fst.position).c_str(), "");
            // }
        }
    }

    // терминальные символы: space ; , . { } ( ) + - * / \n \t ` ' =
    bool isTerminalSymbol(const char c) {
        return c == ' ' || c == ';' || c == ',' || c == '.'  || c == '\'' ||
               c == '{' || c == '}' || c == '(' || c == ')' || c == '+' || c == '=' ||
               c == '-' || c == '*' || c == '/' || c == '\n' || c == '\t';
    }

    void addLexema(const TranslationContext &ctx, const int begin, const int end, const int line, const int col, const char lexema) {
        // TODO
        char* str = new char[end - begin + 2];
        memcpy(str, &ctx.in.text[begin], end - begin + 1);
        str[end - begin + 1] = '\0';
        std::cout << line << ": " << lexema << "        [" << str << "]" << endl;
    }
}
