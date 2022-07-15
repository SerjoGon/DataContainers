#include<iostream>
using std::cout;
using std::cin;
using std::endl;
#define DELIMETER "\n-------------------------------------\n"
#define tab "\t"
class ForwardList;
class Element
{
	int Data;
	Element* pNext;
	static int count;
public:
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
	friend class Iterator;
};

int Element::count = 0;

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) : Temp(Temp)
	{
		cout << "ItConstructor!:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}
	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	const int& operator*()const
	{
		return Temp->Data;
	}
	int& operator*()
	{
		return Temp->Data;
	}
};

class ForwardList
{
	Element* Head;
	unsigned int size;
public:
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ForwardList(Element* Head = nullptr) :Head(Head)
	{
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(std::initializer_list<int>il) : ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin();it != il.end();it++) push_back(*it);
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		/*Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}*/
		*this = other;
		cout << "CopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& other)noexcept :ForwardList()
	{
		/*this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;*/
		*this = std::move(other);
		cout << "MoveConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		clear();
		cout << "LDestructor:\t" << this << endl;
	}
	// operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		clear();
		Element* Temp = other.Head;
		for (Element* Temp = other.Head;Temp ;Temp = Temp->pNext)push_back(Temp->Data);
		/*while(Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}*/
		cout << "CopyAssigment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)noexcept
	{
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "MoveAssignment:\t" << this << endl;
		return *this;
	}

	//				Adding Elements:
	void push_front(int Data)
	{
		Head = new Element(Data,Head);
		size++;
	}
	void push_back(int Data)
	{
		//if (Head == nullptr)// 
		//{
		//	Head = new Element(Data);
		//}
		//else
		//{
		//	Element* current = this->Head;
		//	while (current->pNext != nullptr)
		//	{
		//		current = current->pNext;
		//	}
		//	current->pNext = new Element(Data);
		//}
		if (Head == nullptr)return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext != nullptr) Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Data,int index)
	{
		if (index == 0)push_front(Data);
		if (index > size)return;
		if (index == size)return push_back(Data);
		else
		{
			Element* previous = Head;
			for (int i = 0; i < index -1; i++) previous = previous->pNext;
			/*Element* NewElem = new Element(Data, previous->pNext);
			previous->pNext = NewElem;*/
			previous->pNext = new Element(Data, previous->pNext);
		}
		size++;
	}
	//				Removing Elements:
	void pop_front()
	{
		Element* erased = Head;
		Head = Head->pNext;
		delete erased;
		size--;
	}
	void pop_back()
	{
		if (Head->pNext == nullptr)return pop_front();
		Element* temp = Head;
		while (temp->pNext->pNext)temp = temp->pNext;
		delete temp->pNext;
		temp->pNext = nullptr;
		size--;
	}
	void erase(int index)
	{
		if (index == 0) pop_front();
		else
		{
			Element* previous = this->Head;
			for (int i = 0; i < index - 2; i++)
			{
				previous = previous->pNext;
			}
			Element* erased = previous->pNext;
			previous->pNext = erased->pNext;
			delete erased;
		}
		size--;
	}
	void clear()
	{
		/*Element* Temp = Head;
		while (Temp != nullptr)
		{
			pop_front();
		}*/
		while (Head)pop_front();
	}
	
	//				Methods:
	void  print()const
	{
		/*Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}*/
		for (Element* Temp = Head; Temp ; Temp = Temp->pNext)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
	}
	
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList cat = left;
	/*Element* Temp = right.Head;
	while (Temp)
	{
		cat.push_back(Temp->Data);
		Temp = Temp->pNext;
	}*/
	for (Element* Temp = right.Head;Temp ;Temp = Temp->pNext)
	{
		cat.push_back(Temp->Data);
	}
	cout << "Оператор + " << endl;
	return cat;
}

//#define BASE_CHECK
//#define COUNT_CHECK
//#define OPERATOR_PLUS_CHECK
//#define RANGE_BASED_ARRAY
int main()
{
	setlocale(LC_ALL, "Ru");
#ifdef BASE_CHECK


	
	int n;
	cout << "Введите размер списка: ";cin >> n;
	int index;
	int value;
	ForwardList list;
	for (int i = 0; i < n;i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();

	ForwardList list_2;
	ForwardList list_3;
	for (int i = 0; i < n; i++)
	{
		list_2.push_back(rand() % 30);
	}
	list_2.print();
	cout << "Введите индекс добавочного элемента! ";cin >> index;
	cout << "Введите значение добавочного элемента! ";cin >> value;
	list_2.insert(value, index);
	list_2.print();
	list_3 = list + list_2;
	list_3.print();

	//ForwardList list3 = list;
	
#endif // BASE_CHECK
#ifdef COUNT_CHECK


	ForwardList list;
	list.push_back(12);
	list.push_back(13);
	list.push_back(15);
	list.push_back(32);
	list.push_back(1212);
	list.push_back(99);
	list.print();
	ForwardList list_2;
	list_2.push_back(3);
	list_2.push_back(45);
	list_2.push_back(6);
	list_2.push_back(4);
	list_2.push_back(13);
	list_2.print();
#endif // COUNT_CHECK
#ifdef OPERATOR_PLUS_CHECK
	ForwardList list;
	list.push_back(12);
	list.push_back(13);
	list.push_back(15);
	list.push_back(32);
	list.push_back(1212);
	list.push_back(99);
	list.print();
	ForwardList list_2;
	list_2.push_back(3);
	list_2.push_back(45);
	list_2.push_back(6);
	list_2.push_back(4);
	list_2.push_back(13);
	list_2.print();
	cout << DELIMETER;
	//ForwardList list3 =  list + list_2;// MoveConstructor
	ForwardList list3;
	list3 = list + list_2;
	cout << DELIMETER;
	list3.print();
#endif // OPERATOR_PLUS_CHECK
#ifdef RANGE_BASED_ARRAY
	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]);i++)cout << arr[i] << tab;
	cout << endl;
	for (int i : arr)// range-base for(цикл for на основе диапазона, цикл для контейнеров)
		cout << i << tab;// итератор i  последовательно принимает значение каждого элемента массива.
	cout << endl;
#endif // RANGE_BASED_ARRAY
	ForwardList list = { 3,5,8,13,21 };
	list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
	for (Iterator it = list.begin();it != list.end();++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	//---------------------------------
	return 0;
}