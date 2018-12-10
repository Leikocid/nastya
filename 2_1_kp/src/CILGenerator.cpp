#include "CILGenerator.h"
#include "Utils.h"

// #include <iomanip>

using namespace std;
using namespace Utils;

namespace CG {
    // поток для вывода
    ofstream* out;
    int labelId = 1;

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
                *out << "object";
                break;
            };
        }
    }

    void writeEquation(TranslationContext &ctx, GR::ParseTreeNode* node) {
        for (int i = node->lentaPosition; i < node->lentaPosition + node->notationSize; i++) {
            char lexema = ctx.lexTable.table[i].lexema;

            switch (lexema) {
                case LEX_ID: {
                    int idIndex = ctx.lexTable.table[i].idxTI;
                    if (ctx.idTable.table[idIndex].idtype == T_P) {
                        *out << "\tldarg ";
                    } else {
                        *out << "\tldloc ";
                    }
                    *out << ctx.idTable.table[idIndex].name << "\n";
                    break;
                }
                case LEX_LITERAL: {
                    int idIndex = ctx.lexTable.table[i].idxTI;
                    if (ctx.idTable.table[idIndex].datatype == DT_STR) {
                        *out << "\tldstr \"" << ctx.idTable.table[idIndex].value.vstr.str << "\"\n";
                    } else {
                        *out << "\tldc.i4 " <<  ctx.idTable.table[idIndex].value.vint << "\n";
                    }
                    break;
                }
                case LEX_FUNCTION_REF: {
                    int idIndex = ctx.lexTable.table[i].idxTI;
                    if (strcmp("strlen", ctx.idTable.table[idIndex].name) == 0) {
                        *out << "\tcallvirt instance int32 string::get_Length()\n";
                    } else {
                        *out << "\tcall ";
                        writeDataType(ctx.idTable.table[idIndex].datatype);
                        *out << " " << ctx.idTable.table[idIndex].name << "(";
                        int i = 1;
                        while (ctx.idTable.table[idIndex + i].idtype == T_P) {
                            if (i > 1) {
                                *out << ", ";
                            }
                            writeDataType(ctx.idTable.table[idIndex + i].datatype);
                            i++;
                        }
                        *out << ")\n";
                    }
                    break;
                }
                case LEX_PLUS: {
                    *out << "\tadd\n";
                    break;
                }
                case LEX_MINUS: {
                    *out << "\tsub\n";
                    break;
                }
                case LEX_STAR: {
                    *out << "\tmul\n";
                    break;
                }
                case LEX_DIRSLASH: {
                    *out << "\tdiv\n";
                    break;
                }
            }
        }
    }

    void writeCompairing(TranslationContext &ctx, GR::ParseTreeNode* node) {
        writeEquation(ctx, node->child[0]);
        writeEquation(ctx, node->child[1]->child[0]);
        char firstSymbol = GR::symbolToChar(node->child[1]->chain->symbols[0]);

        switch (firstSymbol) {
            case '<': {
                if (GR::symbolToChar(node->child[1]->chain->symbols[1] == '=')) {
                    *out << "\tble.s ";
                } else {
                    *out << "\tblt.s ";
                }
                break;
            };
            case '>': {
                if (GR::symbolToChar(node->child[1]->chain->symbols[1] == '=')) {
                    *out << "\tbge.s ";
                } else {
                    *out << "\tbgt.s ";
                }
                break;
            };
            case '=': {
                *out << "\tbeq.s ";
                break;
            };
            case '!': {
                *out << "\tceq";
                *out << "\tbrtrue.s";
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
                    *out << ") cil managed {\n\t.maxstack 100\n";
                    processNode(ctx, node->child[1]); // N - тело
                    processNode(ctx, node->child[2]); // E - положить возвращяемое значение на вершину стека
                    *out << "\tret\n}\n";
                    processNode(ctx, node->child[3]); // S
                } else {
                    // main m{N};
                    *out << ".method private static void main() cil managed {\n\t.entrypoint\n\t.maxstack 100\n";
                    processNode(ctx, node->child[0]); // N - тело
                    *out << "\tret\n}\n";
                }
                break;
            }
            case 'N': {
                char firstSymbol = GR::symbolToChar(node->chain->symbols[0]);

                switch (firstSymbol) {
                    case 'c': {
                        // c[EC]{N}; | c[EC]{N};N | c[EC]{N}e{N}; | c[EC]{N}e{N};N
                        int labelOk   = (++labelId);
                        int labelExit = (++labelId);
                        writeCompairing(ctx, node);
                        *out << " LAB_" << labelOk << "\n";
                        int postIndex = 3;
                        if (GR::symbolToChar(node->chain->symbols[8]) == 'e') {
                            processNode(ctx, node->child[3]);
                            postIndex = 4;
                        }
                        *out << "\tbr.s " << "LAB_" << labelExit << "\n";
                        *out << "LAB_" << labelOk << ": nop\n";
                        processNode(ctx, node->child[2]);
                        *out << "LAB_" << labelExit << ": nop\n";
                        if (node->child.size() > postIndex) {
                            processNode(ctx, node->child[postIndex]);
                        }
                        break;
                    };
                    case 'w': {
                        // w[EC]{N}; | w[EC]{N};N
                        int labelStart = (++labelId);
                        int labelOk    = (++labelId);
                        int labelExit  = (++labelId);
                        *out << "LAB_" << labelStart << ": nop\n";
                        writeCompairing(ctx, node);
                        *out << " LAB_" << labelOk << "\n";
                        *out << "\tbr.s " << "LAB_" << labelExit << "\n";
                        *out << "LAB_" << labelOk << ": nop\n";
                        processNode(ctx, node->child[2]);
                        *out << "\tbr.s " << "LAB_" << labelStart << "\n";
                        *out << "LAB_" << labelExit << ": nop\n";
                        if (node->child.size() > 3) {
                            processNode(ctx, node->child[3]);
                        }
                        break;
                    };
                    case 'o': {
                        // oE;N | oE;
                        writeEquation(ctx, node->child[0]);
                        *out << "\tcall void [mscorlib]System.Console::WriteLine(";
                        writeDataType(node->child[0]->datatype);
                        *out << ")\n";
                        if (node->child.size() > 1) {
                            processNode(ctx, node->child[1]);
                        }
                        break;
                    };
                    case 'u': {
                        // ufi(F):t;N | ufi(F):t;
                        if (node->child.size() > 1) {
                            processNode(ctx, node->child[1]);
                        }
                        break;
                    };
                    case 'v': {
                        // vi:t;N | vi:t=E;N | vi:t; | vi:t=E;
                        *out << "\t.locals init(";
                        int idIndex = ctx.lexTable.table[node->lentaPosition + 1].idxTI;
                        writeDataType(ctx.idTable.table[idIndex].datatype);
                        *out << " " << ctx.idTable.table[idIndex].name << ")\n";
                        if (node->child.size() > 0) {
                            if (GR::symbolToChar(node->child[0]->rule->ruleSymbol) == 'E') {
                                processNode(ctx, node->child[0]);     // E - в��чис��ени�� знечения
                                *out << "\tstloc " << ctx.idTable.table[idIndex].name << "\n";
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
                                *out << "\tcallvirt instance int32 string::get_Length()";
                            } else {
                                *out << "\tcall ";
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
                            int idIndex = ctx.lexTable.table[node->lentaPosition].idxTI;
                            processNode(ctx, node->child[0]); // E - calculate
                            *out << "\tst";
                            if (ctx.idTable.table[idIndex].idtype == T_P) {
                                *out << "arg";
                            } else {
                                *out << "loc";
                            }
                            *out << " " << ctx.idTable.table[idIndex].name << "\n";
                        }
                        if (node->child.size() > 1) {
                            processNode(ctx, node->child[1]); // N
                        }
                    }
                }
                break;
            }
            case 'E': {
                writeEquation(ctx, node);
                break;
            }
            case 'M': {
                break;
            }
            case 'F': {
                // i:t | i:t,F
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
                writeEquation(ctx, node);
                if (GR::symbolToChar(node->child[node->child.size() - 1]->rule->ruleSymbol) == 'W') {
                    *out << ", " << node->notationSize;
                    processNode(ctx, node->child[node->child.size() - 1]); // W
                }
                break;
            }
            case 'C': {
                // <E | >E | <=E | >=E | ==E | !=E
                break;
            }
        }
    }

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
