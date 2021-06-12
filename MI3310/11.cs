using System;
using System.IO;
using System.Text;

namespace YearToLunarYear
{
    class Program
    {
        static void Main(string[] args)
        {
            String[] ThienCan = {
                "Canh",
                "Tân",
                "Nhâm",
                "Quý",
                "Giáp",
                "Ất",
                "Bính",
                "Đinh",
                "Mậu",
                "Kỷ",
            };
            string[] DiaChi = {
                "Thân",
                "Dậu",
                "Tuất",
                "Hợi",
                "Tý",
                "Sửu",
                "Dần",
                "Mão",
                "Thìn",
                "Tỵ",
                "Ngọ",
                "Mùi",
            };


            StringBuilder ret = new StringBuilder();
            var IOEncoding = Encoding.UTF8;
            Console.OutputEncoding = IOEncoding;

            
            
            Console.Write("Nhập năm dương lịch từ -2^62 đến 2^63 - 1: ");
            long initial_year = Int64.Parse(Console.ReadLine());
            long calc_year = initial_year;




            if (calc_year < 0) calc_year += (Math.Abs(calc_year) / 60 + 20) * 60;
            ret.Append(ThienCan[calc_year % 10]);
            ret.Append(" ");
            ret.Append(DiaChi[calc_year % 12]);

            
            
            if(initial_year >= 0) Console.WriteLine("Năm âm lịch của năm {0} là {1}", initial_year, ret);
            else Console.WriteLine("Năm âm lịch của năm {0} trước Công nguyên là {1}", Math.Abs(initial_year), ret);
        }
    }
}
