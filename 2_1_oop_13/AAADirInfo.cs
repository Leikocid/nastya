using System;
using System.IO;

namespace ns_2_1_oop {
    public class AAADirInfo {
        public void dirInfo(string path) {
            Console.WriteLine("DirInfo");
            if (Directory.Exists(path)) {
                string[] files = Directory.GetFiles(path);
                int countFiles = 0;
                foreach (string s in files) {
                    countFiles++;
                }
                Console.WriteLine($"\tCountOfFiles: {countFiles}");

                DirectoryInfo dirInfo = new DirectoryInfo(path);
                Console.WriteLine($"\tCreationTime: {dirInfo.CreationTime}");

                string[] dirs	= Directory.GetDirectories(path);
                int countSubDir = 0;
                foreach (string s in dirs) {
                    countSubDir++;
                }
                Console.WriteLine($"\tCountOfSubDirectories: {countSubDir}");

                Console.WriteLine($"\tParent: {dirInfo.Parent}");
            } else {
                Console.WriteLine("This directory doesn't exists");
            }
        }
    }
}
