#include "PolishNotation.h"
#include "LexicalAnalyzer.h"
#include <iostream>
#include <stack>

#define LEX_LEFT_BRACKET '['

using namespace std;

namespace PolishNotation {
    void printExpression(int start, LT::LexTable &lexTable) {
        int i = start;
        while (i < lexTable.table.size() && lexTable.table[i].lexema != LEX_SEMICOLON) {
            cout << i << ": " << lexTable.table[i].lexema;
            if ((lexTable.table[i].lexema == LEX_ID) || (lexTable.table[i].lexema == LEX_FUNCTION_REF)) {
                cout << lexTable.table[i].idxTI;
            }
            cout << endl;
            i++;
        }
    }

    void printStep(char c, int start, int r, LT::LexTable &lexTable, stack<char> stack) {
        cout << c << ":       ";
        for (int j = start; j < r; j++) {
            char o = lexTable.table[j].lexema;
            cout << o;
            if ((lexTable.table[j].lexema == LEX_ID) || (lexTable.table[j].lexema == LEX_FUNCTION_REF)) {
                cout << lexTable.table[j].idxTI;
            }
            cout << " ";
        }
        cout << "   :::   ";
        std::stack<char> temp;
        while (!stack.empty()) {
            char o = stack.top();
            cout << o;
            temp.push(o);
            stack.pop();
        }
        while (!temp.empty()) {
            char o = temp.top();
            stack.push(o);
            temp.pop();
        }
        cout << endl;
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

    bool PolishNotation(int start, LT::LexTable &lexTable, IT::IdTable &idTable) {
        cout << "\nPolishNotation from " << start << ":" << endl;
        printExpression(start, lexTable);
        cout << "----------------------------------" << endl;

        bool result = true;
        stack<char> stack;
        int i = start;
        int r = start; // result index
        while (i < lexTable.table.size() && lexTable.table[i].lexema != LEX_SEMICOLON && result) {
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

                    // for close bracket geterate @ sign (function placeholder)
                    if (o == LEX_LEFT_BRACKET) {
                        lexTable.table[r].lexema     = LEX_FUNCTION_REF;
                        lexTable.table[r].lexemaType = LA::LT_SIGN;
                        lexTable.table[r].idxTI	     = paramsCount;
                        r++;
                    } else {
                        if (paramsCount > 1) {
                            result = false; // found comma inside paranthesys => stop parsing (syntax error)
                        }
                    }
                    break;
                }
                case LEX_EMPTY: {
                    break;
                }
                default: {
                    result = false; // found wrong lexema => stop parsing (syntax error)
                }
            }
            i++;

            printStep(c, start, r, lexTable, stack);
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
        printStep(' ', start, r, lexTable, stack);

        cout << "----------------------------------" << endl;
        if (result) {
            cout << "польская запись построена:" << endl;
            printExpression(start, lexTable);
        } else {
            cout << "польская запиcь не построена" << endl;
        }
        cout << "=================================" << endl;
        return result;
    }

    void testPolishNotations(TranslationContext &ctx) {
        PolishNotation(EXP1, ctx.lexTable, ctx.idTable);
        PolishNotation(EXP2, ctx.lexTable, ctx.idTable);
        PolishNotation(EXP3, ctx.lexTable, ctx.idTable);
    }
}
