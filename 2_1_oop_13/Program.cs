using System;
using System.IO;
namespace ns_2_1_oop {
    class Program {
        static void Main(string[] args) {
            try {
                // 2.
                AAALog.log("Вывод информации о дисках");
                AAADiskInfo diskInfo = new AAADiskInfo();
                diskInfo.diskInfo();

                // 3.
                AAALog.log("Вывод информации о файле " + AAALog.LOG_FILE_NAME);
                AAAFileInfo fileInfo = new AAAFileInfo();
                fileInfo.fileInfo(AAALog.LOG_FILE_NAME);

                // 4.
                string path = new FileInfo(AAALog.LOG_FILE_NAME).DirectoryName;
                AAALog.log("Вывод информации о директории " + path);
                AAADirInfo dirInfo = new AAADirInfo();
                dirInfo.dirInfo(path);

                // 5.
                AAALog.log("Работа с файлами на диске");
                AAAFileManager fileManager = new AAAFileManager();
                fileManager.process(path);

                // 6.
                Console.WriteLine("Журнал работы:");
                AAALog.read();
                Console.WriteLine("Записи содержащие dll:");
                AAALog.search("dll");
                DateTime from = DateTime.Today;
                DateTime to   = DateTime.Today;
                to = to.AddDays(1);
                Console.WriteLine("Записи за последний день:");
                AAALog.search(from, to);

                from = DateTime.Now;
                from = from.AddMinutes(-5);
                to   = DateTime.Now;
                Console.WriteLine("Записи за последние 5 минут:");
                AAALog.search(from, to);

                // оставить записи только за последний час
                from = DateTime.Now;
                from = from.AddHours(-1);
                to   = DateTime.Now;
                AAALog.remain(from, to);
            } catch (Exception ex) {
                Console.WriteLine($"Error: {ex.Message}");
                AAALog.log("Error:" + ex.Message);
            }
        }
    }
}
