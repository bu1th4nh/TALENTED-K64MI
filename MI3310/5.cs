using System;
using System.Text;
using System.Collections.Generic;

namespace BasicLists
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.InputEncoding = Encoding.UTF8;
            Console.OutputEncoding = Encoding.UTF8;


            string[] str1 = { "Mon", "Ki", "Thuat", "Lap", "Trinh" };
            List<string> str = new List<string>(str1);
            str.Add("Lop");                                         // thêm vào cuối danh sách
            str.AddRange(str1);                                     //thêm 1 danh sách vào cuối
            string[] STR = { "CTTN", "Toan", "Tin", "K64" };
            str.InsertRange(6, STR);

            foreach (string s in str) Console.Write(" " + s);       // in ra danh sách cuối cùng
            Console.WriteLine();

            str.Reverse();                                          //đảo ngược các ptu
            str.Sort();                                             //sắp xếp theo thứ tự từ điển

            Console.WriteLine("Độ dài của List sau khi thêm các phần tử: {0} ", str.Count);

            foreach (string s in str) Console.Write(" " + s);       // in ra danh sách cuối cùng
            Console.WriteLine();


            str.ToArray();                                          //chuyển sang mảng 1 chiều
            for (int i = 0; i < str.Count; i++)
            {
                Console.WriteLine("str[{0}]={1}", i, str[i]);
            }


            Console.WriteLine("Nhập phần tử cần kiểm tra: ");
            string str2 = Console.ReadLine();
            bool isExists = str.Contains(str2);                     // kiểm tra xem phần tử có ở trong danh sách không
            if (isExists == false)
            {
                Console.WriteLine("Không tìm thấy {0} trong List", str2);
            }
            else Console.WriteLine("Tìm thấy {0} đầu tiên ở vị trí {1} và cuối cùng ở{2} trong List", str2, str.IndexOf(str2), str.LastIndexOf(str2));

            
            List<string> STR1 = new List<string>(STR);
            string[] a = new string[20];
            NewMethod(STR1, a);
            for (int i = 0; i < 20; i++)
            {
                Console.WriteLine("str[" + i + "]={0}", a[i]);
            }
            Console.WriteLine(str.BinarySearch(str2));//tìm kiếm đối tượng trong List theo tuật toán tìm kiếm nhị phân.
                                                      //Nếu tìm thấy sẽ trả về vị trí của phần tử trong List, nếu k sẽ trả về một số âm
        }

        public static void NewMethod(List<string> STR1, string[] a)//sao chép tất cả các phần tử trong list sang mảng 1 chiều;
        {
            STR1.CopyTo(a, 1);
        }
    }
}