#include "IT.h"
#include "Error.h"

namespace IT {
    // создать таблицу лексем
    IdTable CreateIdTable(int maxsize) {
        if (maxsize > IT_MAXSIZE) {
            maxsize = IT_MAXSIZE;
        }
        IdTable result =  *(new IdTable());
        result.table.reserve(maxsize);
        result.maxsize = maxsize;
        return result;
    }

    void IdTable::Add(Entry entry) {
        if (this->table.size() <= this->maxsize) {
            this->table.push_back(entry);
        } else {
            throw ERROR_THROW(114);
        }
    }

    Entry IdTable::GetEntry(int n) {
        return this->table[n];
    }

    int  IdTable::IsId(char id[ID_MAXSIZE]) {
        for (int i = 0; i < this->table.size(); i++) {
            if (strcmp(this->table[i].id, id) == 0) {
                return i;
            }
        }
        return IT_NULLIDX;
    }

    void IdTable::Delete() {
        this->table.clear();
    }
}
