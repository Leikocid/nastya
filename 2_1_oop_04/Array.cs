using System;
using System.Text;

namespace ns_2_1_oop_04 {
    public class Array {
        protected int[] data;
        public int this[int i] {
            get {
                if ((i >= 0) && (i < data.Length)) {
                    return data[i];
                } else {
                    return 0;
                }
            }
            set {
                if ((i >= 0) && (i < data.Length)) {
                    data[i] = value;
                }
            }
        }

        // конструкторы
        public Array(int size = 10) {
            this.data = new int[size];
        }

        public Array(params int[] integers) : this(integers.Length) {
            data = integers;
        }

        public static long operator *(Array a1, Array a2) {
            long result = 0;
            for (int i = 0; i < a1.data.Length; i++) {
                result += a1[i] * a2[i];
            }
            return result;
        }

        public static bool operator true(Array a) {
            for (int i = 0; i < a.data.Length; i++) {
                if (a[i] < 0) {
                    return false;
                }
            }
            return true;
        }

        public static bool operator false(Array a) {
            for (int i = 0; i < a.data.Length; i++) {
                if (a[i] < 0) {
                    return true;
                }
            }
            return false;
        }

        public static explicit operator int(Array a) {
            return a.data.Length;
        }

        public static bool operator ==(Array a1, Array a2) {
            if (a1.data.Length != a2.data.Length) {
                return false;
            }
            for (int i = 0; i < a1.data.Length; i++) {
                if (a1[i] != a2[i]) {
                    return false;
                }
            }
            return true;
        }

        public static bool operator !=(Array a1, Array a2) {
            if (a1.data.Length != a2.data.Length) {
                return true;
            }
            for (int i = 0; i < a1.data.Length; i++) {
                if (a1[i] != a2[i]) {
                    return true;
                }
            }
            return false;
        }

        public override bool Equals(object obj) {
            if ((obj == null) || (GetType() != obj.GetType())) {
                return false;
            }
            return ((Array)obj) == this;
        }

        public override int GetHashCode() {
            int result = 0;
            for (int i = 0; i < data.Length; i++) {
                result = result ^ this[i];
            }
            return result;
        }

        public double module() {
            double result = 0;
            for (int i = 0; i < data.Length; i++) {
                result += data[i] * data[i];
            }
            return Math.Sqrt(result);
        }

        // сравнение производится на основании векторных длин (моделей)
        public static bool operator <(Array a1, Array a2) {
            return a1.module() < a2.module();
        }

        public static bool operator >(Array a1, Array a2) {
            return a1.module() > a2.module();
        }

        public override string ToString() {
            StringBuilder result = new StringBuilder();
            result.Append("Array [size = ").Append(data.Length).Append("]: {");
            for (int i = 0; i < data.Length; i++) {
                if (i != 0) {
                    result.Append(", ");
                }
                result.Append(i).Append(": ").Append(this[i]);
            }
            result.Append("}");
            return result.ToString();
        }

        public class Owner {
            private static int counter = 0;
            public int Id { get; set; }		= ++counter;
            public string Name { get; }		= "Name";
            public string Organization { get; } = "Organization";
        }

        public  class Date {
            public  DateTime CreationDate { get; } = DateTime.Now;
        }

        public void removeElement(int index) {
            if ((index >= 0) && (index < data.Length)) {
                int[] newData = new int[data.Length - 1];
                for (int i = 0; i < data.Length; i++) {
                    if (i < index) {
                        newData[i] = data[i];
                    } else if (i > index) {
                        newData[i - 1] = data[i];
                    }
                }
                data = newData;
            }
        }

        // просто маленький метод
        string hello() => "hello";
    }
}
