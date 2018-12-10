.assembly extern System.Runtime
{
  .ver 4:2:1:0
  .publickeytoken = (B0 3F 5F 7F 11 D5 0A 3A ) // .?_....:
}
.assembly extern System.Console
{
  .ver 4:1:1:0
  .publickeytoken = (B0 3F 5F 7F 11 D5 0A 3A ) // .?_....:
}
.assembly '2_1_kp'
{
  .custom instance void class [mscorlib]System.Runtime.CompilerServices.CompilationRelaxationsAttribute::'.ctor'(int32) =  (01 00 08 00 00 00 00 00 ) // ........

  .custom instance void class [mscorlib]System.Runtime.CompilerServices.RuntimeCompatibilityAttribute::'.ctor'() =  (
		01 00 01 00 54 02 16 57 72 61 70 4E 6F 6E 45 78   // ....T..WrapNonEx
		63 65 70 74 69 6F 6E 54 68 72 6F 77 73 01       ) // ceptionThrows.

  .custom instance void class [mscorlib]System.Diagnostics.DebuggableAttribute::'.ctor'(valuetype [mscorlib]System.Diagnostics.DebuggableAttribute/DebuggingModes) =  (01 00 07 01 00 00 00 00 ) // ........

  .custom instance void class [mscorlib]System.Runtime.Versioning.TargetFrameworkAttribute::'.ctor'(string) =  (
		01 00 18 2E 4E 45 54 43 6F 72 65 41 70 70 2C 56   // ....NETCoreApp,V
		65 72 73 69 6F 6E 3D 76 32 2E 31 01 00 54 0E 14   // ersion=v2.1..T..
		46 72 61 6D 65 77 6F 72 6B 44 69 73 70 6C 61 79   // FrameworkDisplay
		4E 61 6D 65 00                                  ) // Name.

  .custom instance void class [mscorlib]System.Reflection.AssemblyCompanyAttribute::'.ctor'(string) =  (01 00 06 32 5F 31 5F 6B 70 00 00 ) // ...2_1_kp..

  .custom instance void class [mscorlib]System.Reflection.AssemblyConfigurationAttribute::'.ctor'(string) =  (01 00 05 44 65 62 75 67 00 00 ) // ...Debug..

  .custom instance void class [mscorlib]System.Reflection.AssemblyFileVersionAttribute::'.ctor'(string) =  (01 00 07 31 2E 30 2E 30 2E 30 00 00 ) // ...1.0.0.0..

  .custom instance void class [mscorlib]System.Reflection.AssemblyInformationalVersionAttribute::'.ctor'(string) =  (01 00 05 31 2E 30 2E 30 00 00 ) // ...1.0.0..

  .custom instance void class [mscorlib]System.Reflection.AssemblyProductAttribute::'.ctor'(string) =  (01 00 06 32 5F 31 5F 6B 70 00 00 ) // ...2_1_kp..

  .custom instance void class [mscorlib]System.Reflection.AssemblyTitleAttribute::'.ctor'(string) =  (01 00 06 32 5F 31 5F 6B 70 00 00 ) // ...2_1_kp..

  .hash algorithm 0x00008004
  .ver  1:0:0:0
}
.module 2_1_kp.dll // GUID = {11E71BFE-72F2-42B3-BB19-C9AC4F796E7A}


.namespace main
{
  .class private auto ansi beforefieldinit Program
  	extends [System.Runtime]System.Object
  {

    // method line 1
    .method private static hidebysig 
           default int32 fact (int32 x)  cil managed 
    {
        // Method begins at RVA 0x2050
	// Code size 30 (0x1e)
	.maxstack 3
	.locals init (
		bool	V_0,
		int32	V_1)
	IL_0000:  nop 
	IL_0001:  ldarg.0 
	IL_0002:  ldc.i4.1 
	IL_0003:  cgt 
	IL_0005:  stloc.0 
	IL_0006:  ldloc.0 
	IL_0007:  brfalse.s IL_0017

	IL_0009:  nop 
	IL_000a:  ldarg.0 
	IL_000b:  ldarg.0 
	IL_000c:  ldc.i4.1 
	IL_000d:  sub 
	IL_000e:  call int32 class main.Program::fact(int32)
	IL_0013:  mul 
	IL_0014:  stloc.1 
	IL_0015:  br.s IL_001c

	IL_0017:  nop 
	IL_0018:  ldc.i4.1 
	IL_0019:  stloc.1 
	IL_001a:  br.s IL_001c

	IL_001c:  ldloc.1 
	IL_001d:  ret 
    } // end of method Program::fact

    // method line 2
    .method private static hidebysig 
           default int32 max (int32 x, int32 y)  cil managed 
    {
        // Method begins at RVA 0x207c
	// Code size 24 (0x18)
	.maxstack 2
	.locals init (
		bool	V_0,
		int32	V_1)
	IL_0000:  nop 
	IL_0001:  ldarg.0 
	IL_0002:  ldarg.1 
	IL_0003:  clt 
	IL_0005:  ldc.i4.0 
	IL_0006:  ceq 
	IL_0008:  stloc.0 
	IL_0009:  ldloc.0 
	IL_000a:  brfalse.s IL_0011

	IL_000c:  nop 
	IL_000d:  ldarg.0 
	IL_000e:  stloc.1 
	IL_000f:  br.s IL_0016

	IL_0011:  nop 
	IL_0012:  ldarg.1 
	IL_0013:  stloc.1 
	IL_0014:  br.s IL_0016

	IL_0016:  ldloc.1 
	IL_0017:  ret 
    } // end of method Program::max

    // method line 3
    .method private static hidebysig 
           default int32 min (int32 x, int32 y)  cil managed 
    {
        // Method begins at RVA 0x20a0
	// Code size 24 (0x18)
	.maxstack 2
	.locals init (
		bool	V_0,
		int32	V_1)
	IL_0000:  nop 
	IL_0001:  ldarg.0 
	IL_0002:  ldarg.1 
	IL_0003:  clt 
	IL_0005:  ldc.i4.0 
	IL_0006:  ceq 
	IL_0008:  stloc.0 
	IL_0009:  ldloc.0 
	IL_000a:  brfalse.s IL_0011

	IL_000c:  nop 
	IL_000d:  ldarg.1 
	IL_000e:  stloc.1 
	IL_000f:  br.s IL_0016

	IL_0011:  nop 
	IL_0012:  ldarg.0 
	IL_0013:  stloc.1 
	IL_0014:  br.s IL_0016

	IL_0016:  ldloc.1 
	IL_0017:  ret 
    } // end of method Program::min

    // method line 4
    .method private static hidebysig 
           default int32 fi (int32 x, int32 y)  cil managed 
    {
        // Method begins at RVA 0x20c4
	// Code size 54 (0x36)
	.maxstack 3
	.locals init (
		int32	V_0,
		bool	V_1,
		int32	V_2)
	IL_0000:  nop 
	IL_0001:  ldarg.0 
	IL_0002:  ldarg.0 
	IL_0003:  ldarg.1 
	IL_0004:  add 
	IL_0005:  mul 
	IL_0006:  stloc.0 
	IL_0007:  ldloc.0 
	IL_0008:  ldc.i4.s 0x64
	IL_000a:  bge.s IL_0015

	IL_000c:  ldloc.0 
	IL_000d:  ldarg.0 
	IL_000e:  ceq 
	IL_0010:  ldc.i4.0 
	IL_0011:  ceq 
	IL_0013:  br.s IL_0016

	IL_0015:  ldc.i4.0 
	IL_0016:  stloc.1 
	IL_0017:  ldloc.1 
	IL_0018:  brfalse.s IL_0026

	IL_001a:  nop 
	IL_001b:  ldloc.0 
	IL_001c:  ldc.i4 1000
	IL_0021:  add 
	IL_0022:  stloc.0 
	IL_0023:  nop 
	IL_0024:  br.s IL_0030

	IL_0026:  nop 
	IL_0027:  ldloc.0 
	IL_0028:  ldc.i4 2000
	IL_002d:  add 
	IL_002e:  stloc.0 
	IL_002f:  nop 
	IL_0030:  ldloc.0 
	IL_0031:  stloc.2 
	IL_0032:  br.s IL_0034

	IL_0034:  ldloc.2 
	IL_0035:  ret 
    } // end of method Program::fi

    // method line 5
    .method private static hidebysig 
           default int32 fs (string a, int32 b)  cil managed 
    {
        // Method begins at RVA 0x2108
	// Code size 16 (0x10)
	.maxstack 2
	.locals init (
		int32	V_0,
		int32	V_1)
	IL_0000:  nop 
	IL_0001:  ldarg.0 
	IL_0002:  callvirt instance int32 string::get_Length()
	IL_0007:  ldarg.1 
	IL_0008:  add 
	IL_0009:  stloc.0 
	IL_000a:  ldloc.0 
	IL_000b:  stloc.1 
	IL_000c:  br.s IL_000e

	IL_000e:  ldloc.1 
	IL_000f:  ret 
    } // end of method Program::fs

    // method line 6
    .method private static hidebysig 
           default void Main (string[] args)  cil managed 
    {
        // Method begins at RVA 0x2124
	.entrypoint
	// Code size 172 (0xac)
	.maxstack 2
	.locals init (
		int32	V_0,
		int32	V_1,
		int32	V_2,
		string	V_3,
		string	V_4,
		int32	V_5,
		bool	V_6,
		bool	V_7)
	IL_0000:  nop 
	IL_0001:  ldstr "1234567890"
	IL_0006:  stloc.3 
	IL_0007:  ldc.i4.1 
	IL_0008:  stloc.0 
	IL_0009:  ldc.i4.5 
	IL_000a:  stloc.1 
	IL_000b:  ldstr "1234567890"
	IL_0010:  stloc.3 
	IL_0011:  ldstr "1234567890"
	IL_0016:  stloc.s 4
	IL_0018:  ldloc.0 
	IL_0019:  ldloc.1 
	IL_001a:  call int32 class main.Program::fi(int32, int32)
	IL_001f:  stloc.s 5
	IL_0021:  ldloc.3 
	IL_0022:  ldloc.0 
	IL_0023:  call int32 class main.Program::fs(string, int32)
	IL_0028:  stloc.1 
	IL_0029:  ldstr bytearray (
	3a 04 3e 04 3d 04 42 04 40 04 3e 04 3b 04 4c 04  // :.>.=.B.@.>.;.L.
	3d 04 4b 04 39 04 20 00 3f 04 40 04 38 04 3c 04  // =.K.9. .?.@.8.<.
	35 04 40 04 01 )                                 // 5.@..
	
	IL_002e:  call void class [mscorlib]System.Console::WriteLine(string)
	IL_0033:  nop 
	IL_0034:  ldloc.s 5
	IL_0036:  call void class [mscorlib]System.Console::WriteLine(int32)
	IL_003b:  nop 
	IL_003c:  ldloc.1 
	IL_003d:  call int32 class main.Program::fact(int32)
	IL_0042:  stloc.2 
	IL_0043:  ldloc.2 
	IL_0044:  call void class [mscorlib]System.Console::WriteLine(int32)
	IL_0049:  nop 
	IL_004a:  ldloc.0 
	IL_004b:  ldloc.1 
	IL_004c:  call int32 class main.Program::max(int32, int32)
	IL_0051:  stloc.2 
	IL_0052:  ldloc.2 
	IL_0053:  call void class [mscorlib]System.Console::WriteLine(int32)
	IL_0058:  nop 
	IL_0059:  ldloc.0 
	IL_005a:  ldloc.1 
	IL_005b:  call int32 class main.Program::min(int32, int32)
	IL_0060:  stloc.2 
	IL_0061:  ldloc.2 
	IL_0062:  call void class [mscorlib]System.Console::WriteLine(int32)
	IL_0067:  nop 
	IL_0068:  ldloc.s 4
	IL_006a:  callvirt instance int32 string::get_Length()
	IL_006f:  call void class [mscorlib]System.Console::WriteLine(int32)
	IL_0074:  nop 
	IL_0075:  br.s IL_00a0

	IL_0077:  nop 
	IL_0078:  ldloc.0 
	IL_0079:  ldc.i4.6 
	IL_007a:  cgt 
	IL_007c:  ldc.i4.0 
	IL_007d:  ceq 
	IL_007f:  stloc.s 6
	IL_0081:  ldloc.s 6
	IL_0083:  brfalse.s IL_0090

	IL_0085:  nop 
	IL_0086:  ldloc.0 
	IL_0087:  call void class [mscorlib]System.Console::WriteLine(int32)
	IL_008c:  nop 
	IL_008d:  nop 
	IL_008e:  br.s IL_009b

	IL_0090:  nop 
	IL_0091:  ldloc.0 
	IL_0092:  ldloc.0 
	IL_0093:  mul 
	IL_0094:  call void class [mscorlib]System.Console::WriteLine(int32)
	IL_0099:  nop 
	IL_009a:  nop 
	IL_009b:  ldloc.0 
	IL_009c:  ldc.i4.1 
	IL_009d:  add 
	IL_009e:  stloc.0 
	IL_009f:  nop 
	IL_00a0:  ldloc.0 
	IL_00a1:  ldc.i4.s 0x0a
	IL_00a3:  clt 
	IL_00a5:  stloc.s 7
	IL_00a7:  ldloc.s 7
	IL_00a9:  brtrue.s IL_0077

	IL_00ab:  ret 
    } // end of method Program::Main

    // method line 7
    .method public hidebysig specialname rtspecialname 
           instance default void '.ctor' ()  cil managed 
    {
        // Method begins at RVA 0x21dc
	// Code size 8 (0x8)
	.maxstack 8
	IL_0000:  ldarg.0 
	IL_0001:  call instance void object::'.ctor'()
	IL_0006:  nop 
	IL_0007:  ret 
    } // end of method Program::.ctor

  } // end of class main.Program
}

