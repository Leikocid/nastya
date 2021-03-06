/**
 * @brief
 *
 *              Лексический анализатор
 *
 * • проверяет входной поток символов программы на исходном языке на допустимость, удаляет лишние пробелы;
 * • для выбранной части входного потока выполняется функция распознавания лексемы;
 * • при успешном распознавании информация о выделенной лексеме заносится в таблицу лексем и таблицу идентификаторов;
 * • при неуспешном распознавании выдается сообщение об ошибке, а дальнейшее выполнение прекращается
 * • формирует протокол работы;
 *
 */

#include "LexicalAnalyzer.h"
#include "LT.h"
#include "IT.h"
#include "Utils.h"

#include <iostream>

using namespace LT;
using namespace IT;
using namespace Utils;

namespace LA {
    Recognizers RECOGNIZERS = *(new Recognizers());
    string prefixFunction;
    string prefixLibFunction;
    int	   nestingLevel;

    void analyzeFragment(TranslationContext &ctx, const int begin, const int end, const int line, const int col);
    void addLexema(TranslationContext &ctx,
                   const int	      begin,
                   const int	      end,
                   const int	      line,
                   const int	      col,
                   const char	      lexema,
                   const int	      lexemaType);
    bool isTerminalSymbol(const char c);

    // лексический разбор входного файла ctx.in.txt и построение таблиц ctx.lexTable и ctx.idTable
    void lexicalAnalysis(TranslationContext &ctx) {
        // создаем пустые таблицы
        ctx.lexTable	  = CreateLexTable(LT_MAXSIZE);
        ctx.idTable	  = CreateIdTable(IT_MAXSIZE);
        prefixFunction	  = "";
        prefixLibFunction = "";
        nestingLevel	  = 0;

        // разбираем входящий файл по частям
        int  i		     = 0;     // инщекс текущего символа
        int  begin	     = 0;     // индекс начала фрагмента текста
        int  beginStringLine = 0;     // номер строки начала строковаого литерала
        int  beginStringCol  = 0;     // номер колонки начала строковаого литерала
        int  line	     = 1;     // номер текущей строки
        int  col	     = 1;     // номер текущей колонки
        bool stringMode	     = false; // это специальный режим когда мы ждем только закрывающейся кавычки '

        // проходим последовательно символы исходного текста, отделяя фрагменты текста с помощью
        // терминальных символов: space : ; , . { } ( ) + - * / \n \t ' =
        // в случае если мы определяем границу строкового литерала то терминальный символ это одинарная кавычка: ’
        while (i < strlen((char*)ctx.in.text)) {
            char c = ctx.in.text[i];

            if (stringMode) { // режим строкового литерала
                if (c == '\'') {
                    addLexema(ctx, begin, i, beginStringLine, beginStringCol, LEX_LITERAL, LT_STRING_LITERAL);
                    stringMode = false;
                    begin      = i + 1;
                }
            } else { // обычный режим обработки
                if (isTerminalSymbol(c)) {
                    analyzeFragment(ctx, begin, i - 1, line, col);
                    begin = i + 1;
                }

                switch (c) {
                    case '\'': {
                        stringMode	= true;
                        begin		= i;
                        beginStringLine = line;
                        beginStringCol	= col;
                        break;
                    }
                    case LEX_PLUS:
                    case LEX_MINUS:
                    case LEX_STAR:
                    case LEX_DIRSLASH:
                    case LEX_COMPARE:
                    case LEX_SEMICOLON:
                    case LEX_COLON:
                    case LEX_COMMA:
                    case LEX_EXCLAMATION:
                    case LEX_LESS:
                    case LEX_MORE:
                    case LEX_LEFT_SQ_BR:
                    case LEX_RIGTH_SQ_BR:
                    case LEX_LEFTBRACE:
                    case LEX_RIGTHBRACE:
                    case LEX_LEFTHESIS:
                    case LEX_RIGHTHESIS: {
                        addLexema(ctx, begin - 1, i, line, col, c, LT_SIGN);
                        begin = i + 1;
                        break;
                    }
                }
            }

            if (c == '\n') {
                line++;
                col = 1;
            } else {
                col++;
            }
            i++;
        }
        analyzeFragment(ctx, begin, i - 1, line, col); // обработать последний фрагмент текста
        if (stringMode) {
            throw ERROR_THROW_IN(223, line, col);      // отсутствует закрывающаяся кавычка
        }
        if (nestingLevel > 0) {
            throw ERROR_THROW_IN(226, line, col);      // открывающихся скобок { больше чем закрывающихся }
        }
    }

    // терминальные символы: space : ; , . { } ( ) + - * / \n \t ` ' = ! [ ] < >
    bool isTerminalSymbol(const char c) {
        return c == ' ' || c == ';' || c == ',' || c == '.'  || c == '\'' || c == ':' ||
               c == '{' || c == '}' || c == '(' || c == ')' || c == '+' || c == '=' ||
               c == '-' || c == '*' || c == '/' || c == '\n' || c == '\t' || c == '!' ||
               c == '[' || c == ']' || c == '<' || c == '>';
    }

    void analyzeFragment(TranslationContext &ctx, const int begin, const int end, const int line, const int col) {
        if (begin <= end) {
            char* fragment	   = subString(ctx.in.text, begin, end - begin + 1);
            Recognizer* recognizer = RECOGNIZERS.recognyze(fragment);
            if (!recognizer) {
                throw ERROR_THROW_IN(220, line, col); // Недопустимый синтаксис
            } else {
                addLexema(ctx, begin, end, line, col, recognizer->lexema, recognizer->lexemaType);
            }
            delete[] fragment;
        }
    }

    // последовательное добавление записей в таблицы лексем и идентификаторов
    void addLexema(TranslationContext &ctx, const int begin, const int end, const int line, const int col, const char lexema,
                   const int lexemaType) {
        char* fullFragment    = subString(ctx.in.text, begin, end - begin + 1);
        LT::Entry lexemaEntry = { lexema, lexemaType, line, col, (int)LT_TI_NULLIDX };
        int lexemaIndex	      = ctx.lexTable.table.size();

        switch (lexema) {
            case LEX_MAIN: {
                if ((nestingLevel != 0) || (prefixFunction.size() > 0)) {
                    throw ERROR_THROW_IN(228, line, col); // ключевое слово main встретилось в неположенном месте
                }
                char id[ID_MAXSIZE * 3 + 2];
                id[0] = 0;
                appendChars(id, fullFragment);
                int idIndex = ctx.idTable.IsId(id);
                if (IT_NULLIDX == idIndex) {
                    IT::Entry identifacator = *new IT::Entry();
                    identifacator.idxfirstLE = lexemaIndex;
                    appendChars(identifacator.id, id);
                    identifacator.idtype     = T_F;
                    identifacator.datatype   = DT_INT;
                    identifacator.value.vint = 0;
                    ctx.idTable.Add(identifacator);
                    lexemaEntry.idxTI = idIndex;
                } else {
                    throw ERROR_THROW_IN(232, line, col); //  функция main объявляется второй раз
                }
                break;
            };
            case LEX_SEMICOLON: {
                prefixLibFunction.clear();
                break;
            }
            case LEX_LEFTBRACE: {
                nestingLevel++;
                break;
            };
            case LEX_RIGTHBRACE: {
                nestingLevel--;
                if (nestingLevel == 0) {
                    prefixFunction.clear();
                }
                if (nestingLevel < 0) {
                    throw ERROR_THROW_IN(227, line, col); // закрывающихся скобок } больше чем открывающихся {
                }
                break;
            };
            case LEX_ID: {
                char* fragment = subString(fullFragment, 0, ID_MAXSIZE);

                // строим id учитывая префиксы
                char id[ID_MAXSIZE * 3 + 3];
                id[0] = 0;
                if (prefixFunction.size() > 0) {
                    appendChars(id, prefixFunction.c_str());
                }
                if (prefixLibFunction.size() > 0) {
                    appendChars(id, prefixLibFunction.c_str());
                }
                appendChars(id, fragment);

                int idIndex = ctx.idTable.IsId(id);
                if (IT_NULLIDX == idIndex) {
                    // обнаружен новый идентификатор

                    // проверяем не является ли данный идентификатор библиотечной функцией
                    bool isLibraryFunction = false;
                    int	 lIndex		   = lexemaIndex - 2;
                    if (lIndex >= 0) {
                        if (ctx.lexTable.table[lIndex].lexema == LEX_USE) {
                            lIndex++;
                            if (ctx.lexTable.table[lIndex].lexema == LEX_FUNCTION) {
                                isLibraryFunction = true;
                                prefixLibFunction.append(fragment).append(".");
                            }
                        }
                    }

                    if (!isLibraryFunction && (strlen(fullFragment) > ID_MAXSIZE)) {
                        // для НЕ БИБЛИОТЕЧНЫХ функций размер идентификатора дожен быть не больше 15 символов
                        throw ERROR_THROW_IN(229, line, col);
                    }

                    // создаем новую запись для идентификатора и заполняем значения
                    IT::Entry identifacator = *new IT::Entry();
                    identifacator.idxfirstLE = lexemaIndex;    // ссылка на первую лексему
                    appendChars(identifacator.id,   id);       // id
                    appendChars(identifacator.name, fragment); // name

                    // вычисляем тип идентификатора
                    identifacator.idtype   = T_P;
                    identifacator.datatype = DT_UNKNOWN;
                    lIndex		   = lexemaIndex - 1;
                    if (lIndex >= 0) {
                        if (ctx.lexTable.table[lIndex].lexema == LEX_FUNCTION) {
                            identifacator.idtype = T_F;
                            if (!isLibraryFunction) {
                                if (prefixFunction.size() > 0) {
                                    throw ERROR_THROW_IN(233, line, col); // объявление функции внутри функции недопустимо
                                }
                                prefixFunction.append(fragment).append(".");
                            }
                        } else {
                            if (ctx.lexTable.table[lIndex].lexema == LEX_VAR) {
                                identifacator.idtype = T_V;
                            } else {
                                // это параметр в объявлении функции?
                                if ((prefixLibFunction.size() > 0) || ((nestingLevel == 0) && (prefixFunction.size() > 0))) {
                                    identifacator.idtype = T_P;
                                } else {
                                    // Невозможно определить тип данных для идентификатора либо идентификатор не объявлен
                                    throw ERROR_THROW_IN(230, line, col);
                                }
                            }
                        }
                    }

                    idIndex = ctx.idTable.table.size();
                    ctx.idTable.Add(identifacator);
                } else {
                    // идентификатор уже существует
                    int declareLexemaIndex = lexemaIndex - 2;
                    if (declareLexemaIndex >= 0) {
                        if (ctx.lexTable.table[declareLexemaIndex].lexema == LEX_VAR) {
                            throw ERROR_THROW_IN(231, line, col); // переопределение идентификатора
                        }
                    }
                }
                lexemaEntry.idxTI = idIndex;
                delete[] fragment;
                break;
            };
            case LEX_LITERAL: {
                IT::Entry literal = *new IT::Entry();
                literal.idxfirstLE = lexemaIndex;
                literal.idtype	   = T_L;
                if (lexemaType == LT_INTEGER_LITERAL) {
                    literal.datatype = DT_INT;
                    long long int value = atoll(fullFragment);
                    if ((value > LONG_MAX) || (value < LONG_MIN)) {
                        throw ERROR_THROW_IN(235, line, col); // превышение лимитов целочичленного литерала
                    }
                    literal.value.vint = atoi(fullFragment);
                } else if (lexemaType == LT_STRING_LITERAL) {
                    literal.datatype = DT_STR;
                    if (strlen(fullFragment) > 256) {
                        throw ERROR_THROW_IN(234, line, col); // превышение длины строки
                    }
                    literal.value.vstr.len    = strlen(fullFragment);
                    literal.value.vstr.str[0] = 0;
                    appendChars(literal.value.vstr.str, subString(fullFragment, 1, strlen(fullFragment) - 2));
                }
                int idIndex = ctx.idTable.table.size();
                ctx.idTable.Add(literal);
                lexemaEntry.idxTI = idIndex;
                break;
            };
            case LEX_DATATYPE: {
                int lIndex = lexemaIndex - 1;
                if ((lIndex >= 0) && (ctx.lexTable.table[lIndex].lexema == LEX_COLON)) {
                    int iIndex = -1;

                    // ищем соотвествующую лексему идентификтора
                    lIndex--;
                    if ((lIndex >= 0) && (ctx.lexTable.table[lIndex].lexema == LEX_ID)) {
                        // для переменной и параметра
                        iIndex = lIndex;
                    } else {
                        // для функции
                        while (lIndex >= 0 && ctx.lexTable.table[lIndex].lexema != LEX_LEFTHESIS) {
                            lIndex--;
                        }
                        lIndex--;
                        if ((lIndex >= 0) && (ctx.lexTable.table[lIndex].lexema == LEX_ID)) {
                            iIndex = lIndex;
                        }
                    }
                    if (iIndex >= 0) {
                        int idIndex		 = ctx.lexTable.table[iIndex].idxTI;
                        IT::Entry* identifacator = &ctx.idTable.table[idIndex];

                        // устанавливаем тип данных
                        if (lexemaType == LT_INTEGER_DATATYPE) {
                            identifacator->datatype = DT_INT;
                        } else if (lexemaType == LT_STRING_DATATYPE) {
                            identifacator->datatype = DT_STR;
                        }

                        // устанавливаем начальные значения для идентификатора
                        if (identifacator->datatype == DT_INT) {
                            identifacator->value.vint = 0;
                        } else if (identifacator->datatype == DT_STR) {
                            identifacator->value.vstr.len    = 0;
                            identifacator->value.vstr.str[0] = 0;
                        }
                    } else {
                        // Невозможно определить тип данных для идентификатора либо идентификатор не объявлен
                        throw ERROR_THROW_IN(230, line, col);
                    }
                } else {
                    // Невозможно определить тип данных для идентификатора либо идентификатор не объявлен
                    throw ERROR_THROW_IN(230, line, col);
                }
                break;
            }
        }
        ctx.lexTable.Add(lexemaEntry);

        delete[] fullFragment;
    }
}
