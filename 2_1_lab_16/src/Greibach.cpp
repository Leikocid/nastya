
#include "Greibach.h"
#include "Utils.h"

using namespace Utils;

namespace GRB {
    Greibach* greibach = nullptr;

    void createGreibach() {
        greibach = new Greibach(Chain::N('S'), Chain::T('$'));

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
    }

    Greibach getGreibach() {
        if (!greibach) {
            createGreibach();
        }
        return *greibach;
    }

    short Greibach::getRule(GRBALPHABET pnn, Rule &prule) {
        short rc = -1;
        short k	 = 0;
        while (k < rules.size() && rc == -1) {
            if (rules[k].nn == pnn) {
                prule = rules[k];
                rc    = k;
            }
            k++;
        }
        return rc;
    }

    Rule Greibach::getRule(short n) {
        Rule rc;
        if (n < rules.size()) {
            rc = rules[n];
        }
        return rc;
    }

    char* Rule::getCRule(char* b, short nchain) {
        char bchain[200];
        b[0] = Chain::alphabet_to_char(nn);
        b[1] = '-';
        b[2] = '>';
        b[3] = 0;
        chains[nchain].getCChain(bchain);
        appendChars(b, bchain);
        return b;
    }

    short Rule::getNextChain(GRBALPHABET t, Chain &pchain, short j) {
        short rc = -1;
        while (j < chains.size() && rc == -1) {
            if (chains[j].lexems[0] == t) {
                pchain = chains[j];
                rc     = j;
            }
            j++;
        }
        return rc;
    }

    char* Chain::getCChain(char* b) {
        for (int i = 0; i < lexems.size(); i++) {
            b[i] = Chain::alphabet_to_char(lexems[i]);
        }
        b[lexems.size()] = 0;
        return b;
    }
}
