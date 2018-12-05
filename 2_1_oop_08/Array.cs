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

        public void removeAt(int index) {
            data.RemoveAt(index);
        }

        public void Add(T element) {
            data.Add(element);
        }

        public void Remove(T element) {
            data.Remove(element);
        }

        public int Count() {
            return data.Count;
        }

        public IEnumerator<T> GetEnumerator() {
            return data.GetEnumerator();
        }
    }
}