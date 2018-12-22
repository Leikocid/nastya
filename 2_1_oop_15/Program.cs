using System;
using System.IO;
using System.Threading;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Reflection;

namespace ns_2_1_oop {
    class Program {
        static void Main(string[] args) {
            try {
                // 1.
                using (StreamWriter sw = new StreamWriter("processes.txt")) {
                    Process[] allProcess = Process.GetProcesses();
                    foreach (Process proc in allProcess) {
                        sw.Write("Id: " + proc.Id);
                        sw.Write(", Process name: " + proc.ProcessName);

                        // sw.Write(", Start at: " + proc.StartTime);
                        // sw.Write(", Processor time: " + proc.PrivilegedProcessorTime);
                        // sw.Write(", Memory: " + proc.WorkingSet64);
                        sw.WriteLine();
                    }
                }

                // 2.
                Console.WriteLine("\nCurrent domain: ");
                AppDomain domain = AppDomain.CurrentDomain;
                Console.WriteLine("Name: " + domain.FriendlyName); // + "\nConfiguration: " + domain.SetupInformation);
                Console.WriteLine("Assemblies of current domain: ");
                Assembly[] assembly = domain.GetAssemblies();
                foreach (Assembly ass in assembly) {
                    Console.WriteLine(ass.GetName().Name);
                }

                // AppDomain secdomain = AppDomain.CreateDomain("Second Domain");
                // secdomain.Load(new AssemblyName("OOTP15"));
                // Console.WriteLine("Name: " + secdomain.FriendlyName);
                // foreach (Assembly a in secdomain.GetAssemblies()) {
                //     Console.WriteLine(a.GetName().Name);
                // }
                // AppDomain.Unload(secdomain);

                // 3.
                Thread primeThread = new Thread(new ParameterizedThreadStart(p1 => {
                    int n = (int)p1;
                    using (StreamWriter writer = new StreamWriter("prime.log", false, System.Text.Encoding.Default)) {
                        writer.WriteLine($"Проверка числа {n} на простоту:");
                        Console.WriteLine($"Проверка числа {n} на простоту:");
                    }
                    for (int i = 2; i < Math.Sqrt(n); i++) {
                        using (StreamWriter writer = new StreamWriter("prime.log", true, System.Text.Encoding.Default)) {
                            writer.WriteLine($"проверка делителя: {i}");
                            Console.WriteLine($"проверка делителя: {i}");
                        }

                        if (n % i == 0) {
                            using (StreamWriter writer = new StreamWriter("prime.log", true, System.Text.Encoding.Default)) {
                                writer.WriteLine($"Число {n} - составное. Оно делится на {i}");
                                Console.WriteLine($"Число {n} - составное. Оно делится на {i}");
                            }
                            return;
                        }

                        Thread.Sleep(3);
                    }
                    using (StreamWriter writer = new StreamWriter("prime.log", true, System.Text.Encoding.Default)) {
                        writer.WriteLine($"Число {n} - простое:");
                        Console.WriteLine($"Число {n} - простое:");
                    }
                }));
                primeThread.Name = "Prime check thread";
                Console.WriteLine("\nStart thread to check prime number: ");
                primeThread.Start(994997); // (233);//(994997);

                Console.WriteLine(
                    "Id: " + primeThread.ManagedThreadId + " Name: " + primeThread.Name + " Priority: " + primeThread.Priority + " Status: " +
                    primeThread.ThreadState);

                Thread.Sleep(1000);

                //               primeThread.Suspend();
                Console.WriteLine(
                    "Id: " + primeThread.ManagedThreadId + " Name: " + primeThread.Name + " Priority: " + primeThread.Priority + " Status: " +
                    primeThread.ThreadState);

                Thread.Sleep(1000);

                //               primeThread.Resume();
                Console.WriteLine(
                    "Id: " + primeThread.ManagedThreadId + " Name: " + primeThread.Name + " Priority: " + primeThread.Priority + " Status: " +
                    primeThread.ThreadState);
                primeThread.Join(); // ждем когда primeThread завершится
                Console.WriteLine("\nResume main thread");

                // 4.
                EvenOdd eo	   = new EvenOdd(100);
                Thread	evenThread = new Thread(new ThreadStart(eo.Even));
                Thread	oddThread  = new Thread(new ThreadStart(eo.Odd));
                evenThread.Name = "Even thread";
                oddThread.Name	= "Odd thread";
                Console.WriteLine("\nNormal start:");
                evenThread.Start();
                oddThread.Start();
                evenThread.Join();
                oddThread.Join();
                Console.WriteLine("\nPrioretized start:");

                // 4.a
                // oddThread.Priority  = ThreadPriority.Highest;
                // evenThread.Start();
                // oddThread.Start();
                // evenThread.Join();
                // oddThread.Join();

                // 4.b.i
                evenThread	= new Thread(new ThreadStart(eo.Even_2_1));
                oddThread	= new Thread(new ThreadStart(eo.Odd_2_1));
                evenThread.Name = "Even thread";
                oddThread.Name	= "Odd thread";
                Console.WriteLine("\n4.b.i even then odd:");
                evenThread.Start();
                oddThread.Start();
                eo.evenWaitHandler.Set();
                evenThread.Join();
                oddThread.Join();

                // 4.b.ii
                evenThread	= new Thread(new ThreadStart(eo.Even_2_2)); // создание потоков
                oddThread	= new Thread(new ThreadStart(eo.Odd_2_2));
                evenThread.Name = "Even thread";
                oddThread.Name	= "Odd thread";
                Console.WriteLine("\n4.b.ii run alternatively:");
                eo.evenWaitHandler.Reset(); // восстановить блокироторы в false (блокировано)
                eo.oddWaitHandler.Reset();
                evenThread.Start();         // запуск потоков. они остановятся на болираторах
                oddThread.Start();
                eo.oddWaitHandler.Set();    // открываем один из блокираторов
                evenThread.Join();          // ждем кода оба потока завершатся
                oddThread.Join();

                // 5.
                TimerCallback tm = new TimerCallback(o => {
                    int i = (int)o;
                    Console.WriteLine($"Таймер: параметр = {i}");
                });
                Timer timer = new Timer(tm, 12345, 0, 500);
                Thread.Sleep(5000);
                timer.Dispose();
            } catch (Exception ex) {
                Console.WriteLine("Error: " + ex.Message);
            }
        }
    }
    public class EvenOdd {
        private int x;

        // 4,a
        public object locker = new object();

        // 4.b
        public AutoResetEvent evenWaitHandler = new AutoResetEvent(false);
        public AutoResetEvent oddWaitHandler  = new AutoResetEvent(false);

        static Mutex mutexObj = new Mutex();

        public EvenOdd(int x) {
            this.x = x;
            using (StreamWriter writer = new StreamWriter("even_odd.log", false, System.Text.Encoding.Default)) {
                writer.WriteLine("Threads log:");
            }
        }

        public void Even() {
            for (int i = 1; i < x; i++) {
                if (i % 2 == 0) {
                    log($"{Thread.CurrentThread.Name}: {i}");
                    Thread.Sleep(50);
                }
            }
        }

        public void Odd() {
            for (int i = 1; i < x; i++) {
                if (i % 2 != 0) {
                    log($"{Thread.CurrentThread.Name}: {i}");
                    Thread.Sleep(100);
                }
            }
        }

        private void log(string message) {
            lock (locker) {
                using (StreamWriter writer = new StreamWriter("even_odd.log", true, System.Text.Encoding.Default)) {
                    writer.WriteLine(message);
                    Console.WriteLine(message);
                }
            }
        }

        // 4.b.i
        public void Even_2_1() {
            evenWaitHandler.WaitOne();
            for (int i = 1; i < x; i++) {
                if (i % 2 == 0) {
                    log($"{Thread.CurrentThread.Name}: {i}");
                }
            }
            evenWaitHandler.Set();

            oddWaitHandler.Set();
        }

        public void Odd_2_1() {
            oddWaitHandler.WaitOne();
            for (int i = 1; i < x; i++) {
                if (i % 2 != 0) {
                    log($"{Thread.CurrentThread.Name}: {i}");
                }
            }
            oddWaitHandler.Set();
        }

        // 4.b.ii

        public void Even_2_2() {
            for (int i = 1; i < x; i++) {
                evenWaitHandler.WaitOne();
                if (i % 2 == 0) {
                    log($"{Thread.CurrentThread.Name}: {i}");
                }
                oddWaitHandler.Set();
            }
        }

        public void Odd_2_2() {
            for (int i = 1; i < x; i++) {
                oddWaitHandler.WaitOne();
                if (i % 2 != 0) {
                    log($"{Thread.CurrentThread.Name}: {i}");
                }
                evenWaitHandler.Set();
            }
        }
    }
}
