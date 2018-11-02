#ifndef MFST_H
#define MFST_H

#include "TranslationContext.h"
#include <stack>
#include <iomanip>

#define MFST_DIAGN_MAXSIZE      2 * ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER       3

#define MFST_TRACE_START *ctx.logger << setw(4) << left << "Шаг:"            \
                                     << setw(20) << left << " Правило"       \
                                     << setw(30) << left << " Входная лента" \
                                     << setw(20) << left << " Стек" << endl;
#define MFST_TRACE1     cout << setw(4) << left << ++FST_TRACE_n << ": "            \
                             << setw(20) << left << rule->info                      \
                             << setw(30) << left << getCLenta(lbuf, lenta_position) \
                             << setw(20) << left << getCSt(sbuf) << endl;
#define MFST_TRACE2     cout << setw(4) << left << FST_TRACE_n << ": "              \
                             << setw(20) << left << " "                             \
                             << setw(30) << left << getCLenta(lbuf, lenta_position) \
                             << setw(20) << left << getCSt(sbuf) << endl;
#define MFST_TRACE3     cout << setw(4) << left << ++FST_TRACE_n << ": "            \
                             << setw(20) << left << " "                             \
                             << setw(30) << left << getCLenta(lbuf, lenta_position) \
                             << setw(20) << left << getCSt(sbuf) << endl;
#define MFST_TRACE4(c) cout << setw(4) << left << ++FST_TRACE_n << ": " << setw(20) << left << c << endl;
#define MFST_TRACE5(c) cout << setw(4) << left << FST_TRACE_n << ": " << setw(20) << left << c << endl;
#define MFST_TRACE6(c, k) cout << setw(4) << left << FST_TRACE_n << ": " << setw(20) << left << c << k << endl;
#define MFST_TRACE7 cout << setw(4) << left << state->lenta_position << ": " << setw(20) << left << rule->info << endl;

using namespace GR;

namespace SA {
    struct MfstStack : public std::stack<short> {
        using std::stack<short>::c; // открываем закрытое поле "c" из класса-предка для прямого доступа к нему
    };

    // состояние автомата для сохранения
    struct MfstState {
        short	  lenta_position; // позиция на ленте
        short	  nrule;          // номер текущего правила
        short	  nrulechain;     // номер текущей цепочки текущего правила
        MfstStack st;             // стек автомата

        MfstState(short pposition, MfstStack pst, short pnrule, short pnrulechain) {
            lenta_position = pposition;
            st		   = pst;
            nrule	   = pnrule;
            nrulechain	   = pnrulechain;
        }
    };

    // магазинный автомат
    struct SyntaxAnalyzer {
        // код возврата функции step
        enum RC_STEP {
            NS_OK,                          // найдено правило и цепочка, цепочка записана в стек
            NS_NORULE,                      // не найдено правило в грамматике (ошибка в грамматике)
            NS_NORULECHAIN,                 // не найдена подходящая цепочка правила (ошибка в исходном коде)
            NS_ERROR,                       // нейзвестный нетерминальный символ грамматики
            TS_OK,                          // тек. символ ленты == вершине стека => пробвинулась лента, pop стека
            TS_NOK,                         // тек. символ ленты != вершине стека => восстановлено состояние
            LENTA_END,                      // текущая позиция ленты >= lemnta_size
            SURPRISE                        // неожиданный код возврата (ошибка в step)
        };

        TranslationContext ctx;             // контекст
        GRBALPHABET*	   lenta;           // перекодированная  (TS/NS) лента
        short		   lenta_position;  // текущая позиция на ленте
        short		   nrule;           // номер текущего правила
        short		   nrulechain;      // ногмер текущей цепочки
        short		   lenta_size;      // размер ленты
        Greibach	   grammar;         // грамматика
        LT::LexTable	   lexTable;        // таблица лексем - результат работы лексического анализатора
        MfstStack	   st;              // стек автомата]
        struct MfstStack : public std::stack<MfstState> {
            using std::stack<MfstState>::c; // открываем закрытое поле "c" из класса-предка для прямого доступа к нему
        } storestate;                       // стек для сохранения состояний

        SyntaxAnalyzer(TranslationContext &ctx) {
            this->ctx = ctx;
            grammar   = *ctx.grammar;
            lexTable  = ctx.lexTable;
            lenta     = new short[lenta_size = lexTable.table.size()];
            for (int i = 0; i < lenta_size; i++) {
                lenta[i] = Chain::T(lexTable.table[i].lexema);
            }
            lenta_position = 0;
            st.push(grammar.stbottomT);
            st.push(grammar.startN);
            nrulechain = -1;
        }

        bool	start();                                       // запустить автомат
        void	printrules();                                  // вывести последовательность правил

        RC_STEP step();                                        // выполнить шаг автомата
        char*	getCSt(char* buf);                             // получить содержание стека
        char*	getCLenta(char* buf, short pos, short n = 25); // лента: n символов начиная с pos
        char*	getDiagnosis(short n, char* buf);              // полдучить n-ую строку диагностики или 0
        bool	savestate();                                   // сохранить состояние автомата
        bool	reststate();                                   // восстановить состояние автомата
        bool	push_chain(Chain chain);                       // поместить цепочку правила в стек
        bool	savediagnosis(RC_STEP pprc_step);

        // диагностика
        struct MfstDiagnosis {
            short   lenta_position; // позиция на ленте
            RC_STEP rc_step;        // код завершения шага
            short   nrule;          // номер правила
            short   nrule_chain;    // номер цепочки

            MfstDiagnosis() {
                lenta_position = -1;
                rc_step	       = SURPRISE;
                nrule	       = -1;
                nrule_chain    = -1;
            }

            MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain) {
                lenta_position = plenta_position;
                rc_step	       = prc_step;
                nrule	       = pnrule;
                nrule_chain    = pnrule_chain;
            }
        } diagnosis[MFST_DIAGN_NUMBER]; // последние самые глубокие диагностические сообщения


        // вывод
        struct Deducation {
            short  size;        // количество шагов в выводе
            short* nrules;      // номера правил граммат���������ки
            short* nrulechains; // номера купочек правил грамматики
            Deducation() {
                size = 0; nrules = 0; nrulechains = 0;
            }
        } deducation;

        bool savededucation(); // сохранить дерево вывода
    };
}

#endif // !MFST_H
