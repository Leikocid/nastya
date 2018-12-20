
using System;
using System.IO;
using System.IO.Compression;

namespace ns_2_1_oop {
    public class AAAFileManager {
        public void process(string path) {
            DirectoryInfo dirInspect = new DirectoryInfo(path + Path.DirectorySeparatorChar + "AAAInspect");
            if (dirInspect.Exists) {
                dirInspect.Delete(true);
            }
            dirInspect.Create();

            string   filename = dirInspect.ToString() + Path.DirectorySeparatorChar + "aaadirinfo.txt";
            FileInfo fileInfo = new FileInfo(filename);

            AAALog.log("Запись информацуии о файлах в файл " + filename);
            using (StreamWriter sw = new StreamWriter(filename, false, System.Text.Encoding.Default)) {
                if (Directory.Exists(path)) {
                    sw.WriteLine("Files");
                    string[] files = Directory.GetFiles(path);
                    foreach (string s in files) {
                        sw.WriteLine(s);
                    }
                    sw.WriteLine();
                    sw.WriteLine("Folders");
                    string[] dirs = Directory.GetDirectories(path);
                    foreach (string s in dirs) {
                        sw.WriteLine(s);
                    }
                }
                sw.Close();
            }

            AAALog.log("Создагние копии в файл " + filename + ".copy.txt");
            fileInfo.CopyTo(filename + ".copy.txt", true);
            AAALog.log("Переименование в файл " +  filename + ".renamed.txt");
            fileInfo.MoveTo(filename + ".renamed.txt");
            AAALog.log("Удаление файла");
            fileInfo.Delete();

            DirectoryInfo dirFiles = new DirectoryInfo(path + Path.DirectorySeparatorChar + "AAAFiles");
            dirFiles.Create();
            AAALog.log("Получаем информацию о dll файлах в " + path);
            FileInfo[] dllFiles = new DirectoryInfo(path).GetFiles("*.dll");

            AAALog.log("Копируем dll файлы");
            foreach (FileInfo dllFile in dllFiles) {
                dllFile.CopyTo(dirFiles.ToString() + Path.DirectorySeparatorChar + dllFile.Name, true);
            }
            AAALog.log("Перемещаем в AAAInspect");
            dirFiles.MoveTo(dirInspect.ToString() + Path.DirectorySeparatorChar + dirFiles.Name);

            AAALog.log("Архивируем " + dirFiles);
            ZipFile.CreateFromDirectory(dirFiles.ToString(), dirInspect.ToString() + Path.DirectorySeparatorChar + dirFiles.Name + ".zip");

            AAALog.log("Разархивируем " + dirInspect.ToString() + Path.DirectorySeparatorChar + dirFiles.Name + ".zip");
            Directory.CreateDirectory(dirInspect.ToString() + Path.DirectorySeparatorChar + dirFiles.Name + "2");
            ZipFile.ExtractToDirectory(dirInspect.ToString() + Path.DirectorySeparatorChar + dirFiles.Name + ".zip",
                                       dirInspect.ToString() + Path.DirectorySeparatorChar + dirFiles.Name + "2");
        }
    }
}
