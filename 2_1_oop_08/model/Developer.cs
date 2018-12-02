using System;

namespace ns_2_1_oop {
    public class Developer : AbstractObject, IHasHTMLPresentation {
        public string Name { get; }

        public Developer(string name) {
            Name = name;
        }

        public string getHTML() {
            return $"<div class=\"developer\">{Name}</div>";
        }

        string IHasHTMLPresentation.getCreator() {
            return "HTML publisher";
        }

        public override string getCreator() {
            return Name;
        }
    }
}
