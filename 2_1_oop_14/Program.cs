using System;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization.Formatters.Soap;
using System.Xml.Serialization;
using System.Runtime.Serialization.Json;

using System.Net;
using System.Net.Sockets;
using System.Threading;

using System.Xml;
using System.Xml.Linq;
using System.Linq;

namespace ns_2_1_oop {
    class Program {
        static void Main(string[] args) {
            try {
                // 1.
                Console.Write("Create model...");
                Developer d1 = new Developer("Instinctools Gmbh");
                Developer d2 = new Developer("s_t_u_d_y");
                d2.contact.firstName = "Anastasia";
                d2.contact.lastName  = "Astakhova";
                Computer c1 = new Computer();
                Game	 g1 = new Game("World of Tanks", "1.0", 2018, Genre.Strategy);
                g1.Developer = d2;
                c1.AddSoftware(g1);
                TextProcessor t1 = new TextProcessor("Word", "2012", 2012, new string[] { "txt", "doc" });
                t1.Developer = d1;
                c1.AddSoftware(t1);
                TextProcessor t2 = new TextProcessor("Word", "2016", 2016, new string[] { "txt", "doc", "docx" });
                t2.Developer = d2;
                c1.AddSoftware(t2);
                Console.WriteLine("OK");

                // сериализация/десериализация в бинарный файл. В модели добавлен атрибцут [Serializable]
                BinaryFormatter binFormatter = new BinaryFormatter();
                using (FileStream fs = new FileStream("software.dat", FileMode.OpenOrCreate)) {
                    binFormatter.Serialize(fs, c1);
                    Console.WriteLine("Объект сериализован");
                }
                using (FileStream fs = new FileStream("software.dat", FileMode.Open)) {
                    Computer c2 = (Computer)binFormatter.Deserialize(fs);
                    Console.WriteLine("Объект десериализован");
                    Console.WriteLine($"c2: {c2}");
                }

                // сериализация/десериализация в SOAP файл. десериализация DateTime валится
                SoapFormatter soapFormatter = new SoapFormatter();
                using (FileStream fs = new FileStream("software.soap", FileMode.Create))  {
                    soapFormatter.Serialize(fs, c1);
                    Console.WriteLine("Объект сериализован");
                }
                using (FileStream fs = new FileStream("software.soap", FileMode.Open)) {
                    Computer c2 = (Computer)soapFormatter.Deserialize(fs);
                    Console.WriteLine("Объект десериализован");
                    Console.WriteLine($"c2: {c2}");
                }

                // сериализация/десериализация в XML файл.
                // Все объекты модели должны содержать конструктор без параметров
                // Все поля доступны на set и get
                XmlSerializer xmlFormatter = new XmlSerializer(typeof(Computer), new Type[] {
                    typeof(TextProcessor), typeof(Game)
                });
                using (FileStream fs = new FileStream("software.xml", FileMode.Create))  {
                    xmlFormatter.Serialize(fs, c1);
                    Console.WriteLine("Объект сериализован");
                }
                using (FileStream fs = new FileStream("software.xml", FileMode.Open)) {
                    Computer c2 = (Computer)xmlFormatter.Deserialize(fs);
                    Console.WriteLine("Объект десериализован");
                    Console.WriteLine($"c2: {c2}");
                }

                // сериализация в JSON. В модели добавлен атрибцут [DataContract]
                DataContractJsonSerializer jsonFormatter = new DataContractJsonSerializer(typeof(Computer),  new Type[] {
                    typeof(TextProcessor), typeof(Game)
                });
                using (FileStream fs = new FileStream("software.json", FileMode.Create))  {
                    jsonFormatter.WriteObject(fs, c1);
                    Console.WriteLine("Объект сериализован");
                }
                using (FileStream fs = new FileStream("software.json", FileMode.Open)) {
                    Computer c2 = (Computer)jsonFormatter.ReadObject(fs);
                    Console.WriteLine("Объект десериализован");
                    Console.WriteLine($"c2: {c2}");
                }

                // 2.
                IPEndPoint ipPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 9999);

                // Создание сервера в отдельном потоке
                Thread serverThread = new Thread(new ThreadStart(() => {
                    try  {
                        Socket     serverSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                        serverSocket.Bind(ipPoint);
                        serverSocket.Listen(10); // количество ожидающих в очереди на подключение = 10 и начинаем прослушивание
                        Console.WriteLine(">> Сервер запущен. Ожидание подключений...");

                        int i = 0;
                        while (i < 1) {
                            Socket handler	= serverSocket.Accept();
                            Stream stream	= new NetworkStream(handler);
                            BinaryFormatter bin = new BinaryFormatter();
                            Computer c2		= (Computer)bin.Deserialize(stream);

                            Console.WriteLine(">> Объект получен на сервере");
                            Console.WriteLine($">> c2: {c2} - отправляем его обратно");

                            bin.Serialize(stream, c2);

                            stream.Close();
                            handler.Shutdown(SocketShutdown.Both);
                            handler.Close();
                            i++;
                        }
                        Console.WriteLine(">> Сервер остановлен");
                    } catch (Exception ex) {
                        Console.WriteLine(ex.Message);
                    }
                }));
                serverThread.Start();


                Socket clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                clientSocket.Connect(ipPoint);
                Console.WriteLine("Отправляем объект на сервер");
                Console.WriteLine($"с1: {c1}");
                Stream clientStream		= new NetworkStream(clientSocket);
                BinaryFormatter clientFormatter = new BinaryFormatter();
                clientFormatter.Serialize(clientStream, c1);
                Computer c3 = (Computer)clientFormatter.Deserialize(clientStream);
                Console.WriteLine("Объект получен на клиенте");
                Console.WriteLine($"с3: {c3}");

                // 3.
                XmlDocument xmlDoc = new XmlDocument();
                xmlDoc.Load("software.xml");
                XmlElement xmlRoot = xmlDoc.DocumentElement;
                Console.WriteLine("Поиск TextProcessor:");
                XmlNamespaceManager namespaceManager = new XmlNamespaceManager(xmlDoc.NameTable);
                namespaceManager.AddNamespace("xsi", "http://www.w3.org/2001/XMLSchema-instance");
                XmlNodeList childnodes = xmlRoot.SelectNodes("//AbstractSoftware[@xsi:type=\'TextProcessor\']", namespaceManager);
                foreach (XmlNode n in childnodes) {
                    Console.WriteLine(n.OuterXml);
                }
                Console.WriteLine("Поиск по developer name:");
                childnodes = xmlRoot.SelectNodes("//AbstractSoftware[Developer[@Name=\'s_t_u_d_y\']]");
                foreach (XmlNode n in childnodes) {
                    Console.WriteLine(n.OuterXml);
                }

                // 4.
                XDocument xdoc = new XDocument(new XElement("phones",
                                                            new XElement("phone",
                                                                         new XAttribute("name", "iPhone 6"),
                                                                         new XElement("company", "Apple"),
                                                                         new XElement("price", "40000")),
                                                            new XElement("phone",
                                                                         new XAttribute("name", "Samsung Galaxy S5"),
                                                                         new XElement("company", "Samsung"),
                                                                         new XElement("price", "33000"))));
                xdoc.Save("phones.xml");
                xdoc = XDocument.Load("software.xml");
                var items = xdoc.Descendants("AbstractSoftware")
                            .Where(e => e.Element("Name").Value == "Word")
                            .Select(e => new { name =  e.Element("Name").Value, year =  e.Element("ReleaseYear").Value });
                foreach (var item in items) {
                        Console.WriteLine("{0} - {1}", item.name, item.year);
                }
            } catch (Exception ex) {
                Console.WriteLine($"Error: {ex.Message}\n{ex.InnerException?.Message}");
            }
        }
    }
}
