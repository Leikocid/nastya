using System;
using System.Text;

namespace ns_2_1_oop {
    class Program {
        public class MoveSubscriber {
            private string name;
            public MoveSubscriber(string name) {
                this.name = name;
            }

            public void onMove(string message, double result) {
                Console.WriteLine($"{name}.onMove: result = {result}, {message}");
            }
        }

        public class CompressSubscriber {
            private string name;
            public CompressSubscriber(string name) {
                this.name = name;
            }

            public void onCompress(string message, double result) {
                Console.WriteLine($"{name}.onCompress: result = {result}, {message}");
            }
        }

        public class FullSubscriber {
            private string name;
            public FullSubscriber(string name) {
                this.name = name;
            }

            public void onMove(string message, double result) {
                Console.WriteLine($"{name}.onMove: result = {result}, {message}");
            }

            public void onCompress(string message, double result) {
                Console.WriteLine($"{name}.onCompress: result = {result}, {message}");
            }
        }

        public static string removeComma(string str) {
            return str.Replace(",", "");
        }

        public static string star(string str) {
            return "*" + str + "*";
        }

        public static string upper(string str) {
            return str.ToUpper();
        }

        public static string trim(string str) {
            return str.Trim();
        }

        public static string lower(string str) {
            return str.ToLower();
        }

        public static string concat(string str1, string str2) {
            return str1 + str2;
        }

        public static string multiply(string str, int number) {
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < number; i++) {
                sb.Append(str);
            }
            return sb.ToString();
        }

        static void Main(string[] args) {
            // первое задание
            User u = new User();

            MoveSubscriber ms1	   = new MoveSubscriber("ms1");
            CompressSubscriber cs1 = new CompressSubscriber("cs1");
            FullSubscriber     fs1 = new FullSubscriber("fs1");
            FullSubscriber     fs2 = new FullSubscriber("fs2");

            u.MOVE     += ms1.onMove;
            u.MOVE     += fs1.onMove;
            u.MOVE     += fs2.onMove;
            u.COMPRESS += cs1.onCompress;
            u.COMPRESS += fs1.onCompress;
            u.MOVE     += (message, result) => Console.WriteLine($"LAMBDA.MOVE: result = {result}, {message}");
            u.COMPRESS += (message, result) => Console.WriteLine($"LAMBDA.COMPRESS: result = {result}, {message}");

            u.move(100);
            u.compress(0.5);
            u.move(10);

            // второе задание. Mетод envoke добавлен к string (см. StringUtils)
            string ss = "Мой дядя самых честных правил,\nКогда не в шутку занемог,\nОн уважать себя заставил\nИ лучше выдумать не мог.";
            ss = ss.envoke(trim)
                 .envoke(star)
                 .envoke(removeComma)
                 .envoke(s => s.ToLower())
                 .envoke(concat,   "\n")
                 .envoke(multiply, 3);
            Console.WriteLine(ss);
        }
    }
}
