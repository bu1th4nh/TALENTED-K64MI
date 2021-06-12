using System;
using System.IO;
using System.Text;
using System.Runtime;
using System.Collections.Generic;


namespace Eratosthenes
{
    class Program
    {
        static List<int> EratosthenesSieve(int MAX_LIMITS)
        {
            List<int> primes = new List<int>();
            List<bool> isPrime = new List<bool>();

            for (int i = 0; i <= MAX_LIMITS; ++i) isPrime.Add(true);

            if (isPrime.Count >= 2) isPrime[0] = isPrime[1] = false;
            else while (isPrime.Count < 2) isPrime.Add(false);


            for(int i = 2; i*i <= MAX_LIMITS; ++i) if(isPrime[i]) 
            {
                for(int j = i*i; j <= MAX_LIMITS; j += i)
                { 
                    isPrime[j] = false;
                }
            }

            for (int i = 0; i <= MAX_LIMITS; ++i) if (isPrime[i]) primes.Add(i);
            return primes;
        }
        
        static List<int> ImprovedEratosthenesSieve(int MAX_LIMITS)
        {
            //https://cp-algorithms.com/algebra/prime-sieve-linear.html#toc-tgt-2

            List<int> primes = new List<int>();
            List<int> minPrimeFactor = new List<int>();

            for (int i = 0; i <= MAX_LIMITS; ++i) minPrimeFactor.Add(0);

            if (minPrimeFactor.Count >= 2) minPrimeFactor[0] = minPrimeFactor[1] = 2;
            else while (minPrimeFactor.Count < 2) minPrimeFactor.Add(2);


            for(int i = 2; i <= MAX_LIMITS; ++i) 
            {
                if(minPrimeFactor[i] == 0)
                {
                    minPrimeFactor[i] = i;
                    primes.Add(i);
                }
                for(int j = 0; 
                    j < primes.Count && 
                    primes[j] <= minPrimeFactor[i] && 
                    i * primes[j] <= MAX_LIMITS; 
                ++j) {
                    minPrimeFactor[i * primes[j]] = primes[j];
                }
            }

            return primes;
        }



        static void Main(string[] args)
        {
            var IOEncoding = Encoding.UTF8;
            Console.OutputEncoding = IOEncoding;
            Console.Write("Enter n = ");


            string path = "output.txt";
            int bias    = 0;
            int n       = Convert.ToInt32(Console.ReadLine());
            int limits  = Convert.ToInt32(n * Math.Log(n) + n * Math.Log(Math.Log(n)) + bias);
            List<int> primes = ImprovedEratosthenesSieve(limits);



            Console.WriteLine("Upper limit of nth primes: {0}", limits);
            Console.WriteLine("Found {0} primes, needed {1}", primes.Count, n);





            //if(!File.Exists(path)) File.Create(path);

            var sw = new StreamWriter(path);
            if (primes.Count >= n) for (int i = 0; i < n; ++i) sw.WriteLine(primes[i]);
            else sw.WriteLine("Input too large");
        }


    }
}
