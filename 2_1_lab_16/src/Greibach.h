#ifndef GREIBACH_H
#define GREIBACH_H

#include <vector>
#include "Utils.h"

typedef short GRBALPHABET; //  символы алфавита грамматики. терминалы > 0 а нетерминалы < 0

using namespace std;
using namespace Utils;

namespace GR {
    struct Chain {
        // цепочка лексем для правила
        vector<GRBALPHABET> lexems; // цепочка терминалов (>0) и нетерминалов (<0)
        char*		    info;   // описание цепочки

        Chain(const char* chain) {
            int len = strlen(chain);
            info = new char[len + 5];
            copyChars(info, chain);

            lexems.reserve(len);
            for (int i  = 0; i < len; i++) {
                char c = chain[i];
                if (isupper(c)) {
                    lexems.push_back(N(c));
                } else {
                    lexems.push_back(T(c));
                }
            }
        }

        // терминал
        static GRBALPHABET T(char t) {
            return GRBALPHABET(t);
        }

        // не терминал
        static GRBALPHABET N(char n) {
            return -GRBALPHABET(n);
        }

        // проверка: терминал?
        static bool isT(GRBALPHABET s) {
            return s > 0;
        }

        // проверка: нетерминал?
        static bool isN(GRBALPHABET s) {
            return !isT(s);
        }

        // GRBALPHABET -> char
        static char alphabet_to_char(GRBALPHABET s) {
            return isT(s) ? char(s) : char(-s);
        }
    };

    //  правило в грамматик  Грейбах
    struct Rule {
        GRBALPHABET   nn;      // нетерминал, левый символ правила < 0
        int	      iderror; // идентификатор сообщения об ошибке
        vector<Chain> chains;  // множество цепочек - правых частей правила
        char*	      info;    // описание правила

        Rule(const char nn, const char* rule, const int iderror) {
            this->nn	  = Chain::N(nn);
            this->iderror = iderror;
            int len = strlen(rule);
            info    = new char[len + 5];
            info[0] = nn;
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

        // получить следующую за j подходящую цепочку, вернуть ее номер или -1
        short getNextChainNumber(
            GRBALPHABET t, // первый символ цепочки
            short	j  // номер цепочки
            );

        // получить цепочку по номеру
        Chain* getChain(short n);
    };

    // грамматика Гребах
    struct Greibach {
        GRBALPHABET  startN;    // стартовый символ
        GRBALPHABET  stbottomT; // дно стека
        vector<Rule> rules;     // множестов правил

        Greibach() {}

        Greibach(const GRBALPHABET pstartN, const GRBALPHABET pstbottomT) {
            startN    = pstartN;
            stbottomT = pstbottomT;
        }

        // получить номер правила по левому символу. Возвращается номер правила или -1
        short getRuleNumber(GRBALPHABET pnn);

        // получить правило по номеру
        Rule* getRule(short n);
    };

    Greibach* getGrammar();
}

#endif // !GREIBACH_H
