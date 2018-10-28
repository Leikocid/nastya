#include "Error.h"
#include "Utils.h"

using namespace Utils;

namespace Error {
    // серии ошибок:   0 - 99  - системные ошибки
    //                20 - 50  - ошибки лексического разбора
    //               100 - 109 - ошибки параметров
    //               110 - 119 - ошибки открытия и чтения файлов

    // таблица определенных ошибок
    ERROR errors[] = {
        ERROR_ENTRY( -1, "Неопределенная ошибка"),
        ERROR_ENTRY(  0, "Недопустимый код ошибки"),
        ERROR_ENTRY(  1, "Системный сбой"),

        ERROR_ENTRY( 20, "Недопустимый синтаксис"),
        ERROR_ENTRY( 21, "Превышен максимальный размер таблицы лексем"),
        ERROR_ENTRY( 22, "Превышен максимальный размер таблицы идентификаторов"),
        ERROR_ENTRY( 23, "Отсутствует закрывающаяся кавычка"),
        ERROR_ENTRY( 24, "Недопустимый номер возвращаемой строки таблицы лексем"),
        ERROR_ENTRY( 25, "Недопустимый номер возвращаемой строки таблицы идентификаторов"),
        ERROR_ENTRY( 26, "Открывающихся скобок \'{\' больше чем закрывающихся \'}\'"),
        ERROR_ENTRY( 27, "Для закрывающейся скобки \'}\' не найдена открывающаяся"),
        ERROR_ENTRY( 28, "Ключевое слово main встретилось в неположенном месте"),
        ERROR_ENTRY( 29, "Превышена максимальная длинна идентификатора"),
        ERROR_ENTRY( 30, "Не определен тип данных для индентификатора либо идентификатор не объявлен"),
        ERROR_ENTRY( 31, "Переопределение идентификатора"),
        ERROR_ENTRY( 32, "Функция main объявляется во второй раз"),
        ERROR_ENTRY( 33, "Объявление функции внутри функции недопустимо"),
        ERROR_ENTRY( 34, "Размер длины строки превышен (256)"),
        ERROR_ENTRY( 35, "Превышено максимальное значение целочисленного литерала"),

        ERROR_ENTRY(100, "Параметр -іп должен быть задан"),
        ERROR_ENTRY(104, "Превышена максимальная длинна строки параметра"),
        ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом (-іn)"),
        ERROR_ENTRY(111, "Недопустимый символ в исходном файле (-іn)"),
        ERROR_ENTRY(112, "Ошибка при создании файла протокола(-log)")
    };

    ERROR geterror(int id) {
        ERROR e = *(new ERROR());
        if ((id > 0) && (id < ERROR_MAX_ID)) {
            e.id = id;
            bool found = false;
            int	 i     = 0;
            while (i < ERROR_MAX_ID - 1 && !found) {
                if (errors[i].id == id) {
                    copyChars(e.message, errors[i].message);
                    found = true;
                }
                i++;
            }
            if (!found) {
                copyChars(e.message, errors[ERROR_UNDEFINED_INDEX].message);
            }
        } else {
            e.id = 0;
        }
        return e;
    }

    ERROR geterrorin(int id, int line = -1, int col = -1) {
        ERROR e = geterror(id);
        e.hasInext   = true;
        e.inext.line = line;
        e.inext.col  = col;
        return e;
    }
}
