.assembly extern mscorlib {}
.assembly Program {}
.module Program
.method private static int32 fact (int32 x) cil managed {
	ldarg.0
	ldc.i4 1
	cgt
	brfalse.s IL_0018
	ldarg.0
	ldarg.0
	ldc.i4.1
	sub
	call int32 fact(int32)
	mul
	br.s IL_001c
IL_0018: nop
    ldc.i4.1
IL_001c: nop
	ret
}
.method private static int32 max (int32 x, int32 y) cil managed {
	ldarg.0
	ldarg.1
	cgt
    brfalse.s IL_000e
	ldarg.0
	br.s IL_0013
IL_000e: nop
	ldarg.1
IL_0013: nop
    ret
}
.method private static int32 min (int32 x, int32 y) cil managed {
	ldarg.0
	ldarg.1
	cgt
    brfalse.s IL_000e
	ldarg.1
	br.s IL_0013
IL_000e: nop
	ldarg.0
IL_0013: nop
	ret
}
.method private static int32 fi(int32 x, int32 y) cil managed {
	.maxstack 100
	.locals init(int32 z)
	ldarg x
	ldarg x
	ldarg y
	add
	mul
	stloc z
	ldloc z
	ldc.i4 100
	blt.s  LAB_2
	ldloc z
	ldc.i4 2000
	add
	stloc z
	br.s LAB_3
LAB_2: nop
	ldloc z
	ldc.i4 1000
	add
	stloc z
LAB_3: nop
	ldloc z
	ret
}
.method private static int32 fs(string a, int32 b) cil managed {
	.maxstack 100
	.locals init(int32 c)
	ldarg a
	callvirt instance int32 string::get_Length()
	ldarg b
	add
	stloc c
	ldloc c
	ret
}
.method private static void main() cil managed {
	.entrypoint
	.maxstack 100
	.locals init(int32 x)
	.locals init(int32 y)
	.locals init(int32 z)
	.locals init(string sa)
	ldstr "1234567890"
	stloc sa
	.locals init(string sb)
	ldc.i4 1
	stloc x
	ldc.i4 5
	stloc y
	ldstr "1234567890"
	stloc sa
	ldstr "1234567890"
	stloc sb
	.locals init(int32 w)
	ldloc x
	ldloc y
	call int32 fi(int32, int32)
	stloc w
	ldloc sa
	ldloc x
	call int32 fs(string, int32)
	stloc y
	ldstr "контрольный пример"
	call void [mscorlib]System.Console::WriteLine(string)
	ldloc w
	call void [mscorlib]System.Console::WriteLine(int32)
	ldloc y
	call int32 fact(int32)
	stloc z
	ldloc z
	call void [mscorlib]System.Console::WriteLine(int32)
	ldloc x
	ldc.i4 1
	ldloc y
	ldc.i4 1
	add
	add
	call int32 max(int32, int32)
	stloc z
	ldloc z
	call void [mscorlib]System.Console::WriteLine(int32)
	ldloc x
	ldloc y
	call int32 min(int32, int32)
	stloc z
	ldloc z
	call void [mscorlib]System.Console::WriteLine(int32)
	ldloc sb
	callvirt instance int32 string::get_Length()
	call void [mscorlib]System.Console::WriteLine(int32)
LAB_4: nop
	ldloc x
	ldc.i4 10
	blt.s  LAB_5
	br.s LAB_6
LAB_5: nop
	ldloc x
	ldc.i4 6
	ble.s  LAB_7
	ldloc x
	ldloc x
	mul
	call void [mscorlib]System.Console::WriteLine(int32)
	br.s LAB_8
LAB_7: nop
	ldloc x
	call void [mscorlib]System.Console::WriteLine(int32)
LAB_8: nop
	ldloc x
	ldc.i4 1
	add
	stloc x
	br.s LAB_4
LAB_6: nop
	ret
}
