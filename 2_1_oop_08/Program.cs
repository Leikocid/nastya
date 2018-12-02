using System;
using System.Collections.Generic;

namespace ns_2_1_oop {
    class Program {
        static void Main(string[] args) {
            Console.WriteLine("Arrays:");
            Array<int> a111   = new Array<int>(1, 1, 1);
            Array<int> a222   = new Array<int>(2, 2, 2);
            Array<int> a11    = new Array<int>(1, 1);
            Array<int> a222_2 = new Array<int>(2, 2, 2);
            Array<int> a_neg  = new Array<int>(2, -1, 2);

            Console.WriteLine($"a111: {a111}");
            Console.WriteLine($"a222: {a222}");
            Console.WriteLine($"a11: {a11}");
            Console.WriteLine($"a222_2: {a222_2}");
            Console.WriteLine($"a_neg: {a_neg}");

            Console.WriteLine($"(int)a111 = {(int)a111}");
            Console.WriteLine($"a222 == a222_2 ? = {(a222==a222_2?true:false)}");

            Array<int>.Owner o = new Array<int>.Owner();
            Console.WriteLine($"Array.Owner o.Id = {o.Id}");
            Array<int>.Date d = new Array<int>. Date();
            Console.WriteLine($"Array.Owner d = {d.CreationDate}");

            Console.WriteLine($"MathOperation.count(a111) = {MathOperation.count(a111)}");
            Console.WriteLine($"MathOperation.max(a11) = {MathOperation.max(a11)}");
            Console.WriteLine($"MathOperation.min(a_neg) = {MathOperation.min(a_neg)}");

            Console.WriteLine($"\"Text\".Contains(\"T\") = {"Text".Contains("T")}");
            a_neg.RemoveNegative();
            Console.WriteLine($"a_neg after a_neg.RemoveNegative(): {a_neg}");
        }
    }
}
