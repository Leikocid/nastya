#include "PolishNotation.h"
#include <iostream>

using namespace std;

namespace PolishNotation {
    // Построение польской записи в таблице лексем(позиция выражения в lextable, табл лексем, табл ид)
    // true - построение польской записи выполнено успешно
    // false - построение польской записи не выполнено
    bool PolishNotation(int, LT::LexTable &lexTable, IT::IdTable &idTable) {
        return false;
    }

    // обработка выражений из таблиц лексем
    void testPolishNotations(TranslationContext &ctx) {
        if (PolishNotation(EXP1, ctx.lexTable, ctx.idTable)) {
            cout << EXP1 << ": польская запись построена" << endl;
        } else {
            cout << EXP1 << ": польская запись не построена" << endl;
        }
        if (PolishNotation(EXP2, ctx.lexTable, ctx.idTable)) {
            cout << EXP2 << ": польская запись построена" << endl;
        } else {
            cout << EXP2 << ": польская запись не построена" << endl;
        }
        if (PolishNotation(EXP3, ctx.lexTable, ctx.idTable)) {
            cout << EXP3 << ": польская запись построена" << endl;
        } else {
            cout << EXP3 << ": польская запись не построена" << endl;
        }
    }
}
