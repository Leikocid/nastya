using System;
using System.Text;
using System.Runtime.Serialization;

namespace ns_2_1_oop {
    [Serializable]
    [DataContract]
    public abstract class AbstractObject {
        public abstract string GetCreator();
    }
}
