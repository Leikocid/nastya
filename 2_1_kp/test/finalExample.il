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
.locals init(int32 z)
stloc i
CONDret
}
.method private static int32 fs(string a, int32 b) cil managed {
.locals init(int32 c)
ret
}
.method private static void main() cil managed {
.entrypoint
.locals init(int32 x)
.locals init(int32 y)
.locals init(int32 z)
.locals init(string sa)
stloc sa
.locals init(string sb)
ret
}
