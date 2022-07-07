#include<iostream>
#include<string>
using std::cin;
using std::cout;
using std::endl;

class Human
{
	int age;
	int weight;
	std::string name;
public:
	int get_age()const { return age; }
	int get_weight()const { return weight; }
	std::string get_name()const { return name; }
	void set_age(int age)
	{
		if (age > 0)this->age = age;
		else this->age = 20;
	}
	void set_weight(int weight)
	{
		if (weight > 0)this->weight = weight;
		else weight = 50;
	}
	void set_name(std::string name)
	{
		this->name = name;
	}
	// Constructors

	Human(std::string name = "Name") {}

	Human(int age,int weight, std::string name)
	{
		set_age(age);
		set_weight(weight);
		set_name(name);
	}
	~Human(){}
	// MEthods:
	void print()const
	{
		cout << "ФИО:	" << get_name() << endl;
		cout << "Возраст:	" << get_age() << endl;
		cout << "Вес:	" << get_weight() << endl;
	}
};

int main()
{
	setlocale(LC_ALL, "Ru");

	Human Boris(23,92, "Борис Борисович Бритва");
	Boris.print();
	Human Stuart;
	Stuart.set_age(45);
	Stuart.set_weight(65);
	Stuart.set_name("Stuart Little");
	Stuart.print();


	return 0;
}