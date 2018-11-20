using System;

namespace _2_1_oop_04 {
    class Array {
        enum Operation {
            Add = 1,
            Subtract,
            Multiply,
            Divide
        }

        // просто маленький метод
        string hello() => "hello";

        // переменное количество параметров
        void printParams(params int[] integers) {
            for (int i = 0; i < integers.Length; i++) {
                Console.WriteLine(integers[i]);
            }
        }
    }
}
