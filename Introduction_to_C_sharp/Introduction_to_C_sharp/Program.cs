Console.WriteLine("Привет, введи число от 1 до 100!");
string? number = Console.ReadLine();
double operand = Convert.ToInt32(number);
if(operand > 1 && operand <101)
{
    if (operand % 3 != 0 && operand % 5 != 0) Console.WriteLine(operand);
    if (operand % 3 == 0) Console.Write("Fizz ");
    if (operand % 5 == 0) Console.WriteLine("Buzz!");
}
else
{
    Console.WriteLine("Ошибка! Перезапустите и введите число от 1 до 100!!!");
}