
#include "Greibach.h"
#include "Utils.h"

using namespace Utils;

namespace GR {
    // построить правила синтаксиса
    Greibach* getGrammar() {
        Greibach* greibach = new Greibach(Chain::N('S'), Chain::T('$'));

        greibach->rules.reserve(6);

        // S -> m{NrE;}; | tfi(F){NrE;};S | m{NrE;};S | tfi(F){NrE;};
        greibach->rules.push_back(*new Rule('S', "m{NrE;}; | tfi(F){NrE;};S | m{NrE;};S | tfi(F){NrE;};",
                                            600 // Неверная структура программы
                                            ));

        // N -> dti; | rE; | i=E; | dtfi(F); | dti;N | rE;N | i=E;N | dtfi(F);N
        greibach->rules.push_back(*new Rule('N', "dti; | rE; | i=E; | dtfi(F); | dti;N | rE;N | i=E;N | dtfi(F);N",
                                            601 // Ошибочный оператор
                                            ));

        // E -> i | l | (E) | i(W) | iM | lM | (E)M | i(W)M
        greibach->rules.push_back(*new Rule('E', "ii | l | (E) | i(W) | iM | lM | (E)M | i(W)M",
                                            602 // Ошибка в выражении
                                            ));

        // M -> +E | +EM | -E | -EM | *E | *EM | /E | /EM
        greibach->rules.push_back(*new Rule('M', "+E | +EM | -E | -EM | *E | *EM | /E | /EM",
                                            602 // Ошибка в выражении
                                            ));

        // F -> ti | ti,F
        greibach->rules.push_back(*new Rule('F', "ti | ti,F",
                                            603 // Ошибка в параметрах функции
                                            ));

        // W -> i | l | i,W | l,W
        greibach->rules.push_back(*new Rule('W', "i | l | i,W | l,W",
                                            604 // Ошибка в параметрах вызываемой функции
                                            ));
        return greibach;
    }

    short Greibach::getRuleNumber(GRBALPHABET pnn) {
        short result = -1;
        short k	     = 0;
        while (k < rules.size() && result == -1) {
            if (rules[k].nn == pnn) {
                result = k;
            }
            k++;
        }
        return result;
    }

    Rule* Greibach::getRule(short n) {
        Rule* result = nullptr;
        if (n < rules.size()) {
            result = &rules[n];
        }
        return result;
    }

    short Rule::getNextChainNumber(GRBALPHABET t, short j) {
        short rc = -1;
        while (j < chains.size() && rc == -1) {
            if (chains[j].lexems[0] == t) {
                rc = j;
            }
            j++;
        }
        return rc;
    }

    Chain* Rule::getChain(short n) {
        Chain* result = nullptr;
        if (n < chains.size()) {
            result = &chains[n];
        }
        return result;
    }
}