#ifndef FST_H
#define FST_H

#include <cstdarg>
#include <string.h>

namespace Fst {
    // ребро: символ -> вершина графа переходов КА
    struct RELATION {
        char  symbol; // символ перехода
        short nnode;  // номер смежной вершины - новое состояние
    };

    // вершина графа переходов - состояние КА
    struct NODE {
        short	  n_relation; // количество инцидентных ребер
        RELATION* relations;  // инцидентные ребра
    };

    RELATION R(char c = 0x00, short nn = 0);

    NODE     N();
    NODE     N(RELATION rel1);
    NODE     N(RELATION rel1, RELATION rel2);
    NODE     N(RELATION rel1, RELATION rel2, RELATION rel3);
    NODE     N(RELATION rel1, RELATION rel2, RELATION rel3, RELATION rel4);
    NODE     N(short n, RELATION rel, ...);


    // недетерминированный конечный автомат
    struct FST {
        const char* string;   // цепочка, строка завершающася 0x00
        short	    position; // текущая позиция в цепочке
        short	    nstates;  // количество состояний в автомате
        NODE*	    nodes;    // граф переходов: [0] - начальное состояние, [nstate-1] - конечное
        short*	    rstates;  // возможные состояния автомата для данной позиции

        FST(const char* s, short ns, NODE n, ...) {
            string  = s;
            nstates = ns;
            nodes   = new NODE[ns];
            va_list p;
            va_start(p, n);
            nodes[0] = n;
            for (int i = 1; i < ns; i++) {
                nodes[i] = va_arg(p, NODE);
            }
            va_end(p);
            rstates = new short[ns];
            memset(rstates, 0xff, sizeof(short) * ns);
            rstates[0] = 0;
            position   = -1;
        }

        // специальный конструктор для строки
        FST(const char* word) {
            string  = "";
            nstates = strlen(word) + 1;
            nodes   = new NODE[nstates];
            for (int i = 0; i < nstates - 1; i++) {
                nodes[i] = N(1, R(word[i], i + 1));
            }
            nodes[nstates - 1] = N();
            rstates	       = new short[nstates];
            memset(rstates, 0xff, sizeof(short) * nstates);
            rstates[0] = 0;
            position   = -1;
        }

        // выполнить распознование цепочки
        bool execute();
    };
}

#endif // !FST_H
