/**
 * @brief
 *
 *      Транслятор
 *
 */

#include "TranslationContext.h"
#include "LexicalAnalyzer.h"

// using namespace Out;
using namespace Log;

TranslationContext ctx;

void output_LT(Log::LOG log, LT::LexTable lextable) {
    *log.stream << "\nТаблица лексем:\n";
    for (int i = 0; i < lextable.table.size(); i++) {
        LT::Entry e  = lextable.table[i];
        int prevLine = 0;
        if (i > 0) {
            prevLine = lextable.table[i - 1].line;
        }
        if (e.line != prevLine) {
            for (int l = prevLine + 1; l <= e.line; l++) {
                *log.stream << std::endl;
                if (l < 10) {
                    (*log.stream) << "0";
                }
                (*log.stream) << l << ": ";
            }
        }
        *log.stream << e.lexema;
        if (e.lexema == 'i') {
            *log.stream << "[" << e.idxTI << "]";
        }
    }
    *log.stream << endl;
}

void output_IT(Log::LOG log, IT::IdTable idtable) {
    (*log.stream) << "\nТаблица идентификаторов:\n\n";
    for (int i = 0; i < idtable.table.size(); i++) {
        if (i < 10) {
            *log.stream << "0";
        }
        *log.stream << i << " : ";

        switch (idtable.table[i].iddatatype) {
            case IT::DT_STR: {
                *log.stream << "str";
                break;
            }; case IT::DT_INT: {
                *log.stream << "int";
                break;
            }; case IT::DT_UNKNOWN: {
                *log.stream << "<unknown>";
                break;
            };
        }
        *log.stream << " " << idtable.table[i].id << " [" << idtable.table[i].idxfirstLE << "] ";

        switch (idtable.table[i].idtype) {
            case IT::T_F: {
                break;
            }
            case IT::T_P:
            case IT::T_V:
            case IT::T_L: {
                if (idtable.table[i].iddatatype == IT::DT_STR) {
                    *log.stream << "= <" << idtable.table[i].value.vstr.str << "> lenght = " << (int)idtable.table[i].value.vstr.len;
                } else if (idtable.table[i].iddatatype == IT::DT_INT) {
                    *log.stream << "= <" << (int)idtable.table[i].value.vint << ">";
                }
                break;
            }
        }
        *log.stream << endl;
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "rus");

    try {
        ctx = *(new TranslationContext());

        // разбираем параметры коммандной строки
        ctx.params = Parm::getparm(argc, argv);

        // инициализируем логирование
        ctx.logger = getLog(ctx.params.log);
        logLog(ctx.logger);
        logParm(ctx.logger, ctx.params);

        // считываем входящий файл и проверям на допустимость символов
        ctx.in = getin(ctx.params.in);
        logIn(ctx.logger, ctx.in);

        // строим таблицы лексем и идентификаторов
        LA::lexicalAnalysis(ctx);

        output_LT(ctx.logger, ctx.lexTable);
        output_IT(ctx.logger, ctx.idTable);

        // writeResult(ctx.params.out, ctx.in.text);
    } catch (ERROR e) {
        logError(ctx.logger, e);
    }
    closeLog(ctx.logger);
    return 0;
}
