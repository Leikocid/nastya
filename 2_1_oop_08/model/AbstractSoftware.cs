using System;
using System.Text;

namespace ns_2_1_oop {
    public abstract class AbstractSoftware : AbstractObject {
        public string Name { get; }

        public string Version { get; }

        public DateTime ReleaseDate { get; }


        public AbstractSoftware(string name, string version, DateTime releaseDate) {
            if (name == null) {
                throw new ArgumentException("Name must be specified");
            }
            Name	= name;
            Version	= version;
            ReleaseDate = releaseDate;
        }

        public override bool Equals(object obj) {
            if ((obj == null) || !(obj is AbstractSoftware)) {
                return false;
            }
            AbstractSoftware other = obj as AbstractSoftware;
            if ((Name != null) && Name.Equals(other.Name)) {
                return Version != null && Version.Equals(other.Version);
            }
            return false;
        }

        public override int GetHashCode() {
            int result = Name.GetHashCode();
            if (Version != null) {
                result = result * 31 ^ Version.GetHashCode();
            }
            return result;
        }

        public override string ToString() {
            StringBuilder result = new StringBuilder();
            result.Append(GetType()).Append(": {Name = ").Append(Name);
            if (Version != null) {
                result.Append(", Version = ").Append(Version);
            }
            if (ReleaseDate != null) {
                result.Append(", ReleaseDate = ").Append(ReleaseDate.Date);
            }
            result.Append("}");
            return result.ToString();
        }
    }
}
