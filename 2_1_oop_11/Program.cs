using System;
using System.Linq;
using System.Collections.Generic;

namespace ns_2_1_oop {
    class Program {
        static void Main(string[] args) {
            // 1.
            string[] months = {
                "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
            };
            int n	 = 7;
            var selected = from m in months where m.Length == n select m;
            foreach (string m in selected) {
                Console.WriteLine(m);
            }
            Console.WriteLine("----------");
            string[] summer = {
                "June", "July", "August"
            };
            string[] winter = {
                "December", "January", "February"
            };
            selected = months.Intersect(summer.Union(winter));
            foreach (string m in selected) {
                Console.WriteLine(m);
            }
            Console.WriteLine("----------");
            selected = months.OrderBy(m => m);
            foreach (string m in selected) {
                Console.WriteLine(m);
            }
            int count = months.Where(m => m.Contains("u") && m.Length >= 4).Count();
            Console.WriteLine(count);

            // 2.
            List<Vector> vectors = new List<Vector>() {
                new Vector(0, 1, 2, 3, 4, 5, 6),
                new Vector(0, 3, -4, 5, 6, 7, 8),
                new Vector(1, 3, 5, 7, 9, 11, 13),
                new Vector(2, 4, -6, 8, 10, 11, 14),
                new Vector(3, 4),
                new Vector(4, 3),
                new Vector(5)
            };

            // 3.
            count = vectors.Where(v => v.hasZero()).Count();
            Console.WriteLine(count);
            Console.WriteLine("----------");
            var r1 = vectors.Select(v => new { v = v, m = v.module() });
            foreach (var r in r1) {
                Console.WriteLine(r);
            }
            Console.WriteLine("..........");
            var r2 = vectors.Select(v => new { v = v, m = v.module() })
                     .Join(new List<double> { vectors.Min(v => v.module()) }, v => v.m, m => m, (v, m) => v).Select(v => v.v);
            foreach (var r in r2) {
                Console.WriteLine(r);
            }
            Console.WriteLine("----------");
            var r3 = vectors.Where(v => (v.Size == 3 || v.Size == 5) || (v.Size == 7)).Select(v => v);
            foreach (var r in r3) {
                Console.WriteLine(r);
            }
            Console.WriteLine("----------");

            var r4 = vectors.Where(v => {
                for (int i = 0; i < v.Size; i++) {
                    if (v[i] < 0) {
                        return true;
                    }
                }
                return false;
            }).Take(1);
            foreach (var r in r4) {
                Console.WriteLine(r);
            }
            Console.WriteLine("----------");
            var r5 = vectors.OrderBy(v => v.Size);
            foreach (var r in r5) {
                Console.WriteLine(r);
            }
            Console.WriteLine("----------");

            // 4.
            // как второй + где модуль меньше 3 и сортировка по размеру
            var r6 = vectors.Where(v => v.Size < 3).Select(v => new { v = v, m = v.module() })
                     .Join(new List<double> { vectors.Min(v => v.module()) }, v => v.m, m => m, (v, m) => v).Select(v => v.v)
                     .OrderBy(v => v.Size);
            foreach (var r in r6) {
                Console.WriteLine(r);
            }
            Console.WriteLine("----------");

            // 5.
            var r7 = vectors.OrderBy(v => v.Size);
            foreach (var r in r7) {
                Console.WriteLine(r);
            }
            Console.WriteLine("----------");
        }
    }
}
