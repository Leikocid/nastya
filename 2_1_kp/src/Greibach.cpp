
#include "Greibach.h"
#include "Utils.h"

using namespace Utils;

namespace GR {
    // построить правила синтаксиса
    Grammar* getGrammar() {
        Grammar* grammar = new Grammar(charToN('S'), charToT('$'));

        grammar->rules.reserve(6);

        // S -> fi(F):t{NrE;};S | m{N};
        grammar->rules.push_back(*new Rule('S', "fi(F):t{NrE;};S | m{N};",
                                           600 // Неверная структура программы
                                           ));

        // N -> i=E;N | vi:t;N | vi:t=E;N |  ufi(F):t;N | i(W);N | oE;N | vi:t; | vi:t=E; | i=E; | ufi(F):t; | i(W); | oE; | c[EC]{N}; |
        // c[EC]{N};N | c[EC]{N}e{N}; | c[EC]{N}e{N};N | w[EC]{N}; | w[EC]{N};N"
        grammar->rules.push_back(*new Rule('N',
                                           "i=E;N | vi:t;N | vi:t=E;N |  ufi(F):t;N | i(W);N | oE;N | vi:t; | vi:t=E; | i=E; | ufi(F):t; | i(W); | oE; | c[EC]{N}; | c[EC]{N};N | c[EC]{N}e{N}; | c[EC]{N}e{N};N | w[EC]{N}; | w[EC]{N};N",
                                           601 // Ошибочный оператор
                                           ));

        // E -> i | l | (E) | i(W) | iM | lM | (E)M | i(W)M
        grammar->rules.push_back(*new Rule('E', "i | l | (E) | i(W) | iM | lM | (E)M | i(W)M",
                                           602 // Ошибка в выражении
                                           ));

        // M -> +E | +EM | -E | -EM | *E | *EM | /E | /EM
        grammar->rules.push_back(*new Rule('M', "+E | +EM | -E | -EM | *E | *EM | /E | /EM",
                                           602 // Ошибка в выражении
                                           ));

        // F -> i:t | i:t,F
        grammar->rules.push_back(*new Rule('F', "i:t | i:t,F",
                                           603 // Ошибка в параметрах функции
                                           ));

        // W -> i | l | i,W | l,W | (E) | i(W) | iM | lM | (E)M | i(W)M | (E),W | i(W),W | iM,W | lM,W | (E)M,W | i(W)M,W
        grammar->rules.push_back(*new Rule('W',
                                           "i | l | i,W | l,W | (E) | i(W) | iM | lM | (E)M | i(W)M | (E),W | i(W),W | iM,W | lM,W | (E)M,W | i(W)M,W",
                                           604 // Ошибка в параметрах вызываемой функции
                                           ));

        // C -> <E | >E | <=E | >=E | ==E | !=E
        grammar->rules.push_back(*new Rule('C', "<E | >E | <=E | >=E | ==E | !=E",
                                           605 // Ошибка в условии ветвления или цикла
                                           ));


        return grammar;
    }

    short Grammar::getRuleIndex(TN_SYMBOL ruleSymbol) {
        short result = -1;
        short k	     = 0;
        while (k < rules.size() && result == -1) {
            if (rules[k].ruleSymbol == ruleSymbol) {
                result = k;
            }
            k++;
        }
        return result;
    }

    Rule* Grammar::getRule(short idx) {
        Rule* result = nullptr;
        if ((idx >= 0) && (idx < rules.size())) {
            result = &rules[idx];
        }
        return result;
    }

    short Rule::getNextChainIndex(TN_SYMBOL symbol, short idx) {
        short rc = -1;
        idx++;
        while (idx < chains.size() && rc == -1) {
            if (chains[idx].symbols[0] == symbol) {
                rc = idx;
            }
            idx++;
        }
        return rc;
    }

    Chain* Rule::getChain(short idx) {
        Chain* result = nullptr;
        if ((idx >= 0) && (idx < chains.size())) {
            result = &chains[idx];
        }
        return result;
    }

    // терминал
    TN_SYMBOL charToT(char c) {
        return TN_SYMBOL(c);
    }

    // не терминал
    TN_SYMBOL charToN(char c) {
        return -TN_SYMBOL(c);
    }

    // проверка: терминал?
    bool isT(TN_SYMBOL s) {
        return s > 0;
    }

    // проверка: нетерминал?
    bool isN(TN_SYMBOL s) {
        return !isT(s);
    }

    // TN_SYMBOL -> char
    char symbolToChar(TN_SYMBOL s) {
        return isT(s) ? char(s) : char(-s);
    }

    char* info(TN_SYMBOL ruleSymbol, Chain* chain) {
        char* result = new char[strlen(chain->info) + 5];
        result[0] = symbolToChar(ruleSymbol);
        result[1] = 0;
        appendChars(result, " -> ");
        appendChars(result, chain->info);
        return result;
    }
}
