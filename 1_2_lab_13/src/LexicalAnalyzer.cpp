/**
 * @brief
 *
 *              Лексический анализатор
 *
 * • проверяет входной поток символов программы на исходном языке на допустимость, удаляет лишние пробелы;
 * • для выбранной части входного потока выполняется функция распознавания лексемы;
 * • при успешном распознавании информация о выделенной лексеме заносится в таблицу лексем и таблицу идентификаторов;
 * • при неуспешном распознавании выдается сообщение об ошибке, а дальнейшее выполнение прекращается
 * • формирует протокол работы;
 *
 */

#include "LexicalAnalyzer.h"
#include "LT.h"
#include "IT.h"
#include "Utils.h"

#include <iostream>

using namespace LT;
using namespace IT;
using namespace Utils;

namespace LA {
    Recognizers RECOGNIZERS = *(new Recognizers());

    void analyzeFragment(const TranslationContext &ctx, const int begin, const int end, const int line, const int col);
    void addLexema(const TranslationContext &ctx,
                   const int		    begin,
                   const int		    end,
                   const int		    line,
                   const int		    col,
                   const char		    lexema,
                   const int		    lexemaType);
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
                    addLexema(ctx, begin, i, beginLine, col, LEX_LITERAL, LT_STRING_LITERAL);
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
                        addLexema(ctx, begin - 1, i, beginLine, col, c, LT_SIGN);
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

    // терминальные символы: space ; , . { } ( ) + - * / \n \t ` ' =
    bool isTerminalSymbol(const char c) {
        return c == ' ' || c == ';' || c == ',' || c == '.'  || c == '\'' ||
               c == '{' || c == '}' || c == '(' || c == ')' || c == '+' || c == '=' ||
               c == '-' || c == '*' || c == '/' || c == '\n' || c == '\t';
    }

    void analyzeFragment(const TranslationContext &ctx, const int begin, const int end, const int line, const int col) {
        if (begin <= end) {
            char* fragment	   = subString(ctx.in.text, begin, end - begin + 1);
            Recognizer* recognizer = RECOGNIZERS.recognyze(fragment);
            if (!recognizer) {
                throw ERROR_THROW_IN(25, line, col);
            } else {
                addLexema(ctx, begin, end, line, col, recognizer->lexema, recognizer->lexemaType);
            }
        }
    }

    // добавление записей в таблицы лексем и идентификаторов
    void addLexema(const TranslationContext &ctx, const int begin, const int end, const int line, const int col, const char lexema,
                   const int lexemaType) {
        char* fragment = subString(ctx.in.text, begin, end - begin + 1);

        // TODO: добавление записей

        // TODO: логирование
        std::cout << line << ": " << lexema << "        [" << fragment << "]" << endl;
    }
}
