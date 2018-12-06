using System;

namespace ns_2_1_oop_05 {
    public enum Platform {
        Windows = 1, MacOS, Linux, Android, iOS
    }

    public class Software : AbstractSoftware {
        public Platform[] TargetPlatforms { get; set; }

        public Developer Developer { get; set; }

        public Software(string name, string version, DateTime releaseDate) : base(name, version, releaseDate) {}

        public virtual bool isFree() {
            return true;
        }

        public override string getCreator() {
            if (Developer == null) {
                return "unknown";
            } else {
                return Developer.Name;
            }
        }
    }
}
