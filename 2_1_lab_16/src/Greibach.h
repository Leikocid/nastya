#ifndef GREIBACH_H
#define GREIBACH_H

typedef short GRBALPHABET; //  символы алфавита грамматики. терминалы > 0 а нетерминалы < 0

namespace GRB {
    //  правило в грамматик  Грейбах
    struct Rule {
        GRBALPHABET nn;     // нетерминал, левый символ правила < 0
        int	    derror; // идентификатор лдиагностического сообщения
        short	    size;   // количество цепочек - правых частей правила

        // цепочка - правая часть правила
        struct Chain {
            short	 size; // длина цепочки
            GRBALPHABET* nt;   // цепочка терминалов (>0) и нетерминалов (<0)

            Chain() {
                size = 0;
                nt   = 0;
            }

            Chain(
                short psize,          // количество символов в цепочке
                GRBALPHABET s, ...    // символы
                );

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
        }* chains; // массив цепочек - правых частей правила

        Rule() {
            nn = 0x00; size = 0;
        }

        Rule(
            GRBALPHABET pnn, // нетерминал < 0
            int iderror,     // идентификатор диагностического сообщения
            short psize,     // количество цепочек - правых частей правила
            Chain c, ...     // множество цепочек - правых частей правила
            );

        // получить правило в виде N->цепочка для распечатки
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
        short	    size;      // количество правил
        GRBALPHABET startN;    // с тартовый символ
        GRBALPHABET stbottomT; // дно стека
        Rule*	    rules;     // множестов правил

        Greibach() {
            short size = 0; startN = 0; stbottomT = 0; rules = 0;
        }

        Greibach(
            GRBALPHABET pstartN,    // стартовый символ
            GRBALPHABET pstbottomT, // дно стека
            short psize,            // количество правил
            Rule r, ...             // правила
            );

        // получить правила. Возвращается номер правила или -1
        short getRule(
            GRBALPHABET pnn,   // левый символ правила
            Rule	&prule // возвращаемое правило грамматики
            );

        // получить правило по номеру
        Rule getRule(short n);
    };

    Greibach getGreibach();
}

#endif // !GREIBACH_H
