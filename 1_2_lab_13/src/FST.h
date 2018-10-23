#ifndef IN_FST
#define IN_FST

#include <cstdarg>
#include <string.h>
#include <vector>

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
    };

    // выполнить распознование цепочки
    bool     execute(FST &fst);

    RELATION R(char c = 0x00, short nn = 0);

    NODE     N();
    NODE     N(RELATION rel1);
    NODE     N(RELATION rel1, RELATION rel2);
    NODE     N(RELATION rel1, RELATION rel2, RELATION rel3);
    NODE     N(RELATION rel1, RELATION rel2, RELATION rel3, RELATION rel4);
    NODE     N(short n, RELATION rel, ...);
}

#endif // !IN_FST.H
