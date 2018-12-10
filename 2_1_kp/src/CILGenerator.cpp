#include "CILGenerator.h"
#include "PolishNotation.h"
#include "Utils.h"

// #include <iomanip>

using namespace std;
using namespace Utils;

namespace CG {
    void processNode(TranslationContext &ctx, GR::ParseTreeNode* node) {
        // обход дерева снизу-вверх
        if (node->child.size() > 0) {
            for (int i = 0; i < node->child.size(); i++) {
                processNode(ctx, node->child[i]); // это не правильный обход
            }
        }

        switch (GR::symbolToChar(node->rule->ruleSymbol)) {
            case 'S': {
                // fi(F):t{NrE;};S | m{N};

                break;
            }
            case 'N': {
                // i=E;N | vi:t;N | vi:t=E;N | ufi(F):t;N | i(W);N | oE;N | vi:t; | vi:t=E; | i=E; | ufi(F):t; | i(W); | oE;
                // | c[EC]{N}; | c[EC]{N};N | c[EC]{N}e{N}; | c[EC]{N}e{N};N | w[EC]{N}; | w[EC]{N};N

                break;
            }
            case 'E': {
                // E -> i | l | (E) | i(W) | iM | lM | (E)M | i(W)M
                // обработка выражений


                // применение польской нотации и генегирование кода
                // PolishNotation::testPolishNotations(ctx);

                break;
            }
            case 'M': {
                // +E | +EM | -E | -EM | *E | *EM | /E | /EM
                // обработка выражений

                break;
            }
            case 'F': {
                // i:t | i:t,F
                // параметры объявления функции

                break;
            }
            case 'W': {
                // i | l | i,W | l,W | (E) | i(W) | iM | lM | (E)M | i(W)M | (E),W | i(W),W | iM,W | lM,W | (E)M,W | i(W)M,W
                // параметр вызова функции
                // обработка выражений

                break;
            }
            case 'C': {
                // <E | >E | <=E | >=E | ==E | !=E
                // правая часть в сравнении

                break;
            }
        }
    }

    // семантический анализ
    void  generate(TranslationContext &ctx) {
        *ctx.logger << "\nГенерирование кода:" << endl;

        string fileName = toChars(ctx.params.out);
        ofstream* out	= new ofstream();
        out->open(fileName);
        if (!out->is_open()) {
            throw ERROR_THROW(113);
        }
        *out << START_TEMPLATE;

        processNode(ctx, ctx.parseTree);

        *out << END_TEMPLATE;
        out->close();

        *ctx.logger << "\nГенерирование кода выполнено успешно." << endl;
    }
}
