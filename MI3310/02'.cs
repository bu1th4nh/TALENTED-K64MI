using System;
using System.IO;
using System.Text;
using System.Runtime;
using System.Collections.Generic;

namespace SparseMatrix
{
    class Program
    {
        static void Main(string[] args)
        {
            var IOEncoding = Encoding.UTF8;
            Console.OutputEncoding = IOEncoding;

            int m;

            m = Int32.Parse(Console.ReadLine());
            List<List<int>> a = new List<List<int>>();
            List<int> kichthuocmang = new List<int>();

            for (int i = 0; i < m; ++i) kichthuocmang.Add(Int32.Parse(Console.ReadLine()));

            for (int i = 0; i < m; ++i)
            {
                List<int> tmp = new List<int>();
                for (int j = 0; j < kichthuocmang[i]; ++j) tmp.Add(Int32.Parse(Console.ReadLine()));
                a.Add(tmp);
            }    
                

            foreach(var x in a)
            {
                foreach(var y in x) Console.Write("{0} ", y);
                Console.WriteLine();
            }    
        }
    }
}
