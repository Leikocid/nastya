using System;
using System.Linq;
using System.Collections.Generic;

namespace ns_2_1_oop {
    class Program {
        static void Main(string[] args) {
            Reflector reflector = new Reflector();

            // a.
            reflector.writeClass(typeof(Vector).ToString(),	 "Vector.txt");
            reflector.writeClass(typeof(Array<int>).ToString(),	 "Array.txt");
            reflector.writeClass(typeof(System.Math).ToString(), "Math.txt");
            eflector.writeClass(typeof(System.String).ToString(), "String.txt");

            // b.
            reflector.printPublicMethods(typeof(Vector).ToString());
            reflector.printPublicMethods(typeof(Array<int>).ToString());
            reflector.printPublicMethods(typeof(System.Math).ToString());
            reflector.printPublicMethods(typeof(System.String).ToString());

            // c.
            reflector.printFields(typeof(Vector).ToString());
            reflector.printFields(typeof(Array<int>).ToString());
            reflector.printFields(typeof(System.Math).ToString());
            reflector.printFields(typeof(System.String).ToString());

            // d.
            reflector.printInterfaces(typeof(Vector).ToString());
            reflector.printInterfaces(typeof(Array<int>).ToString());
            reflector.printInterfaces(typeof(System.Math).ToString());
            reflector.printInterfaces(typeof(System.String).ToString());

            // e.
            try {
                Console.Write("Введите имя класса (System.String): ");
                String className = Console.ReadLine();
                if (className.Length == 0) {
                    className = "System.String";
                }
                Console.Write("Введите имя типа параметра (System.Int32): ");
                String typeName = Console.ReadLine();
                if (typeName.Length == 0) {
                    typeName = "System.Int32";
                }
                reflector.printMethods(className, typeName);
            } catch (Exception e) {
                Console.WriteLine($"Ошибка обработки: {e}");
            }

            // f.
            reflector.callMethod("System.Math", "BigMul", "Params.txt");
        }
    }
}
