#ifndef ERROR_H
#define ERROR_H

#define ERROR_THROW(id) Error::geterror(id);                  // throw ERROR_THROW(id)
#define ERROR_THROW_IN(id, l, c) Error::geterrorin(id, l, c); // throw ERROR_THROW_IN(id, строка, колонка)
#define ERROR_ENTRY(id, m) { id, m, false, { -1, -1 } }       // элемент таблицы ошибок
#define ERROR_MAXSIZE_MESSAGE 200                             // максимальная длина сообщения об ошибке
#define ERROR_UNDEFINED_INDEX 0                               // текст сообщения для неопределенной ошибки
#define ERROR_MAX_ID 1000                                     // максимальный идентификатор

namespace Error {
    // тип исключения для throw ERROR_THRON lERROR_THRON_IN и catch(ERROR)
    struct ERROR {
        int  id;                                 // код ошибки
        char message[ERROR_MAXSIZE_MESSAGE];     // сообщение об ошибке
        bool hasInext;
        struct IN {                              // расширение для ошибок при обработке входных данных
            short line;                          // номер строки (0, 1, 2,
            short col;
        } inext;                                 // номер позиции в строке (0, 1, 2,
    };

    ERROR geterror(int id);                      // сформировать ERROR для ERROR_THROW
    ERROR geterrorin(int id, int line, int col); // сформировать ERROR для ERROR_THROW_IN
}  // namespace Error

#endif // ERROR_H
