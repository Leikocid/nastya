/**
 * @brief
 *
 *      Транслятор
 *
 */

#include "TranslationContext.h"
#include "LexicalAnalyzer.h"
#include "PolishNotation.h"

// using namespace Out;
using namespace Log;

TranslationContext ctx;

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "rus");

    try {
        ctx = *new TranslationContext();

        // разбираем параметры коммандной строки
        ctx.params = Parm::getparm(argc, argv);

        // инициализируем логирование
        ctx.logger = getLog(ctx.params);
        ctx.logger->logLog();
        ctx.logger->logParm(ctx.params);

        // считываем входящий файл и проверям на допустимость символов
        ctx.in = getin(ctx.params.in);
        ctx.logger->logIn(ctx.in);

        // строим таблицы лексем и идентификаторов
        LA::lexicalAnalysis(ctx);
        ctx.logger->logLexemTables(ctx.lexTable, ctx.idTable);

        // применение польской нотации
        PolishNotation::testPolishNotations(ctx);

        // syntax analysis
        MFST_TRACE_START
        MFST::Mfst mfst(ctx.lexTable, GRB::getGreibach());
        mfst.start();
        mfst.savededucation();
        mfst.printrules();

        ctx.lexTable.Delete();
        ctx.idTable.Delete();
    } catch (ERROR e) {
        ctx.logger->logError(e);
    }
    ctx.logger->closeLog();
    return 0;
}
