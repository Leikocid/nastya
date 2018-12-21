using System;
using System.Text;
using System.Runtime.Serialization;

namespace ns_2_1_oop {
    [Serializable]
    [DataContract]
    public abstract class AbstractSoftware : AbstractObject, IComparable<AbstractSoftware> {
        [DataMember]
        public string Name { get; set; }


        [DataMember]
        public string Version { get; set; }


        [DataMember]
        public int ReleaseYear { get; set; }

        public AbstractSoftware() {}

        public AbstractSoftware(string name, string version, int releaseYear) {
            if (name == null) {
                throw new ArgumentException("Name must be specified");
            }
            Name	     = name;
            Version	     = version;
            this.ReleaseYear = releaseYear;
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

            if (ReleaseYear != 0) {
                result.Append(", ReleaseDate = ").Append(ReleaseYear);
            }
            result.Append("}");
            return result.ToString();
        }

        public int CompareTo(AbstractSoftware other) {
            int result = this.Name.CompareTo(other.Name);
            if (result == 0) {
                result = this.Version.CompareTo(other.Version);
            }
            return result;
        }
    }
}
