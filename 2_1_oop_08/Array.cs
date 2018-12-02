using System;
using System.Text;
using System.Collections.Generic;

namespace ns_2_1_oop {
    public class Array<T> {
        protected List<T> data = new List<T>();
        public T this[int i] {
            get {
                return data[i];
            }
            set {
                data[i] = value;
            }
        }

        // конструкторы
        public Array() {}

        public Array(params T[] values) {
            data.AddRange(values);
        }

        public static explicit operator int(Array<T> a) {
            return a.data.Count;
        }

        public override string ToString() {
            StringBuilder result = new StringBuilder();
            result.Append("Array [size = ").Append(data.Count).Append("]: {");
            for (int i = 0; i < data.Count; i++) {
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
            if ((index >= 0) && (index < data.Count)) {
                data.RemoveAt(index);
            }
        }

        void Add(T element) {
            data.Add(element);
        }

        void Remove(T element) {
            data.Remove(element);
        }

        IEnumerator<T> GetEnumerator() {
            return data.GetEnumerator();
        }
    }
}
