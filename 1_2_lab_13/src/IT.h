#ifndef IT_H
#define IT_H

#define ID_MAXSIZE      5         // максимальное количество сиволов в идентификаторе
#define IT_MAXSIZE      4096      // максимальное количество строк в таблице идентификаторов
#define IT_INT_DEFAULT 0x00000000 // значение по умолчанию для типа integer
#define IT_STR_DEFAULT 0x00       // значение по умолчанию для типа string
#define IT_NULLIDX 0xffffffff     // нет элемента в таблице идентификаторов
#define IT_STR_MAXSIZE 255

// таблица идентификаторов
namespace IT {
    // типы данных идентификаторов: integer, string
    enum IDDATATYPE {
        INT = 1, STR = 2
    };

    // типы идентификаторов: переменная, функция, параметр, литерал
    enum IDTYPE {
        V = 1, F = 2, P = 3, L = 3
    };

    // строка таблицы
    struct Entry {
        int	   idxfirstLE;                 // индекс первой строки в таблице лексем
        char	   id[ID_MAXSIZE];             //  идентификатор (автоматически усекается до ID_MAXSIZE)
        IDDATATYPE iddatatype;                 // тип данных
        IDTYPE	   idtype;                     // тип идентикатора
        union {
            int vint;                          // значение integer
            struct {
                char len;                      // количесво символов в string
                char str[IT_STR_MAXSIZE -  1]; // символы string
            } vstr[IT_STR_MAXSIZE];            // значение string
        } value;                               // значение идентификатора
    };

    // экземпляр таблицы идентификаторов
    struct IdTable {
        int    maxsize; // емкость таблицы идентификаторов < TI_MAXSIZE
        int    size;    // текущий размер таблицы идентификаторов < maxsize
        Entry* table;   // массив строк таблицы идентификаторов

        // добавить строку в таблицу идентификаторов
        void Add(
            Entry entry // строка таблицы идентификаторов
            );

        // получить строку таблицы идентификаторов
        Entry GetEntry(
            int п // номер получаемой строки
            );

        // возврат: номер строки (если есть), TI_NULLIDX(ecnH нет)
        int Isld(
            char id[ID_MAXSIZE] // идентификатор
            );

        // удалить таблицу лексем (освободить память)
        void Delete(IdTable &idtable);
    };

    //	создать	таблицу идентификаторов
    IdTable CreateIdTable(
        int size //	емкость	таблицы идентификаторов	< TI_MAXSIZE
        );
}

#endif // !IT_H
