using System;
using System.Text;
using System.Collections.Generic;
using System.Security.Cryptography;


namespace ListTimeComparison
{
    class Program
    {
        static void sequentialAssignRandomValueTest(int size)
        {
            var timer_array = new System.Diagnostics.Stopwatch();
            var timer_lists = new System.Diagnostics.Stopwatch();

            int[] arrayz = new int[size];
            List<int> listz = new List<int>(arrayz);

            timer_array.Start();
            for(int i = 0; i < size; ++i)
            {
                arrayz[i] = RandomNumberGenerator.GetInt32(Int32.MinValue, Int32.MaxValue);
            }
            timer_array.Stop();
            
            timer_lists.Start();
            for(int i = 0; i < size; ++i)
            {
                listz[i] = RandomNumberGenerator.GetInt32(Int32.MinValue, Int32.MaxValue);

            }
            timer_lists.Stop();

            Console.WriteLine("Thời gian gán tuần tự {0} phần tử của mảng kích cỡ {0} bằng giá trị ngẫu nhiên là {1} ms", size, timer_array.ElapsedMilliseconds);
            Console.WriteLine("Thời gian gán tuần tự {0} phần tử của List kích cỡ {0} bằng giá trị ngẫu nhiên là {1} ms", size, timer_lists.ElapsedMilliseconds);
        }

        static void sequentialAssignPredefValueTest(int size)
        {
            var timer_array = new System.Diagnostics.Stopwatch();
            var timer_lists = new System.Diagnostics.Stopwatch();

            int[] arrayz = new int[size];
            List<int> listz = new List<int>(arrayz);

            timer_array.Start();
            for (int i = 0; i < size; ++i)
            {
                arrayz[i] = i;
            }
            timer_array.Stop();

            timer_lists.Start();
            for (int i = 0; i < size; ++i)
            {
                listz[i] = i;

            }
            timer_lists.Stop();

            Console.WriteLine("Thời gian gán tuần tự {0} phần tử của mảng kích cỡ {0} bằng giá trị định trước là {1} ms", size, timer_array.ElapsedMilliseconds);
            Console.WriteLine("Thời gian gán tuần tự {0} phần tử của List kích cỡ {0} bằng giá trị định trước là {1} ms", size, timer_lists.ElapsedMilliseconds);
        }

        static void RandomAssignRandomValueTest(int size, int assign_attempt)
        {
            var timer_array = new System.Diagnostics.Stopwatch();
            var timer_lists = new System.Diagnostics.Stopwatch();

            int[] arrayz = new int[size];
            List<int> listz = new List<int>(arrayz);

            timer_array.Start();
            for(int i = 0; i < assign_attempt; ++i)
            {
                arrayz[RandomNumberGenerator.GetInt32(size)] = RandomNumberGenerator.GetInt32(
                    Int32.MinValue, 
                    Int32.MaxValue
                );
            }
            timer_array.Stop();
            
            timer_lists.Start();
            for(int i = 0; i < assign_attempt; ++i)
            {
                listz[RandomNumberGenerator.GetInt32(size)] = RandomNumberGenerator.GetInt32(
                    Int32.MinValue, 
                    Int32.MaxValue
                );

            }
            timer_lists.Stop();

            Console.WriteLine("Thời gian gán ngẫu nhiên {0} lần của mảng kích cỡ {1} bằng giá trị ngẫu nhiên là {2} ms", assign_attempt, size, timer_array.ElapsedMilliseconds);
            Console.WriteLine("Thời gian gán ngẫu nhiên {0} lần của List kích cỡ {1} bằng giá trị ngẫu nhiên là {2} ms", assign_attempt, size, timer_lists.ElapsedMilliseconds);
        }

        static void RandomAssignPredefValueTest(int size, int assign_attempt)
        {
            var timer_array = new System.Diagnostics.Stopwatch();
            var timer_lists = new System.Diagnostics.Stopwatch();

            int[] arrayz = new int[size];
            List<int> listz = new List<int>(arrayz);

            timer_array.Start();
            for(int i = 0; i < assign_attempt; ++i)
            {
                arrayz[RandomNumberGenerator.GetInt32(size)] = i;
            }
            timer_array.Stop();
            
            timer_lists.Start();
            for(int i = 0; i < assign_attempt; ++i)
            {
                listz[RandomNumberGenerator.GetInt32(size)] = i;

            }
            timer_lists.Stop();

            Console.WriteLine("Thời gian gán ngẫu nhiên {0} lần của mảng kích cỡ {1} bằng giá trị định trước là {2} ms", assign_attempt, size, timer_array.ElapsedMilliseconds);
            Console.WriteLine("Thời gian gán ngẫu nhiên {0} lần của List kích cỡ {1} bằng giá trị định trước là {2} ms", assign_attempt, size, timer_lists.ElapsedMilliseconds);
        }







        static void sequentialQueryTest(int size)
        {
            var timer_array = new System.Diagnostics.Stopwatch();
            var timer_lists = new System.Diagnostics.Stopwatch();

            int[] arrayz = new int[size];
            List<int> listz = new List<int>(arrayz);
            for(int i = 0; i < size; ++i)
            {
                arrayz[i] = RandomNumberGenerator.GetInt32(Int32.MinValue, Int32.MaxValue);
                listz[i] = arrayz[i];
            }

            int examinate;

            timer_array.Start();
            for(int i = 0; i < size; ++i)
            {
                examinate = arrayz[i];        
            }
            timer_array.Stop();
            
            timer_lists.Start();
            for(int i = 0; i < size; ++i)
            {
                examinate = listz[i];
            }
            timer_lists.Stop();

            Console.WriteLine("Thời gian truy vấn tuần tự của mảng kích cỡ {0} là {1} ms", size, timer_array.ElapsedMilliseconds);
            Console.WriteLine("Thời gian truy vấn tuần tự của List kích cỡ {0} là {1} ms", size, timer_lists.ElapsedMilliseconds);
        }
        static void randomlQueryTest(int size, int query_attempt)
        {
            var timer_array = new System.Diagnostics.Stopwatch();
            var timer_lists = new System.Diagnostics.Stopwatch();

            int[] arrayz = new int[size];
            List<int> listz = new List<int>(arrayz);
            for(int i = 0; i < size; ++i)
            {
                arrayz[i] = RandomNumberGenerator.GetInt32(Int32.MinValue, Int32.MaxValue);
                listz[i] = arrayz[i];
            }

            int examinate;

            timer_array.Start();
            for(int i = 0; i < query_attempt; ++i)
            {
                examinate = arrayz[RandomNumberGenerator.GetInt32(size)];        
            }
            timer_array.Stop();
            
            timer_lists.Start();
            for(int i = 0; i < query_attempt; ++i)
            {
                examinate = listz[RandomNumberGenerator.GetInt32(size)];
            }
            timer_lists.Stop();

            Console.WriteLine("Thời gian truy vấn ngẫu nhiên {0} lần của mảng kích cỡ {1} là {2} ms", query_attempt, size, timer_array.ElapsedMilliseconds);
            Console.WriteLine("Thời gian truy vấn ngẫu nhiên {0} lần của List kích cỡ {1} là {2} ms", query_attempt, size, timer_lists.ElapsedMilliseconds);
        }


        static void Test(int size, int attempts)
        {
            sequentialAssignRandomValueTest(size);
            sequentialAssignPredefValueTest(size);


            RandomAssignRandomValueTest(size, attempts);
            RandomAssignPredefValueTest(size, attempts);


            sequentialQueryTest(size);
            randomlQueryTest(size, attempts);
        }


        static void Main(string[] args)
        {
            var IOEncoding = Encoding.UTF8;
            Console.OutputEncoding = IOEncoding;

            Test(10000000, 10000000);
        }
    }
}
