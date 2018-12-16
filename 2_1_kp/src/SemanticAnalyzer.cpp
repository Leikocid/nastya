#include "SemanticAnalyzer.h"
#include "PolishNotation.h"
#include "IT.h"
#include <iomanip>

#define lexems ctx.lexTable.table
#define ids ctx.idTable.table

using namespace std;
using namespace IT;
using namespace GR;
using namespace PolishNotation;

namespace SEM {
    // логирование
    void log(TranslationContext &ctx, const char* message, int firstIndex, int secondIndex) {
        *ctx.logger << endl << setw(14) << left << "" << setw(20) << left << message << setw(4) << left << firstIndex
                    << " == " << setw(18) << left << secondIndex << ":";
    }

    // логирование
    void log(TranslationContext &ctx, const char* message, int firstIndex, int secondIndex, int paramIndex) {
        *ctx.logger << endl << setw(14) << left << "" << setw(20) << left << message << setw(4) << left << firstIndex
                    << " == " << setw(4) << left << secondIndex << " [" << paramIndex << setw(11) << left << "]" << ":";
    }

    // находим индекс нашего узла в цепочке у родителя
    int symbolIndexInParent(ParseTreeNode* node) {
        // находим индекс node в списке детей родительского узла
        int r = -1;
        for (int i = 0; i < node->parent->child.size() && r == -1; i++) {
            if (node->parent->child[i] == node) {
                r = i;
            }
        }
        r++;
        if (r > 0) {
            // ищем индекс r-ого недетерминала (Большой буквы)
            for (int i = 0; i < node->parent->chain->symbols.size(); i++) {
                if (isN(node->parent->chain->symbols[i])) {
                    r--;
                    if (r == 0) {
                        return i;
                    }
                }
            }
        }
        return -1;
    }

    // обходим дерево снизу вверх, вычисляя тип данных для каждого узла. Делаем проверки.
    void verifyDataType(TranslationContext &ctx, ParseTreeNode* node) {
        // обход дерева снизу-вверх
        if (node->child.size() > 0) {
            for (int i = 0; i < node->child.size(); i++) {
                verifyDataType(ctx, node->child[i]);
            }
        }

        // логирование
        *ctx.logger << "Verify node: " << setw(4) << left << node->lentaPosition << ":" << setw(40) << left
                    << info(node->rule->ruleSymbol, node->chain) << "  :";

        char firstSymbol = symbolToChar(node->chain->symbols[0]);
        switch (symbolToChar(node->rule->ruleSymbol)) {
            case 'S': {
                if (firstSymbol == 'f') {
                    // fi(F):t{NrE;};S - обработка блока для функции
                    int idIndex = lexems[node->lentaPosition + 1].idxTI;
                    node->datatype = ids[idIndex].datatype;

                    // тип данных в объявлении фунцкии должен соотвествовать типу в выражении после ключевого слова return
                    DATATYPE returnDataType = node->child[2]->datatype;
                    if (returnDataType != node->datatype) {
                        throw ERROR_THROW_IN(704, lexems[node->child[2]->lentaPosition].line, lexems[node->child[2]->lentaPosition].col);
                    } else {
                        log(ctx, "Checked (704)", node->lentaPosition + 1, node->child[2]->lentaPosition);
                    }
                }
                break;
            }
            case 'N': {
                switch (firstSymbol) {
                    case 'w':
                    case 'c': {
                        // c[EC]{N}; | c[EC]{N};N | c[EC]{N}e{N}; | c[EC]{N}e{N};N | w[EC]{N}; | w[EC]{N};N - проверка сравнений
                        node->datatype = node->child[0]->datatype;

                        // типы данных в левом и правом выражении для сравнения должны совпадать
                        if (node->child[0]->datatype != node->child[1]->datatype) {
                            throw ERROR_THROW_IN(701, lexems[node->child[0]->lentaPosition].line, lexems[node->child[0]->lentaPosition].col);
                        } else {
                            log(ctx, "Checked (701)", node->child[0]->lentaPosition, node->child[1]->child[0]->lentaPosition);
                        }
                        break;
                    }
                    case 'o': {
                        // oE;N | oE; - вывод в консоль, нету проверок
                        node->datatype = node->child[0]->datatype;

                        break;
                    }
                    default: {
                        // i=E;N | vi:t;N | vi:t=E;N | i(W);N | vi:t; | vi:t=E; | i=E; | i(W); | ufi(F):t;N | ufi(F):t;
                        int eqIndex = -1; // индекс =
                        int iIndex  = -1; // индекс i
                        for (int i = 0; i < node->chain->symbols.size(); i++) {
                            char lexema = symbolToChar(node->chain->symbols[i]);
                            if (lexema == '=') {
                                eqIndex = i;
                            }
                            if (lexema == 'i') {
                                iIndex = i;
                            }
                        }
                        int idIndex = lexems[node->lentaPosition + iIndex].idxTI;
                        node->datatype = ids[idIndex].datatype;

                        if (eqIndex != -1) {
                            // i=E;N | vi:t=E;N | vi:t=E; | i=E; - проверка присваивания
                            DATATYPE rigthDataType = node->child[0]->datatype;
                            if (rigthDataType != node->datatype) {
                                throw ERROR_THROW_IN(702, lexems[node->lentaPosition].line, lexems[node->lentaPosition].col);
                            } else {
                                log(ctx, "Checked (702)", node->lentaPosition + iIndex, node->child[0]->lentaPosition);
                            }
                        }
                        if (firstSymbol == 'u') {
                            // ufi(F):t;N | ufi(F):t; - проверка корректности вызова библиотечных функций
                            bool  found	  = false;
                            int	  idIndex = lexems[node->lentaPosition + 2].idxTI;
                            char* idName  = ids[idIndex].name;
                            if (strcmp("fact", idName) == 0) {
                                if ((ids[idIndex].datatype == DT_INT) &&
                                    (ids[idIndex + 1].idtype == T_P) && (ids[idIndex + 1].datatype == DT_INT) &&
                                    (ids[idIndex + 2].idtype != T_P)) {
                                    found = true;
                                }
                            }
                            if (strcmp("strlen", idName) == 0) {
                                if ((ids[idIndex].datatype == DT_INT) &&
                                    (ids[idIndex + 1].idtype == T_P) && (ids[idIndex + 1].datatype == DT_STR) &&
                                    (ids[idIndex + 2].idtype != T_P)) {
                                    found = true;
                                }
                            }
                            if ((strcmp("min", idName) == 0) || (strcmp("max", idName) == 0)) {
                                if ((ids[idIndex].datatype == DT_INT) &&
                                    (ids[idIndex + 1].idtype == T_P) && (ids[idIndex + 1].datatype == DT_INT) &&
                                    (ids[idIndex + 2].idtype == T_P) && (ids[idIndex + 2].datatype == DT_INT) &&
                                    (ids[idIndex + 3].idtype != T_P)) {
                                    found = true;
                                }
                            }
                            if (!found) { // если found == true то библиотечная успешно распознана и используется корректно
                                throw ERROR_THROW_IN(705, lexems[node->lentaPosition + 2].line, lexems[node->lentaPosition + 2].col);
                            } else {
                                log(ctx, "Checked (705)", node->lentaPosition + 2, -1);
                            }
                        }
                    }
                }
                break;
            }
            case 'M':
            case 'E': {
                // E -> i | l | (E) | i(W) | iM | lM | (E)M | i(W)M | +E | +EM | -E | -EM | *E | *EM | /E | /EM - обработка выражений
                if ((firstSymbol == 'i') || (firstSymbol == 'l')) {
                    int idIndex = lexems[node->lentaPosition].idxTI;
                    node->datatype = ids[idIndex].datatype;
                } else {
                    node->datatype = node->child[0]->datatype;
                }

                char lastSymbol = symbolToChar(node->chain->symbols[node->chain->symbols.size() - 1]);
                if (lastSymbol == 'M') {
                    // типы данных для переменных в одной операции должны совпадать
                    DATATYPE lastDataType = node->child[node->child.size() - 1]->datatype;
                    if (lastDataType != node->datatype) {
                        throw ERROR_THROW_IN(700, lexems[node->lentaPosition].line, lexems[node->lentaPosition].col);
                    } else {
                        log(ctx, "Checked (700)", node->lentaPosition, node->lentaPosition + node->chain->symbols.size() - 1);
                    }
                }
                break;
            }
            case 'F': {
                // i:t | i:t,F -параметры объявления функции
                int idIndex = lexems[node->lentaPosition].idxTI;
                node->datatype = ids[idIndex].datatype;

                break;
            }
            case 'W': {
                // i | l | i,W | l,W | (E) | i(W) | iM | lM | (E)M | i(W)M | (E),W | i(W),W | iM,W | lM,W | (E)M,W | i(W)M,W - параметры
                // вызова функции
                if ((firstSymbol == 'i') || (firstSymbol == 'l')) {
                    int idIndex = lexems[node->lentaPosition].idxTI;
                    node->datatype = ids[idIndex].datatype;
                } else {
                    node->datatype = node->child[0]->datatype;
                }

                int mIndex = -1;
                int j	   = -1;
                for (int i = 0; i < node->chain->symbols.size(); i++) {
                    char lexema = symbolToChar(node->chain->symbols[i]);
                    if (isN(node->chain->symbols[i])) {
                        j++;
                    }
                    if (lexema == 'M') {
                        mIndex = j;
                    }
                }

                if (mIndex != -1) {
                    // типы данных для переменных в одной операции должны совпадать
                    DATATYPE mDataType = node->child[mIndex]->datatype;
                    if (mDataType != node->datatype) {
                        throw ERROR_THROW_IN(700, lexems[node->lentaPosition].line, lexems[node->lentaPosition].col);
                    } else {
                        log(ctx, "Checked (700)", node->lentaPosition, node->child[mIndex]->lentaPosition);
                    }
                }

                // проверка соотвествия типа данных текущей переменной и типа данных параметра в объявлении функции.
                int paramIndex	    = 1; // номер параметра по порядку в функции вызова
                ParseTreeNode* temp = node->parent;
                int childIndex	    = symbolIndexInParent(node);
                while (temp != nullptr && symbolToChar(temp->rule->ruleSymbol) == 'W'
                       && temp->chain->symbols[childIndex - 1] == ',') { // считаем только W -> ... ,W
                    paramIndex++;
                    childIndex = symbolIndexInParent(temp);
                    temp       = temp->parent;
                }
                int iIndex = -1;
                for (int i = 0; i < temp->chain->symbols.size(); i++) {
                    char lexema = symbolToChar(temp->chain->symbols[i]);
                    if (lexema == 'i') {
                        iIndex = i;
                    }
                }
                int idIndex	       = lexems[temp->lentaPosition + iIndex].idxTI;
                DATATYPE paramDataType = ids[idIndex + paramIndex].datatype;
                if (paramDataType != node->datatype) {
                    throw ERROR_THROW_IN(703, lexems[node->lentaPosition].line, lexems[node->lentaPosition].col);
                } else {
                    log(ctx, "Checked (703)", node->lentaPosition, temp->lentaPosition, paramIndex);
                }
                break;
            }
            case 'C': {
                // <E | >E | <=E | >=E | ==E | !=E - обработка правой части в сравнении
                node->datatype = node->child[0]->datatype;

                break;
            }
        }

        // логирование
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

    void buildPolishNotations(TranslationContext &ctx, ParseTreeNode* node) {
        switch (symbolToChar(node->rule->ruleSymbol)) {
            case 'E': {
                int result = buildRPN(ctx, node->lentaPosition);
                if (result < 0) {
                    throw ERROR_THROW_IN(706, lexems[node->lentaPosition].line, lexems[node->lentaPosition].col);
                } else {
                    node->notationSize = result;
                }
                break;
            }
            case 'W': {
                int result = buildRPN(ctx, node->lentaPosition);
                if (result < 0) {
                    throw ERROR_THROW_IN(706, lexems[node->lentaPosition].line, lexems[node->lentaPosition].col);
                } else {
                    node->notationSize = result;
                }

                char lastSymbol = symbolToChar(node->chain->symbols[node->chain->symbols.size() - 1]);
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
