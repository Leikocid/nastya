using System;
using System.Collections.Generic;

namespace main {
    class Program {
        static int fact(int x) {
            if (x > 1) {
                return x * fact(x - 1);
            } else {
                return 1;
            }
        }

        static int max(int x, int y) {
            if (x > y) {
                return x;
            } else {
                return y;
            }
        }

        static int min(int x, int y) {
            if (x > y) {
                return y;
            } else {
                return x;
            }
        }

        static int fi(int x, int y) {
            int z;
            z = x * (x + y);
            if (z < 100) {
                z = z + 1000;
            } else {
                z = z + 2000;
            }
            return z;
        }

        static int fs(string a, int b) {
            int c;
            c = a.Length + b;
            return c;
        }

        static void Main(string[] args) {
            int x;
            int y;
            int z;
            string sa = "1234567890";
            string sb;
            x  = 1;
            y  = 5;
            sa = "1234567890";
            sb = "1234567890";
            int w;
            w = fi(x, y);
            y = fs(sa, x);
            Console.WriteLine("контрольный пример");
            Console.WriteLine(w);
            z = fact(y);
            Console.WriteLine(z);
            z = max(x, y);
            Console.WriteLine(z);
            z = min(x, y);
            Console.WriteLine(z);
            Console.WriteLine(sb.Length);
            while (x < 10) {
                if (x <= 6) {
                    Console.WriteLine(x);
                } else {
                    Console.WriteLine(x * x);
                }
                x = x + 1;
            }
        }
    }
}
