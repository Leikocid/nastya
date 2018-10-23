#ifndef IN_H
#define IN_H

#include "string.h"

#define IN_MAX_LEN_TEXT 1024 * 1024 // максимальный размер исходного кода = 1МВ
#define IN_CODE_ENDL '\n'           // символ конца строки

// таблица проверки входной информации, индекс = код (windows-1251) символа
// значения IN::F - заперщенный символ, IN::T - разрешенный символ, IN::I -игнорировать (не вводить),
// если 0 <= значение ‹ 256 - то вводится данное значение

// перенос строки - ращрешен; спецсимволы - запрещены; все символы, цифры, буквы и знаки - разрешены
#define IN_CODE_TABLE {                                                                                                                 \
        /* 0 */ IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, /*   */ IN::F, IN::F, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, \
        /* 1 */ IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, /*   */ IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
        /* 2 */ IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, /*   */ IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
        /* 3 */ IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, /*   */ IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
        /* 4 */ IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, /*   */ IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
        /* 5 */ IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, /*   */ IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
        /* 6 */ IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, /*   */ IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
        /* 7 */ IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, /*   */ IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::F, \
                                                                                                                                        \
        /* 8 */ IN::F, IN::F, IN::F, IN::F, IN::T, IN::T, IN::F, IN::F, /*   */ IN::T, IN::T, IN::F, IN::T, IN::F, IN::F, IN::F, IN::F, \
        /* 9 */ IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, /*   */ IN::T, IN::T, IN::F, IN::T, IN::F, IN::F, IN::F, IN::F, \
        /* A */ IN::F, IN::T, IN::T, IN::F, IN::F, IN::F, IN::F, IN::T, /*   */ IN::T, IN::T, IN::T, IN::T, IN::F, IN::F, IN::T, IN::F, \
        /* B */ IN::T, IN::T, IN::T, IN::T, IN::F, IN::F, IN::T, IN::T, /*   */ IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::F, \
        /* C */ IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, /*   */ IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
        /* D */ IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, /*   */ IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
        /* E */ IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, /*   */ IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
        /* F */ IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, /*   */ IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T  \
}

namespace In {
    // исходные данные
    struct IN {
        // Т - допустимый символ, F - недопустимый, I - игнорировать, иначе заменить
        enum {
            T = 1024,
            F = 2048,
            I = 4096
        };
        int	       size;      // размер исходного кода
        int	       lines;     // количество строк
        int	       ignor;     // количество проигнорированных символов
        unsigned char* text;      // исходный код (Windows - 1251)
        int	       code[256]; // таблица проверки: Т, F, I новое значение

        IN() {
            int code[256] = IN_CODE_TABLE;
            memcpy(this->code, code, 256 * sizeof(int));
            this->text	= new unsigned char[IN_MAX_LEN_TEXT];
            this->size	= 0;
            this->ignor = 0;
        }
    };

    IN getin(wchar_t infile[]); // ввести и проверить входной поток
} // namespace In

#endif // !IN_H
