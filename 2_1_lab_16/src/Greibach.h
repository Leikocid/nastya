#ifndef GREIBACH_H
#define GREIBACH_H

#include <vector>

typedef short GRBALPHABET; //  символы алфавита грамматики. терминалы > 0 а нетерминалы < 0

using namespace std;

namespace GRB {
    struct Chain {
        // цепочка лексем для правила
        vector<GRBALPHABET> lexems; // цепочка терминалов (>0) и нетерминалов (<0)

        Chain() {}

        Chain(const char* chain) {
            int size = strlen(chain);
            lexems.reserve(size);
            for (int i  = 0; i < size; i++) {
                char c = chain[i];
                if (isupper(c)) {
                    lexems.push_back(N(c));
                } else {
                    lexems.push_back(T(c));
                }
            }
        }

        char* getCChain(char* b); // пролучить правую сторону правила

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

        Rule() {
            nn = 0;
        }

        Rule(const GRBALPHABET nn, const int iderror) {
            this->nn	  = nn;
            this->iderror = iderror;
        }

        // получить правило в виде "N -> цепочка для распечатки"
        char* getCRule(
            char* b,     // буфер
            short nchain // номер цепочки (правой части) в правиле
            );

        // получить следующую за j подходящую цепочку, вернуть ее номер или -1
        short getNextChain(
            GRBALPHABET t,       // первый символ цепочки
            Chain	&pchain, // возвращаемая цепочка
            short	j        // номер цепочки
            );
    };

    // грамматика Гребах
    struct Greibach {
        GRBALPHABET  startN;    // стартовый символ
        GRBALPHABET  stbottomT; // дно стека
        vector<Rule> rules;     // множестов правил

        Greibach(const GRBALPHABET pstartN, const GRBALPHABET pstbottomT) {
            startN    = pstartN;
            stbottomT = pstbottomT;
        }

        // получить правило по левому симваолу. Возвращается номер правила или -1
        short getRule(GRBALPHABET pnn, Rule &prule);

        // получить правило по номеру
        Rule getRule(short n);
    };

    Greibach getGreibach();
}

#endif // !GREIBACH_H
