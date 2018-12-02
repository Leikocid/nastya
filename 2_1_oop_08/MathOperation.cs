using System;

namespace ns_2_1_oop {
    public static class MathOperation {
        public static int max(Array<int> a) {
            int result = 0;
            for (int i = 0; i < count(a); i++) {
                if ((i == 0) || (a[i] > result)) {
                    result = a[i];
                }
            }
            return result;
        }

        public static int min(Array<int> a) {
            int result = 0;
            for (int i = 0; i < count(a); i++) {
                if ((i == 0) || (a[i] < result)) {
                    result = a[i];
                }
            }
            return result;
        }

        public static int count<T>(Array<T> a) {
            return a.Count();
        }

        public static bool Contains(this string str, char c) {
            for (int i = 0; i < str.Length; i++) {
                if (str[i] == c) {
                    return true;
                }
            }
            return false;
        }

        public static void RemoveNegative(this Array<int> a) {
            int i = 0;
            while (i < count(a)) {
                if (a[i] < 0) {
                    a.removeAt(i);
                }
                i++;
            }
        }
    }
}
