using System;
using System.Text;
using System.Xml.Serialization;
using System.Runtime.Serialization;

namespace ns_2_1_oop {
    [Serializable]
    [DataContract]
    public sealed  class TextProcessor : Software {
        [DataMember]
        public string[] WorkExtensions { get; set; }

        public TextProcessor() {}

        public TextProcessor(string name, string version, int releaseYear, string[] workExtensions) : base(name, version, releaseYear) {
            WorkExtensions = workExtensions;
        }

        public override string ToString() {
            StringBuilder result = new StringBuilder(base.ToString());
            if (WorkExtensions != null) {
                result.Append(" (WorkExtensions = ").Append(string.Join(", ", WorkExtensions)).Append(")");
            }
            return result.ToString();
        }

        private bool freeStatus = true;


        public void SetFree(bool isFree) {
            this.freeStatus = isFree;
        }

        public override bool IsFree() {
            return freeStatus;
        }
    }
}
