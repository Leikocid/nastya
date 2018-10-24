#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include "TranslationContext.h"
#include "FST.h"
#include <vector>

using namespace Fst;

namespace LA {
    // тип распознавателя
    enum RECOGNIZER_TYPE {
        RT_KEYWORD = 0, RT_DATATYPE = 1, RT_LITERAL = 2, RT_IDENTIFIER = 3, RT_MAIN = 4
    };
    struct Recognizer {
        char lexema;
        FST* fst = nullptr;
        int  type;


        Recognizer(char lexema, FST* fst, int type) {
            this->lexema = lexema;
            this->fst	 = fst;
            this->type	 = type;
        }

        bool recognized(const char* fragment);
    };

    struct Recognizers {
        vector<Recognizer> recognizers;

        Recognizers() {
            recognizers.reserve(10);
            recognizers.push_back(*(new Recognizer(LEX_INTEGER, new FST("integer"), RT_DATATYPE)));
            recognizers.push_back(*(new Recognizer(LEX_STRING, new FST("string"), RT_DATATYPE)));
            recognizers.push_back(*(new Recognizer(LEX_DECLARE, new FST("declate"), RT_KEYWORD)));
            recognizers.push_back(*(new Recognizer(LEX_FUNCTION, new FST("function"), RT_KEYWORD)));
            recognizers.push_back(*(new Recognizer(LEX_MAIN, new FST("main"), RT_IDENTIFIER)));
            recognizers.push_back(*(new Recognizer(LEX_PRINT, new FST("print"), RT_IDENTIFIER)));
            recognizers.push_back(*(new Recognizer(LEX_RETURN,  new FST("return"), RT_KEYWORD)));

            // TODO:
            // FST fst_integer_literal;
            // FST fst_string_literal;
            // FST fst_identifier;
        }
    };

    // лексический разбор входного файла ctx.in.txt и построение таблиц ctx.lt и ctx.it
    void lexicalAnalysis(TranslationContext &ctx);
}

#endif // !LEXICAL_ANALYZER_H
