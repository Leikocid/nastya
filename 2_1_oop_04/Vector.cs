using System;
using System.Collections;

namespace _2_1_oop_04 {
    class Vector {
        protected readonly int size;
        public float Size {
            get
            {
                return size;
            }
        }

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

        private int status = 0;
        public float Status {
            get
            {
                return status;
            }
        }


        public Vector(int size) {
            this.size = size;
            this.data = new int[size];
        }

        public void add(int value) {
            for (int i = 0; i < size; i++) {
                data[i] = data[i] + value;
            }
        }

        public void mul(int value) {
            for (int i = 0; i < size; i++) {
                data[i] = data[i] * value;
            }
        }

        public double module() {
            double result = 0;
            for (int i = 0; i < size; i++) {
                result += data[i] * data[i];
            }
            return Math.Sqrt(result);
        }

        public bool hasZero() {
            for (int i = 0; i < size; i++) {
                if (data[i] == 0) {
                    return true;
                }
            }
            return false;
        }

        public void print() {
            Console.WriteLine("Vecor [size = {0}]:", size);
            for (int i = 0; i < size; i++) {
                Console.WriteLine("{0} = {1}", i, this[i]);
            }
        }
    }
}
