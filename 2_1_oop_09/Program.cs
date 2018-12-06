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

        public class StringProcessor {
            private string s;
            public StringProcessor(string s) {
                this.s = s;
            }

            public  string removeComma(string str) {
                return str.Replace(",", "");
            }

            public string star(string str) {
                return "*" + str + "*";
            }

            public string upper(string str) {
                return str.ToUpper();
            }

            public string trim(string str) {
                return str.Trim();
            }

            public string lower(string str) {
                return str.ToLower();
            }

            public string concat(string str1, string str2) {
                return str1 + str2;
            }

            public string multiply(string str, int number) {
                StringBuilder sb = new StringBuilder();
                for (int i = 1; i < number; i++) {
                    sb.Append(str);
                }
                return sb.ToString();
            }

            public StringProcessor envoke(Func<string, string> f) {
                s = f(s);
                return this;
            }

            public StringProcessor envoke(Func<string, string, string> f, string str) {
                s = f(s, str);
                return this;
            }

            public StringProcessor envoke(Func<string, int, string> f, int number) {
                s = f(s, number);
                return this;
            }

            public string toString() {
                return s;
            }
        }

        static void Main(string[] args) {
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

            StringProcessor sp = new StringProcessor(
                "Мой дядя самых честных правил,\nКогда не в шутку занемог,\nОн уважать себя заставил\nИ лучше выдумать не мог.");
            string res = sp.envoke(sp.trim)
                         .envoke(sp.star)
                         .envoke(sp.removeComma)
                         .envoke(s => s.ToLower())
                         .envoke(sp.concat,   "\n")
                         .envoke(sp.multiply, 3)
                         .toString();
            Console.WriteLine(res);
        }
    }
}
