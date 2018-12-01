using System;

namespace ns_2_1_oop_05 {
    public class Developer : AbstractObject, IHasHTMLPresentation {
        public string Name { get; }

        public Contact contact = new Contact();

        public Developer(string name) {
            Name = name;
        }

        public string GetHTML() {
            return $"<div class=\"developer\">{Name}</div>";
        }

        string IHasHTMLPresentation.GetCreator() {
            return "HTML publisher";
        }

        public override string GetCreator() {
            return Name;
        }
    }
}
