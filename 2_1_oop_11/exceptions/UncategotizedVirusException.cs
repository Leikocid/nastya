using System;
using System.Text;

namespace ns_2_1_oop {
    public class UncategotizedVirusException : ModelException {
        public UncategotizedVirusException() : base("Virus have to be categotized") {}
    }
}
