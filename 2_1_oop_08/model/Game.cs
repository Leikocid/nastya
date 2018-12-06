using System;
using System.Text;

namespace ns_2_1_oop {
    [Serializable]
    public class Game : Software, IHasHTMLPresentation {
        public string Genre { get; }

        public byte ageLimit { get; set; }


        public Game(string name, string version, DateTime releaseDate, string genre) : base(name, version, releaseDate) {
            Genre = genre;
        }

        public string getHTML() {
            return $"<div class=\"game\">{Name}</div>";
        }

        public override string ToString() {
            StringBuilder result = new StringBuilder(base.ToString());
            if (Genre != null) {
                result.Append(" (Genre = ").Append(Genre).Append(")");
            }
            return result.ToString();
        }
    }
}
