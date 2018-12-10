#include "CILGenerator.h"
#include "Utils.h"

// #include <iomanip>

using namespace std;
using namespace Utils;

namespace CG {
    // поток для вывода
    ofstream* out;

    void writeDataType(DATATYPE datatype) {
        switch (datatype) {
            case DT_INT: {
                *out << "int32";
                break;
            };
            case DT_STR: {
                *out << "string";
                break;
            };
            case DT_UNKNOWN: {
                *out << " string";
                break;
            };
        }
    }

    void processNode(TranslationContext &ctx, GR::ParseTreeNode* node) {
        switch (GR::symbolToChar(node->rule->ruleSymbol)) {
            case 'S': {
                char firstSymbol = GR::symbolToChar(node->chain->symbols[0]);
                if (firstSymbol == 'f') {
                    // функция fi(F):t{NrE;};S
                    *out << ".method private static ";
                    int idIndex = ctx.lexTable.table[node->lentaPosition + 1].idxTI;
                    writeDataType(ctx.idTable.table[idIndex].datatype);
                    *out << " " << ctx.idTable.table[idIndex].name << "(";
                    processNode(ctx, node->child[0]); // F- парметры
                    *out << ") cil managed {\n";
                    processNode(ctx, node->child[1]); // N - тело
                    processNode(ctx, node->child[2]); // E - положить возвращяемое значение на вершину стека
                    *out << "ret\n}\n";
                    processNode(ctx, node->child[3]); // S
                } else {
                    // main m{N};
                    *out << ".method private static void main() cil managed {\n.entrypoint\n";
                    processNode(ctx, node->child[0]); // N - тело
                    *out << "ret\n}\n";
                }
                break;
            }
            case 'N': {
                char firstSymbol = GR::symbolToChar(node->chain->symbols[0]);

                switch (firstSymbol) {
                    case 'c': {
                        // c[EC]{N}; | c[EC]{N};N | c[EC]{N}e{N}; | c[EC]{N}e{N};N
                        // TODO:
                        *out << "COND";
                        break;
                    };
                    case 'w': {
                        // w[EC]{N}; | w[EC]{N};N
                        // TODO:

                        *out << "LOOP";
                        break;
                    };
                    case 'o': {
                        // oE;N | oE;
                        // TODO:
                        *out << "OUT";
                        break;
                    };
                    case 'u': {
                        break;
                    };
                    case 'v': {
                        // vi:t;N | vi:t=E;N | vi:t; | vi:t=E;
                        *out << ".locals init(";
                        int idIndex = ctx.lexTable.table[node->lentaPosition + 1].idxTI;
                        writeDataType(ctx.idTable.table[idIndex].datatype);
                        *out << " " << ctx.idTable.table[idIndex].name << ")\n";
                        if (node->child.size() > 0) {
                            if (GR::symbolToChar(node->child[0]->rule->ruleSymbol) == 'E') {
                                processNode(ctx, node->child[0]);     // E - вычисление знечения
                                *out << "stloc " << ctx.idTable.table[idIndex].name << "\n";
                                if (node->child.size() > 1) {
                                    processNode(ctx, node->child[1]); // N
                                }
                            } else {
                                processNode(ctx, node->child[0]);     // N
                            }
                        }
                        break;
                    };
                    default: {
                        if (GR::symbolToChar(node->child[0]->rule->ruleSymbol) == 'W') {
                            // вызов функции  i(W);N | i(W);
                            processNode(ctx, node->child[0]); // W
                            int idIndex = ctx.lexTable.table[node->lentaPosition].idxTI;
                            if (strcmp("strlen", ctx.idTable.table[idIndex].name) == 0) {
                                *out << "callvirt instance int32 string::get_Length()";
                            } else {
                                *out << "call ";
                                writeDataType(ctx.idTable.table[idIndex].datatype);
                                *out << " " << ctx.idTable.table[idIndex].name << "(";
                                int i = 1;
                                while (ctx.idTable.table[idIndex + i].idtype == T_P) {
                                    if (i > 1) {
                                        *out << ", ";
                                    }
                                    writeDataType(ctx.idTable.table[idIndex + i].datatype);
                                }
                                *out << ")\n";
                            }
                        } else {
                            // i=E;N | i=E;
                            int idIndex = ctx.lexTable.table[node->lentaPosition + 1].idxTI;
                            processNode(ctx, node->child[0]); // E - вычисление знечения
                            *out << "stloc " << ctx.idTable.table[idIndex].name << "\n";
                        }
                        if (node->child.size() > 1) {
                            processNode(ctx, node->child[1]); // N
                        }
                    }
                }
                break;
            }
            case 'E': {
                // E -> i | l | (E) | i(W) | iM | lM | (E)M | i(W)M


                // TODO:
                // обработка выражений


                // применение польской нотации и генегирование кода
                // PolishNotation::testPolishNotations(ctx);

                break;
            }
            case 'M': {
                // +E | +EM | -E | -EM | *E | *EM | /E | /EM
                // TODO:
                // обработка выражений

                break;
            }
            case 'F': {
                // параметры i:t | i:t,F
                int idIndex = ctx.lexTable.table[node->lentaPosition].idxTI;
                writeDataType(ctx.idTable.table[idIndex].datatype);
                *out << " " << ctx.idTable.table[idIndex].name;
                if (node->child.size() > 0) {
                    *out << ", ";
                    processNode(ctx, node->child[0]); // F - следующий параметр
                }
                break;
            }
            case 'W': {
                // i | l | i,W | l,W | (E) | i(W) | iM | lM | (E)M | i(W)M | (E),W | i(W),W | iM,W | lM,W | (E)M,W | i(W)M,W
                // TODO:
                // параметр вызова функции
                // обработка выражений
                // применение польской нотации и генегирование кода

                break;
            }
            case 'C': {
                // <E | >E | <=E | >=E | ==E | !=E
                // правая часть в сравнении

                break;
            }
        }
    }

    // семантический анализ
    void  generate(TranslationContext &ctx) {
        *ctx.logger << "\nГенерирование кода:" << endl;

        string fileName = toChars(ctx.params.out);
        out = new ofstream();
        out->open(fileName);
        if (!out->is_open()) {
            throw ERROR_THROW(113);
        }
        *out << START_TEMPLATE;

        processNode(ctx, ctx.parseTree);

        *out << END_TEMPLATE;
        out->close();

        *ctx.logger << "\nГенерирование кода выполнено успешно." << endl;
    }
}
