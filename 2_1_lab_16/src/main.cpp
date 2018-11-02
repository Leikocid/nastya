/**
 * @brief
 *
 *      Транслятор
 *
 */

#include "TranslationContext.h"
#include "LexicalAnalyzer.h"
#include "PolishNotation.h"
#include "SyntaxAnalyzer.h"

// using namespace Out;
using namespace Log;
using namespace std;

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

        // синтаксический анализ
        ctx.grammar = GR::getGrammar();

        SA::SyntaxAnalyzer mfst(ctx);
        mfst.start();
        mfst.savededucation(); // сохранить и вывести правила вывода
        mfst.printrules();     // отладка: вывести правила вывода

        // применение польской нотации
        PolishNotation::testPolishNotations(ctx);

        ctx.lexTable.Delete();
        ctx.idTable.Delete();
    } catch (ERROR e) {
        ctx.logger->logError(e);
    }
    ctx.logger->closeLog();
    return 0;
}
