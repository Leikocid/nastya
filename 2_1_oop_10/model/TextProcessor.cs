using System;
using System.Text;

namespace ns_2_1_oop {
    public sealed partial class TextProcessor : Software, IHasHTMLPresentation {
        public string[] WorkExtensions { get; }


        public TextProcessor(string name, string version, DateTime releaseDate, string[] workExtensions) : base(name, version, releaseDate) {
            WorkExtensions = workExtensions;
        }

        public string GetHTML() {
            return $"<div class=\"text_precessor\">{Name} - {Version}</div>";
        }

        string IHasHTMLPresentation.GetCreator() {
            return "HTML publisher";
        }

        public override string ToString() {
            StringBuilder result = new StringBuilder(base.ToString());
            if (WorkExtensions != null) {
                result.Append(" (WorkExtensions = ").Append(string.Join(", ", WorkExtensions)).Append(")");
            }
            return result.ToString();
        }
    }
}
