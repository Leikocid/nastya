#include "Error.h"
#include "Utils.h"

using namespace Utils;

namespace Error {
    // серии ошибок:   0 - 19  - системные ошибки
    //               100 - 109 - ошибки параметров
    //               110 - 119 - ошибки открытия и чтения файлов
    //               200 - 299 - ошибки лексического разбора
    //               600 - 699 - ошибки синтаксического разбора
    //               700 - 799 - ошибки семантического разбора

    // таблица определенных ошибок
    ERROR errors[] = {
        ERROR_ENTRY( -1, "Неопределенная ошибка"),
        ERROR_ENTRY(  0, "Недопустимый код ошибки"),
        ERROR_ENTRY(  1, "Системный сбой"),

        ERROR_ENTRY(100, "Параметр -іп должен быть задан"),
        ERROR_ENTRY(104, "Превышена максимальная длинна строки параметра"),
        ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом (-іn)"),
        ERROR_ENTRY(111, "Недопустимый символ в исходном файле (-іn)"),
        ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log)"),
        ERROR_ENTRY(113, "Ошибка при создании файла результата (-out)"),

        ERROR_ENTRY(220, "Недопустимый синтаксис"),
        ERROR_ENTRY(221, "Превышен максимальный размер таблицы лексем"),
        ERROR_ENTRY(222, "Превышен максимальный размер таблицы идентификаторов"),
        ERROR_ENTRY(223, "Отсутствует закрывающаяся кавычка"),
        ERROR_ENTRY(224, "Недопустимый номер возвращаемой строки таблицы лексем"),
        ERROR_ENTRY(225, "Недопустимый номер возвращаемой строки таблицы идентификаторов"),
        ERROR_ENTRY(226, "Открывающихся скобок \'{\' больше чем закрывающихся \'}\'"),
        ERROR_ENTRY(227, "Для закрывающейся скобки \'}\' не найдена открывающаяся"),
        ERROR_ENTRY(228, "Ключевое слово main встретилось в неположенном месте"),
        ERROR_ENTRY(229, "Превышена максимальная длинна идентификатора"),
        ERROR_ENTRY(230, "Не определен тип данных для индентификатора либо идентификатор не объявлен"),
        ERROR_ENTRY(231, "Переопределение идентификатора"),
        ERROR_ENTRY(232, "Функция main объявляется во второй раз"),
        ERROR_ENTRY(233, "Объявление функции внутри функции недопустимо"),
        ERROR_ENTRY(234, "Размер длины строки превышен (255)"),
        ERROR_ENTRY(235, "Превышено максимальное значение целочисленного литерала"),

        ERROR_ENTRY(600, "Неверная структура программы"),
        ERROR_ENTRY(601, "Ошибочный оператор"),
        ERROR_ENTRY(602, "Ошибка в выражении"),
        ERROR_ENTRY(603, "Ошибка в параметрах функции"),
        ERROR_ENTRY(604, "Ошибка в параметрах вызываемой функции"),
        ERROR_ENTRY(605, "Ошибка в условии ветвления или цикла"),

        ERROR_ENTRY(700, "Не совпадают типы данных в выражении"),
        ERROR_ENTRY(701, "Не совпадают типы сравниваемых значений"),
        ERROR_ENTRY(702, "Переменной присваивается значение неверного типа"),
        ERROR_ENTRY(703, "Тип передаваемых данных не совпадает с типом данных для вызываемой функции"),
        ERROR_ENTRY(704, "Тип возвращаемых из функции данных не соответсвует описанию функции"),
        ERROR_ENTRY(705, "Библиотечная функция c указанными параметрами не найдена"),
        ERROR_ENTRY(706, "Ошибка синтаксиса в выражении")
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
