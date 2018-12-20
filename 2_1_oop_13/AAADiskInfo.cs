using System;
using System.IO;

namespace ns_2_1_oop {
    public class AAADiskInfo {
        public void diskInfo() {
            Console.WriteLine("DiskInfo");
            DriveInfo[] drives = DriveInfo.GetDrives();
            foreach (DriveInfo drive in drives) {
                Console.WriteLine("\tName: {0}", drive.Name);
                Console.WriteLine("\tType: {0}", drive.DriveType);

                if (drive.IsReady) {
                    Console.WriteLine("\tFormat: {0}", drive.DriveFormat);
                    Console.WriteLine("\tFreeSpace: available - {0} MB, total - {1} MB",
                                      drive.AvailableFreeSpace / 1024 / 1024,
                                      drive.TotalFreeSpace / 1024 / 1024);
                    Console.WriteLine("\tCapacity: {0} GB", drive.TotalSize / 1024 / 1024 / 1024);
                }
                Console.WriteLine();
            }
        }
    }
}
