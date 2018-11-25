using System;
using System.Text;

namespace ns_2_1_oop_04 {
    partial class Vector {
        // константа
        public const string classDysplayName = "Vector";

        // Статический счетчик созданных объектов. Доступ к set ограничен
        public static int Counter { get; private set; } = 0;

        private static Random rnd = new Random();

        // автоматичесоке свойство: размер вектора. Доступ по set убран
        public int Size { get; }

        // элементы вектора
        protected int[] data;

        // индексатор c set и get
        public int this[int i] {
            get {
                if ((i >= 0) && (i < data.Length)) {
                    return data[i];
                } else {
                    return 0;
                }
            } set {
                if ((i >= 0) && (i < data.Length)) {
                    data[i] = value;
                }
            }
        }

        // поле статуса.
        public int Status { get; }

        // поле только для чтения
        public readonly int id;

        // конструкторы
        public Vector(int size = 10) {
            Counter++;
            this.Size = size;
            this.data = new int[size];
            this.id   = rnd.Next(int.MinValue, int.MaxValue);
        }

        public Vector(params int[] integers) : this(integers.Length) {
            data = integers;
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

        // метод для работы с ref/out параметрами
        public void decreaseFirst(ref int value, out int index) {
            index = -1;
            for (int i = 0; i < Size; i++) {
                if (this[i] == value) {
                    index = i;
                    this[i]--;
                    value--;
                    return;
                }
            }
        }

        // override object.Equals
        public override bool Equals(object obj) {
            if ((obj == null) || (GetType() != obj.GetType())) {
                return false;
            }
            return ((Vector)obj).id == id;
        }

        // override object.GetHashCode
        public override int GetHashCode() {
            return id.GetHashCode();
        }

        public override string ToString() {
            StringBuilder result = new StringBuilder();
            result.Append(classDysplayName).Append(" [size = ").Append(Size).Append(", id = ").Append(id).Append("]: {");
            for (int i = 0; i < Size; i++) {
                if (i != 0) {
                    result.Append(", ");
                }
                result.Append(i).Append(": ").Append(this[i]);
            }
            result.Append("}");
            return result.ToString();
        }
    }
}
