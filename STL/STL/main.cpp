#include<iostream>
#include<array>
#include<vector>
#include<deque>
using std::cout;
using std::cin;
using std::endl;
//#define VECTOR
//#define ARRAY
#define DEQUE
#define tab "\t"
int main()
{
	setlocale(LC_ALL, "ru");
	typedef int datatype;
#ifdef ARRAY
	const int n = 5;
	std::array<int, 5> arr = {3,5,8,13,21};
	for (int i = 0; i < n;i++)
	{
		cout << arr[i]<< tab;
	}
	cout << endl;
#endif // ARRAY
#ifdef VECTOR
	std::vector<datatype> vec = { 0,1,1,2,3,5,8,13,21,34 };
	vec.front() = 1024;
	try
	{
		for (int i = 0; i < vec.size(); i++)
		{
			//cout << vec[i] << tab;
			cout << vec.at(i) << tab;
		}
		cout << endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
	for (std::vector<datatype>::iterator it = vec.begin();it != vec.end();++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	for (std::vector<datatype>::reverse_iterator it = vec.rbegin();it != vec.rend();++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	cout << vec.front() << endl;
	cout << vec.back() << endl;
	cout << *vec.data() << endl;
	cout << "\n============== Vector capacity ==================\n";
	cout << "Capacity:" << vec.capacity() << endl;
	cout << "Size: \t" << vec.size() << endl;
	cout << "MaxSize:" << vec.max_size() << endl;
	
	vec.push_back(55);
	vec.push_back(45);
	
	cout << "Capacity:" << vec.capacity() << endl;
	cout << "Size: \t" << vec.size() << endl;
	cout << "MaxSize:" << vec.max_size() << endl;
	
	//vec.shrink_to_fit();
	//vec.resize(15);
	vec.reserve(25);
	//vec.assign({ 1024,2048,3072,4096,5120 });
	for (int i : vec)cout << i << tab;
	cout << endl;

	cout << "Capacity:" << vec.capacity() << endl;
	cout << "Size: \t" << vec.size() << endl;
	cout << "MaxSize:" << vec.max_size() << endl;
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: ";cin >> index;
	cout << "Введите значение добавляемого элемента: ";cin >> value;
	std::vector<datatype>::iterator position = vec.begin()+index;
	//if(index <= vec.size())vec.insert(position,value);
	if(index <= vec.size())vec.insert(position,2,value);
	for (int i : vec)cout << i << tab;cout << endl;
	vec.insert(vec.begin() + 2, vec.end() -1, vec.end());
	for (int i : vec)cout << i << tab;cout << endl;
#endif // VECTOR
#ifdef DEQUE
	std::deque<datatype> deque = { 3,5,8,13,21 };
	for (std::deque<datatype>::iterator it = deque.begin();it != deque.end();++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	deque.push_back(34);
	deque.push_back(55);
	deque.push_back(89);
	deque.push_front(2);
	deque.push_front(1);
	deque.push_front(1);
	deque.push_front(0);
	for (int i : deque)cout << i << tab;cout << endl;
#endif // DEQUE

	return 0;
}
