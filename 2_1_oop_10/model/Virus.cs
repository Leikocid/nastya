using System;
using System.Text;

namespace ns_2_1_oop {
    public class Virus : Software {
        public string Type { get; }

        public Virus(string name, string version, DateTime releaseDate, string type) : base(name, version, releaseDate) {
            if ((type == null) || (type.Length == 0)) {
                throw new UncategotizedVirusException();
            }
            Type = type;
        }

        public override bool IsFree() {
            return true;
        }

        public override string ToString() {
            StringBuilder result = new StringBuilder(base.ToString());
            if (Type != null) {
                result.Append(" (Type = ").Append(Type).Append(")");
            }
            return result.ToString();
        }
    }
}
