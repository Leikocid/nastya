#include "SyntaxAnalyzer.h"
#include <iostream>
#include <sstream>

using namespace std;
using namespace GR;

int FST_TRACE_n = -1;

char rbuf[205], sbuf[205], lbuf[1024];
namespace SA {
    // запуск процедуры синтаксического анализа
    bool SyntaxAnalyzer::start() {
        *ctx.logger << setw(4) << left << "Шаг:" << setw(20) << left << " Правило" \
                    << setw(30) << left << " Входная лента"  << setw(20) << left << " Стек" << endl;

        bool rc		= false;
        RC_STEP rc_step = SURPRISE;
        rc_step = step();
        while (rc_step == NS_OK || rc_step == NS_NORULECHAIN || rc_step == TS_OK || rc_step == TS_NOK) {
            rc_step = step();
        }

        // вывод результата
        switch (rc_step) {
            case NS_NORULE: {
                *ctx.logger << setw(4) << left << ++FST_TRACE_n << ": " << setw(20) << left << "-------> NS_NORULE" << endl;
                *ctx.logger << "--------------------------------------------------------------" << endl;
                *ctx.logger << getDiagnosis(0) << endl;
                *ctx.logger << getDiagnosis(1) << endl;
                *ctx.logger << getDiagnosis(2) << endl;
                break;
            }
            case NS_NORULECHAIN: {
                *ctx.logger << setw(4) << left << ++FST_TRACE_n << ": " << setw(20) << left << "------> NS_NORULECHAIN" << endl;
                break;
            }
            case NS_ERROR:  {
                *ctx.logger << setw(4) << left << ++FST_TRACE_n << ": " << setw(20) << left << "------> NS_ERROR" << endl;
                break;
            }
            case LENTA_END: {
                *ctx.logger << setw(4) << left << ++FST_TRACE_n << ": " << setw(20) << left << "-------> NS_LENTA_END" << endl;
                *ctx.logger << "--------------------------------------------------------------" << endl;
                *ctx.logger << setw(4) << left << ": всего строк " << lenta_size << ", синтаксический анализ выполнен без ошибок" << endl;
                rc = true;
                break;
            }
            case SURPRISE: {
                *ctx.logger << setw(4) << left << ++FST_TRACE_n << ": " << setw(20) << left << "------> SURPRISE" << endl;
                break;
            }
            default: {}
        }
        return rc;
    }

    // шаг автомата
    SyntaxAnalyzer::RC_STEP SyntaxAnalyzer::step() {
        RC_STEP rc = SURPRISE;
        if (lenta_position < lenta_size) {
            if (Chain::isN(st.top())) {
                nrule = grammar.getRuleNumber(st.top());
                if (nrule  >= 0) {
                    Rule* rule = grammar.getRule(nrule);
                    nrulechain = rule->getNextChainNumber(lenta[lenta_position], nrulechain + 1);
                    if (nrulechain >= 0) {
                        Chain* chain = rule->getChain(nrulechain);

                        *ctx.logger << setw(4) << left << ++FST_TRACE_n << ": " << setw(20) << left << rule->info \
                                    << setw(30) << left << getCLenta(lbuf, lenta_position) << setw(20) << left << getCSt(sbuf) << endl;

                        savestate();
                        st.pop();
                        push_chain(*chain);
                        rc = NS_OK;

                        *ctx.logger << setw(4) << left << FST_TRACE_n << ": " << setw(20) << left << " " \
                                    << setw(30) << left << getCLenta(lbuf, lenta_position) << setw(20) << left << getCSt(sbuf) << endl;
                    } else {
                        *ctx.logger << setw(4) << left << ++FST_TRACE_n << ": " << setw(20) << left << "TNS_NORULECHAIN/NS_NORULE" << endl;
                        savediagnosis(NS_NORULECHAIN);
                        rc = reststate() ? NS_NORULECHAIN : NS_NORULE;
                    }
                } else {
                    rc = NS_ERROR;
                }
            } else if (st.top() == lenta[lenta_position]) {
                lenta_position++;
                st.pop();
                nrulechain = -1;
                rc	   = TS_OK;

                *ctx.logger << setw(4) << left << ++FST_TRACE_n << ": "  << setw(20) << left << " " \
                            << setw(30) << left << getCLenta(lbuf, lenta_position) << setw(20) << left << getCSt(sbuf) << endl;
            } else {
                *ctx.logger << setw(4) << left << ++FST_TRACE_n << ": " << setw(20) << left << "TS_NOK/NS_NORULECHAIN" << endl;
                rc = reststate() ? TS_NOK : NS_NORULECHAIN;
            }
        } else {
            rc = LENTA_END;
            *ctx.logger << setw(4) << left << ++FST_TRACE_n << ": " << setw(20) << left << "LENTA_END" << endl;
        }
        return rc;
    }

    bool SyntaxAnalyzer::push_chain(Chain chain) {
        for (int i = chain.lexems.size() - 1; i >= 0; i--) {
            st.push(chain.lexems[i]);
        }
        return true;
    }

    bool SyntaxAnalyzer::savestate() {
        storestate.push(MfstState(lenta_position, st, nrule, nrulechain));

        *ctx.logger << setw(4) << left << FST_TRACE_n << ": " << setw(20) << left << "SAVESTATE:" << storestate.size() << endl;
        return true;
    }

    bool SyntaxAnalyzer::reststate() {
        bool rc = storestate.size() > 0;
        MfstState* state;
        if (rc) {
            state	   = &storestate.top();
            lenta_position = state->lenta_position;
            st		   = state->st;
            nrule	   = state->nrule;
            nrulechain	   = state->nrulechain;
            storestate.pop();

            *ctx.logger << setw(4) << left << FST_TRACE_n << ": " << setw(20) << left << "RESSTATE" << endl;
            *ctx.logger << setw(4) << left << FST_TRACE_n << ": " << setw(20) << left << " " \
                        << setw(30) << left << getCLenta(lbuf, lenta_position) << setw(20) << left << getCSt(sbuf) << endl;
        }
        return rc;
    }

    bool SyntaxAnalyzer::savediagnosis(RC_STEP prc_step) {
        short k = 0;
        while (k < MFST_DIAGN_NUMBER && lenta_position <= diagnosis[k].lenta_position) {
            k++;
        }
        bool result = k < MFST_DIAGN_NUMBER;
        if (result) {
            diagnosis[k] = MfstDiagnosis(lenta_position, prc_step, nrule, nrulechain);
            for (short j = k + 1; j < MFST_DIAGN_NUMBER; j++) {
                diagnosis[j].lenta_position = -1;
            }
        }
        return result;
    }

    char* SyntaxAnalyzer::getCSt(char* buf) {
        for (int i = (signed)st.size() - 1; i >= 0; --i) {
            short p = st.c[i];
            buf[st.size() - 1 - i] = Chain::alphabet_to_char(p);
        }
        buf[st.size()] = 0x00;
        return buf;
    }

    char* SyntaxAnalyzer::getCLenta(char* buf, short pos, short n) {
        short i, k = (pos + n < lenta_size) ? pos + n : lenta_size;
        for (i = pos; i < k; i++) {
            buf[i - pos] = Chain::alphabet_to_char(lenta[i]);
        }
        buf[i - pos] = 0x00;
        return buf;
    }

    const char* SyntaxAnalyzer::getDiagnosis(short n) {
        char* rc = { 0 };
        if (n < MFST_DIAGN_NUMBER) {
            int errid = 0;
            int lpos  = diagnosis[n].lenta_position;
            if (lpos >= 0) {
                errid = grammar.getRule(diagnosis[n].nrule)->iderror;
                Error::ERROR  err = Error::geterror(errid);
                ostringstream stream;
                stream <<  err.id << ": строка " << lexTable.table[lpos].line << ", " << err.message;
                return stream.str().c_str();
            }
        }
        return rc;
    }

    void SyntaxAnalyzer::printrules() {
        MfstState* state;
        Rule* rule;
        for (unsigned short i = 0; i < storestate.size(); i++) {
            state = &storestate.c[i];
            rule  = grammar.getRule(state->nrule);

            *ctx.logger << setw(4) << left << state->lenta_position << ": " << setw(20) << left << rule->info << endl;
        }
    }

    bool SyntaxAnalyzer::savededucation() {
        MfstState* state;
        deducation.nrules      = new short[deducation.size = storestate.size()];
        deducation.nrulechains = new short[deducation.size];
        for (unsigned short i = 0; i < storestate.size(); i++) {
            state		      = &storestate.c[i];
            deducation.nrules[i]      = state->nrule;
            deducation.nrulechains[i] = state->nrulechain;
        }
        return true;
    }
}
