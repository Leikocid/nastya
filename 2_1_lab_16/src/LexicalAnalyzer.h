#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include "TranslationContext.h"
#include "FST.h"
#include <vector>

using namespace Fst;

namespace LA {
    // тип лексемы
    enum LEXEMA_TYPE {
        LT_KEYWORD = 0, LT_INTEGER_DATATYPE = 1,  LT_STRING_DATATYPE = 2, LT_INTEGER_LITERAL = 3, LT_STRING_LITERAL = 4, LT_IDENTIFIER = 5,
        LT_MAIN	   = 6, LT_SIGN = 7
    };

    struct Recognizer {
        char lexema;
        int  lexemaType;
        FST* fst;

        // конструктор
        Recognizer(char lexema, int lexemaType, FST* fst) {
            this->lexema     = lexema;
            this->lexemaType = lexemaType;
            this->fst	     = fst;
        }

        // деструктор
        virtual ~Recognizer() {}

        // применяем недетерменированный конечный автомат для распознания фрагмента
        virtual bool isRecognized(const char* fragment) {
            fst->string = fragment;
            return fst->execute();
        }
    };

    struct StringLiteralRecognizer : Recognizer {
        // конструктор
        StringLiteralRecognizer() : Recognizer(LEX_LITERAL, LT_STRING_LITERAL, nullptr) {}

        ~StringLiteralRecognizer() {}

        // проверяем что первый и последний символы это апострофы
        bool isRecognized(const char* fragment) {
            int size = strlen(fragment);
            return size >= 2 && fragment[0] == '\'' && fragment[size - 1] == '\'';
        }
    };

    struct Recognizers {
        vector<Recognizer*> recognizers;

        Recognizers() {
            recognizers.reserve(10);
            recognizers.push_back(new Recognizer(LEX_INTEGER, LT_INTEGER_DATATYPE, new FST("integer")));
            recognizers.push_back(new Recognizer(LEX_STRING, LT_STRING_DATATYPE, new FST("string")));
            recognizers.push_back(new Recognizer(LEX_DECLARE, LT_KEYWORD, new FST("declare")));
            recognizers.push_back(new Recognizer(LEX_FUNCTION, LT_KEYWORD, new FST("function")));
            recognizers.push_back(new Recognizer(LEX_MAIN, LT_MAIN, new FST("main")));
            recognizers.push_back(new Recognizer(LEX_PRINT, LT_IDENTIFIER, new FST("print")));
            recognizers.push_back(new Recognizer(LEX_RETURN, LT_KEYWORD,  new FST("return")));
            recognizers.push_back(new Recognizer(LEX_LITERAL, LT_INTEGER_LITERAL,
                                                 new FST("", 2,
                                                         N(20,
                                                           R('0', 1), R('0', 0),
                                                           R('1', 1), R('1', 0),
                                                           R('2', 1), R('2', 0),
                                                           R('3', 1), R('3', 0),
                                                           R('4', 1), R('4', 0),
                                                           R('5', 1), R('5', 0),
                                                           R('6', 1), R('6', 0),
                                                           R('7', 1), R('7', 0),
                                                           R('8', 1), R('8', 0),
                                                           R('9', 1), R('9', 0)),
                                                         N())));
            recognizers.push_back(new StringLiteralRecognizer());
            recognizers.push_back(new Recognizer(LEX_ID, LT_IDENTIFIER,
                                                 new FST("", 2,
                                                         N(52, // все меленькие латинские буквы
                                                           R('\x61', 0), R('\x62', 0), R('\x63', 0), R('\x64', 0), R('\x65', 0),
                                                           R('\x66', 0), R('\x67', 0), R('\x68', 0), R('\x69', 0), R('\x6A', 0),
                                                           R('\x6B', 0), R('\x6C', 0), R('\x6D', 0), R('\x6E', 0), R('\x6F', 0),
                                                           R('\x70', 0), R('\x71', 0), R('\x72', 0), R('\x73', 0), R('\x74', 0),
                                                           R('\x75', 0), R('\x76', 0), R('\x77', 0), R('\x78', 0), R('\x79', 0),
                                                           R('\x7A', 0),
                                                           R('\x61', 1), R('\x62', 1), R('\x63', 1), R('\x64', 1), R('\x65', 1),
                                                           R('\x66', 1), R('\x67', 1), R('\x68', 1), R('\x69', 1), R('\x6A', 1),
                                                           R('\x6B', 1), R('\x6C', 1), R('\x6D', 1), R('\x6E', 1), R('\x6F', 1),
                                                           R('\x70', 1), R('\x71', 1), R('\x72', 1), R('\x73', 1), R('\x74', 1),
                                                           R('\x75', 1), R('\x76', 1), R('\x77', 1), R('\x78', 1), R('\x79', 1),
                                                           R('\x7A', 1)),
                                                         N())));
        }

        // определение первого распознавателя, который узнал фрагмент
        Recognizer* recognyze(const char* fragment) {
            Recognizer* result = nullptr;
            int i	       = 0;
            while (i < recognizers.size() && !result) {
                if (recognizers[i]->isRecognized(fragment)) {
                    result = recognizers[i];
                }
                i++;
            }
            return result;
        }
    };

    // лексический разбор входного файла ctx.in.txt и построение таблиц ctx.lexTable и ctx.idTable
    void lexicalAnalysis(TranslationContext &ctx);
}
#endif // !LEXICAL_ANALYZER_H
