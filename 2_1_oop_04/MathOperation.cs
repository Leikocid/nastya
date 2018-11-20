using System;

namespace ns_2_1_oop_04 {
    public static class MathOperation {
        public static int max(Array a) {
            int result = 0;
            for (int i = 0; i < count(a); i++) {
                if ((i == 0) || (a[i] > result)) {
                    result = a[i];
                }
            }
            return result;
        }

        public static int min(Array a) {
            int result = 0;
            for (int i = 0; i < count(a); i++) {
                if ((i == 0) || (a[i] < result)) {
                    result = a[i];
                }
            }
            return result;
        }

        public static int count(Array a) {
            return (int)a;
        }

        public static bool Contains(this string str, char c) {
            for (int i = 0; i < str.Length; i++) {
                if (str[i] == c) {
                    return true;
                }
            }
            return false;
        }

        public static void RemoveNegative(this Array a) {
            int i = 0;
            while (i < count(a)) {
                if (a[i] < 0) {
                    a.removeElement(i);
                }
                i++;
            }
        }
    }
}
