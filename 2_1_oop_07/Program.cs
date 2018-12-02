using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace ns_2_1_oop_05 {
    class Program {
        static void Main(string[] args) {
            List<object> allObjects = new List<object>();
            Console.Write("Create model...");
            Developer d1 = new Developer("Instinctools Gmbh");
            allObjects.Add(d1);
            Developer d2 = new Developer("s_t_u_d_y");
            d2.contact.firstName = "Anastasia";
            d2.contact.lastName	 = "Astakhova";
            allObjects.Add(d2);

            Computer c1 = new Computer();
            allObjects.Add(c1);

            Game g1 = new Game("World of Tanks", "1.0", new DateTime(2018, 1, 1), Genre.Strategy);
            g1.Developer = d2;
            c1.AddSoftware(g1);
            allObjects.Add(g1);

            TextProcessor t1 = new TextProcessor("Word", "2012", new DateTime(2012, 1, 1), new string[] { "txt", "doc" });
            t1.Developer = d1;
            c1.AddSoftware(t1);
            allObjects.Add(t1);

            TextProcessor t2 = new TextProcessor("Word", "2016", new DateTime(2016, 1, 1), new string[] { "txt", "doc", "docx" });
            t2.Developer = d2;
            c1.AddSoftware(t2);
            allObjects.Add(t2);

            Virus v1 = new Virus("MyDoom", "1", new DateTime(2011, 1, 1), "worm");
            allObjects.Add(v1);
            Console.WriteLine("[OK]");


            Console.WriteLine("All Objects:");
            foreach (object o in allObjects) {
                if (o is Software) {
                    Software s = o as Software;
                    Console.WriteLine($"{s.ToString()} by {s.GetCreator()}");
                } else if (o is Developer) {
                    Developer d = o as Developer;
                    Console.WriteLine($"{d.ToString()}: {d.Name}");
                } else {
                    Console.WriteLine($"{o.ToString()}");
                }
            }

            Console.WriteLine("HTML Catalog:");
            foreach (object o in allObjects) {
                if (o is IHasHTMLPresentation) {
                    Console.WriteLine((o as IHasHTMLPresentation).GetHTML() +
                                      " - html created by " + (o as IHasHTMLPresentation).GetCreator());
                } else {
                    Console.WriteLine($"<div>{o.ToString()}</div>");
                }
            }

            Console.WriteLine("Printer:");
            Printer p = new Printer();
            foreach (object o in allObjects) {
                if (o is AbstractObject) {
                    p.iAmPrinting(o as AbstractObject);
                }
            }

            c1.PrintSoftware();

            ComputerController cc = new ComputerController();
            List<Game> games	  = cc.FindGames(c1, Genre.Strategy);
            Console.WriteLine($"Found {games.Count} games in computer");
            TextProcessor textProcessor = cc.FindTextProcessor(c1, "Word", "2016");
            if (textProcessor == null) {
                Console.WriteLine($"TextProcessor not Found");
            } else {
                Console.WriteLine($"Found {textProcessor.ToString()}");
            }
            cc.PrintSoftwareAlphabetically(c1);

            try {
                c1.AddSoftware(v1);
            } catch (ModelException e) {
                Console.WriteLine($"EXCEPTION {e.GetType()}: {e.Message}\n{e.StackTrace}");
            }
            try {
                c1.AddSoftware(t1);
            } catch (DuplicateSoftwareException e) {
                Console.WriteLine($"EXCEPTION {e.GetType()}: {e.Message}\n{e.StackTrace}");
            }
            try {
                new Virus("MyDoom", "2", new DateTime(2011, 1, 1), "");
            } catch (Exception e) {
                Console.WriteLine($"EXCEPTION {e.GetType()}: {e.Message}\n{e.StackTrace}");
            }
            try {
                new Developer(null);
            } catch (ModelException e) {
                Console.WriteLine($"EXCEPTION {e.GetType()}: {e.Message}\n{e.StackTrace}");
            }
        }
    }
}
