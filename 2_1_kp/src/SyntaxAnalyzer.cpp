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
    bool SyntaxAnalyzer::syntaxAnalysis() {
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
                printDiagnosis();
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

                        saveDiagnosis(NS_NORULECHAIN);
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

    GR::ParseTreeNode* createParseTreeNode(TranslationContext ctx, stack<MfstState>* stack) {
        MfstState s = stack->top();
        stack->pop();
        Rule* rule = ctx.grammar->getRule(s.ruleIdx);

        *ctx.logger << setw(4) << left << s.lentaPosition << ": " << setw(40) << left
                    << info(rule->ruleSymbol, rule->getChain(s.chainIdx)) << endl;

        return new GR::ParseTreeNode(s.lentaPosition, rule, rule->getChain(s.chainIdx));
    }

    void buildParseTreeNode(TranslationContext ctx, GR::ParseTreeNode* parent, stack<MfstState>* stack) {
        int len = 0;
        for (int i = 0; i < parent->chain->symbols.size(); i++) {
            if (GR::isN(parent->chain->symbols[i])) {
                len++;
            }
        }
        for (int i = 0; i < len; i++) {
            GR::ParseTreeNode* node = createParseTreeNode(ctx, stack);
            parent->child.push_back(node);
            node->parent = parent;
            buildParseTreeNode(ctx, node, stack);
        }
    }

    ParseTreeNode* SyntaxAnalyzer::buildParseTree() {
        *ctx.logger << "\nДерево разбора:" << endl;
        stack<MfstState> temp;
        while (!statesStack.empty()) {
            MfstState s = statesStack.top();
            temp.push(s);
            statesStack.pop();
        }
        ParseTreeNode* tree = nullptr;
        if (!temp.empty()) {
            tree = createParseTreeNode(ctx, &temp);
            buildParseTreeNode(ctx, tree, &temp);
        }
        return tree;
    }

    bool SyntaxAnalyzer::saveDiagnosis(RC_STEP rc_step) {
        short k = 0;
        while (k < MFST_DIAGN_NUMBER && lentaPosition <= diagnosis[k].lentaPosition) {
            k++;
        }
        bool result = k < MFST_DIAGN_NUMBER;
        if (result) {
            diagnosis[k] = MfstDiagnosis(lentaPosition, rc_step, ruleIdx, chainIdx);
            for (short j = k + 1; j < MFST_DIAGN_NUMBER; j++) {
                diagnosis[j].lentaPosition = -1;
            }

            int errid	     = ctx.grammar->getRule(diagnosis[k].ruleIdx)->errorId;
            Error::ERROR err = Error::geterror(errid);
            *ctx.logger <<  "Регистрация ошибки: " << k << " (" << lentaPosition << ") строка " << ctx.lexTable.table[lentaPosition].line
                        << ", [" << errid << "] " << err.message << endl;
        }
        return result;
    }

    void SyntaxAnalyzer::printDiagnosis() {
        for (int n = 0; n < MFST_DIAGN_NUMBER; n++) {
            int errid = 0;
            int lpos  = diagnosis[n].lentaPosition;
            if (lpos >= 0) {
                errid = ctx.grammar->getRule(diagnosis[n].ruleIdx)->errorId;
                Error::ERROR err = Error::geterror(errid);
                *ctx.logger <<  err.id << ": строка " << ctx.lexTable.table[lpos].line << ", " << err.message << endl;
            }
        }
    }
}
