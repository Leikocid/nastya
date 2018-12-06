#include "SemanticAnalyzer.h"

#include <iomanip>

using namespace std;

namespace SEM {
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

    // семантический анализ
    void semanticAnalysis(TranslationContext ctx) {
        showParseTree(ctx.parseTree);
    }
}
