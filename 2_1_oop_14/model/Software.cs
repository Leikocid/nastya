using System;
using System.Runtime.Serialization;

namespace ns_2_1_oop {
    public enum Platform {
        Windows = 1, MacOS, Linux, Android, iOS
    }
    [Serializable]
    [DataContract]
    public class Software :  AbstractSoftware {
        [DataMember]
        public Platform[] TargetPlatforms { get; set; }

        [DataMember]
        public Developer Developer { get; set; }

        public Software() {}

        public Software(string name, string version, int releaseYear) : base(name, version, releaseYear)  {}

        public virtual bool IsFree() {
            return true;
        }

        public override string GetCreator() {
            if (Developer == null) {
                return "unknown";
            } else {
                return Developer.Name;
            }
        }
    }
}
