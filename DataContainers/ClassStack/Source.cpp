//Project:	ForwardList
//Solution:	DataContainers
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n------------------------------------\n"

class ForwardList;
class Element
{
	int Data;		//�������� ��������
	Element* pNext;	//����� ���������� ���������
	static int count;
public:
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
	friend class Iterator;
	friend class ForwardList;
	friend class Stack;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

int Element::count = 0;

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
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
protected:
	Element* Head;	//������ ������
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
	ForwardList()
	{
		Head = nullptr; //����� ������ ������ ��������� �� 0 - ������ ����
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(initializer_list<int> il) :ForwardList()
	{
		//initializer_list - ��� ���������.
		//��������� - ��� ������, ������� ���������� �������� ������ �������� � ������.
		//� ������ ���������� ���� ������ begin() � end()
		//begin() - ���������� �������� �� ������ ����������
		//end() - ���������� �������� �� ����� ����������
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
			push_back(*it);
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		/*Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}*/
		*this = other;	//CopyAssignment
		cout << "CopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& other) :ForwardList()
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
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//				Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		Element* Temp = other.Head;
		while (Temp)
		{
			this->push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
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
		////1) ������� ����� �������:
		//Element* New = new Element(Data);
		////2) ������������ ����� ������� � ������ ������:
		//New->pNext = Head;
		////3) �������, ��� ����� ������� �������� ������� ������:
		//Head = New;
		Head = new Element(Data, Head);
		//Head = New;
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1) ������� ����� �������:
		//Element* New = new Element(Data);
		//2) ����� �� ����� �������:
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		//3) ������������ ����� ������� � ������:
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index == 0)return push_front(Data);
		if (Index == size)return push_back(Data);
		if (Index > size)
		{
			cout << "Error: Out of range" << endl;
			return;
		}
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		/*Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}
	//				Removing elements:
	void pop_front()
	{
		//1) ���������� ����� ���������� ��������;
		Element* erased = Head;
		//2) ��������� ������� �� ������:
		Head = Head->pNext;
		//3) ������� ������� �� ������
		delete erased;
		size--;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	//				Methods:
	void print()const
	{
		/*Element* Temp = Head;	//Temp - ��� ��������.
		//�������� - ��� ���������, ��� ������ ��������
		//����� �������� ������ � ��������� ��������� ������.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//������� �� ��������� �������
		}*/
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "���������� ��������� ������:" << size << endl;
		cout << "����� ���������� ���������: " << Element::count << endl;
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
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)
		cat.push_back(Temp->Data);
	cout << "Operator + " << endl;
	return cat;
}

class Stack :private ForwardList
{
public:
	unsigned int get_size()const
	{
		return size;
	}
	void push(int Data)
	{
		//��������� �������� � � ���������
		ForwardList::push_front(Data);
	}
	void pop()
	{
		//������� ������� �����
		ForwardList::pop_front();
	}
	const int& top()const
	{
		return Head->Data;
	}
	int& top()
	{
		return Head->Data;
	}

	void print()const
	{
		ForwardList::print();
	}
};

//#define BASE_CHECK
//#define OPERATOR_PLUS_CHECK
//#define RANGE_BASED_ARRAY
//#define RANGE_BASED_LIST

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "������� ������ ������: "; cin >> n;
	int arr[5];
	ForwardList list;	//����������� ������ list
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
		//list.push_back(rand() % 100);
	}
	list = list;
	list.print();
	list.pop_front();
	list.print();
	int value;
	int index;
	cout << "������� �������� ������������ ��������: "; cin >> value;
	cout << "������� ������ ������������ ��������: "; cin >> index;
	list.insert(value, index);
	list.print();

	cout << delimiter << endl;
	ForwardList list2 = list;	//CopyConstructor
	cout << delimiter << endl;
	//ForwardList list2;
	//list2 = list;
	list2.print();
#endif // BASE_CHECK

#ifdef OPERATOR_PLUS_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();

	cout << delimiter << endl;
	//ForwardList list3 = list1 + list2;	//MoveConstructor
	ForwardList list3;
	list3 = list1 + list2;
	cout << delimiter << endl;
	list3.print();
#endif // COUNT_CHECK

#ifdef RANGE_BASED_ARRAY
	int arr[] = { 3,5,8,13,21 };

	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
		cout << arr[i] << tab;
	cout << endl;

	//range-based for 
	//(���� for �� ������ ���������, ���� for ��� �����������)
	for (int i : arr)
		cout << i << tab;
	cout << endl;
	//�������� 'i' ��������������� ��������� �������� ������� �������� �������.  
#endif // RANGE_BASED_ARRAY

#ifdef RANGE_BASED_LIST
	ForwardList list = { 3,5,8,13,21 };
	list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
	for (Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // RANGE_BASED_LIST

	Stack stack;
	stack.push(3);
	stack.push(5);
	stack.push(8);
	stack.push(13);
	stack.push(21);
	cout << stack.get_size() << endl;
	stack.print();
	for (;stack.get_size(); stack.pop())
		cout << stack.top() << endl;
	stack.print();
}