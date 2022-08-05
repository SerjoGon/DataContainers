#include<iostream>

using std::cin;
using std::cout;
using std::endl;

class Point
{
private:
	int x;
	int y;
public:
	// get/set methods:
	void set_y(int valueY)
	{
		y = valueY;
	}
	void set_X(int valueX)
	{
		x = valueX;
	}
	// Constructors:  
	Point() 
	{
		x = 0;
		y = 0;
	}
	Point(int valueX, int valueY)
	{
		x = valueX;
		y = valueY;
	}
	// Other Methods:
	void Print()const
	{
		cout << "Point X = " << x << "\tPoint Y = " << y << endl;
	}
};

int main()
{
	setlocale(LC_ALL, "Ru");
	Point a(5, 11);
	a.Print();
	Point b;
	b.Print();
	return 0;
}