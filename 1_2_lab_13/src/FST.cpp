#include "FST.h"
#include <iostream>

namespace Fst {
    // один шаг автомата
    bool step(FST* fst, short* &rstates) {
        bool rc = false;
        std::swap(rstates, fst->rstates); // смена массивов
        for (short i = 0; i < fst->nstates; i++) {
            if (rstates[i] == fst->position) {
                for (short j = 0; j < fst->nodes[i].n_relation; j++) {
                    if (fst->nodes[i].relations[j].symbol == fst->string[fst->position]) {
                        fst->rstates[fst->nodes[i].relations[j].nnode] = fst->position + 1;
                        rc					       = true;
                    }
                }
            }
        }
        return rc;
    }

    bool FST::execute() {
        this->position = -1;
        this->rstates  = new short[this->nstates];
        memset(this->rstates, 0xff, sizeof(short) * this->nstates);
        this->rstates[0] = 0;

        short* rstates = new short[this->nstates];
        memset(rstates, 0xff, sizeof(short) * this->nstates);
        short lstring = strlen(this->string);
        bool  rc      = true;
        for (short i = 0; i < lstring && rc; i++) {
            this->position++;         // продвинули позицию
            rc = step(this, rstates); // один шаг автомата
        }
        delete[] rstates;
        return (rc ? (this->rstates[this->nstates - 1] == lstring) : rc);
    }

    RELATION R(char c, short nn) {
        RELATION* result = new RELATION();
        result->symbol = c;
        result->nnode  = nn;
        return *result;
    }

    NODE N() {
        NODE* result = new NODE();
        return *result;
    }

    NODE N(RELATION rel1) {
        NODE* result = new NODE();
        result->n_relation   = 1;
        result->relations    = new RELATION[1];
        result->relations[0] = rel1;
        return *result;
    }

    NODE N(RELATION rel1, RELATION rel2) {
        NODE* result = new NODE();
        result->n_relation   = 2;
        result->relations    = new RELATION[2];
        result->relations[0] = rel1;
        result->relations[1] = rel2;
        return *result;
    }

    NODE N(RELATION rel1, RELATION rel2, RELATION rel3) {
        NODE* result = new NODE();
        result->n_relation   = 3;
        result->relations    = new RELATION[3];
        result->relations[0] = rel1;
        result->relations[1] = rel2;
        result->relations[2] = rel3;
        return *result;
    }

    NODE N(RELATION rel1, RELATION rel2, RELATION rel3, RELATION rel4) {
        NODE* result = new NODE();
        result->n_relation   = 4;
        result->relations    = new RELATION[4];
        result->relations[0] = rel1;
        result->relations[1] = rel2;
        result->relations[2] = rel3;
        result->relations[3] = rel4;
        return *result;
    }

    NODE N(short n, RELATION rel, ...) {
        NODE* result = new NODE();
        result->n_relation = n;
        result->relations  = new RELATION[n];
        va_list p;
        va_start(p, rel);
        result->relations[0] = rel;
        for (int i = 1; i < n; i++) {
            result->relations[i] = va_arg(p, RELATION);
        }
        va_end(p);
        return *result;
    }
}
