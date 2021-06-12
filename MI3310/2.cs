using System;
using System.IO;
using System.Text;
using System.Runtime;
using System.Collections.Generic;

namespace ArraySeparate
{
    class Program
    {
        static bool checkInputValidity(ref List<int> arr)
        {
            if (arr.Count == 0) { Console.WriteLine("Mảng trống"); return false; }
            if (arr.Count <= 2) { Console.WriteLine("Kích thước mảng không đủ"); return false; }

            return true;
        }

        static void Main(string[] args)
        {
            var IOEncoding = Encoding.UTF8;
            Console.OutputEncoding = IOEncoding;
            List<int>        a = new List<int>(new int[] {1, 2, 3, 4, 5});

            int              n = a.Count;
            int            mid = (n + (n & 1)) >> 1;


            if (n == 0) { Console.WriteLine("Mảng trống"); return; }
            if (n <= 2) { Console.WriteLine("Kích thước mảng không đủ"); return; }


            List<List<int>>  c = new List<List<int>>();
            c.Add(a.GetRange(0, mid));
            c.Add(a.GetRange(mid, n - mid));
            foreach (var x in c)
            {
                foreach (var y in x)
                {
                    Console.Write("{0} ", y);
                }
                Console.WriteLine();
            }




            int[,]           b = new int[2, mid];
            for (int i = 0, cnt = 0; i < mid; ++i)
            {
                b[0, cnt++] = a[i];
            }
            for(int i = mid, cnt = 0; i < n; ++i)
            {
                b[1, cnt++] = a[i];
            }

            bool is_odd = (n & 1) == 1;
            for(int i = 0; i < 2; ++i)
            {
                for(int j = 0; j < mid; ++j)
                {
                    if (is_odd && i == 1 && j == mid - 1) break;
                    Console.Write("{0} ", b[i, j]);
                }
                Console.WriteLine();
            }
            Console.WriteLine();
             
        }
    }
}
