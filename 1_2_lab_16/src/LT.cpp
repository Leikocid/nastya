#include "LT.h"
#include "Error.h"

namespace LT {
    // создать таблицу лексем
    LexTable CreateLexTable(int maxsize) {
        if (maxsize > LT_MAXSIZE) {
            maxsize = LT_MAXSIZE;
        }
        LexTable result =  *(new LexTable());
        result.table.reserve(maxsize);
        result.maxsize = maxsize;
        return result;
    }

    void LexTable::Add(Entry entry) {
        if (this->table.size() <= this->maxsize) {
            this->table.push_back(entry);
        } else {
            throw ERROR_THROW(21);
        }
    }

    Entry LexTable::GetEntry(int n) {
        if ((n < 0) || (n >= this->table.size())) {
            throw ERROR_THROW(24);
        }
        return this->table[n];
    }

    // удалить таблицу лексем (освободить память)
    void LexTable::Delete() {
        this->table.clear();
    }
}
