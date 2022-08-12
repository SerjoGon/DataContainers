//#include"List.h"
#include"List.cpp"
//#define BASE_CHECK

int main()
{
	setlocale(LC_ALL, "ru");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();
	cout << DELIMETER;
	int value;
	int index;
	cout << "Введите значение добавляемого элемента: ";cin >> value;
	cout << "Введите индекс добавляемого элемента: ";cin >> index;
	try
	{
		list.insert(value, index);
		list.print();
		list.reverse_print();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
	cout << DELIMETER;
	cout << "Введите индекс удаляемого элемента: ";cin >> index;
	try
	{
		list.erase(index);
		list.print();
		list.reverse_print();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
	cout << DELIMETER;
#endif // BASE_CHECK

	List<double> list = { 3,5,8,13,21,34 };
	list.print();
	for (double i : list)cout << i << tab;cout << endl;
	List<double>::ConstReverseIterator rend = list.rend();
	for (List<double>::ConstReverseIterator rit = list.rbegin();rit != rend;++rit)
	{
		cout << *rit << tab;
	}
	cout << endl;
	List<int> list1 = { 3,5,8,13,21 };
	List<int> list2 = { 34,55,89 };
	List<int> list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
	list3.reverse_print();
	return 0;
}

