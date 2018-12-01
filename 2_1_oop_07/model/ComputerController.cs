using System;
using System.Collections.Generic;

namespace ns_2_1_oop_05 {
    public class ComputerController {
        public List<Game> FindGames(Computer computer, Genre genre) {
            List<Game> result = new List<Game>();
            foreach (AbstractSoftware s in computer.GetSoftwares()) {
                if (s is Game) {
                    Game g = s as Game;
                    if (g.Genre == genre) {
                        result.Add(g);
                    }
                }
            }
            return result;
        }

        public TextProcessor FindTextProcessor(Computer computer, string name, string version) {
            foreach (AbstractSoftware s in computer.GetSoftwares()) {
                if (s is TextProcessor) {
                    TextProcessor t = s as TextProcessor;
                    if (t.Name.Equals(name) && (t.Version.Equals(version))) {
                        return t;
                    }
                }
            }
            return null;
        }

        public void PrintSoftwareAlphabetically(Computer computer) {
            List<AbstractSoftware> softwares = computer.GetSoftwares();
            softwares.Sort();
            Console.WriteLine("Software in computer alphabetically:");
            foreach (AbstractSoftware s in softwares) {
                Console.WriteLine($"{s.ToString()} by {s.GetCreator()}");
            }
        }
    }
}
