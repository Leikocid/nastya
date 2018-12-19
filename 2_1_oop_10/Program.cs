using System;

using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections.Specialized;

namespace ns_2_1_oop {
    public class Student {}

    class Program {
        static void Main(string[] args) {
            ArrayList l1 = new ArrayList();
            l1.Add(33);
            l1.Add(35);
            l1.Add(37);
            l1.Add(23);
            l1.Add(25);

            Student s = new Student();
            l1.Add( s);

            l1.Remove(37);

            Console.Write($"l1 (Count={l1.Count}): ");
            for (int i = 0; i < l1.Count; i++) {
                if (i != 0) {
                    Console.Write(", ");
                }
                Console.Write(l1[i]);
            }
            Console.WriteLine();

            int idx = l1.IndexOf(35);
            Console.WriteLine($"element (idx = {idx}) found: {l1[idx]}");

            idx = l1.IndexOf(s);
            Console.WriteLine($"element (idx = {idx}) found: {l1[idx]}");

            // 2.
            Stack<char> st = new Stack<char>();
            st.Push('a');
            st.Push('r');
            st.Push('t');
            st.Push('a');
            st.Push('m');
            st.Push('d');
            st.Push('e');

            Console.Write($"st (Count={st.Count}): ");
            for (int i = 0; i < st.Count; i++) {
                if (i != 0) {
                    Console.Write(", ");
                }
                Console.Write(st.ToArray()[i]);
            }
            Console.WriteLine();

            for (int i = 0; i < 3; i++) {
                st.Pop();
            }
            st.Push('t');

            List<char> l2 = new List<char>();
            char c;
            while (st.TryPop(out c)) {
                l2.Add(c);
            }

            Console.Write($"l2 (Count={l2.Count}): ");
            for (int i = 0; i < l2.Count; i++) {
                if (i != 0) {
                    Console.Write(", ");
                }
                Console.Write(l2[i]);
            }
            Console.WriteLine();

            idx = l2.IndexOf('r');
            Console.WriteLine($"element (idx = {idx}) found: {l2[idx]}");

            // 3.
            Stack<Software> st2 = new Stack<Software>();
            st2.Push(new Game("World of Tanks", "1.0", new DateTime(2018, 1, 1), Genre.Strategy));
            st2.Push(new TextProcessor("Word", "2012", new DateTime(2012, 1, 1), new string[] { "txt", "doc" }));
            st2.Push(new TextProcessor("Word", "2016", new DateTime(2016, 1, 1), new string[] { "txt", "doc", "docx" }));
            st2.Push(new Virus("MyDoom", "1", new DateTime(2011, 1, 1), "worm"));
            st2.Push(new Game("Miner", "1.0", new DateTime(2018, 1, 1), Genre.Puzzle));
            st2.Push(new Game("Miner", "2.0", new DateTime(2018, 1, 1), Genre.Puzzle));
            st2.Push(new Game("Miner", "3.0", new DateTime(2018, 1, 1), Genre.Puzzle));

            Console.Write($"st2 (Count={st2.Count}):\n");
            for (int i = 0; i < st2.Count; i++) {
                if (i != 0) {
                    Console.Write(",\n");
                }
                Console.Write(st2.ToArray()[i]);
            }
            Console.WriteLine();

            for (int i = 0; i < 3; i++) {
                st2.Pop();
            }
            Game g = new Game("Miner", "4.0", new DateTime(2018, 1, 1), Genre.Puzzle);
            st2.Push(g);

            List<Software> l3 = new List<Software>();
            foreach (Software soft in st2) {
                l3.Add(soft);
            }

            Console.Write($"l3 (Count={l3.Count}):\n");
            for (int i = 0; i < l3.Count; i++) {
                if (i != 0) {
                    Console.Write(",\n");
                }
                Console.Write(l3[i]);
            }
            Console.WriteLine();

            idx = l3.IndexOf(g);
            Console.WriteLine($"element (idx = {idx}) found: {l3[idx]}");

            // 4.
            ObservableCollection<Software> o = new ObservableCollection<Software>(){
                new Game("World of Tanks", "1.0", new DateTime(2018, 1, 1), Genre.Strategy),
                new TextProcessor("Word", "2012", new DateTime(2012, 1, 1), new string[] { "txt", "doc" }),
                new TextProcessor("Word", "2016", new DateTime(2016, 1, 1), new string[] { "txt", "doc", "docx" }),
                new Virus("MyDoom", "1", new DateTime(2011, 1, 1), "worm")
            };
            o.CollectionChanged += onCollectionChanged;

            o.Add(new Game("Miner", "2.0", new DateTime(2018, 1, 1), Genre.Puzzle));
            o.RemoveAt(1);
            o[0] = new Game("Miner", "3.0", new DateTime(2018, 1, 1), Genre.Puzzle);
        }

        private static void onCollectionChanged(object sender, NotifyCollectionChangedEventArgs e) {
            switch (e.Action) {
                case NotifyCollectionChangedAction.Add: { // если добавление
                    Software s = e.NewItems[0] as Software;
                    Console.WriteLine($"Добавлен новый объект: {s}");
                    break;
                }
                case NotifyCollectionChangedAction.Remove: { // если удаление
                    Software s = e.OldItems[0] as Software;
                    Console.WriteLine($"Удален объект: {s}");
                    break;
                }
                case NotifyCollectionChangedAction.Replace: { // если замена
                    Software s1 = e.OldItems[0] as Software;
                    Software s2 = e.NewItems[0] as Software;
                    Console.WriteLine($"Объект {s1} заменен объектом {s2}");
                    break;
                }
            }
        }
    }
}
