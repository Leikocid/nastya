using System;
using System.Linq;
using System.Collections.Generic;

namespace ns_2_1_oop {
    class Program {
        static void Main(string[] args) {
            Reflector reflector = new Reflector();
            reflector.printClass(typeof(Vector).ToString(),			  "Vector.txt");
            reflector.printClass(typeof(Array).ToString(),			  "Array.txt");
            reflector.printClass(typeof(System.Collections.ArrayList).ToString(), "ArrayList.txt");
            reflector.printClass(typeof(System.String).ToString(),		  "String.txt");
        }
    }
}
