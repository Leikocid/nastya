using System;

namespace ns_2_1_oop_05 {
    public class TextProcessor : Software {
        public string[] WorkExtensions { get; }

        public TextProcessor(string name, string version, DateTime releaseDate, string[] workExtensions) : base(name, version, releaseDate) {
            WorkExtensions = workExtensions;
        }
    }
}
