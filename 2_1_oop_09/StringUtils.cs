
using System;

namespace ns_2_1_oop {
    static class StringUtils {
        public static string envoke(this string str, Func<string, string> f) {
            return f(str);
        }

        public static string envoke(this string str, Func<string, string, string> f, string str2) {
            return f(str, str2);
        }

        public static string envoke(this string str, Func<string, int, string> f, int number) {
            return f(str, number);
        }
    }
}
