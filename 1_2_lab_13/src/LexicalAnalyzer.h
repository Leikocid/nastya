#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include "TranslationContext.h"

namespace LA {
    // лексический разбор входного файла ctx.in.txt и построение таблиц ctx.lt и ctx.it
    bool lexicalAnalysis(TranslationContext &ctx);
}

#endif // !LEXICAL_ANALYZER_H
