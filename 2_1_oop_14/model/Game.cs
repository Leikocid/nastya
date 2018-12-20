using System;
using System.Text;
namespace ns_2_1_oop {
    public enum Genre {
        Strategy, Action, Puzzle
    }
    [Serializable]
    public class Game : Software, IHasHTMLPresentation {
        public Genre Genre { get; protected set; }

        public byte ageLimit { get; set; }

        public Game(string name, string version, DateTime releaseDate, Genre genre) : base(name, version, releaseDate) {
            Genre = genre;
        }

        public string GetHTML() {
            return $"<div class=\"game\">{Name}</div>";
        }

        public override string ToString() {
            StringBuilder result = new StringBuilder(base.ToString());
            result.Append(" (Genre = ").Append(Genre).Append(")");
            return result.ToString();
        }
    }
}
