#include "PolishNotation.h"
#include "LexicalAnalyzer.h"
#include <iostream>
#include <stack>

using namespace std;

namespace PolishNotation {
    void printExpression(Log::LOG &logger, int start, LT::LexTable &lexTable) {
        int i = start;
        while (i < lexTable.table.size() && lexTable.table[i].lexema != LEX_SEMICOLON && lexTable.table[i].lexema != LEX_COMPARE &&
               lexTable.table[i].lexema != LEX_MORE && lexTable.table[i].lexema != LEX_LESS && lexTable.table[i].lexema != LEX_RIGTH_SQ_BR) {
            logger << i << ": " << lexTable.table[i].lexema;
            if ((lexTable.table[i].lexema == LEX_ID) || (lexTable.table[i].lexema == LEX_FUNCTION_REF)) {
                logger << lexTable.table[i].idxTI;
            }
            logger << endl;
            i++;
        }
    }

    void printStep(Log::LOG &logger, char c, int start, int r, LT::LexTable &lexTable, stack<char> stack) {
        logger << c << ": ";
        std::stack<char> temp;
        int count = 0;
        while (!stack.empty()) {
            char o = stack.top();
            logger << o;
            count++;
            temp.push(o);
            stack.pop();
        }
        while (!temp.empty()) {
            char o = temp.top();
            stack.push(o);
            temp.pop();
        }
        for (int i = count; i < 10; i++) {
            logger << ' ';
        }
        for (int j = start; j < r; j++) {
            char o = lexTable.table[j].lexema;
            logger << o;
            if ((lexTable.table[j].lexema == LEX_ID) || (lexTable.table[j].lexema == LEX_FUNCTION_REF)) {
                logger << lexTable.table[j].idxTI;
            }
            logger << ' ';
        }
        logger << endl;
    }

    int priority(char c) {
        if ((c == LEX_PLUS) || (c == LEX_MINUS)) {
            return 10;
        }
        if ((c == LEX_STAR) || (c == LEX_DIRSLASH)) {
            return 20;
        }
        return 0;
    }

    int buildRPN(const int start, TranslationContext &ctx) {
        LT::LexTable &lexTable = ctx.lexTable;
        *ctx.logger << "\nTry to build polish notation from " << start << " position:" << endl;
        printExpression(*ctx.logger, start, lexTable);
        *ctx.logger << "----------------------------------" << endl;

        bool ok = true;
        std::stack<char> stack;
        std::stack<int>	 functionStack;
        int i = start;
        int r = start; // result index
        while (i < lexTable.table.size() && lexTable.table[i].lexema != LEX_SEMICOLON && lexTable.table[i].lexema != LEX_COMPARE &&
               lexTable.table[i].lexema != LEX_MORE && lexTable.table[i].lexema != LEX_LESS && lexTable.table[i].lexema != LEX_RIGTH_SQ_BR &&
               ok) {
            char c = lexTable.table[i].lexema;

            switch (c) {
                case LEX_LEFTHESIS: {
                    if ((i - 1 < 0) || (lexTable.table[i - 1].lexema != LEX_ID)) {
                        stack.push(LEX_LEFTHESIS);
                    }
                    break;
                }
                case LEX_PLUS:
                case LEX_MINUS:
                case LEX_STAR:
                case LEX_DIRSLASH: {
                    // extract all operations from stack with high or equal priority and move them to result
                    bool extractOperation = !stack.empty();
                    while (extractOperation) {
                        char o = stack.top();
                        if (priority(o) >= priority(c)) {
                            stack.pop();
                            lexTable.table[r].lexema	 = o;
                            lexTable.table[r].lexemaType = LA::LT_SIGN;
                            lexTable.table[r].idxTI	 = LT_TI_NULLIDX;
                            r++;
                            if (stack.empty()) {
                                extractOperation = false;
                            }
                        } else {
                            extractOperation = false;
                        }
                    }
                    stack.push(c);
                    break;
                }
                case LEX_ID:
                case LEX_LITERAL: {
                    if ((i + 1 < lexTable.table.size()) && (lexTable.table[i + 1].lexema == LEX_LEFTHESIS)) {
                        // start of function. push "["
                        stack.push(LEX_LEFT_BRACKET);
                        functionStack.push(lexTable.table[i].idxTI);
                    } else {
                        // move operand to result position
                        lexTable.table[r] = lexTable.table[i];
                        r++;
                    }
                    break;
                }
                case LEX_COMMA: {
                    stack.push(LEX_COMMA);
                    break;
                }
                case LEX_RIGHTHESIS: {
                    // extract all operations from stack while find open bracket or paranthesys and move them to result
                    int	 paramsCount	  = 1; // number of function parameters
                    bool extractOperation = !stack.empty();
                    char o		  = LEX_LEFTHESIS;
                    while (extractOperation) {
                        o = stack.top();
                        stack.pop();
                        if ((o != LEX_LEFTHESIS) && (o != LEX_LEFT_BRACKET)) {
                            if (o == LEX_COMMA) {
                                paramsCount++;
                            } else {
                                lexTable.table[r].lexema     = o;
                                lexTable.table[r].lexemaType = LA::LT_SIGN;
                                lexTable.table[r].idxTI	     = LT_TI_NULLIDX;
                                r++;
                            }
                            if (stack.empty()) {
                                extractOperation = false;
                            }
                        } else {
                            extractOperation = false;
                        }
                    }

                    if ((paramsCount == 1) && (i > start) && (lexTable.table[i - 1].lexema == LEX_LEFTHESIS)) {
                        paramsCount = 0;
                    }

                    // for close bracket generate @ sign (function placeholder)
                    if (o == LEX_LEFT_BRACKET) {
                        lexTable.table[r].lexema     = LEX_FUNCTION_REF;
                        lexTable.table[r].lexemaType = LA::LT_SIGN;
                        int functionIdx = functionStack.top();
                        functionStack.pop();
                        lexTable.table[r].idxTI = functionIdx; // нужен индекс ид объявления функции
                        r++;
                    } else {
                        if (paramsCount > 1) {
                            ok = false; // found comma inside paranthesys => stop parsing (syntax error)
                        }
                    }
                    break;
                }
                case LEX_EMPTY: {
                    break;
                }
                default: {
                    ok = false; // found wrong lexema => stop parsing (syntax error)
                }
            }
            i++;

            printStep(*ctx.logger, c, start, r, lexTable, stack);
        }
        while (!stack.empty()) {
            char o = stack.top();
            stack.pop();
            lexTable.table[r].lexema	 = o;
            lexTable.table[r].lexemaType = LA::LT_SIGN;
            lexTable.table[r].idxTI	 = LT_TI_NULLIDX;
            r++;
        }
        while (r < i) {
            lexTable.table[r].lexema	 = LEX_EMPTY;
            lexTable.table[r].lexemaType = LA::LT_SIGN;
            lexTable.table[r].idxTI	 = LT_TI_NULLIDX;
            r++;
        }
        printStep(*ctx.logger, ' ', start, r, lexTable, stack);

        *ctx.logger << "----------------------------------" << endl;
        if (ok) {
            *ctx.logger << "польская запись построена:" << endl;
            printExpression(*ctx.logger, start, lexTable);
        } else {
            *ctx.logger << "польская запиcь не построена" << endl;
        }
        *ctx.logger << "=================================" << endl;
        return ok ? (r - start) : (start - r);
    }
}
