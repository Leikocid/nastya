.assembly HelloWorld
{
.hash algorithm 0x00008004
.ver 1:0:1:1
}
.module HelloWorld.exe
// hello() - единственный метод в нашей сборке
.method public static void hello() cil managed
{
.entrypoint
.maxstack 8
// Загружаем строку "Hello, World!" на стек
ldstr "Hello, World!"

// Выводим строку на экран
call void [mscorlib]System.Console::WriteLine(string)

// Ожидаем, пока пользователь введет строку
call string [mscorlib]System.Console::ReadLine()

// Выводим введенную строку на экран
call void [mscorlib]System.Console::WriteLine(string)

// Завершаем выполнение
ret
}