using System;

namespace PBValue_vs_PBRefrence
{
    class Program
    {
        static void PassByValue(int objects)
        {
            objects += 6969;
        }

        static void PassByRefrence(ref int objects)
        {
            objects += 6969;
        }

        static void Main(string[] args)
        {
            int object1 = 0;
            int object2 = 0;

            Console.WriteLine("object1 = {0}", object1);
            Console.WriteLine("object2 = {0}", object2);

            Console.WriteLine("Running: PassByRefrence(object1); PassByValue(object2); ");
            PassByRefrence(ref object1);
            PassByValue(object2);

            Console.WriteLine("object1 = {0}", object1);
            Console.WriteLine("object2 = {0}", object2);
        }
    }
}
