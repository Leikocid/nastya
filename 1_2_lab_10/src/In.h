#ifndef IN_H
#define IN_H

#define IN_MAX_LEN_TEXT 1024 * 1024 // максимальный размер исходного кода = 1МВ
#define IN_CODE_ENDL '\n'           // символ конца строки
// таблица проверки входной информации, индекс = код (windows-1251) символа
// значения IN::F - заперщенный символ, IN::T - разрешенный символ, IN::I -игнорировать (не вводить),
// если 0 <= значение ‹ 256 - то вводится данное значение
#define IN_CODE_TABLE {                                                                                                 \
        IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T, IN::F, IN::F, IN::I, IN::F, IN::F, \
        IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
        IN::T, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
        IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
        IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
        IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T, IN::I, '!',   IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
        IN::F, IN::F, IN::F, IN::F, IN::T, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T, IN::F, IN::F, IN::T, \
        IN::F, IN::F, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
                                                                                                                        \
        IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
        IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
        IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
        IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
        IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T, IN::F, IN::F, IN::T, \
        IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
        IN::F, IN::F, IN::T, IN::F, IN::F, IN::T, IN::F, IN::F, IN::T, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
        IN::T, IN::F, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F  \
}

#define IN_CODE_TABLE_ASTAKHOVA {                                                                                                              \
        IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T, IN::F, IN::F, IN::T, IN::F, IN::F,                        \
        IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,                        \
        IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,                        \
        IN::F, IN::T /*1*/, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T /*9*/, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,            \
        IN::F, IN::T /*A*/, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,                  \
        IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::I /*X*/, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,                  \
        IN::F, IN::T /*a*/, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T /*h*/, IN::F, IN::F, IN::T /*k*/, IN::F, IN::F, IN::T /*n*/,       \
        IN::T /*o*/,                                                                                                                           \
        IN::F, IN::F, IN::F, IN::T /*s*/, IN::T /*t*/, IN::F, IN::T /*v*/, IN::F, IN::F, IN::T /*y*/, IN::F, IN::F, IN::F, IN::F, IN::F,       \
        IN::F,                                                                                                                                 \
                                                                                                                                               \
        IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,                        \
        IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,                        \
        IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,                        \
        IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,                        \
        '-' /* А */, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,                  \
        IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,                        \
        IN::T /*а*/, IN::F, IN::T /*в*/, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T /*и*/, IN::F, IN::F, IN::F, IN::F, IN::T /*н*/, IN::T /*о*/, \
        IN::F,                                                                                                                                 \
        IN::F, IN::T /*с*/, IN::T /*т*/, IN::F, IN::F, IN::T /*х*/, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T /*я*/ \
}


namespace In {
    // исходные данные
    struct IN {
        // Т - допустимый символ, F - недопустимый, I - игнорировать, иначе заменить
        enum {
            T = 1024, F = 2048, I = 4096
        };
        int	       size;      // размер исходного кода
        int	       lines;     // количество строк
        int	       ignor;     // количество проигнорированных символов
        unsigned char* text;      // исходный код (Windows - 1251)
        int	       code[256]; // таблица проверки: Т, F, I новое значение
    };

    IN getin(wchar_t infile[]);   // ввести и проверить входной поток
}
#endif // !IN_H
