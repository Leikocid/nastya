using System;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

namespace ns_2_1_oop {
    class Program {
        static void Main(string[] args) {
            try {
                Console.Write("Create model...");
                Developer d1 = new Developer("Instinctools Gmbh");
                Developer d2 = new Developer("s_t_u_d_y");
                d2.contact.firstName = "Anastasia";
                d2.contact.lastName  = "Astakhova";
                Computer c1 = new Computer();
                Game	 g1 = new Game("World of Tanks", "1.0", new DateTime(2018, 1, 1), Genre.Strategy);
                g1.Developer = d2;
                c1.AddSoftware(g1);
                TextProcessor t1 = new TextProcessor("Word", "2012", new DateTime(2012, 1, 1), new string[] { "txt", "doc" });
                t1.Developer = d1;
                c1.AddSoftware(t1);
                TextProcessor t2 = new TextProcessor("Word", "2016", new DateTime(2016, 1, 1), new string[] { "txt", "doc", "docx" });
                t2.Developer = d2;
                c1.AddSoftware(t2);
                Console.WriteLine("OK");

                // сериализация/десериализация в бинарный файл
                BinaryFormatter formatter = new BinaryFormatter();
                using (FileStream fs = new FileStream("software.dat", FileMode.OpenOrCreate)) {
                    formatter.Serialize(fs, c1);
                    Console.WriteLine("Объект сериализован");
                }
                using (FileStream fs = new FileStream("software.dat", FileMode.OpenOrCreate)) {
                    Computer c2 = (Computer)formatter.Deserialize(fs);
                    Console.WriteLine("Объект десериализован");
                    Console.WriteLine($"c2: {c2}");
                }
            } catch (Exception ex) {
                Console.WriteLine($"Error: {ex.Message}");
            }
        }
    }
}
