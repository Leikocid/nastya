using System;
using System.Text;
using System.Collections;
using System.Collections.Generic;

namespace ns_2_1_oop {
    [Serializable]
    public class StructArray<T>: Array<T> where T : struct {
        public StructArray() : base() {}

        public StructArray(params T[] values) : base(values) {}
    }
}
