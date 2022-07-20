#include<iostream>

using namespace std;
//#define TRY_SYNTAX

int main()
{
	setlocale(LC_ALL, "Ru");
#ifdef TRY_SYNTAX
	try
	{
	throw 1;
	}
	catch (short e)
	{
		cerr << "Eror #" << e << " (short)\n";
	}
	catch (int e)
	{
		cerr << "Eror #" << e << " (int)\n";
	}
#endif // TRY_SYNTAX
	//cout << 2 / 0 << endl;
	int a, b;
	cout << "Введите два числа: ";cin >> a >> b;
	try
	{
	cout << a / b << endl;

	}
	catch (...)
	{
		cerr << "Что то пошло не так!!!/n" << endl;
	}

	return 0;
}