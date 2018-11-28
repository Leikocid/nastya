using System;

namespace ns_2_1_oop_05 {
    public enum Platform {
        Windows = 1, MacOS, Linux, Android, iOS
    }

    public class Software {
        public string Name { get; }

        public string Version { get; }

        public DateTime ReleaseDate { get; }

        public Platform[] targetPlatforms { get; set; }

        public Developer developer { get; set; }


        public Software(string name, string version, DateTime releaseDate) {
            Name	= name;
            Version	= version;
            ReleaseDate = releaseDate;
        }
    }
}
