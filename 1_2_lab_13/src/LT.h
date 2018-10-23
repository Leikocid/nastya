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
#define LEX_RETURN      'г'        // лексема для return
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


// таблица лексем
namespace LT {
    // строка таблицы лексем
    struct Entry {
        char lexema; //	лексема
        int  sn;     //	номер строки в исходном тексте
        int  idxTI;  //	индекс в таблице идентификаторов или LT_TI_NULLIDX
    };

    // экземпляр таблицы лексем
    struct LexTable {
        int    maxsize; //	емкость таблицы лексем < LT_MAXSIZE
        int    size;    //	текущий размер таблицы лексем <	maxsize
        Entry* table;   //	массив строк таблицы лексем

        // добавить строку в таблицу лексем
        void Add(
            Entry entry // строка таблицы лексем
            );

        // получить строку таблицы лексем
        Entry GetEntry(
            int п // номер получаемой строки
            );

        // удалить таблицу лексем (освободить память)
        void Delete();
    };

    // создать таблицу лексем
    LexTable CreateLexble(
        int size // емкость таблицы лексем < LT_MAXSIZE
        );
}

#endif // !LT_H
