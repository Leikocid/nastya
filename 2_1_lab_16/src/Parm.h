#ifndef PARAM_H
#define PARAM_H

#define PARM_IN L"-in:"              // ключ для файла исходного кода
#define PARM_OUT L"-out:"            // ключ для файла объектного кода
#define PARM_LOG L"-log:"            // ключ для файла журнала
#define PARM_MAX_SIZE 300            // максимальная длинна строки параметра
#define PARM_OUT_DEFAULT_EXT L".out" // расширение файла объектного кода по умолчанию
#define PARM_LOG_DEFAULT_EXT L".log" // расширение файла протокола по умолчанию

// обработка входных параметров
namespace Parm {
    // входные параметры
    struct PARM {
        wchar_t in[PARM_MAX_SIZE];      // -in: имя файла исходного кода
        wchar_t out[PARM_MAX_SIZE + 4]; // -out: имя файла объектного кода
        wchar_t log[PARM_MAX_SIZE + 4]; // -log: имя файла протокола
        bool	logToConsole;
    };

    PARM getparm(int argc, char* argv[]); // сфрмировать struct РАRM на основе параметров функции main
}

#endif // !PARAM_H
