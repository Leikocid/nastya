
#include "Greibach.h"
#include "Utils.h"

using namespace Utils;

namespace GRB {
    Rule createRule(char pnn, int piderror, const char* rule) {
        Rule  result =  *new Rule(Chain::N(pnn), piderror);
        int   size   = strlen(rule);
        char* chain  = new char[size];
        int   i	     = 0;
        int   r	     = 0;
        while (i < size) {
            char c = rule[i];
            if (c == '|') {
                chain[r] = 0;
                result.chains.push_back(*new Chain(chain));
                r = 0;
            } else if (c != ' ') {
                chain[r] = c;
                r++;
            }
        }
        chain[r] = 0;
        result.chains.push_back(*new Chain(chain));
        return result;
    }

    Greibach* greibach = nullptr;

    void createGreibach() {
        greibach = new Greibach(Chain::N('S'), Chain::T('$'));
        greibach->rules.reserve(6);

        // S -> m{NrE;}; | tfi(F){NrE;};S | m{NrE;};S | tfi(F){NrE;};
        greibach->rules.push_back(createRule('S', 600, // Неверная структура программы
                                             "m{NrE;}; | tfi(F){NrE;};S | m{NrE;};S | tfi(F){NrE;};"));

        // N -> dti; | rE; | i=E; | dtfi(F); | dti;N | rE;N | i=E;N | dtfi(F);N
        greibach->rules.push_back(createRule('N', 601, // Ошибочный оператор
                                             "dti; | rE; | i=E; | dtfi(F); | dti;N | rE;N | i=E;N | dtfi(F);N"));

        // E -> i | l | (E) | i(W) | iM | lM | (E)M | i(W)M
        greibach->rules.push_back(createRule('E', 602, // Ошибка в выражении
                                             "ii | l | (E) | i(W) | iM | lM | (E)M | i(W)M"));

        // M -> +E | +EM | -E | -EM | *E | *EM | /E | /EM
        greibach->rules.push_back(createRule('M', 602, // Ошибка в выражении
                                             "+E | +EM | -E | -EM | *E | *EM | /E | /EM"));

        // F -> ti | ti,F
        greibach->rules.push_back(createRule('F', 603, // Ошибка в параметрах функции
                                             "ti | ti,F"));

        // W -> i | l | i,W | l,W
        greibach->rules.push_back(createRule('W', 604, // Ошибка в параметрах вызываемой функции
                                             "i | l | i,W | l,W"));
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
