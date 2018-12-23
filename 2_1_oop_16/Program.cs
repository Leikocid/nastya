using System;
using System.Threading;
using System.Threading.Tasks;
using System.Collections.Generic;
using System.Diagnostics;
using System.Collections.Concurrent;

namespace ns_2_1_oop {
    class Program {
        static void Main(string[] args) {
            try {
                CancellationTokenSource cancelTokenSource = new CancellationTokenSource();
                CancellationToken token			  = cancelTokenSource.Token;

                // 1.
                // Console.WriteLine("Запуск задачи");
                // Task<List<int> > task1 = Task<List<int> >.Run(() => eratosfen(200_000, token));
                // Thread.Sleep(1000);
                // Console.WriteLine($"Статус задачи: зарвешена ли? = {task1.IsCompleted}");

                // task1.Wait();
                // Console.WriteLine($"Количество простых чисел: {task1.Result.Count}");

                // // 2.
                // Console.WriteLine("Запуск задачи");
                // Task<List<int> > task2 = Task<List<int> >.Run(() => eratosfen(10_000_000, token));
                // Thread.Sleep(1000);
                // Console.WriteLine($"Статус задачи: зарвешена ли? = {task2.IsCompleted}");

                // Console.WriteLine("Завершаем задачу");
                // cancelTokenSource.Cancel();
                // task2.Wait();
                // Console.WriteLine("Задача завершена");

                // // 3.
                // Task<int>[] tasks = new Task<int>[3] {
                //     new Task<int>(() => { Thread.Sleep(100); return 100; }),
                //     new Task<int>(() => { Thread.Sleep(200); return 200; }),
                //     new Task<int>(() => { Thread.Sleep(300); return 300; })
                // };

                // // 4.1
                // foreach (var t in tasks) {
                //     t.Start();
                // }
                // Task<int> sumTask = new Task<int>(() => tasks[0].Result + tasks[1].Result + tasks[2].Result);
                // Task nextTesk	  = sumTask.ContinueWith((t) => {
                //     Console.WriteLine($"Результат сложения: {t.Result}");
                // });
                // sumTask.Start();
                // nextTesk.Wait();

                // // 4.2
                // Task<int> sumTask2 = new Task<int>(() => tasks[0].Result + tasks[1].Result + tasks[2].Result);
                // Task nextTesk2	   = new Task(() => {
                //     Console.WriteLine($"Результат сложения: {sumTask2.GetAwaiter().GetResult()}");
                // });
                // sumTask2.Start();
                // nextTesk2.Start();
                // nextTesk2.Wait();

                // // 5.
                // Console.WriteLine("Генерирование случайного массива...");
                // Random	  random   = new Random();
                // double[]  data	   = new double[500_000_000];
                // Stopwatch watchSeq = new Stopwatch();
                // watchSeq.Start();
                // for (int i = 0; i < data.Length; i++) {
                //     data[i] = random.NextDouble() * random.NextDouble();
                // }
                // watchSeq.Stop();
                // Console.WriteLine($"Последовательное решение заняло времени: {watchSeq.Elapsed}");

                // Stopwatch watchPar = new Stopwatch();
                // watchPar.Start();
                // Parallel.For(1, 10, (x) => {
                //     Random        random2 = new Random();
                //     int start		  = x * (data.Length / 10);
                //     int end		  = (x + 1) * (data.Length / 10);
                //     for (int i = start; i < end; i++) {
                //         data[i] = random2.NextDouble() * random2.NextDouble();
                //     }
                // });
                // watchPar.Stop();
                // Console.WriteLine($"Распараллеленное решение заняло времени: {watchPar.Elapsed}");

                // Stopwatch watchPar2 = new Stopwatch();
                // watchPar2.Start();
                // Parallel.For(1, 10, (x) => {
                //     int start = x * (data.Length / 10);
                //     int end   = (x + 1) * (data.Length / 10);

                //     for (int i = start; i < end; i++) {
                //         data[i] = random.NextDouble() * random.NextDouble();
                //     }
                // });
                // watchPar2.Stop();
                // Console.WriteLine($"Распараллеленное решение2 заняло времени: {watchPar2.Elapsed}");

                // // 6.
                // Parallel.Invoke(() => { Console.WriteLine($"Выполняется задача {Task.CurrentId}");
                //                         int x	    = 20;
                //                         long result = 1;
                //                         for (int i = 1; i <= x; i++) {
                //                             result *= i;
                //                         }
                //                         Console.WriteLine("Факториал числа {0} равен {1}", x, result); },
                //                 () => { Console.WriteLine($"Выполняется задача {Task.CurrentId}");
                //                         Thread.Sleep(1000); });

                // 7.
                Task[] suppliers = new Task[] {
                    new Task(() => add(1, token)),
                    new Task(() => add(2, token)),
                    new Task(() => add(3, token)),
                    new Task(() => add(4, token)),
                    new Task(() => add(5, token))
                };
                Task[] clients = new Task[] {
                    new Task(() => take(1, token)),
                    new Task(() => take(2, token)),
                    new Task(() => take(3, token)),
                    new Task(() => take(4, token)),
                    new Task(() => take(5, token)),
                    new Task(() => take(6, token)),
                    new Task(() => take(7, token)),
                    new Task(() => take(8, token)),
                    new Task(() => take(9, token)),
                    new Task(() => take(10, token))
                };

                foreach (var t in suppliers) {
                    t.Start();
                }
                foreach (var t in clients) {
                    t.Start();
                }
                Thread.Sleep(5000);
                cancelTokenSource.Cancel();
                Thread.Sleep(100);

                // 8.
                CancellationTokenSource cancelTokenSource8 = new CancellationTokenSource();
                CancellationToken token8		   = cancelTokenSource8.Token;
                eratosfenAsync(200_000, token8);
                Console.WriteLine("Выполнение основного потока");
                Thread.Sleep(2000);
                Console.WriteLine("Выполнение основного потока 2 сек");
                Thread.Sleep(2000);
                Console.WriteLine("Выполнение основного потока 4 сек");
                Thread.Sleep(2000);
                Console.WriteLine("Выполнение основного потока 6 сек");
                Console.WriteLine(		   "Прерываем задачу");
                cancelTokenSource.Cancel();
                Console.WriteLine("Выполнение основного потока завершено");
            } catch (Exception ex) {
                Console.WriteLine("Error: " + ex.Message);
            }
        }

        public static BlockingCollection<string> shop = new BlockingCollection<string>();
        public static int counter		      = 0;

        public static void add(int supplierIdx, CancellationToken token) {
            while (true) {
                string product = "Product_" + supplierIdx + "_" + (++counter);
                lock (shop) {
                    shop.Add(product);
                    Console.WriteLine($"{product} added. Size = {shop.Count}");
                }
                if (token.IsCancellationRequested) {
                    return;
                }
                Thread.Sleep(supplierIdx * 10);
            }
        }

        public static void take(int clientInx, CancellationToken token) {
            while (true) {
                string product;
                lock (shop) {
                    if (shop.TryTake(out product)) {
                        Console.WriteLine($"Client {clientInx} took {product}. Size = {shop.Count}");
                    } else {
                        Console.WriteLine($"Client {clientInx} visited empty shop");
                    }
                    if (token.IsCancellationRequested) {
                        return;
                    }
                }
                Thread.Sleep(clientInx * 10);
            }
        }

        public static List<int> eratosfen(int maxNumber, CancellationToken token) {
            Stopwatch watch = new Stopwatch();

            watch.Start();
            List<int> primeNumbers = new List<int>();
            int i;
            for (i = 1; i < maxNumber; i++) {
                primeNumbers.Add(i);
            }
            i = 1;
            while (i < primeNumbers.Count) {
                int prime = primeNumbers[i];

                int j = i + 1;
                while (j < primeNumbers.Count) {
                    // прерываение исполнения
                    if (token.IsCancellationRequested) {
                        Console.WriteLine("Операция прервана токеном");
                        return null;
                    }

                    if (primeNumbers[j] % prime == 0) {
                        primeNumbers.RemoveAt(j);
                    } else {
                        j++;
                    }
                }
                i++;
            }

            watch.Stop();
            Console.WriteLine($"Расчет закончен: заняло времени - {watch.Elapsed}");

            return primeNumbers;
        }

        static async void eratosfenAsync(int maxNumber, CancellationToken token) {
            Console.WriteLine("Начало метода eratosfenAsync");                                    // выполняется синхронно
            List<int> result = await Task.Run(() => eratosfen(maxNumber, token));                 // выполняется асинхронно
            if (result != null) {
                Console.WriteLine($"Конец метода eratosfenAsync: result.Count = {result.Count}"); // выполняется синхронно
            } else {
                Console.WriteLine($"Конец метода eratosfenAsync. Метод был прерван...");
            }
        }
    }
}
