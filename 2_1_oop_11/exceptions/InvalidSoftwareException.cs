using System;
using System.Text;

namespace ns_2_1_oop {
    public class InvalidSoftwareException : ModelException {
        public InvalidSoftwareException(string message) : base(message) {}
    }
}
