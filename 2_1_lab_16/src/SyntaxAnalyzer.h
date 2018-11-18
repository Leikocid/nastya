#ifndef SA_H
#define SA_H

#include "TranslationContext.h"
#include <stack>
#include <iomanip>

#define MFST_DIAGN_MAXSIZE      2 * ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER       3


using namespace GR;

namespace SA {
    struct SymbolStack : public std::stack<TN_SYMBOL> {};

    // состояние автомата для сохранения
    struct MfstState {
        short	    lentaPosition; // позиция на ленте
        short	    ruleIdx;       // индекс текущего правила
        short	    chainIdx;      // индекс текущей цепочки текущего правила
        SymbolStack stack;         // стек автомата

        MfstState(short pposition, SymbolStack pst, short pnrule, short pnrulechain) {
            lentaPosition = pposition;
            stack	  = pst;
            ruleIdx	  = pnrule;
            chainIdx	  = pnrulechain;
        }
    };

    // магазинный автомат
    struct SyntaxAnalyzer {
        // код возврата функции step
        enum RC_STEP {
            NS_OK,                        // найдено правило и цепочка, цепочка записана в стек
            NS_NORULE,                    // не найдено правило в грамматике (ошибка в грамматике)
            NS_NORULECHAIN,               // не найдена подходящая цепочка правила (ошибка в исходном коде)
            NS_ERROR,                     // нейзвестный нетерминальный символ грамматики
            TS_OK,                        // тек. символ ленты == вершине стека => пробвинулась лента, pop стека
            TS_NOK,                       // тек. символ ленты != вершине стека => восстановлено состояние
            LENTA_END,                    // текущая позиция ленты >= lemnta_size
            SURPRISE                      // неожиданный код возврата (ошибка в step)
        };

        TranslationContext ctx;           // контекст
        int		   stepNumber;    // номер шага
        TN_SYMBOL*	   lenta;         // перекодированная  в (TS/NS) входная лента
        short		   lentaSize;     // размер ленты
        short		   lentaPosition; // текущая позиция на ленте
        short		   ruleIdx;       // индекс текущего правила
        short		   chainIdx;      // индекс текущей цепочки
        SymbolStack	   symbolStack;   // стек автомата
        stack<MfstState>   statesStack;   // стек для сохранения состояний

        SyntaxAnalyzer(TranslationContext &ctx) {
            this->ctx = ctx;
            lenta     = new short[lentaSize = ctx.lexTable.table.size()];
            for (int i = 0; i < lentaSize; i++) {
                lenta[i] = charToT(ctx.lexTable.table[i].lexema);
            }
            lentaPosition = 0;
            stepNumber	  = 0;
            symbolStack.push(ctx.grammar->bottomSymbol);
            symbolStack.push(ctx.grammar->startSymbol);
            chainIdx = -1;
        }

        bool	    start();                          // запустить автомат
        void	    printRules();                     // вывести последовательность правил
        bool	    saveDeduction();                  // сохранить дерево вывода

        private:
            RC_STEP step();                           // выполнить шаг автомата
            void logRow(const char* message);         // вывести строку отладки
            bool saveState();                         // сохранить состояние автомата
            bool restoreState();                      // восстановить состояние автомата
            bool addChainSymbolsToStack(Chain chain); // поместить цепочку правила в стек

            bool saveDiagnosis(RC_STEP pprc_step);    // зарегистрировать диагностическое сообщение
            void printDiagnosis();                    // вывести диагностические сообщения

            // диагностика
            struct MfstDiagnosis {
                short	lentaPosition; // позиция на ленте
                RC_STEP rc_step;       // код завершения шага
                short	ruleIdx;       // номер правила
                short	chainIdx;      // номер цепочки

                MfstDiagnosis() {
                    lentaPosition = -1;
                    rc_step	  = SURPRISE;
                    ruleIdx	  = -1;
                    chainIdx	  = -1;
                }

                MfstDiagnosis(short lentaPosition, RC_STEP rc_step, short ruleIdx, short chainIdx) {
                    this->lentaPosition = lentaPosition;
                    this->rc_step	= rc_step;
                    this->ruleIdx	= ruleIdx;
                    this->chainIdx	= chainIdx;
                }
            } diagnosis[MFST_DIAGN_NUMBER]; // последние самые глубокие диагностические сообщения
    };
}

#endif // !SA_H
