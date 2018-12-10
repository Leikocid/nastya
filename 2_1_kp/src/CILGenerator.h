#ifndef CG_H
#define CG_H

#include "TranslationContext.h"

namespace CG {
    static const char* START_TEMPLATE =
        ".assembly extern mscorlib {}\n\
.assembly Program {}\n\
.module Program\n\
.method private static int32 fact (int32 x) cil managed {\n\
	ldarg.0\n\
	ldc.i4 1\n\
	cgt\n\
	brfalse.s IL_0018\n\
	ldarg.0\n\
	ldarg.0\n\
	ldc.i4.1\n\
	sub\n\
	call int32 fact(int32)\n\
	mul\n\
	br.s IL_001c\n\
IL_0018: nop\n\
    ldc.i4.1\n\
IL_001c: nop\n\
	ret\n\
}\n\
.method private static int32 max (int32 x, int32 y) cil managed {\n\
	ldarg.0\n\
	ldarg.1\n\
	cgt\n\
    brfalse.s IL_000e\n\
	ldarg.0\n\
	br.s IL_0013\n\
IL_000e: nop\n\
	ldarg.1\n\
IL_0013: nop\n\
    ret\n\
}\n\
.method private static int32 min (int32 x, int32 y) cil managed {\n\
	ldarg.0\n\
	ldarg.1\n\
	cgt\n\
    brfalse.s IL_000e\n\
	ldarg.1\n\
	br.s IL_0013\n\
IL_000e: nop\n\
	ldarg.0\n\
IL_0013: nop\n\
	ret\n\
}\n";

    static const char* END_TEMPLATE = "";

    // генерирование кода
    void generate(TranslationContext &ctx);
}

#endif // CG_H
