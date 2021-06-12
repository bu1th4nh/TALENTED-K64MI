using System;
using System.IO;
using System.Text;
using System.Numerics;

namespace ComplexQuadraticFunctions
{
    class Program
    {

        static bool RemoveChars(ref string str)
        {
            bool check_imag = false;

            for (int i = str.Length - 1; i >= 0; --i)
            {
                if (str[i] == ' ') str = str.Remove(i, 1);
                else if (str[i] == 'i') {str = str.Remove(i, 1); check_imag = true;}
                else if (str[i] == 'j') {str = str.Remove(i, 1); check_imag = true;}
                else if (str[i] == 'k') {str = str.Remove(i, 1); check_imag = true;}
                //while (i > str.Length - 1) --i;
            }

            return check_imag;
        } 
        static Complex ParseComplex(string x)
        {
            double real = 0.0, imag = 0.0;

            var tokens = x.Split('+');
            foreach(var raw_token in tokens)
            {
                var token = raw_token;
                bool is_imag = RemoveChars(ref token);

                if (is_imag) imag += Convert.ToDouble(token);
                else real += Convert.ToDouble(token);
            }
        

            return new Complex(real, imag);
        }
        static String CmplxToString(Complex z)
        {
            StringBuilder ret = new StringBuilder();
            ret.Append(z.Real.ToString());
            ret.Append(" + ");
            ret.Append(z.Imaginary.ToString());
            ret.Append("i");
            return ret.ToString();
        }


        static void SolveQuadraticEq(ref Complex a, ref Complex b, ref Complex c)
        {
            if (a == 0)
            {
                if (b == 0)
                {
                    if (c == 0)
                    {
                        Console.WriteLine("PT có vô số nghiêm");
                    }
                    else Console.WriteLine("PT vô nghiệm");
                }
                else Console.WriteLine("PT có nghiệm duy nhất x = {0}", -c / b);

                return;
            }


            Complex delta = b * b - 4 * a * c;
            if (delta == 0)
            {
                Complex x = -b / (2 * a);
                Console.WriteLine("PT có nghiệm kép x1 = x2 = {0}", CmplxToString(x));
            }
            else
            {
                Complex x1 = (-b + Complex.Sqrt(delta)) / (2 * a);
                Complex x2 = (-b - Complex.Sqrt(delta)) / (2 * a);
                Console.WriteLine("PT có 2 nghiệm phân biệt x1 = {0} và x2 = {1}", CmplxToString(x1), CmplxToString(x2));
            }
        }


        static void Main(string[] args)
        {
            var IOEncoding = Encoding.UTF8;
            Console.OutputEncoding = IOEncoding;

            Console.Write("Nhập a = ");
            Complex a = ParseComplex(Console.ReadLine());
            Console.Write("Nhập b = ");
            Complex b = ParseComplex(Console.ReadLine());
            Console.Write("Nhập c = ");
            Complex c = ParseComplex(Console.ReadLine());

            SolveQuadraticEq(ref a, ref b, ref c);

        }
    }
}
