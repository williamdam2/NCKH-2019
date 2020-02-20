
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CalLogaritEX
{
    class Program
    {

        static double[] sLn = { 0,0, 0.69314718056, 1.09861228867, 1.38629436112, 1.60943791243, 1.79175946923,
                                1.945910149066,2.07944154168,2.19722457734,2.30258509299};
        static double LnNew(double A)
        {
            double Ln=0;
            int b=0;
            double a=0;
            uint k = 1;
            PhanTichSo(A, ref a, ref b);
            
            k = (uint)a;
            a = a / k;
            Ln = sLn[k] + sLn[10] * b;
            Ln = Ln + calSLn(a);
            return Ln;
        }
        
        static double calSLn(double a)
        {
            double cal=0;
            double y = a - 1;
            y = y / (a + 1);
            for(int i=0;i<50;i++)
            {
                cal += (1 / (2 * i + 1)) * IPOW(y, 2 * i);
            }
            cal = cal * 2 * y;

            return cal;
        }

        static void PhanTichSo(double A , ref double a,ref int b)
        {
            int i = 0;
           
            if(A>10)
            {
                while(A>10)
                {
                    A = A / 10;
                    i++;
                }
            }
            else if(A<1)
            {
                while(A<1)
                {
                    A = A * 10;
                    i--;
                }
            }

            //
            if (A >= 1 && A <= 10)
            {
                b = i;
                a = A;
            }
            

        }
        //static double TayLor(double B)
        //{
        //    double Tb=0;
        //    for(int i=0;i<10;i++)
        //    {
        //        Tb += (Math.Pow(-1, i)) * ((Math.Pow(B, i + 1)) / (i + 1));
        //    }

        //    return Tb;
        //}

        //static double LnX(double A)
        //{
            
        //    double B = 0;
        //    if (A < 2 && A>0)
        //    {
        //        return TayLor(A-1);
        //    }
        //    else
        //    {
        //        B = A / 1.9;
        //        return Ln19 + LnX(B);
        //    }
            
        //}

        //static double LnNew(double x)
        //{
        //    double Ln;
            

        //    return Ln;
        //}
        static double IPOW(double  x,long  y)
        {
            double pow = x;
            
            if(y==0)
            {
                return 1;
            }
             else
            {
                for (int i = 0; i < y - 1; i++)
                {
                    pow = pow * x;
                }
                return pow;
            }
            
        }
        
        static long GiaiThua(int n)
        {
            long giaiThua = 1;
            if(n==0||n==1)
            {
                return 1;
            }
            else
            {
                for (int i = 2; i <= n; i++)
                {
                    giaiThua = giaiThua * i;
                }
                return giaiThua;
            }
           
        }

        static long DayNhan(int s,int t,int n)
        {
            long daynhan = 1;
            for(int i = 0; i<n;i++)
            {
                daynhan *= (s - i * t);
            }

            return daynhan;
        }
        static double DayTong(double x , int s ,int t)
        {
            double dayTong = 0;
            for(int i =0; i<50;i++)
            {
                dayTong += (DayNhan(s, t, i) * IPOW(x, i)) / (GiaiThua(i) * IPOW(t, i));
            }

            return dayTong;
        }

        
       

        static void Main(string[] args)
        {
            string h = "n";
            //string A; 
            //do
            //{
            //    Console.WriteLine("Phần Mềm tính LN(x).......");
            //    Console.WriteLine("Nhâp Vào X");
            //    A= Console.ReadLine();
            //    double X = Convert.ToDouble(A);
            //    double KetQua = LnX(X);
            //    A = KetQua.ToString();
            //    Console.WriteLine(A);
            //    Console.WriteLine("Ban Co muon tinh tiep hay khong y/n ????");
            //    h = Console.ReadLine();
            //    Console.Clear();

            //} while (h == "y");

            //double A = POW(4.2, 4);
            //string B = A.ToString();
            //Console.WriteLine(B);
            //Console.ReadKey();


            //Console.WriteLine(RPOW(1.5, 41, 10).ToString());
            //Console.ReadKey();
            do
            {
                double x;
                Console.WriteLine("Hay nhap vao x :");
                x = Convert.ToDouble(Console.ReadLine());
                double ln = LnNew(x);
                Console.WriteLine(ln.ToString());

                Console.WriteLine("Ban Co muon tinh tiep hay khong y/n ????");
                h = Console.ReadLine();
            } while (h == "Y" || h == "y");




        }
    }
}
