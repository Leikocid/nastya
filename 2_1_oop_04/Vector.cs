using System;
using System.Collections;

namespace _2_1_oop_04 {
    class Vector {
        // размер вектора
        public int Size {
            get;
        }

        // элементы вектора
        protected int[] data;

        // индексатор
        public int this[int i]
        {
            get
            {
                return data[i];
            }
            set
            {
                data[i] = value;
            }
        }

        // поле статуса.
        public int Status {
            get;
        }

        // конструктор
        public Vector(int size) {
            this.Size = size;
            this.data = new int[size];
        }

        // добавить значение ко всем элементам
        public void add(int value) {
            for (int i = 0; i < Size; i++) {
                data[i] = data[i] + value;
            }
        }

        // умножить все элементы на значение
        public void mul(int value) {
            for (int i = 0; i < Size; i++) {
                data[i] = data[i] * value;
            }
        }

        // посчитать модуль
        public double module() {
            double result = 0;
            for (int i = 0; i < Size; i++) {
                result += data[i] * data[i];
            }
            return Math.Sqrt(result);
        }

        // содержит 0 ?
        public bool hasZero() {
            for (int i = 0; i < Size; i++) {
                if (data[i] == 0) {
                    return true;
                }
            }
            return false;
        }

        // респечатать вевтор в вконсоль
        public void print() {
            Console.WriteLine("Vecor [size = {0}]:", Size);
            for (int i = 0; i < Size; i++) {
                Console.WriteLine("{0} = {1}", i, this[i]);
            }
        }
    }
}
