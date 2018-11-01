#include "MFST.h"
#include <iostream>

using namespace std;
using namespace GRB;


int  FST_TRACE_n = -1;
char rbuf[205], sbuf[205], lbuf[1024];
namespace MFST {
    MfstState::MfstState() {
        lenta_position = 0;
        nrule	       = -1;
        nrulechain     = -1;
    }

    MfstState::MfstState(short pposition, MfstStack pst, short pnrulechain) {
        lenta_position = pposition;
        st	       = pst;
        nrulechain     = pnrulechain;
    }

    MfstState::MfstState(short pposition, MfstStack pst, short pnrule, short pnrulechain) {
        lenta_position = pposition;
        st	       = pst;
        nrule	       = pnrule;
        nrulechain     = pnrulechain;
    }

    Mfst::MfstDiagnosis::MfstDiagnosis() {
        lenta_position = -1;
        rc_step	       = SURPRISE;
        nrule	       = -1;
        nrule_chain    = -1;
    }

    Mfst::MfstDiagnosis::MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain) {
        lenta_position = plenta_position;
        rc_step	       = prc_step;
        nrule	       = pnrule;
        nrule_chain    = pnrule_chain;
    }

    Mfst::Mfst() {
        lenta	   = 0;
        lenta_size = lenta_position = 0;
    }

    Mfst::Mfst(LT::LexTable plex, Greibach pgrebach) {
        greibach = pgrebach;
        lexTable = plex;
        lenta	 = new short[lenta_size = lexTable.table.size()];
        for (int i = 0; i < lenta_size; i++) {
            lenta[i] = Chain::T(lexTable.table[i].lexema);
        }
        lenta_position = 0;
        st.push(greibach.stbottomT);
        st.push(greibach.startN);
        nrulechain = -1;
    }

    Mfst::RC_STEP Mfst::step() {
        RC_STEP rc = SURPRISE;
        if (lenta_position < lenta_size) {
            if (Chain::isN(st.top())) {
                Rule rule;
                if ((nrule = greibach.getRule(st.top(), rule)) >= 0) {
                    Chain chain;
                    if ((nrulechain = rule.getNextChain(lenta[lenta_position], chain, nrulechain + 1)) >= 0) {
                        MFST_TRACE1
                            savestate();
                        st.pop();
                        push_chain(chain);
                        rc = NS_OK;
                        MFST_TRACE2
                    } else {
                        MFST_TRACE4("TNS_NORULECHAIN/NS_NORULE")
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
                MFST_TRACE3
            } else {
                MFST_TRACE4("TS_NOK/NS_NORULECHAIN")
                rc = reststate() ? TS_NOK : NS_NORULECHAIN;
            }
        } else {
            rc = LENTA_END;
            MFST_TRACE4("LENTA_END")
        }
        return rc;
    }

    bool Mfst::push_chain(Chain chain) {
        for (int i = chain.lexems.size() - 1; i >= 0; i--) {
            st.push(chain.lexems[i]);
        }
        return true;
    }

    bool Mfst::savestate() {
        storestate.push(MfstState(lenta_position, st, nrule, nrulechain));
        MFST_TRACE6("SAVESTATE:", storestate.size());
        return true;
    }

    bool Mfst::reststate() {
        bool rc = false;
        MfstState state;
        if (rc = (storestate.size() > 0)) {
            state	   = storestate.top();
            lenta_position = state.lenta_position;
            st		   = state.st;
            nrule	   = state.nrule;
            nrulechain	   = state.nrulechain;
            storestate.pop();
            MFST_TRACE5("RESSTATE")
            MFST_TRACE2
        }
        return rc;
    }

    bool Mfst::savediagnosis(RC_STEP prc_step) {
        bool  rc = false;
        short k	 = 0;
        while (k < MFST_DIAGN_NUMBER && lenta_position <= diagnosis[k].lenta_position) k++;
        if (rc = (k < MFST_DIAGN_NUMBER)) {
            diagnosis[k] = MfstDiagnosis(lenta_position, prc_step, nrule, nrulechain);
            for (short j = k + 1; j < MFST_DIAGN_NUMBER; j++) {
                diagnosis[j].lenta_position = -1;
            }
        }
        return rc;
    }

    bool Mfst::start() {
        bool rc		= false;
        RC_STEP rc_step = SURPRISE;
        char	buf[MFST_DIAGN_MAXSIZE];
        rc_step = step();
        while (rc_step == NS_OK || rc_step == NS_NORULECHAIN || rc_step == TS_OK || rc_step == TS_NOK) {
            rc_step = step();
        }

        switch (rc_step) {
            case NS_NORULE: {
                MFST_TRACE4("-------> NS_NORULE")
                cout << "--------------------------------------------------------------" << endl;
                cout << getDiagnosis(0, buf) << endl;
                cout << getDiagnosis(1, buf) << endl;
                cout << getDiagnosis(2, buf) << endl;
                break;
            }
            case NS_NORULECHAIN: {
                MFST_TRACE4("------> NS_NORULECHAIN")
                break;
            }
            case NS_ERROR:  {
                MFST_TRACE4("------> NS_ERROR")
                break;
            }
            case LENTA_END: {
                MFST_TRACE4("-------> NS_LENTA_END")
                cout << "--------------------------------------------------------------" << endl;
                sprintf_s(buf, MFST_DIAGN_MAXSIZE, "%d: всего строк %d, синтаксический анализ выполнен без ошибок", 0, lenta_size);
                cout << setw(4) << left << ": всего строк " << lenta_size << ", синтаксический анализ выполнен без ошибок" << endl;
                rc = true;
                break;
            }
            case SURPRISE: {
                MFST_TRACE4("------> SURPRISE")
                break;
            }
            default: {}
        }
        return rc;
    }

    char* Mfst::getCSt(char* buf) {
        for (int i = (signed)st.size() - 1; i >= 0; --i) {
            short p = st.c[i];
            buf[st.size() - 1 - i] = Chain::alphabet_to_char(p);
        }
        buf[st.size()] = 0x00;
        return buf;
    }

    char* Mfst::getCLenta(char* buf, short pos, short n) {
        short i, k = (pos + n < lenta_size) ? pos + n : lenta_size;
        for (i = pos; i < k; i++) {
            buf[i - pos] = Chain::alphabet_to_char(lenta[i]);
        }
        buf[i - pos] = 0x00;
        return buf;
    }

    char* Mfst::getDiagnosis(short n, char* buf) {
        char* rc    = { 0 };
        int   errid = 0;
        int   lpos  = -1;
        if ((n < MFST_DIAGN_NUMBER) && ((lpos = diagnosis[n].lenta_position) >= 0)) {
            errid = greibach.getRule(diagnosis[n].nrule).iderror;
            Error::ERROR err = Error::geterror(errid);
            sprintf_s(buf, MFST_DIAGN_MAXSIZE, "%d: строка %d, %s", err.id, lexTable.table[lpos].lexema, err.message);
            rc = buf;
        }
        return rc;
    }

    void Mfst::printrules() {
        MfstState state;
        Rule rule;
        for (unsigned short i = 0; i < storestate.size(); i++) {
            state = storestate.c[i];
            rule  = greibach.getRule(state.nrule);
            MFST_TRACE7
        }
    }

    bool Mfst::savededucation() {
        MfstState state;
        Rule rule;
        deducation.nrules      = new short[deducation.size = storestate.size()];
        deducation.nrulechains = new short[deducation.size];
        for (unsigned short i = 0; i < storestate.size(); i++) {
            state		      = storestate.c[i];
            deducation.nrules[i]      = state.nrule;
            deducation.nrulechains[i] = state.nrulechain;
        }
        return true;
    }
}
