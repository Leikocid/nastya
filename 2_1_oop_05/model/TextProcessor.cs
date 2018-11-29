using System;
using System.Text;

namespace ns_2_1_oop_05 {
    public sealed class TextProcessor : Software, IHasHTMLPresentation {
        public string[] WorkExtensions { get; }

        private bool freeStatus = true;


        public TextProcessor(string name, string version, DateTime releaseDate, string[] workExtensions) : base(name, version, releaseDate) {
            WorkExtensions = workExtensions;
        }

        public string getHTML() {
            return $"<div class=\"text_precessor\">{Name} - {Version}</div>";
        }

        public void setFree(bool isFree) {
            this.freeStatus = isFree;
        }

        public override bool isFree() {
            return freeStatus;
        }

        string IHasHTMLPresentation.getCreator() {
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
