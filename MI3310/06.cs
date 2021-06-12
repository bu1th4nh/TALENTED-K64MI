using System;
using System.IO;
using System.Text;
using System.Runtime;
using System.Collections.Generic;

namespace PrimeCheck
{
    class Program
    {
        static void Main(string[] args)
        {
            var IOEncoding = Encoding.UTF8;
            Console.OutputEncoding = IOEncoding;

            Console.WriteLine("Entering integer from input.txt....");
            int x = Convert.ToInt32(File.ReadAllText("input.txt"));
            Console.WriteLine("Done entering.");

            if (x <= 1) Console.WriteLine("{0} is not a prime number!", x);
            else if (x == 2) Console.WriteLine("2 is a prime number");
            else
            {
                int rpt_limit = Convert.ToInt32(Math.Sqrt(x)) + 1;
                for(int i = 2; i <= rpt_limit + 1 && i < x; ++i)
                {
                    if(x % i == 0) { Console.WriteLine("{0} is not a prime number!", x); return; }
                }
                Console.WriteLine("{0} is a prime number!", x);
            }    
        }
    }
}
