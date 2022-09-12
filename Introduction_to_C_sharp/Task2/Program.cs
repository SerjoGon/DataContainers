using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task2
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Введите число!");
            string number = Console.ReadLine();
            Console.WriteLine("Введите процент первого числа");
            string percent = Console.ReadLine();
            Console.WriteLine("{1}% от числа {0} = {2}",number,percent,Convert.ToDouble(number)*(Convert.ToDouble(percent) / 100));
        }
    }
}
