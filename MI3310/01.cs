using System;
using System.IO;
using System.Text;
using System.Runtime;
using System.Collections.Generic;

namespace StringOps
{
    class Program
    {
        static bool isEligible(char chr)
        {
            return Char.IsLetter(chr) || Char.IsLetterOrDigit(chr);
        }


        static List<String> Parsing(ref StringBuilder str)
        {
            var gg = str.ToString().Split(new char[] { '.', ' ', ',' }, StringSplitOptions.RemoveEmptyEntries);

            return new List<String>(gg);
        }


        static bool checkInputValidity(ref StringBuilder str)
        {
            if (str.Length == 0)
            {
                Console.WriteLine("Đây là xâu rỗng");
                return false;
            }

            for (int i = 0; i < str.Length; ++i) if (isEligible(str[i]))
            { 
                return true; 
            }

            Console.WriteLine("Xâu này chỉ có ký tự cách");
            return false;
        }
        


        static void Main(string[] args)
        {
            var IOEncoding = Encoding.UTF8;
            Console.OutputEncoding = IOEncoding;

            StringBuilder str = new StringBuilder(File.ReadAllText("input.txt", IOEncoding));

            Console.WriteLine(str);

            if (!checkInputValidity(ref str)) return;

            Console.WriteLine("============================== Kết quả tách từ ==============================");
            List<String> ret = Parsing(ref str);
            ret.ForEach(Console.WriteLine);
            Console.WriteLine("=============================================================================");
        }
    }
}