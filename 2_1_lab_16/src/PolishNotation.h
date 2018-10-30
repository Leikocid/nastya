#ifndef POLISH_NOTATION_H
#define POLISH_NOTATION_H

#include "TranslationContext.h"

#define EXP1 17
#define EXP2 62
#define EXP3 151
#define LEX_FUNCTION_REF '@'
#define LEX_EMPTY ' '


// перестроение выражений в польскую нотацию
namespace PolishNotation {
    // Построение польской записи в таблице лексем(позиция выражения в lextable, табл лексем, табл ид)
    // true - построение польской записи выполнено успешно
    // false - построение польской записи не выполнено
    bool PolishNotation(int start, LT::LexTable &lexTabkle, IT::IdTable &idTable);

    // обработка выражений из таблиц лексем
    void testPolishNotations(TranslationContext &ctx);
}

#endif // !POLISH_NOTATION_H
