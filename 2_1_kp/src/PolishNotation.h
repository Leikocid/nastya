#ifndef POLISH_NOTATION_H
#define POLISH_NOTATION_H

#include "TranslationContext.h"

#define EXP1 17
#define EXP2 62
#define EXP3 151

#define LEX_LEFT_BRACKET '['
#define LEX_EMPTY ' '

// перестроение выражений в польскую нотацию
namespace PolishNotation {
    // Построение польской записи в таблице лексем(позиция выражения в lextable, табл лексем, табл ид)
    // >0 - построение польской записи выполнено успешно - размер нотации
    // <0 - построение польской записи не выполнено
    int buildRPN(TranslationContext &ctx, const int start);
}

#endif // !POLISH_NOTATION_H
