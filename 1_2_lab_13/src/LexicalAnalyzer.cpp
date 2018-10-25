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

#include <iostream>

using namespace LT;
using namespace IT;

namespace LA {
    Recognizers RECOGNIZERS = *(new Recognizers());

    void analyzeFragment(const TranslationContext &ctx, const int begin, const int end, const int line, const int col);
    void addLexema(const TranslationContext &ctx, const int begin, const int end, const int line, const int col, const char lexema);
    bool isTerminalSymbol(const char c);

    // лексический разбор входного файла ctx.in.txt и построение таблиц ctx.lexTable и ctx.idTable
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
            throw ERROR_THROW_IN(22, line, col);
        }
        analyzeFragment(ctx, begin, i - 1, line, col); // обработать последний фрагмент текста
    }

    void analyzeFragment(const TranslationContext &ctx, const int begin, const int end, const int line, const int col) {
        if (begin <= end) {
            // TODO - сделать вырезание части строки платформонезависимым
            char* str = new char[end - begin + 2];
            memcpy(str, &ctx.in.text[begin], end - begin + 1);
            str[end - begin + 1] = '\0';
            std::cout << line << ": фрагмент [" << str << "] ";

            Recognizer* recognizer = RECOGNIZERS.recognyze(str);
            if (!recognizer) {
                // TODO: throw ERROR_THROW(1111); - фрагмент не распознан
                std::cout << "-" << endl;
            } else {
                // TODO: заполнение таблиц
                std::cout << recognizer->lexema << " " << recognizer->type << endl;
            }

            // TODO: логирование
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
