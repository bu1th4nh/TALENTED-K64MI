using System;
using System.IO;
using System.Text;
using System.Numerics;

namespace PiNumberEstimation
{
    class Program
    {
        static string PiEstimate(int precision)
        {
            double tarrget = 0.00;
            double inv_eps = Math.Pow(10.00, precision);



            for (int i = 0; true; ++i)
            {
                int i_mult_8 = i << 3;
                double add1 = 4.0 / (i_mult_8 + 1) -
                               2.0 / (i_mult_8 + 4) -
                               1.0 / (i_mult_8 + 5) -
                               1.0 / (i_mult_8 + 6);

                if (add1 * inv_eps < Math.Pow(16.0, i)) break;
                tarrget += add1 / Math.Pow(16.0, i);
            }




            StringBuilder format = new StringBuilder("{0:0.}");
            format.Insert(format.Length - 1, "0", precision);
            //Console.WriteLine(format);

            return String.Format(format.ToString(), tarrget);
        }

        static void Main_(string[] args)
        {
            string path = "output.txt";
            var IOEncoding = Encoding.UTF8;
            Console.OutputEncoding = IOEncoding;


            Console.Write("Nhập độ chính xác sau dấu phẩy của số pi: ");
            int precision = Convert.ToInt32(Console.ReadLine());

            
            using (StreamWriter ws = new StreamWriter(path))
            {
                ws.WriteLine(PiEstimate(precision));
            }
        }
    }
}
