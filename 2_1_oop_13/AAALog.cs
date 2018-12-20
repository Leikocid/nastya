using System;
using System.IO;

namespace ns_2_1_oop {
    public class AAALog {
        public static string LOG_FILE_NAME = "AAAlogfile.txt";
        private static AAALog logger;
        private static AAALog getLogger() {
            if (logger == null) {
                logger = new AAALog();
            }
            return logger;
        }

        public static void log(string message) {
            getLogger().append(message);
        }

        public static void read() {
            using (StreamReader reader = new StreamReader(getLogger().logFile.ToString(), System.Text.Encoding.Default)) {
                int cnt = 0;
                while (true) {
                    if (reader.EndOfStream) {
                        break;
                    }
                    Console.WriteLine(reader.ReadLine());
                    cnt++;
                }
                Console.WriteLine("Кол-во записей: " + cnt);
            }
        }

        public static void search(string text) {
            using (StreamReader reader = new StreamReader(getLogger().logFile.ToString(), System.Text.Encoding.Default)) {
                while (true) {
                    if (reader.EndOfStream) {
                        break;
                    }
                    string line = reader.ReadLine();
                    if (line.Contains(text)) {
                        Console.WriteLine(line);
                    }
                }
            }
        }

        public static void search(DateTime from, DateTime to) {
            using (StreamReader reader = new StreamReader(getLogger().logFile.ToString(), System.Text.Encoding.Default)) {
                while (true) {
                    if (reader.EndOfStream) {
                        break;
                    }
                    string   line	 = reader.ReadLine();
                    DateTime logDateTime = DateTime.Parse(line.Substring(0, 19));
                    if (((from == null) || (from <= logDateTime)) && ((to == null) || (logDateTime <= to))) {
                        Console.WriteLine(line);
                    }
                }
            }
        }

        public static void remain(DateTime from, DateTime to) {
            FileInfo tmp =  new FileInfo(getLogger().logFile.ToString() + ".tmp");
            using (StreamWriter writer = new StreamWriter(tmp.ToString(), false, System.Text.Encoding.Default)) {
                using (StreamReader reader = new StreamReader(getLogger().logFile.ToString(), System.Text.Encoding.Default)) {
                    while (true) {
                        if (reader.EndOfStream) {
                            break;
                        }
                        string	 line	     = reader.ReadLine();
                        DateTime logDateTime = DateTime.Parse(line.Substring(0, 19));
                        if (((from == null) || (from <= logDateTime)) && ((to == null) || (logDateTime <= to))) {
                            writer.WriteLine(line);
                        }
                    }
                }
            }
            getLogger().logFile.Delete();
            tmp.MoveTo(getLogger().logFile.ToString());
        }

        private FileInfo logFile;

        private AAALog() {
            logFile = new FileInfo(LOG_FILE_NAME);
        }

        private void append(string message) {
            using (StreamWriter writer = new StreamWriter(logFile.ToString(), true, System.Text.Encoding.Default)) {
                writer.WriteLine(DateTime.Now + ": " + message);
            }
        }
    }
}
