
using System;
using System.Collections.Generic;

namespace ns_2_1_oop {
    public interface IAccessable<T>: IEnumerable<T> {
        void Add(T element);
        void Remove(T element);
    }
}
