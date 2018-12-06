using System;
using System.Text;
using System.Collections;
using System.Collections.Generic;

namespace ns_2_1_oop {
    [Serializable]
    public class SoftwareArray : Array<Software> {
        public SoftwareArray() : base() {}

        public SoftwareArray(params Software[] values) : base(values) {}
    }
}
