using System;
using System.Collections.Generic;
using System.Reflection;
using System.Reflection.Metadata;
using System.Linq;
using System.IO;

namespace ns_2_1_oop {
    class Reflector {
        public void writeClass(string className, string fileName) {
            Console.WriteLine($"Write information for class: {className}");

            Type t = Type.GetType(className);
            using (StreamWriter sw = new StreamWriter(fileName, false, System.Text.Encoding.GetEncoding("utf-8"))) {
                sw.WriteLine("Listing all the members (public and non public) of the {0} type", t);

                // Lists static fields first.
                FieldInfo[] fi = t.GetFields(BindingFlags.Static | BindingFlags.NonPublic | BindingFlags.Public);
                sw.WriteLine("// Static Fields");
                writeMembers(sw, fi);

                // Static properties.
                PropertyInfo[] pi = t.GetProperties(BindingFlags.Static |  BindingFlags.NonPublic | BindingFlags.Public);
                sw.WriteLine("// Static Properties");
                writeMembers(sw, pi);

                // Static events.
                EventInfo[] ei = t.GetEvents(BindingFlags.Static | BindingFlags.NonPublic | BindingFlags.Public);
                sw.WriteLine("// Static Events");
                writeMembers(sw, ei);

                // Static methods.
                MethodInfo[] mi = t.GetMethods(BindingFlags.Static | BindingFlags.NonPublic | BindingFlags.Public);
                sw.WriteLine("// Static Methods");
                writeMembers(sw, mi);

                // Constructors.
                ConstructorInfo[] ci = t.GetConstructors(BindingFlags.Instance |  BindingFlags.NonPublic | BindingFlags.Public);
                sw.WriteLine("// Constructors");
                writeMembers(sw, ci);

                // Instance fields.
                fi = t.GetFields(BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public);
                sw.WriteLine("// Instance Fields");
                writeMembers(sw, fi);

                // Instance properites.
                pi = t.GetProperties(BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public);
                sw.WriteLine("// Instance Properties");
                writeMembers(sw, pi);

                // Instance events.
                ei = t.GetEvents(BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public);
                sw.WriteLine("// Instance Events");
                writeMembers(sw, ei);

                // Instance methods.
                mi = t.GetMethods(BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public);
                sw.WriteLine("// Instance Methods");
                writeMembers(sw, mi);

                Type[] it = t.GetInterfaces();
                sw.WriteLine("// Interfaces");
                foreach (Type tt in it) {
                    sw.WriteLine($"     {tt}");
                }
                sw.WriteLine();
            }
        }

        public void printPublicMethods(string className) {
            Console.WriteLine($"Print public methods for class: {className}");

            Type t	    = Type.GetType(className);
            MethodInfo[] mi = t.GetMethods(BindingFlags.Static | BindingFlags.Public);
            Console.WriteLine("// Public Static Methods");
            writeMembers(Console.Out, mi);
            mi = t.GetMethods(BindingFlags.Instance | BindingFlags.Public);
            Console.WriteLine("// Public Instance Methods");
            writeMembers(Console.Out, mi);
        }

        public void printFields(string className) {
            Console.WriteLine($"Print fields and properties for class: {className}");

            Type t = Type.GetType(className);

            // Lists static fields first.
            FieldInfo[] fi = t.GetFields(BindingFlags.Static | BindingFlags.NonPublic | BindingFlags.Public);
            Console.WriteLine("// Static Fields");
            writeMembers(Console.Out, fi);

            // Static properties.
            PropertyInfo[] pi = t.GetProperties(BindingFlags.Static |  BindingFlags.NonPublic | BindingFlags.Public);
            Console.WriteLine("// Static Properties");
            writeMembers(Console.Out, pi);

            // Instance fields.
            fi = t.GetFields(BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public);
            Console.WriteLine("// Instance Fields");
            writeMembers(Console.Out, fi);

            // Instance properites.
            pi = t.GetProperties(BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public);
            Console.WriteLine("// Instance Properties");
            writeMembers(Console.Out, pi);
        }

        public void printInterfaces(string className) {
            Console.WriteLine($"Print public methods for class: {className}");

            Type   t  = Type.GetType(className);
            Type[] it = t.GetInterfaces();
            Console.WriteLine("// Interfaces");
            foreach (Type tt in it) {
                Console.WriteLine($"     {tt}");
            }
            Console.WriteLine();
        }

        public static void writeMembers(TextWriter sw, MemberInfo[] ms) {
            foreach (MemberInfo m in ms) {
                sw.WriteLine($"     {m}");
            }
            sw.WriteLine();
        }

        public void printMethods(string className, string typeName) {
            Console.WriteLine($"Print methods for class {className} that contain type {typeName}:");

            Type t	    = Type.GetType(className);
            Type pt	    = Type.GetType(typeName);
            MethodInfo[] mi = t.GetMethods(BindingFlags.Static | BindingFlags.Public | BindingFlags.Instance | BindingFlags.NonPublic);
            var selected    =
                mi.SelectMany(m => m.GetParameters(), (m, p) => new { m = m, p = p })
                .Where(m_p => m_p.p.ParameterType.Equals(pt))
                .Select(m_p => m_p.m);
            foreach (var i in selected) {
                Console.WriteLine($"     {i}");
            }
            Console.WriteLine();
        }

        public void callMethod(string className, string methodName, string fileName) {
            Type t	      = Type.GetType(className);
            MethodInfo[] mis  = t.GetMethods(BindingFlags.Static | BindingFlags.Public);
            MethodInfo	 mi   = mis.Where(m => m.Name.Equals(methodName)).First();
            List<object> args = new List<object>();
            if (mi != null) {
                using (StreamReader sr = new StreamReader(fileName, System.Text.Encoding.GetEncoding("utf-8"))) {
                    ParameterInfo[] par = mi.GetParameters();
                    int i		= 0;
                    string arg;
                    while ((arg = sr.ReadLine()) != null && (i < par.Length)) {
                        if (par[i].ParameterType.Equals(typeof(String))) {
                            args.Add(arg);
                        } else if (par[i].ParameterType.Equals(typeof(Int16))) {
                            args.Add(Int16.Parse(arg));
                        } else if (par[i].ParameterType.Equals(typeof(Int32))) {
                            args.Add(Int32.Parse(arg));
                        } else if (par[i].ParameterType.Equals(typeof(Int64))) {
                            args.Add(Int64.Parse(arg));
                        }
                        i++;
                    }
                }

                object res = mi.Invoke(null, args.ToArray());
                Console.WriteLine($"Call result: {res}");
            } else {
                Console.WriteLine($"Method {methodName} not found");
            }
        }
    }
}
