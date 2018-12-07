using System;

namespace ns_2_1_oop {
    public class Printer {
        public void iAmPrinting(AbstractObject obj) {
            Console.WriteLine($"{obj.ToString()} by {obj.GetCreator()}");
        }
    }
}
