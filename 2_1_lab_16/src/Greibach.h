#ifndef GREIBACH_H
#define GREIBACH_H

#include <vector>
#include "Utils.h"

typedef short TN_SYMBOL; //  символы алфавита грамматики. терминалы > 0 а нетерминалы < 0

using namespace std;
using namespace Utils;

namespace GR {
    TN_SYMBOL charToT(char c);           // char -> терминал
    TN_SYMBOL charToN(char c);           // char -> не терминал
    bool      isT(TN_SYMBOL s);          // проверка: терминал?
    bool      isN(TN_SYMBOL s);          // проверка: нетерминал?
    char      symbolToChar(TN_SYMBOL s); // TN_SYMBOL -> char

    struct Chain {
        vector<TN_SYMBOL> symbols;       // цепочка терминалов (>0) и нетерминалов (<0)
        char*		  info;          // описание цепочки

        Chain(const char* chain) {
            int len = strlen(chain);
            info = new char[len + 5];
            copyChars(info, chain);

            symbols.reserve(len);
            for (int i  = 0; i < len; i++) {
                char c = chain[i];
                if (isupper(c)) {
                    symbols.push_back(charToN(c));
                } else {
                    symbols.push_back(charToT(c));
                }
            }
        }
    };

    char* info(TN_SYMBOL ruleSymbol, Chain* chain); // напечетать информацию по цепочке


    //  правило в грамматике Грейбах
    struct Rule {
        TN_SYMBOL     ruleSymbol; // нетерминал, левый символ правила < 0
        int	      errorId;    // идентификатор сообщения об ошибке
        vector<Chain> chains;     // множество цепочек - правых частей правила
        char*	      info;       // описание правила

        Rule(const char ruleSymbol, const char* rule, const int errorId) {
            this->ruleSymbol = charToN(ruleSymbol);
            this->errorId    = errorId;
            int len = strlen(rule);
            info    = new char[len + 5];
            info[0] = ruleSymbol;
            info[1] = ' ';
            info[2] = '-';
            info[3] = '>';
            info[4] = ' ';
            appendChars(info, rule);

            char* chain = new char[len];
            int	  r	= 0;
            for (int i = 0; i < len; i++) {
                char c = rule[i];
                if (c == '|') {
                    chain[r] = 0;
                    chains.push_back(*new Chain(chain));
                    r = 0;
                } else if (c != ' ') {
                    chain[r] = c;
                    r++;
                }
            }
            chain[r] = 0;
            chains.push_back(*new Chain(chain));
        }

        // получить следующую после idx подходящую цепочку (начинающуюся с symbol), вернуть ее индекс или -1
        short  getNextChainIndex(TN_SYMBOL symbol, short idx);

        // получить цепочку по индексу
        Chain* getChain(short n);
    };

    // грамматика Гребах
    struct Grammar {
        TN_SYMBOL    startSymbol;  // стартовый символ
        TN_SYMBOL    bottomSymbol; // дно стека
        vector<Rule> rules;        // множестов правил

        Grammar() {}

        Grammar(const TN_SYMBOL startSymbol, const TN_SYMBOL bottomSymbol) {
            this->startSymbol  = startSymbol;
            this->bottomSymbol = bottomSymbol;
        }

        // получить индекс правила по левому символу. Возвращается номер правила или -1
        short getRuleIndex(TN_SYMBOL s);

        // получить правило по индексу
        Rule* getRule(short idx);
    };

    Grammar*  getGrammar();
}

#endif // !GREIBACH_H
