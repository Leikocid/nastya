using System;
using System.Text;

namespace ns_2_1_oop_05 {
    public sealed partial class TextProcessor : Software, IHasHTMLPresentation {
        private bool freeStatus = true;


        public void SetFree(bool isFree) {
            this.freeStatus = isFree;
        }

        public override bool IsFree() {
            return freeStatus;
        }
    }
}
