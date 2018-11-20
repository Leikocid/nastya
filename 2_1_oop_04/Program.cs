using System;
using System.Collections.Generic;

namespace _2_1_oop_04 {
    class Program {
        static void Main(string[] args) {
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
        }
    }
}
