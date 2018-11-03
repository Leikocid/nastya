#include "SyntaxAnalyzer.h"
#include <iostream>
#include <sstream>

using namespace std;
using namespace GR;

namespace SA {
    void SyntaxAnalyzer::logRow(const char* message) {
        *ctx.logger << setw(4) << left << stepNumber << ": " << setw(30) << left << message;
        for (int i = 0; i < 37; i++) {
            if (i + lentaPosition < lentaSize) {
                *ctx.logger << symbolToChar(lenta[i + lentaPosition]);
            } else {
                *ctx.logger << ' ';
            }
        }
        *ctx.logger << "   ";
        SymbolStack temp;
        while (!symbolStack.empty()) {
            TN_SYMBOL s = symbolStack.top();
            *ctx.logger << symbolToChar(s);
            temp.push(s);
            symbolStack.pop();
        }
        while (!temp.empty()) {
            TN_SYMBOL s = temp.top();
            symbolStack.push(s);
            temp.pop();
        }
        *ctx.logger << endl;
    }

    // запуск процедуры синтаксического анализа
    bool SyntaxAnalyzer::start() {
        *ctx.logger << endl << "--------------------------------------------------------------" << endl;
        *ctx.logger << "Шаг : Правило                      " \
                    << "  Входная лента                           Стек" << endl;

        bool result	= false;
        RC_STEP rc_step = SURPRISE;
        rc_step = step();
        while (rc_step == NS_OK || rc_step == NS_NORULECHAIN || rc_step == TS_OK || rc_step == TS_NOK) {
            rc_step = step();
        }

        // вывод результата
        switch (rc_step) {
            case NS_NORULE: {
                logRow("-------> NS_NORULE");
                *ctx.logger << "--------------------------------------------------------------" << endl;
                *ctx.logger << getDiagnosis(0) << endl;
                *ctx.logger << getDiagnosis(1) << endl;
                *ctx.logger << getDiagnosis(2) << endl;
                break;
            }
            case NS_NORULECHAIN: {
                logRow("------> NS_NORULECHAIN");
                break;
            }
            case NS_ERROR:  {
                logRow("------> NS_ERROR");
                break;
            }
            case LENTA_END: {
                logRow("-------> NS_LENTA_END");
                *ctx.logger << "--------------------------------------------------------------" << endl;
                *ctx.logger << "Всего лексем " << lentaSize << ", синтаксический анализ выполнен без ошибок" << endl;
                result = true;
                break;
            }
            case SURPRISE: {
                logRow("------> SURPRISE");
                break;
            }
            default: {}
        }
        return result;
    }

    // шаг автомата
    SyntaxAnalyzer::RC_STEP SyntaxAnalyzer::step() {
        RC_STEP rc = SURPRISE;
        if (lentaPosition < lentaSize) {
            if (isN(symbolStack.top())) {
                ruleIdx = ctx.grammar->getRuleIndex(symbolStack.top());
                if (ruleIdx  >= 0) {
                    Rule* rule = ctx.grammar->getRule(ruleIdx);
                    chainIdx = rule->getNextChainIndex(lenta[lentaPosition], chainIdx);
                    if (chainIdx >= 0) {
                        Chain* chain = rule->getChain(chainIdx);

                        logRow(info(rule->ruleSymbol, chain));

                        saveState();
                        symbolStack.pop();
                        addChainSymbolsToStack(*chain);
                        rc = NS_OK;

                        logRow(" ");
                    } else {
                        logRow("TNS_NORULECHAIN/NS_NORULE");

                        savediagnosis(NS_NORULECHAIN);
                        rc = restoreState() ? NS_NORULECHAIN : NS_NORULE;
                    }
                } else {
                    rc = NS_ERROR;
                }
            } else if (symbolStack.top() == lenta[lentaPosition]) {
                lentaPosition++;
                symbolStack.pop();
                chainIdx = -1;
                rc	 = TS_OK;

                logRow(" ");
            } else {
                logRow("TS_NOK/NS_NORULECHAIN");

                rc = restoreState() ? TS_NOK : NS_NORULECHAIN;
            }
        } else {
            rc = LENTA_END;
            logRow("LENTA_END");
        }
        stepNumber++;
        return rc;
    }

    bool SyntaxAnalyzer::saveState() {
        statesStack.push(MfstState(lentaPosition, symbolStack, ruleIdx, chainIdx));

        ostringstream stream;
        stream <<  "SAVESTATE: " << statesStack.size();
        logRow(stream.str().c_str());

        return true;
    }

    bool SyntaxAnalyzer::restoreState() {
        bool rc = statesStack.size() > 0;
        MfstState* state;
        if (rc) {
            state	  = &statesStack.top();
            lentaPosition = state->lentaPosition;
            symbolStack	  = state->stack;
            ruleIdx	  = state->ruleIdx;
            chainIdx	  = state->chainIdx;
            statesStack.pop();

            ostringstream stream;
            stream <<  "RESSTATE: " << statesStack.size();
            logRow(stream.str().c_str());
        }
        return rc;
    }

    bool SyntaxAnalyzer::addChainSymbolsToStack(Chain chain) {
        for (int i = chain.symbols.size() - 1; i >= 0; i--) {
            symbolStack.push(chain.symbols[i]);
        }
        return true;
    }

    bool SyntaxAnalyzer::savediagnosis(RC_STEP prc_step) {
        short k = 0;
        while (k < MFST_DIAGN_NUMBER && lentaPosition <= diagnosis[k].lenta_position) {
            k++;
        }
        bool result = k < MFST_DIAGN_NUMBER;
        if (result) {
            diagnosis[k] = MfstDiagnosis(lentaPosition, prc_step, ruleIdx, chainIdx);
            for (short j = k + 1; j < MFST_DIAGN_NUMBER; j++) {
                diagnosis[j].lenta_position = -1;
            }
        }
        return result;
    }

    const char* SyntaxAnalyzer::getDiagnosis(short n) {
        char* rc = { 0 };
        if (n < MFST_DIAGN_NUMBER) {
            int errid = 0;
            int lpos  = diagnosis[n].lenta_position;
            if (lpos >= 0) {
                errid = ctx.grammar->getRule(diagnosis[n].nrule)->errorId;
                Error::ERROR err = Error::geterror(errid);

                ostringstream stream;
                stream <<  err.id << ": строка " << ctx.lexTable.table[lpos].line << ", " << err.message;
                return stream.str().c_str();
            }
        }
        return rc;
    }

    void SyntaxAnalyzer::printRules() {
        stack<MfstState> temp;
        while (!statesStack.empty()) {
            MfstState s = statesStack.top();
            temp.push(s);
            statesStack.pop();
        }
        while (!temp.empty()) {
            MfstState s	   = temp.top();
            Rule*     rule = ctx.grammar->getRule(s.ruleIdx);
            *ctx.logger << setw(4) << left << s.lentaPosition << ": " << setw(40) << left
                        << info(rule->ruleSymbol, rule->getChain(s.chainIdx)) << endl;
            statesStack.push(s);
            temp.pop();
        }
    }
}
