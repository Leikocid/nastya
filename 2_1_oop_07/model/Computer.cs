using System;
using System.Collections.Generic;

namespace ns_2_1_oop_05 {
    public class Computer {
        private List<AbstractSoftware> softwares = new List<AbstractSoftware>();

        public void AddSoftware(AbstractSoftware software) {
            softwares.Add(software);
        }

        public List<AbstractSoftware> GetSoftwares() {
            return new List<AbstractSoftware>(softwares);
        }

        public void RemoveSoftwareAt(int index) {
            if ((index >= 0) && (index < softwares.Count)) {
                softwares.RemoveAt(index);
            }
        }

        public void SetSoftwareAt(AbstractSoftware software, int index) {
            if ((index >= 0) && (index < softwares.Count)) {
                softwares[index] = software;
            }
        }

        public int GetSoftwareCount() {
            return softwares.Count;
        }

        public AbstractSoftware GetSoftwareAt(int index) {
            if ((index < 0) || (index >= softwares.Count)) {
                return null;
            }
            return softwares[index];
        }

        public void PrintSoftware() {
            Console.WriteLine("Software in computer:");
            foreach (AbstractSoftware s in softwares) {
                Console.WriteLine($"{s.ToString()} by {s.GetCreator()}");
            }
        }
    }
}
