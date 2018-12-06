using System;

namespace ns_2_1_oop {
    class User {
        private double volume = 0;

        public delegate void MoveDelegate(string message, double result);
        public event MoveDelegate MOVE;

        public delegate void CompressDelegate(string message, double result);
        public event CompressDelegate COMPRESS;


        public void move(double offset) {
            volume += offset;

            MOVE?.Invoke($"Перемещено на {offset}", volume);
        }

        public void compress(double factor) {
            volume *= factor;

            COMPRESS?.Invoke($"Сжато в {factor}", volume);
        }
    }
}
