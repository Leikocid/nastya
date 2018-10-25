#ifndef IT_H
#define IT_H

#define ID_MAXSIZE      5         // максимальное количество сиволов в идентификаторе
#define IT_MAXSIZE      4096      // максимальное количество строк в таблице идентификаторов
#define IT_INT_DEFAULT 0x00000000 // значение по умолчанию для типа integer
#define IT_STR_DEFAULT 0x00       // значение по умолчанию для типа string
#define IT_NULLIDX 0xffffffff     // нет элемента в таблице идентификаторов
#define IT_STR_MAXSIZE 255

#include <vector>

// таблица идентификаторов
namespace IT {
    // типы данных идентификаторов: integer, string
    enum IDDATATYPE {
        DT_UNKNOWN = 0, DT_INT = 1, DT_STR = 2
    };

    // типы идентификаторов: переменная, функция, параметр, литерал
    enum IDTYPE {
        T_V = 1, T_F = 2, T_P = 3, T_L = 4
    };

    // строка таблицы
    struct Entry {
        int	   idxfirstLE;                 // индекс первой строки в таблице лексем
        char	   id[ID_MAXSIZE * 3 + 3];     // резервируем в 3 раза больше места так как может добавляться 2 префикса и разделители (.)
        IDDATATYPE iddatatype;                 // тип данных
        IDTYPE	   idtype;                     // тип идентификатора
        union {
            int vint;                          // значение integer
            struct {
                char len;                      // количество символов в string
                char str[IT_STR_MAXSIZE -  1]; // символы string
            } vstr;                            // значение string
        } value;                               // значение идентификатора
    };

    // экземпляр таблицы идентификаторов
    struct IdTable {
        int		   maxsize; // емкость таблицы идентификаторов < TI_MAXSIZE
        std::vector<Entry> table;   // массив строк таблицы идентификаторов

        // добавить строку в таблицу идентификаторов
        void  Add(Entry entry);

        // получить строку таблицы идентификаторов по номеру
        Entry GetEntry(int п);

        // возврат: номер строки если есть, IT_NULLIDX eсли нет
        int  IsId(char id[ID_MAXSIZE * 3 + 3]);

        // удалить таблицу лексем (освободить память)
        void Delete();
    };

    //	создать	таблицу идентификаторов
    IdTable CreateIdTable(int maxsize);
}

#endif // !IT_H
