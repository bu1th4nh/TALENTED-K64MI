using System;
using System.IO;
using System.Text;
using System.Runtime;
using System.Globalization;
using System.Collections.Generic;

namespace ToUpperCase
{
    class Program
    {
        static StringBuilder toUpperByAvailableFunction(StringBuilder str)
        {
            //Vietnamese only, can use with ASCII and UTF-8

            string x = str.ToString();


            return new StringBuilder(x.ToUpper(new CultureInfo("vi-VN")));
        }
        static StringBuilder toUpperByIntValueIdentification(StringBuilder str)
        {
            //ASCII Only

            for(int i = 0; i < str.Length; ++i)
            {
                if (Char.IsLower(str[i])) str[i] = (char)(str[i] - Math.Abs('A' - 'a'));
            }

            return str;
        }
        static StringBuilder toUpperCaseBySwitchCase(StringBuilder str)
        {
            //ASCII Characters Only, later can use with UTF-8

            for(int i = 0; i < str.Length; ++i)
            {
                switch (str[i])
                {
                    case 'a':
                        str[i] = 'A';
                        break;
                    case 'b':
                        str[i] = 'B';
                        break;
                    case 'c':
                        str[i] = 'C';
                        break;
                    case 'd':
                        str[i] = 'D';
                        break;
                    case 'e':
                        str[i] = 'E';
                        break;
                    case 'f':
                        str[i] = 'F';
                        break;
                    case 'g':
                        str[i] = 'G';
                        break;
                    case 'h':
                        str[i] = 'H';
                        break;
                    case 'i':
                        str[i] = 'I';
                        break;
                    case 'j':
                        str[i] = 'J';
                        break;
                    case 'k':
                        str[i] = 'K';
                        break;
                    case 'l':
                        str[i] = 'L';
                        break;
                    case 'm':
                        str[i] = 'M';
                        break;
                    case 'n':
                        str[i] = 'N';
                        break;
                    case 'o':
                        str[i] = 'O';
                        break;
                    case 'p':
                        str[i] = 'P';
                        break;
                    case 'q':
                        str[i] = 'Q';
                        break;
                    case 'r':
                        str[i] = 'R';
                        break;
                    case 's':
                        str[i] = 'S';
                        break;
                    case 't':
                        str[i] = 'T';
                        break;
                    case 'u':
                        str[i] = 'U';
                        break;
                    case 'v':
                        str[i] = 'V';
                        break;
                    case 'w':
                        str[i] = 'W';
                        break;
                    case 'x':
                        str[i] = 'X';
                        break;
                    case 'y':
                        str[i] = 'Y';
                        break;
                    case 'z':
                        str[i] = 'Z';
                        break;
                    
                    default: break;
                }
            }

            return str;
        }


        static void Main(string[] args)
        {
            var IOEncoding = Encoding.UTF8;
            Console.OutputEncoding = IOEncoding;
            //Console.InputEncoding = IOEncoding;

            Console.Write("Nhập xâu cần chuyển: ");
            StringBuilder src = new StringBuilder(Console.ReadLine());


            var dst0 = toUpperByAvailableFunction(src);
            var dst1 = toUpperByIntValueIdentification(src);
            var dst2 = toUpperCaseBySwitchCase(src);


            Console.WriteLine("Xâu viết hoa theo hàm có sẵn: {0}", dst0.ToString());
            Console.WriteLine("Xâu viết hoa theo nhận diện mã: {0}", dst1.ToString());
            Console.WriteLine("Xâu viết hoa theo switch-case: {0}", dst2.ToString());
        }
    }
}
