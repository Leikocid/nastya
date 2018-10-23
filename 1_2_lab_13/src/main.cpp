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

        // writeResult(ctx.params.out, ctx.in.text);
    } catch (ERROR e) {
        logError(ctx.logger, e);
    }
    closeLog(ctx.logger);
    return 0;
}
