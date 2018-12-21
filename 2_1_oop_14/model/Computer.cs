using System;

using System.Collections.Generic;
using System.Collections;
using System.Xml.Serialization;
using System.Runtime.Serialization;


namespace ns_2_1_oop {
    [Serializable]
    [DataContract]
    public class Computer {
        public Computer() {}

        [DataMember]
        public List<AbstractSoftware> softwares = new List<AbstractSoftware>();

        public void AddSoftware(AbstractSoftware software) {
            softwares.Add(software);
        }

        public List<AbstractSoftware> GetSoftwares() {
            return new List<AbstractSoftware>(softwares);
        }

        public void RemoveSoftwareAt(int index) {
            if ((index < 0) || (index >= softwares.Count)) {
                throw new IndexOutOfRangeException();
            }
            softwares.RemoveAt(index);
        }

        public void SetSoftwareAt(AbstractSoftware software, int index) {
            if ((index < 0) || (index >= softwares.Count)) {
                throw new IndexOutOfRangeException();
            }
            softwares[index] = software;
        }

        public int GetSoftwareCount() {
            return softwares.Count;
        }

        public AbstractSoftware GetSoftwareAt(int index) {
            if ((index < 0) || (index >= softwares.Count)) {
                throw new IndexOutOfRangeException();
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
