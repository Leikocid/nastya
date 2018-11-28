using System;

namespace ns_2_1_oop_05 {
    public class Game : Software {
        public string Genre { get; }

        public byte ageLimit { get; set; }

        public Game(string name, string version, DateTime releaseDate, string genre) : base(name, version, releaseDate) {
            Genre = genre;
        }
    }
}
