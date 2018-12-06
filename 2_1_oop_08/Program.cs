using System;
using System.Collections.Generic;

using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

namespace ns_2_1_oop {
    class Program {
        static void Main(string[] args) {
            Console.WriteLine("Arrays:");
            Array<int> a111	    = new Array<int>(1, 1, 1);
            Array<int> a222	    = new Array<int>(2, 2, 2);
            StructArray<int> a11    = new StructArray<int>(1, 1);
            StructArray<int> a222_2 = new StructArray<int>(2, 2, 2);
            StructArray<int> a_neg  = new StructArray<int>(2, -1, 2);

            Console.WriteLine($"a111: {a111}");
            Console.WriteLine($"a222: {a222}");
            Console.WriteLine($"a11: {a11}");
            Console.WriteLine($"a222_2: {a222_2}");
            Console.WriteLine($"a_neg: {a_neg}");

            Console.WriteLine($"a222 == a222_2 ? = {(a222==a222_2?true:false)}");

            Console.WriteLine($"MathOperation.count(a111) = {MathOperation.count(a111)}");
            Console.WriteLine($"MathOperation.max(a11) = {MathOperation.max(a11)}");
            Console.WriteLine($"MathOperation.min(a_neg) = {MathOperation.min(a_neg)}");

            Console.WriteLine($"\"Text\".Contains(\"T\") = {"Text".Contains("T")}");
            a_neg.RemoveNegative();
            Console.WriteLine($"a_neg after a_neg.RemoveNegative(): {a_neg}");

            StructArray<double> sa1 = new StructArray<double>(1.1, 1.2, 1.3);
            sa1.Remove(1.2);
            sa1.Add(1.4);
            Console.WriteLine($"sa1: {sa1}");

            try {
                a111.removeAt(5);
            } catch (Exception e) {
                Console.WriteLine(e);
            }

            SoftwareArray sa2 = new SoftwareArray();
            TextProcessor t1  = new TextProcessor("Word", "2012", new DateTime(2012, 1, 1), new string[] { "txt", "doc" });
            sa2.Add(t1);
            TextProcessor t2 = new TextProcessor("Word", "2016", new DateTime(2016, 1, 1), new string[] { "txt", "doc", "docx" });
            sa2.Add(t2);
            Virus v1 = new Virus("MyDoom", "1", new DateTime(2011, 1, 1), "worm");
            sa2.Add(v1);
            Console.WriteLine($"sa2: {sa2}");

            // сериализация/десериализация в бинарный файл
            BinaryFormatter formatter = new BinaryFormatter();
            using (FileStream fs = new FileStream("software.dat", FileMode.OpenOrCreate)) {
                formatter.Serialize(fs, sa2);
                Console.WriteLine("Объект сериализован");
            }
            using (FileStream fs = new FileStream("software.dat", FileMode.OpenOrCreate)) {
                SoftwareArray sa3 = (SoftwareArray)formatter.Deserialize(fs);
                Console.WriteLine("Объект десериализован");
                Console.WriteLine($"sa3: {sa3}");
            }

            using (FileStream fs = new FileStream("double.dat", FileMode.OpenOrCreate)) {
                formatter.Serialize(fs, sa1);
                Console.WriteLine("Объект сериализован");
            }
            using (FileStream fs = new FileStream("double.dat", FileMode.OpenOrCreate)) {
                StructArray<double> sa4 = (StructArray<double>)formatter.Deserialize(fs);
                Console.WriteLine("Объект десериализован");
                Console.WriteLine($"sa4: {sa4}");
            }
        }
    }
}
