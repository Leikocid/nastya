using System;
using System.Text;

namespace ns_2_1_oop_05 {
    public class DuplicateSoftwareException : ModelException {
        public DuplicateSoftwareException() : base("Computer already contains this Software") {}
    }
}
