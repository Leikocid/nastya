using System;
using System.Collections;

namespace ns_2_1_oop_04 {
    partial class Vector {
        // статтический конструктор
        static Vector() {
            Console.WriteLine("Create class Vector");
        }

        public static void printClassInfo() {
            Console.WriteLine("имя класса: Vector");
            Console.WriteLine($"количенство созданных объектов: {Counter}");
        }
    }
}
