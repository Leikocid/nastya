#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include "TranslationContext.h"
#include "FST.h"
#include <vector>

using namespace Fst;

namespace LA {
    // тип распознавателя
    enum RECOGNIZER_TYPE {
        RT_KEYWORD = 0, RT_DATATYPE = 1, RT_INTEGER_LITERAL = 2, RT_STRING_LITERAL = 3, RT_IDENTIFIER = 4, RT_MAIN = 5
    };
    struct Recognizer {
        char lexema;
        FST* fst;
        int  type;

        // конструктор
        Recognizer(char lexema, FST* fst, int type) {
            this->lexema = lexema;
            this->fst	 = fst;
            this->type	 = type;
        }

        // деструктор
        virtual ~Recognizer() {}

        // применяем недетерменированный конечный автомат для распознания фрагмента
        virtual bool recognized(const char* fragment) {
            fst->string = fragment;
            return fst->execute();
        }
    };

    struct StringLiteralRecognizer : Recognizer {
        // конструктор
        StringLiteralRecognizer(char lexema, int type) : Recognizer(lexema, nullptr, type) {}

        ~StringLiteralRecognizer() {}

        // проверяем что первый и последний символы это апострофы
        bool recognized(const char* fragment) {
            int size = strlen(fragment);
            return size > 2 && fragment[0] == '\'' && fragment[size - 1] == '\'';
        }
    };

    struct Recognizers {
        vector<Recognizer*> recognizers;

        Recognizers() {
            recognizers.reserve(10);
            recognizers.push_back(new Recognizer(LEX_INTEGER, new FST("integer"), RT_DATATYPE));
            recognizers.push_back(new Recognizer(LEX_STRING, new FST("string"), RT_DATATYPE));
            recognizers.push_back(new Recognizer(LEX_DECLARE, new FST("declate"), RT_KEYWORD));
            recognizers.push_back(new Recognizer(LEX_FUNCTION, new FST("function"), RT_KEYWORD));
            recognizers.push_back(new Recognizer(LEX_MAIN, new FST("main"), RT_MAIN));
            recognizers.push_back(new Recognizer(LEX_PRINT, new FST("print"), RT_IDENTIFIER));
            recognizers.push_back(new Recognizer(LEX_RETURN,  new FST("return"), RT_KEYWORD));
            recognizers.push_back(new Recognizer(LEX_LITERAL, new FST("", 2,
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
                                                                      N()), RT_INTEGER_LITERAL));
            recognizers.push_back(new StringLiteralRecognizer(LEX_LITERAL, RT_STRING_LITERAL));
            recognizers.push_back(new Recognizer(LEX_ID, new FST("", 2,
                                                                 N(52,
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
                                                                 N()), RT_IDENTIFIER));
        }

        // определение первого распознавателя, который узнал фрагмент
        Recognizer* recognyze(const char* fragment) {
            Recognizer* result = nullptr;
            int i	       = 0;
            while (i < recognizers.size() && !result) {
                if (recognizers[i]->recognized(fragment)) {
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
