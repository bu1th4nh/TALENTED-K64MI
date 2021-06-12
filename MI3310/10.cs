using System;
using System.IO;
using System.Text;
using System.Runtime;
using System.Globalization;
using System.Collections.Generic;

namespace MoneyTeller
{
    class Money
    {
        //Constants -------------------------------------------------------------------------
        String[][] units =
        {
            new String[]{
                "",
                "một trăm",
                "hai trăm",
                "ba trăm",
                "bốn trăm",
                "năm trăm",
                "sáu trăm",
                "bảy trăm",
                "tám trăm",
                "chín trăm",
                "không trăm"
            },
            new String[]{
                "",
                "mười",
                "hai mươi",
                "ba mươi",
                "bốn mươi",
                "năm mươi",
                "sáu mươi",
                "bảy mươi",
                "tám mươi",
                "chín mươi",
                "linh"
            },
            new String[]{
                "",
                "một",
                "hai",
                "ba",
                "bốn",
                "năm",
                "sáu",
                "bảy",
                "tám",
                "chín",
                "mốt",
                "lăm",
                "không"
            },
        };
        String[] power10 = {
            "",
            "nghìn",
            "triệu"
        };
        String currency  = "Bitcoin";


        //Variables -------------------------------------------------------------------------
        int n;
        StringBuilder src_amount;
        StringBuilder teller_amount;
        List<StringBuilder> tokens;

        //Constructors -------------------------------------------------------------------------
        public Money(string src)
        {
            teller_amount = new StringBuilder();
            src_amount = new StringBuilder(src);

            while (src_amount.Length % 3 != 0) src_amount.Insert(0, '0');
            n = src_amount.Length;
        }
        public Money()
        {
            n = 0;
            src_amount = new StringBuilder();
            teller_amount = new StringBuilder();
        }

        //Utilities -------------------------------------------------------------------------
        private void addWhitespace(ref StringBuilder s)
        {
            if (s.Length == 0) return;
            if (s[s.Length - 1] != ' ') s.Append(' ');
        }
        private void Upperlize(ref StringBuilder s)
        {
            if (s.Length == 0) return;

            String r1 = new string(s[0], 1);
            String r2 = r1.ToUpper(new CultureInfo("vi-VN", false));

            s[0] = r2[0];
        }
        private bool isTrueZeros(StringBuilder x)
        {
            return x[0] == x[1] && x[1] == x[2] && x[2] == '0';
        }


        //Core functions -------------------------------------------------------------------------
        private void Tokenize()
        {
            tokens = new List<StringBuilder>();
            StringBuilder tmp = new StringBuilder();

            for(int i = 0; i < n; ++i)
            {
                tmp.Append(src_amount[i]);
                if(tmp.Length == 3)
                {
                    tokens.Add(tmp);
                    tmp = new StringBuilder();
                }
            }

            for(int i = 0, j = tokens.Count - 1; i < j; ++i, --j)
            {
                tmp = tokens[i];
                tokens[i] = tokens[j];
                tokens[j] = tmp;
            }


        }
        private StringBuilder ParseParts(StringBuilder x, bool isLargestToken)
        {
            StringBuilder ret = new StringBuilder("");

            // Số 000
            if (isTrueZeros(x)) return isLargestToken ? new StringBuilder("không") : ret;


            // Trường hợp khác
            if (isLargestToken)
            {
                //Hàng trăm của số có bậc lớn nhất
                ret.Append(units[0][x[0] - '0']);

                addWhitespace(ref ret);

                //Hàng chục của số có bậc max
                if (x[0] != '0' && x[1] == '0' && x[2] != '0')
                {
                    ret.Append(units[1][10]);       //Một trăm linh hai
                }
                else ret.Append(units[1][x[1] - '0']);
            }
            else
            {
                //Hàng trăm
                if (x[0] == '0')
                {
                    ret.Append(units[0][10]);       //không trăm
                }
                else ret.Append(units[0][x[0] - '0']);

                addWhitespace(ref ret);

                //Hàng chục
                if (x[1] == '0' && x[2] != '0')
                {
                    ret.Append(units[1][10]);       //Một trăm linh hai
                }
                else ret.Append(units[1][x[1] - '0']);
            }

            addWhitespace(ref ret);

            //Hàng đơn vị
            if (x[1] != '0' && x[2] == '5')
            {
                ret.Append(units[2][11]);           //Mười lăm
            }
            else if (x[1] != '0' && x[1] != '1' && x[2] == '1')
            {
                ret.Append(units[2][10]);           //Hai mươi mốt
            }
            else ret.Append(units[2][x[2] - '0']);
             

            return ret;
        }
        private void buildResult()
        {
            for(int i = tokens.Count - 1; i >= 0; --i)
            {
                StringBuilder number = ParseParts(tokens[i], i == tokens.Count - 1);
                StringBuilder powers = new StringBuilder(power10[i % 3]);
                StringBuilder billns = new StringBuilder();
                bool check = false;


                if(i != 0 && i % 3 == 0)
                {
                    for(int j = i; j > 1; j /= 3)
                    {
                        addWhitespace(ref billns);
                        billns.Append("tỷ");
                    }

                    for (int j = i; j < tokens.Count; ++j) if(!isTrueZeros(tokens[j]))
                    {
                        check = true;
                        break;
                    }
                        
                }



                addWhitespace(ref teller_amount);
                teller_amount.Append(number);


                addWhitespace(ref teller_amount);
                if (!isTrueZeros(tokens[i])) teller_amount.Append(powers);


                addWhitespace(ref teller_amount);
                if (check) teller_amount.Append(billns);
            }

            addWhitespace(ref teller_amount);
            teller_amount.Append(currency);
            Upperlize(ref teller_amount);
        }


        //Driver functions -------------------------------------------------------------------------
        public void Initialize()
        {
            Tokenize();
            buildResult();
        }
        public StringBuilder getTellerStrBuilder()
        {
            return teller_amount;
        }
        public String getTellerString()
        {
            return teller_amount.ToString();
        }
        public void printTeller()
        {
            Console.Write("Số tiền (bằng chữ): ");
            Console.WriteLine(teller_amount);
        }
    }
    
    class Program
    {
        static void Main(string[] args)
        {
            var IOEncoding = Encoding.UTF8;
            Console.OutputEncoding = IOEncoding;

            Console.Write("Nhập số tiền (bằng số): ");
            string str = Console.ReadLine();

            Money xxx = new Money(str);
            xxx.Initialize();
            xxx.printTeller();

        }
    }
}
