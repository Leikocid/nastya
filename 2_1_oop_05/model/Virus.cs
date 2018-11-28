using System;

namespace ns_2_1_oop_05 {
    public class Virus : Software {
        public string Type { get; }

        public Virus(string name, string version, DateTime releaseDate, string type) : base(name, version, releaseDate) {
            Type = type;
        }
    }
}
