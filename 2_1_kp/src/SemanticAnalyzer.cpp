#include "SemanticAnalyzer.h"
#include "PolishNotation.h"
#include "IT.h"

#include <iomanip>

using namespace std;
using namespace IT;
using namespace PolishNotation;

namespace SEM {
    void log(TranslationContext &ctx, const char* message, int firstIndex, int secondIndex) {
        *ctx.logger << endl << setw(14) << left << "" << setw(20) << left << message << setw(4) << left << firstIndex
                    << " == " << setw(18) << left << secondIndex << ":";
    }

    void log(TranslationContext &ctx, const char* message, int firstIndex, int secondIndex, int paramIndex) {
        *ctx.logger << endl << setw(14) << left << "" << setw(20) << left << message << setw(4) << left << firstIndex
                    << " == " << setw(4) << left << secondIndex << " [" << paramIndex << setw(11) << left << "]" << ":";
    }

    int symbolIndexInParent(GR::ParseTreeNode* node) {
        int r = -1;
        for (int i = 0; i < node->parent->child.size() && r == -1; i++) {
            if (node->parent->child[i] == node) {
                r = i;
            }
        }
        r++;
        if (r > 0) {
            for (int i = 0; i < node->parent->chain->symbols.size(); i++) {
                if (GR::isN(node->parent->chain->symbols[i])) {
                    r--;
                    if (r == 0) {
                        return i;
                    }
                }
            }
        }
        return -1;
    }

    void verifyDataType(TranslationContext &ctx, GR::ParseTreeNode* node) {
        // обход дерева снизу-вверх
        if (node->child.size() > 0) {
            for (int i = 0; i < node->child.size(); i++) {
                verifyDataType(ctx, node->child[i]);
            }
        }

        *ctx.logger << "Verify node: " << setw(4) << left << node->lentaPosition << ":" << setw(40) << left
                    << info(node->rule->ruleSymbol, node->chain) << " :";

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
                        log(ctx, "Checked (704)", node->lentaPosition + 1, node->child[2]->lentaPosition);
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
                        log(ctx, "Checked (701)", node->child[0]->lentaPosition, node->child[1]->child[0]->lentaPosition);
                    }
                } else {
                    // проверка присваивания
                    int eqIndex = -1;
                    int iIndex	= -1;
                    int oIndex	= -1;
                    int uIndex	= -1;
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
                        if (lexema == 'u') {
                            uIndex = i;
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
                                log(ctx, "Checked (702)", node->lentaPosition + iIndex, node->child[0]->lentaPosition);
                            }
                        }
                    }
                    if (oIndex != -1) { // out
                        node->datatype = node->child[0]->datatype;
                    }
                    if (uIndex != -1) { // use - проверка корректности вызова библиотечных функций
                        bool  found   = false;
                        int   idIndex = ctx.lexTable.table[node->lentaPosition + 2].idxTI;
                        char* idName  = ctx.idTable.table[idIndex].name;
                        if (strcmp("fact", idName) == 0) {
                            if ((ctx.idTable.table[idIndex].datatype == DT_INT) &&
                                (ctx.idTable.table[idIndex + 1].idtype == T_P) && (ctx.idTable.table[idIndex + 1].datatype == DT_INT) &&
                                (ctx.idTable.table[idIndex + 2].idtype != T_P)) {
                                found = true;
                            }
                        }
                        if (strcmp("strlen", idName) == 0) {
                            if ((ctx.idTable.table[idIndex].datatype == DT_INT) &&
                                (ctx.idTable.table[idIndex + 1].idtype == T_P) && (ctx.idTable.table[idIndex + 1].datatype == DT_STR) &&
                                (ctx.idTable.table[idIndex + 2].idtype != T_P)) {
                                found = true;
                            }
                        }
                        if ((strcmp("min", idName) == 0) || (strcmp("max", idName) == 0)) {
                            if ((ctx.idTable.table[idIndex].datatype == DT_INT) &&
                                (ctx.idTable.table[idIndex + 1].idtype == T_P) && (ctx.idTable.table[idIndex + 1].datatype == DT_INT) &&
                                (ctx.idTable.table[idIndex + 2].idtype == T_P) && (ctx.idTable.table[idIndex + 2].datatype == DT_INT) &&
                                (ctx.idTable.table[idIndex + 3].idtype != T_P)) {
                                found = true;
                            }
                        }
                        if (!found) {
                            throw ERROR_THROW_IN(705,
                                                 ctx.lexTable.table[node->lentaPosition + 2].line,
                                                 ctx.lexTable.table[node->lentaPosition + 2].col);
                        } else {
                            log(ctx, "Checked (705)", node->lentaPosition + 2, -1);
                        }
                    }
                }
                break;
            }
            case 'E': {
                // E -> i | l | (E) | i(W) | iM | lM | (E)M | i(W)M
                // обработка в��ражений
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
                        log(ctx, "Checked (700)", node->lentaPosition, node->lentaPosition + node->chain->symbols.size() - 1);
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
                        log(ctx, "Checked (700): ", node->lentaPosition, node->lentaPosition + node->chain->symbols.size() - 1);
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
                        log(ctx, "Checked (700)", node->lentaPosition, node->child[mIndex]->lentaPosition);
                    }
                }

                int paramIndex		= 1;
                GR::ParseTreeNode* temp = node->parent;
                int childIndex		= symbolIndexInParent(node);
                while (temp != nullptr && GR::symbolToChar(temp->rule->ruleSymbol) == 'W'
                       && temp->chain->symbols[childIndex - 1] == ',') { // считаем только W -> ... ,W
                    paramIndex++;
                    childIndex = symbolIndexInParent(temp);
                    temp       = temp->parent;
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
                    log(ctx, "Checked (703)", node->lentaPosition, temp->lentaPosition, paramIndex);
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

        switch (node->datatype) {
            case DT_STR: {
                *ctx.logger << " str";
                break;
            }; case DT_INT: {
                *ctx.logger << " int";
                break;
            }; case DT_UNKNOWN: {
                *ctx.logger << " <unknown>";
                break;
            };
        }
        *ctx.logger << endl;
    }

    void buildPolishNotations(TranslationContext &ctx, GR::ParseTreeNode* node) {
        switch (GR::symbolToChar(node->rule->ruleSymbol)) {
            case 'E': {
                // E -> i | l | (E) | i(W) | iM | lM | (E)M | i(W)M
                // обработка выражений
                int result = buildRPN(node->lentaPosition, ctx);
                if (result < 0) {
                    throw ERROR_THROW_IN(706, ctx.lexTable.table[node->lentaPosition].line, ctx.lexTable.table[node->lentaPosition].col);
                } else {
                    node->notationSize = result;
                }
                break;
            }
            case 'W': {
                int result = buildRPN(node->lentaPosition, ctx);
                if (result < 0) {
                    throw ERROR_THROW_IN(706, ctx.lexTable.table[node->lentaPosition].line, ctx.lexTable.table[node->lentaPosition].col);
                } else {
                    node->notationSize = result;
                }
                char lastSymbol = GR::symbolToChar(node->chain->symbols[node->chain->symbols.size() - 1]);
                if (lastSymbol == 'W') {
                    buildPolishNotations(ctx, node->child[node->chain->symbols.size() - 1]);
                }
                break;
            }
            default: {
                if (node->child.size() > 0) {
                    for (int i = 0; i < node->child.size(); i++) {
                        buildPolishNotations(ctx, node->child[i]);
                    }
                }
            }
        }
    }

    // семантический анализ
    void  semanticAnalysis(TranslationContext &ctx) {
        *ctx.logger << "\nСемантический анализ. Проверка типов данных:" << endl;
        verifyDataType(ctx, ctx.parseTree);
        *ctx.logger << "\nСемантический анализ. Проверка выражений:" << endl;
        buildPolishNotations(ctx, ctx.parseTree);
        ctx.logger->logLexemTables(ctx.lexTable, ctx.idTable);
    }
}
