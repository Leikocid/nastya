using System;
using System.Runtime.Serialization;

namespace ns_2_1_oop {
    [Serializable]
    [DataContract]
    public struct Contact {
        [DataMember]
        public string firstName;
        [DataMember]
        public string middleName;
        [DataMember]
        public string lastName;
        [DataMember]
        public string phone;
        [DataMember]
        public string email;
        [DataMember]
        public string telegram;
    }
}
