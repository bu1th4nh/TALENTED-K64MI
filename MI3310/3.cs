using System;
using System.IO;
using System.Text;
using System.Runtime;
using System.Collections.Generic;

namespace Newton
{
    class Program
    {
        static double f(double x)
        {
            double f = x * x * x - 0.2 * x * x - 0.2 * x - 1.2;
            return f;
        }
        static double df(double x)
        {
            double df = 3 * x * x - 0.4 * x - 0.2;
            return df;
        }

        static double NewtonCore()
        {
            double epsilon1 = Math.Sqrt((2 * 2.4 * Math.Pow(10, -6)) / 5.95);
            double b = 0;
            double x = 1;
            do
            {
                double a = x;
                x = x - f(x) / df(x);
                b = x - a;
            }
            while (Math.Abs(b) >= epsilon1);

            return x;
        }

        static void Main(string[] args)
        {
            /*input f(x) = x^3 - 0.2x^2 - 0.2x - 1.2
            * f'(x) = 3x^2 - 0.4x - 0.2
            * f''(x) = 6x - 0.4
            * kcl (1; 1,5)
            * x0 = 1, m = 2.4, M = 5.95, epsilon = 10e-6
           */

            Console.WriteLine(NewtonCore());
        }
    }
}
