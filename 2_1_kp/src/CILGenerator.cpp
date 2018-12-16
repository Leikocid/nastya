#include "CILGenerator.h"
#include "Utils.h"
#include "Out.h"

#define lexems ctx.lexTable.table
#define ids ctx.idTable.table
#define res *ctx.result

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
                res << "int32";
                break;
            };
            case DT_STR: {
                res << "string";
                break;
            };
            case DT_UNKNOWN: {
                res << "object";
                break;
            };
        }
    }

    // запись выражения: делаем notationSize шагов. идентификаторы и литералы просто ложим в стек, операнды записываем как есть
    void writeEquation(TranslationContext &ctx, ParseTreeNode* node) {
        for (int i = node->lentaPosition; i < node->lentaPosition + node->notationSize; i++) {
            char lexema = lexems[i].lexema;
            switch (lexema) {
                case LEX_ID: {
                    // загрузка в стек аргумента или локальной переменной
                    int idIndex = lexems[i].idxTI;
                    if (ids[idIndex].idtype == T_P) {
                        res << "\tldarg ";
                    } else {
                        res << "\tldloc ";
                    }
                    res << ids[idIndex].name << "\n";
                    break;
                }
                case LEX_LITERAL: {
                    // загрузка в стек константы
                    int idIndex = lexems[i].idxTI;
                    if (ids[idIndex].datatype == DT_STR) {
                        res << "\tldstr \"" << ids[idIndex].value.vstr.str << "\"\n";
                    } else {
                        res << "\tldc.i4 " <<  ids[idIndex].value.vint << "\n";
                    }
                    break;
                }
                case LEX_FUNCTION_REF: {
                    // генерирование вызова функции
                    int idIndex = lexems[i].idxTI;
                    if (strcmp("strlen", ids[idIndex].name) == 0) {
                        res << "\tcallvirt instance int32 string::get_Length()\n";
                    } else {
                        res << "\tcall ";
                        writeDataType(ctx, ids[idIndex].datatype);
                        res << " " << ids[idIndex].name << "(";
                        int n = 1;
                        while (ids[idIndex + n].idtype == T_P) {
                            if (n > 1) {
                                res << ", ";
                            }
                            writeDataType(ctx, ids[idIndex + n].datatype);
                            n++;
                        }
                        res << ")\n";
                    }
                    break;
                }

                // метематические операнды
                case LEX_PLUS: {
                    res << "\tadd\n";
                    break;
                }
                case LEX_MINUS: {
                    res << "\tsub\n";
                    break;
                }
                case LEX_STAR: {
                    res << "\tmul\n";
                    break;
                }
                case LEX_DIRSLASH: {
                    res << "\tdiv\n";
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
                    res << "\tble.s "; // <=
                } else {
                    res << "\tblt.s "; // <
                }
                break;
            }
            case '>': {
                if (symbolToChar(node->child[1]->chain->symbols[1] == '=')) {
                    res << "\tbge.s "; // >=
                } else {
                    res << "\tbgt.s "; // >
                }
                break;
            }
            case '=': {
                res << "\tbeq.s "; // ==
                break;
            }
            case '!': {
                res << "\tceq"; // !=
                res << "\tbrtrue.s";
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
                    res << ".method private static ";
                    int idIndex = lexems[node->lentaPosition + 1].idxTI;
                    writeDataType(ctx, ids[idIndex].datatype);
                    res << " " << ids[idIndex].name << "(";
                    writeNode(ctx, node->child[0]); // F- парметры
                    res << ") cil managed {\n\t.maxstack 100\n";
                    writeNode(ctx, node->child[1]); // N - тело
                    writeNode(ctx, node->child[2]); // E - положить возвращяемое значение на вершину стека
                    res << "\tret\n}\n";
                    writeNode(ctx, node->child[3]); // S
                } else {
                    // m{N}; - секция main
                    res << ".method private static void main() cil managed {\n\t.entrypoint\n\t.maxstack 100\n";
                    writeNode(ctx, node->child[0]); // N - тело
                    res << "\tret\n}\n";
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
                        res << " LAB_" << labelOk << "\n";

                        int postIndex = 3;
                        if (symbolToChar(node->chain->symbols[8]) == 'e') {
                            writeNode(ctx, node->child[3]);
                            postIndex = 4;
                        }
                        res << "\tbr.s " << "LAB_" << labelExit << "\n";
                        res << "LAB_" << labelOk << ": nop\n";
                        writeNode(ctx, node->child[2]);
                        res << "LAB_" << labelExit << ": nop\n";

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
                        res << "LAB_" << labelStart << ": nop\n";

                        writeCompairing(ctx, node);
                        res << " LAB_" << labelOk << "\n";

                        res << "\tbr.s " << "LAB_" << labelExit << "\n";
                        res << "LAB_" << labelOk << ": nop\n";
                        writeNode(ctx, node->child[2]);
                        res << "\tbr.s " << "LAB_" << labelStart << "\n";
                        res << "LAB_" << labelExit << ": nop\n";

                        // обработка последнего нетерминала N, если он есть
                        if (node->child.size() > 3) {
                            writeNode(ctx, node->child[3]);
                        }
                        break;
                    };
                    case 'o': {
                        // oE;N | oE; - запись вывода в консоль
                        writeEquation(ctx, node->child[0]);
                        res << "\tcall void [mscorlib]System.Console::WriteLine(";
                        writeDataType(ctx, node->child[0]->datatype);
                        res << ")\n";

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
                        res << "\t.locals init(";
                        int idIndex = lexems[node->lentaPosition + 1].idxTI;
                        writeDataType(ctx, ids[idIndex].datatype);
                        res << " " << ids[idIndex].name << ")\n";

                        if (node->child.size() > 0) {
                            if (symbolToChar(node->child[0]->rule->ruleSymbol) == 'E') {
                                writeNode(ctx, node->child[0]);     // E - вычисление знечения
                                res << "\tstloc " << ids[idIndex].name << "\n";
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
                        int idIndex = lexems[node->lentaPosition].idxTI;
                        writeNode(ctx, node->child[0]); // E - тут значение будет загружено в стек

                        res << "\tst";                  // забираем значение из стека
                        if (ids[idIndex].idtype == T_P) {
                            res << "arg";
                        } else {
                            res << "loc";
                        }
                        res << " " << ids[idIndex].name << "\n";

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
                int idIndex = lexems[node->lentaPosition].idxTI;
                writeDataType(ctx, ids[idIndex].datatype);
                res << " " << ids[idIndex].name;
                if (node->child.size() > 0) {
                    res << ", ";
                    writeNode(ctx, node->child[0]); // F - следующий параметр
                }
                break;
            }
        }
    }

    void generate(TranslationContext &ctx) {
        *ctx.logger << "\nГенерирование кода:" << endl;

        ctx.result = createOut(ctx.params);
        res << START_TEMPLATE;
        writeNode(ctx, ctx.parseTree);
        res << END_TEMPLATE;
        ctx.result->close();

        *ctx.logger << "\nГенерирование кода выполнено успешно." << endl;
    }
}
