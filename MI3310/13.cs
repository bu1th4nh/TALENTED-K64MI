using System;

namespace BitOps
{
    class Program
    {
        static void FlipBit(ref int x, int k)
        {
            x = x ^ (1 << k);
        }
        
        static int FlipBit(int x, int k)
        {
            return x ^ (1 << k);
        }

        static int checkBit(int x, int k)
        {
            return (x >> k) & 1;
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
        }
    }
}
