using System;
using System.Collections.Generic;

namespace ns_2_1_oop_04 {
    class Program {
        static void Main(string[] args) {
            Console.WriteLine("*********** LAB 03 ***********");

            // инициализация
            Console.WriteLine("Vectors:");
            List<Vector> vectors = new List<Vector>();

            Vector v = new Vector(5);
            v.add(3);
            v.mul(5);
            v[3] = 0;
            int value = 15;
            v.decreaseFirst(ref value, out int index);
            vectors.Add(v);
            Console.WriteLine(v);
            Console.WriteLine($"value = {value}, index = {index}");


            v = new Vector(10, 20, 30, 40, 50, 60);
            vectors.Add(v);
            Console.WriteLine(v);

            v = new Vector();
            v.add(2);
            v.mul(2);
            vectors.Add(v);
            Console.WriteLine(v);

            v = new Vector(10);
            v.add(-2);
            v.mul(3);
            vectors.Add(v);
            Console.WriteLine(v);

            Vector.printClassInfo();

            Console.WriteLine("Vectors with 0:");
            foreach (Vector vec in vectors) {
                if (vec.hasZero()) {
                    Console.WriteLine(vec);
                }
            }

            Console.WriteLine("Vector with least module:");
            int ind	  = -1;
            double module = 0;
            for (int i = 0; i < vectors.Count; i++) {
                if ((ind == -1) || (vectors[i].module() < module)) {
                    ind	   = i;
                    module = vectors[i].module();
                }
            }
            if (ind >= 0) {
                Console.WriteLine(vectors[ind]);
            }


            Console.WriteLine("*********** LAB 04 ***********");
            Console.WriteLine("Arrays:");
            Array a111	 = new Array(1, 1, 1);
            Array a222	 = new Array(2, 2, 2);
            Array a11	 = new Array(1, 1);
            Array a222_2 = new Array(2, 2, 2);
            Array a_neg	 = new Array(2, -1, 2);

            Console.WriteLine($"a111: {a111}");
            Console.WriteLine($"a222: {a222}");
            Console.WriteLine($"a11: {a11}");
            Console.WriteLine($"a222_2: {a222_2}");
            Console.WriteLine($"a_neg: {a_neg}");

            Console.WriteLine($"a111 * a222 = {a111 * a222}");
            Console.WriteLine($"a111 ? = {(a111?true:false)}");
            Console.WriteLine($"a_neg ? = {(a_neg?true:false)}");
            Console.WriteLine($"a222 == a222_2 ? = {(a222==a222_2?true:false)}");
            Console.WriteLine($"a111 > a_neg ? = {(a111>a_neg?true:false)}");

            Array.Owner o = new Array.Owner();
            Console.WriteLine($"Array.Owner o.Id = {o.Id}");
            Array.Date d = new Array.Date();
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
