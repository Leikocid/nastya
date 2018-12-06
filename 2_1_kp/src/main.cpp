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

void showParseTree(GR::ParseTreeNode* node) {
    if (node->child.size() > 0) {
        for (int i = 0; i < node->child.size(); i++) {
            showParseTree(node->child[i]);
        }
        cout << "NODE: " << setw(4) << left << node->lentaPosition << ": " << setw(40) << left
             << info(node->rule->ruleSymbol, node->chain) << endl;
    } else {
        cout << "LIST: " << setw(4) << left << node->lentaPosition << ": " << setw(40) << left
             << info(node->rule->ruleSymbol, node->chain) << endl;
    }


    // TODO: precess node here;
}

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

        SA::SyntaxAnalyzer syntaxAnalyzer(ctx);
        if (syntaxAnalyzer.start()) {
            ctx.parseTree = syntaxAnalyzer.buildParseTree();

            showParseTree(ctx.parseTree);


            // применение польской нотации
            PolishNotation::testPolishNotations(ctx);
        }
        ctx.lexTable.Delete();
        ctx.idTable.Delete();
    }
    catch (ERROR e) {
        ctx.logger->logError(e);
    }
    ctx.logger->closeLog();
    return 0;
}
