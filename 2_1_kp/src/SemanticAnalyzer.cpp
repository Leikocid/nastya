#include "SemanticAnalyzer.h"
#include "IT.h"

#include <iomanip>

using namespace std;

using namespace IT;

namespace SEM {
    void processNode(TranslationContext &ctx, GR::ParseTreeNode* node) {
        // обход дерева снизу-вверх
        if (node->child.size() > 0) {
            for (int i = 0; i < node->child.size(); i++) {
                processNode(ctx, node->child[i]);
            }
        }

        switch (GR::symbolToChar(node->rule->ruleSymbol)) {
            case 'S': {
                // fi(F):t{NrE;};S | m{N};
                char firstSymbol = GR::symbolToChar(node->chain->symbols[0]);
                if (firstSymbol == 'f') {
                    int idIndex = ctx.lexTable.table[node->lentaPosition + 1].idxTI;
                    node->datatype = ctx.idTable.table[idIndex].datatype;
                    DATATYPE returnDataType = node->child[2]->datatype;
                    if (returnDataType != node->datatype) {
                        throw ERROR_THROW_IN(704, ctx.lexTable.table[node->child[2]->lentaPosition].line,
                                             ctx.lexTable.table[node->child[2]->lentaPosition].col);
                    } else {
                        // отладка
                        cout << " CHECK: " << node->lentaPosition + 1 << " == " << node->child[2]->lentaPosition << " (" << node->datatype <<
                            ")" << endl;
                    }
                }
                break;
            }
            case 'N': {
                // i=E;N | vi:t;N | vi:t=E;N | ufi(F):t;N | i(W);N | oE;N | vi:t; | vi:t=E; | i=E; | ufi(F):t; | i(W); | oE;
                // | c[EC]{N}; | c[EC]{N};N | c[EC]{N}e{N}; | c[EC]{N}e{N};N | w[EC]{N}; | w[EC]{N};N
                char firstSymbol = GR::symbolToChar(node->chain->symbols[0]);
                if ((firstSymbol == 'c') || (firstSymbol == 'w')) {
                    // проверка сравнений в ветвлениях и циклах
                    node->datatype = node->child[0]->datatype;
                    if (node->child[0]->datatype != node->child[1]->datatype) {
                        throw ERROR_THROW_IN(701, ctx.lexTable.table[node->child[0]->lentaPosition].line,
                                             ctx.lexTable.table[node->child[0]->lentaPosition].col);
                    } else {
                        // отладка
                        cout << " CHECK: " << node->child[0]->lentaPosition << " == " << node->child[1]->child[0]->lentaPosition <<
                            " (" << node->child[0]->datatype << ")" << endl;
                    }
                } else {
                    // проверка присваивания
                    int eqIndex = -1;
                    int iIndex	= -1;
                    int oIndex	= -1;
                    for (int i = 0; i < node->chain->symbols.size(); i++) {
                        char lexema = GR::symbolToChar(node->chain->symbols[i]);
                        if (lexema == '=') {
                            eqIndex = i;
                        }
                        if (lexema == 'i') {
                            iIndex = i;
                        }
                        if (lexema == 'o') {
                            oIndex = i;
                        }
                    }
                    if (iIndex != -1) {
                        int idIndex = ctx.lexTable.table[node->lentaPosition + iIndex].idxTI;
                        node->datatype = ctx.idTable.table[idIndex].datatype;
                        if (eqIndex != -1) {
                            DATATYPE rigthDataType = node->child[0]->datatype;
                            if (rigthDataType != node->datatype) {
                                throw ERROR_THROW_IN(702,
                                                     ctx.lexTable.table[node->lentaPosition].line,
                                                     ctx.lexTable.table[node->lentaPosition].col);
                            } else {
                                // отладка
                                cout << " CHECK: " << node->lentaPosition + iIndex << " == " <<
                                    node->child[0]->lentaPosition << " (" << node->datatype << ")" << endl;
                            }
                        }
                    }
                    if (oIndex != -1) {
                        node->datatype = node->child[0]->datatype;
                    }
                }
                break;
            }
            case 'E': {
                // E -> i | l | (E) | i(W) | iM | lM | (E)M | i(W)M
                // обработка выражений
                if (ctx.lexTable.table[node->lentaPosition].lexema != '(') {
                    int idIndex = ctx.lexTable.table[node->lentaPosition].idxTI;
                    node->datatype = ctx.idTable.table[idIndex].datatype;
                } else {
                    node->datatype = node->child[0]->datatype;
                }
                char lastSymbol = GR::symbolToChar(node->chain->symbols[node->chain->symbols.size() - 1]);
                if (lastSymbol == 'M') {
                    DATATYPE lastDataType = node->child[node->child.size() - 1]->datatype;
                    if (lastDataType != node->datatype) {
                        throw ERROR_THROW_IN(700, ctx.lexTable.table[node->lentaPosition].line, ctx.lexTable.table[node->lentaPosition].col);
                    } else {
                        // отладка
                        cout << " CHECK: " << node->lentaPosition << " == " << (node->lentaPosition + node->chain->symbols.size() - 1) <<
                            " (" << node->datatype << ")" << endl;
                    }
                }
                break;
            }
            case 'M': {
                // +E | +EM | -E | -EM | *E | *EM | /E | /EM
                // обработка выражений
                node->datatype = node->child[0]->datatype;
                char lastSymbol = GR::symbolToChar(node->chain->symbols[node->chain->symbols.size() - 1]);
                if (lastSymbol == 'M') {
                    DATATYPE lastDataType = node->child[node->child.size() - 1]->datatype;
                    if (lastDataType != node->datatype) {
                        throw ERROR_THROW_IN(700, ctx.lexTable.table[node->lentaPosition].line, ctx.lexTable.table[node->lentaPosition].col);
                    } else {
                        // отладка
                        cout << " CHECK: " << node->lentaPosition << " == " << (node->lentaPosition + node->chain->symbols.size() - 1) <<
                            " (" << node->datatype << ")" << endl;
                    }
                }
                break;
            }
            case 'F': {
                // i:t | i:t,F
                // параметры объявления функции
                int idIndex = ctx.lexTable.table[node->lentaPosition].idxTI;
                node->datatype = ctx.idTable.table[idIndex].datatype;
                break;
            }
            case 'W': {
                // i | l | i,W | l,W | (E) | i(W) | iM | lM | (E)M | i(W)M | (E),W | i(W),W | iM,W | lM,W | (E)M,W | i(W)M,W
                // параметр вызова функции
                // обработка выражений
                if (ctx.lexTable.table[node->lentaPosition].lexema != '(') {
                    int idIndex = ctx.lexTable.table[node->lentaPosition].idxTI;
                    node->datatype = ctx.idTable.table[idIndex].datatype;
                } else {
                    node->datatype = node->child[0]->datatype;
                }
                int mIndex = -1;
                int j	   = -1;
                for (int i = 0; i < node->chain->symbols.size(); i++) {
                    char lexema = GR::symbolToChar(node->chain->symbols[i]);
                    if (GR::isN(node->chain->symbols[i])) {
                        j++;
                    }
                    if (lexema == 'M') {
                        mIndex = j;
                    }
                }
                if (mIndex != -1) {
                    DATATYPE mDataType = node->child[mIndex]->datatype;
                    if (mDataType != node->datatype) {
                        throw ERROR_THROW_IN(700, ctx.lexTable.table[node->lentaPosition].line, ctx.lexTable.table[node->lentaPosition].col);
                    } else {
                        // отладка
                        cout << " CHECK: " << node->lentaPosition << " == " << node->child[mIndex]->lentaPosition << " (" << node->datatype <<
                            ")" << endl;
                    }
                }
                int paramIndex		= 1;
                GR::ParseTreeNode* temp = node->parent;
                while (temp != nullptr && GR::symbolToChar(temp->rule->ruleSymbol) == 'W') {
                    paramIndex++;
                    temp = temp->parent;
                }
                int iIndex = -1;
                for (int i = 0; i < temp->chain->symbols.size(); i++) {
                    char lexema = GR::symbolToChar(temp->chain->symbols[i]);
                    if (lexema == 'i') {
                        iIndex = i;
                    }
                }
                int idIndex	       = ctx.lexTable.table[temp->lentaPosition + iIndex].idxTI;
                DATATYPE paramDataType = ctx.idTable.table[idIndex + paramIndex].datatype;
                if (paramDataType != node->datatype) {
                    throw ERROR_THROW_IN(703, ctx.lexTable.table[node->lentaPosition].line, ctx.lexTable.table[node->lentaPosition].col);
                } else {
                    // отладка
                    cout << " CHECK: " << node->lentaPosition << " == " << temp->lentaPosition << "[" << paramIndex << "] (" <<
                        node->datatype << ")" << endl;
                }
                break;
            }
            case 'C': {
                // <E | >E | <=E | >=E | ==E | !=E
                // правая часть в сравнении
                node->datatype = node->child[0]->datatype;
                break;
            }
        }

        // *ctx.logger << "NODE: " << setw(4) << left << node->lentaPosition << ": " << setw(40) << left
        //             << info(node->rule->ruleSymbol, node->chain) << " : ";

        // switch (node->datatype) {
        //     case DT_STR: {
        //         *ctx.logger << "str";
        //         break;
        //     }; case DT_INT: {
        //         *ctx.logger << "int";
        //         break;
        //     }; case DT_UNKNOWN: {
        //         *ctx.logger << "<unknown>";
        //         break;
        //     };
        // }
        // *ctx.logger << endl;
    }

    // семантический анализ
    void  semanticAnalysis(TranslationContext &ctx) {
        *ctx.logger << "\nСемантический анализ:" << endl;
        processNode(ctx, ctx.parseTree);
    }
}
