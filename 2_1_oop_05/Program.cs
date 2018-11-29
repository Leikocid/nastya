using System;
using System.Collections.Generic;

namespace ns_2_1_oop_05 {
    class Program {
        static void Main(string[] args) {
            List<object> allObjects = new List<object>();
            Console.Write("Create model...");
            Developer d1 = new Developer("Instinctools Gmbh");
            allObjects.Add(d1);
            Developer d2 = new Developer("Anastasia Astakhova");
            allObjects.Add(d2);
            TextProcessor t1 = new TextProcessor("Word", "2012", new DateTime(2012, 1, 1), new string[] { "txt", "doc" });
            t1.Developer = d1;
            allObjects.Add(t1);
            TextProcessor t2 = new TextProcessor("Word", "2016", new DateTime(2016, 1, 1), new string[] { "txt", "doc", "docx" });
            t2.Developer = d2;
            allObjects.Add(t2);
            Game g1 = new Game("World of Tanks", "1.0", new DateTime(2018, 1, 1), "strategic");
            g1.Developer = d2;
            allObjects.Add(g1);
            Virus v1 = new Virus("MyDoom", "1", new DateTime(2011, 1, 1), "worm");
            allObjects.Add(v1);
            Console.WriteLine("[OK]");


            Console.WriteLine("Objects:");
            foreach (object o in allObjects) {
                if (o is Software) {
                    Software s = o as Software;
                    Console.WriteLine($"{s.ToString()} by {s.getCreator()}");
                } else if (o is Developer) {
                    Developer d = o as Developer;
                    Console.WriteLine($"{d.ToString()}: {d.Name}");
                }
            }

            Console.WriteLine("HTML Catalog:");
            foreach (object o in allObjects) {
                if (o is IHasHTMLPresentation) {
                    Console.WriteLine((o as IHasHTMLPresentation).getHTML() +
                                      " - html created by " + (o as IHasHTMLPresentation).getCreator());
                } else {
                    Console.WriteLine($"<div>{o.ToString()}</div>");
                }
            }

            Console.WriteLine("Printer:");
            Printer p = new Printer();
            foreach (object o in allObjects) {
                p.iAmPrinting(o as AbstractObject);
            }
        }
    }
}
