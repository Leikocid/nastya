
using System;
using System.IO;

namespace ns_2_1_oop {
    public class AAAFileInfo {
        public void fileInfo(string fileName) {
            Console.WriteLine("FileInfo");
            FileInfo fileInf = new FileInfo(fileName);
            if (fileInf.Exists) {
                Console.WriteLine("\tFull path : {0}", fileInf.DirectoryName);
                Console.WriteLine("\tName: {0}",       fileInf.Name);
                Console.WriteLine("\tCapacity: {0} KB\n\tExtension: {1}\n\tCreationTime: {2}",
                                  fileInf.Length / 1024,
                                  fileInf.Extension,
                                  fileInf.CreationTime);
            } else {
                Console.WriteLine("This file doesn't exists");
            }
        }
    }
}
