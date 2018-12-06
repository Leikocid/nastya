#ifndef TRANSTATION_CONTEXT_H
#define TRANSTATION_CONTEXT_H

#include "Parm.h"
#include "Log.h"
#include "In.h"
#include "LT.h"
#include "IT.h"
#include "Greibach.h"

// контекст работы транслятора
struct TranslationContext {
    // параметры запуска
    Parm::PARM params;

    // логгер
    Log::LOG* logger;

    // входной текст
    In::IN in;

    // таблица лексем
    LT::LexTable lexTable;

    // таблица идентификаторов
    IT::IdTable idTable;

    // грамматика для синтаксического анализатора
    GR::Grammar* grammar;

    // дерево рвзбора
    GR::ParseTreeNode* parseTree;
};

#endif // !TRANSTATION_CONTEXT_H
