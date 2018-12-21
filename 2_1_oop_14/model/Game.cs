using System;
using System.Text;
using System.Runtime.Serialization;

namespace ns_2_1_oop {
    public enum Genre {
        Strategy, Action, Puzzle
    }
    [Serializable]
    [DataContract]
    public class Game : Software {
        [DataMember]
        public Genre Genre { get; set; }

        [DataMember]
        public byte ageLimit { get; set; }

        public Game() {}

        public Game(string name, string version, int releaseYear, Genre genre) : base(name, version, releaseYear) {
            Genre = genre;
        }

        public override string ToString() {
            StringBuilder result = new StringBuilder(base.ToString());
            result.Append(" (Genre = ").Append(Genre).Append(")");
            return result.ToString();
        }
    }
}
