using System;
using System.Diagnostics;
using System.Xml.Serialization;
using System.Runtime.Serialization;

namespace ns_2_1_oop {
    [Serializable]
    [DataContract]
    public class Developer : AbstractObject {
        [XmlAttribute]
        [DataMember]
        public string Name { get; set; }

        [DataMember]
        public Contact contact = new Contact();

        public Developer() {}

        public Developer(string name) {
            Name = name;
        }

        public override string GetCreator() {
            return Name;
        }
    }
}
