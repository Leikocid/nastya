#include "CILGenerator.h"
#include "Utils.h"
#include "Out.h"

using namespace std;
using namespace Utils;
using namespace GR;
using namespace Out;

namespace CG {
    int labelId = 1; // счетчик для генерирования меток перехода кода

    // запись типа данных
    void writeDataType(TranslationContext &ctx, DATATYPE datatype) {
        switch (datatype) {
            case DT_INT: {
                *ctx.result << "int32";
                break;
            };
            case DT_STR: {
                *ctx.result << "string";
                break;
            };
            case DT_UNKNOWN: {
                *ctx.result << "object";
                break;
            };
        }
    }

    // запись выражения: делаем notationSize шагов. идентификаторы и литералы просто ложим в стек, операнды записываем как есть
    void writeEquation(TranslationContext &ctx, ParseTreeNode* node) {
        for (int i = node->lentaPosition; i < node->lentaPosition + node->notationSize; i++) {
            char lexema = ctx.lexTable.table[i].lexema;
            switch (lexema) {
                case LEX_ID: {
                    // загрузка в стек аргумента или локальной переменной
                    int idIndex = ctx.lexTable.table[i].idxTI;
                    if (ctx.idTable.table[idIndex].idtype == T_P) {
                        *ctx.result << "\tldarg ";
                    } else {
                        *ctx.result << "\tldloc ";
                    }
                    *ctx.result << ctx.idTable.table[idIndex].name << "\n";
                    break;
                }
                case LEX_LITERAL: {
                    // загрузка в стек константы
                    int idIndex = ctx.lexTable.table[i].idxTI;
                    if (ctx.idTable.table[idIndex].datatype == DT_STR) {
                        *ctx.result << "\tldstr \"" << ctx.idTable.table[idIndex].value.vstr.str << "\"\n";
                    } else {
                        *ctx.result << "\tldc.i4 " <<  ctx.idTable.table[idIndex].value.vint << "\n";
                    }
                    break;
                }
                case LEX_FUNCTION_REF: {
                    // генерирование вызова функции
                    int idIndex = ctx.lexTable.table[i].idxTI;
                    if (strcmp("strlen", ctx.idTable.table[idIndex].name) == 0) {
                        *ctx.result << "\tcallvirt instance int32 string::get_Length()\n";
                    } else {
                        *ctx.result << "\tcall ";
                        writeDataType(ctx, ctx.idTable.table[idIndex].datatype);
                        *ctx.result << " " << ctx.idTable.table[idIndex].name << "(";
                        int i = 1;
                        while (ctx.idTable.table[idIndex + i].idtype == T_P) {
                            if (i > 1) {
                                *ctx.result << ", ";
                            }
                            writeDataType(ctx, ctx.idTable.table[idIndex + i].datatype);
                            i++;
                        }
                        *ctx.result << ")\n";
                    }
                    break;
                }

                // метематические операнды
                case LEX_PLUS: {
                    *ctx.result << "\tadd\n";
                    break;
                }
                case LEX_MINUS: {
                    *ctx.result << "\tsub\n";
                    break;
                }
                case LEX_STAR: {
                    *ctx.result << "\tmul\n";
                    break;
                }
                case LEX_DIRSLASH: {
                    *ctx.result << "\tdiv\n";
                    break;
                }
            }
        }
    }

    // запись команджы условного перехода. в стек добавляются два значения (результаты двух выражений) и дальше записываем условный переход
    void writeCompairing(TranslationContext &ctx, ParseTreeNode* node) {
        writeEquation(ctx, node->child[0]);
        writeEquation(ctx, node->child[1]->child[0]);

        char firstSymbol = symbolToChar(node->child[1]->chain->symbols[0]);
        switch (firstSymbol) {
            case '<': {
                if (symbolToChar(node->child[1]->chain->symbols[1] == '=')) {
                    *ctx.result << "\tble.s "; // <=
                } else {
                    *ctx.result << "\tblt.s "; // <
                }
                break;
            }
            case '>': {
                if (symbolToChar(node->child[1]->chain->symbols[1] == '=')) {
                    *ctx.result << "\tbge.s "; // >=
                } else {
                    *ctx.result << "\tbgt.s "; // >
                }
                break;
            }
            case '=': {
                *ctx.result << "\tbeq.s "; // ==
                break;
            }
            case '!': {
                *ctx.result << "\tceq"; // !=
                *ctx.result << "\tbrtrue.s";
                break;
            }
        }
    }

    // обработка узла из дерева разбора
    void writeNode(TranslationContext &ctx, ParseTreeNode* node) {
        switch (symbolToChar(node->rule->ruleSymbol)) {
            case 'S': {
                char firstSymbol = symbolToChar(node->chain->symbols[0]);
                if (firstSymbol == 'f') {
                    // fi(F):t{NrE;};S - запись функции программы
                    *ctx.result << ".method private static ";
                    int idIndex = ctx.lexTable.table[node->lentaPosition + 1].idxTI;
                    writeDataType(ctx, ctx.idTable.table[idIndex].datatype);
                    *ctx.result << " " << ctx.idTable.table[idIndex].name << "(";
                    writeNode(ctx, node->child[0]); // F- парметры
                    *ctx.result << ") cil managed {\n\t.maxstack 100\n";
                    writeNode(ctx, node->child[1]); // N - тело
                    writeNode(ctx, node->child[2]); // E - положить возвращяемое значение на вершину стека
                    *ctx.result << "\tret\n}\n";
                    writeNode(ctx, node->child[3]); // S
                } else {
                    // m{N}; - секция main
                    *ctx.result << ".method private static void main() cil managed {\n\t.entrypoint\n\t.maxstack 100\n";
                    writeNode(ctx, node->child[0]); // N - тело
                    *ctx.result << "\tret\n}\n";
                }
                break;
            }
            case 'N': {
                char firstSymbol = symbolToChar(node->chain->symbols[0]);
                switch (firstSymbol) {
                    case 'c': {
                        // c[EC]{N}; | c[EC]{N};N | c[EC]{N}e{N}; | c[EC]{N}e{N};N - запись ветвления кода
                        int labelOk   = (++labelId);
                        int labelExit = (++labelId);
                        writeCompairing(ctx, node);
                        *ctx.result << " LAB_" << labelOk << "\n";

                        int postIndex = 3;
                        if (symbolToChar(node->chain->symbols[8]) == 'e') {
                            writeNode(ctx, node->child[3]);
                            postIndex = 4;
                        }
                        *ctx.result << "\tbr.s " << "LAB_" << labelExit << "\n";
                        *ctx.result << "LAB_" << labelOk << ": nop\n";
                        writeNode(ctx, node->child[2]);
                        *ctx.result << "LAB_" << labelExit << ": nop\n";

                        // обработка последнего нетерминала N, если он есть
                        if (node->child.size() > postIndex) {
                            writeNode(ctx, node->child[postIndex]);
                        }
                        break;
                    };
                    case 'w': {
                        // w[EC]{N}; | w[EC]{N};N - запись циклв
                        int labelStart = (++labelId);
                        int labelOk    = (++labelId);
                        int labelExit  = (++labelId);
                        *ctx.result << "LAB_" << labelStart << ": nop\n";

                        writeCompairing(ctx, node);
                        *ctx.result << " LAB_" << labelOk << "\n";

                        *ctx.result << "\tbr.s " << "LAB_" << labelExit << "\n";
                        *ctx.result << "LAB_" << labelOk << ": nop\n";
                        writeNode(ctx, node->child[2]);
                        *ctx.result << "\tbr.s " << "LAB_" << labelStart << "\n";
                        *ctx.result << "LAB_" << labelExit << ": nop\n";

                        // обработка последнего нетерминала N, если он есть
                        if (node->child.size() > 3) {
                            writeNode(ctx, node->child[3]);
                        }
                        break;
                    };
                    case 'o': {
                        // oE;N | oE; - запись вывода в консоль
                        writeEquation(ctx, node->child[0]);
                        *ctx.result << "\tcall void [mscorlib]System.Console::WriteLine(";
                        writeDataType(ctx, node->child[0]->datatype);
                        *ctx.result << ")\n";

                        if (node->child.size() > 1) {
                            writeNode(ctx, node->child[1]);
                        }
                        break;
                    };
                    case 'u': {
                        // ufi(F):t;N | ufi(F):t;
                        if (node->child.size() > 1) {
                            writeNode(ctx, node->child[1]);
                        }
                        break;
                    };
                    case 'v': {
                        // vi:t;N | vi:t=E;N | vi:t; | vi:t=E; - запись заведения локальных переменных
                        *ctx.result << "\t.locals init(";
                        int idIndex = ctx.lexTable.table[node->lentaPosition + 1].idxTI;
                        writeDataType(ctx, ctx.idTable.table[idIndex].datatype);
                        *ctx.result << " " << ctx.idTable.table[idIndex].name << ")\n";

                        if (node->child.size() > 0) {
                            if (symbolToChar(node->child[0]->rule->ruleSymbol) == 'E') {
                                writeNode(ctx, node->child[0]);     // E - вычисление знечения
                                *ctx.result << "\tstloc " << ctx.idTable.table[idIndex].name << "\n";
                                if (node->child.size() > 1) {
                                    writeNode(ctx, node->child[1]); // N
                                }
                            } else {
                                writeNode(ctx, node->child[0]);     // N
                            }
                        }
                        break;
                    };
                    default: {
                        // i=E;N | i=E; - запись присвоения значения переенной (через стек)
                        int idIndex = ctx.lexTable.table[node->lentaPosition].idxTI;
                        writeNode(ctx, node->child[0]); // E - тут значение будет загружено в стек

                        *ctx.result << "\tst";          // забираем значение из стека
                        if (ctx.idTable.table[idIndex].idtype == T_P) {
                            *ctx.result << "arg";
                        } else {
                            *ctx.result << "loc";
                        }
                        *ctx.result << " " << ctx.idTable.table[idIndex].name << "\n";

                        // обработка последнего нетерминала N, если он есть
                        if (node->child.size() > 1) {
                            writeNode(ctx, node->child[1]); // N
                        }
                    }
                }
                break;
            }
            case 'E': {
                writeEquation(ctx, node);
                break;
            }
            case 'F': {
                // i:t | i:t,F - запись переметра функции
                int idIndex = ctx.lexTable.table[node->lentaPosition].idxTI;
                writeDataType(ctx, ctx.idTable.table[idIndex].datatype);
                *ctx.result << " " << ctx.idTable.table[idIndex].name;
                if (node->child.size() > 0) {
                    *ctx.result << ", ";
                    writeNode(ctx, node->child[0]); // F - следующий параметр
                }
                break;
            }
        }
    }

    void generate(TranslationContext &ctx) {
        *ctx.logger << "\nГенерирование кода:" << endl;

        ctx.result = createOut(ctx.params);
        *ctx.result << START_TEMPLATE;
        writeNode(ctx, ctx.parseTree);
        *ctx.result << END_TEMPLATE;
        ctx.result->close();

        *ctx.logger << "\nГенерирование кода выполнено успешно." << endl;
    }
}
