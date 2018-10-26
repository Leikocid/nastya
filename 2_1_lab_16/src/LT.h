#ifndef LT_H
#define LT_H

#define LT_MAXSIZE      4096       // максимальное количество строк в таблице лексем
#define LT_TI_NULLIDX   0xffffffff // нет элемента в таблице идентификаторов
#define LEX_INTEGER     't'        // лексема для integer
#define LEX_STRING      't'        // лексема для string
#define LEX_ID          'i'        // лексема для идентификатора
#define LEX_LITERAL     'l'        // лексема для литерала
#define LEX_FUNCTION    'f'        // лексема для function
#define LEX_DECLARE     'd'        // лексема для declare
#define LEX_RETURN      'r'        // лексема для return
#define LEX_PRINT       'p'        // лексема для print
#define LEX_SEMICOLON   ';'        // лексема для ;
#define LEX_COMMA       ','        // лексема для ,
#define LEX_LEFTBRACE   '{'        // лексема для {
#define LEX_RIGTHBRACE  '}'        // лексема для }
#define LEX_LEFTHESIS   '('        // лексема для (
#define LEX_RIGHTHESIS  ')'        // лексема для )
#define LEX_PLUS        '+'        // лексема для +
#define LEX_MINUS       '-'        // лексема для -
#define LEX_STAR        '*'        // лексема для *
#define LEX_DIRSLASH    '/'        // лексема для /
#define LEX_COMPARE     '='        // лексема для =
#define LEX_MAIN        'm'        // лексема для main

#include <vector>

// таблица лексем
namespace LT {
    // строка таблицы лексем
    struct Entry {
        char lexema;     //	лексема
        int  lexemaType; // тип лексемы
        int  line;       //	номер строки в исходном тексте
        int  idxTI;      //	индекс в таблице идентификаторов или LT_TI_NULLIDX
    };

    // экземпляр таблицы лексем
    struct LexTable {
        int		   maxsize; // емкость таблицы лексем < LT_MAXSIZE
        std::vector<Entry> table;   // массив строк таблицы лексем

        // добавить строку в таблицу лексем
        void  Add(Entry entry);

        // получить строку таблицы лексем по номеру строки
        Entry GetEntry(int n);

        // удалить таблицу лексем (освободить память)
        void  Delete();
    };

    // создать таблицу лексем (емкость таблицы лексем < LT_MAXSIZE)
    LexTable CreateLexTable(int maxsize);
}

#endif // !LT_H
