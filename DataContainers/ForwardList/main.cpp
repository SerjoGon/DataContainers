#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"

class Element
{
	int Data;
	Element* pNext;
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
	friend class ForwardList;
};

int Element::count = 0;

class ForwardList
{
	Element* Head;
	unsigned int size;
public:
	ForwardList(Element* Head = nullptr) :Head(Head)
	{
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		cout << "CopyConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		clear();
		cout << "LDestructor:\t" << this << endl;
	}
	// operators:
	ForwardList& operator=(const ForwardList& other)
	{
		clear();
		Element* Temp = other.Head;
		while(Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		cout << "CopyAssigment:\t" << this << endl;
		return *this;
	}

	//				Adding Elements:
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
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
		Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext != nullptr) Temp = Temp->pNext;
		Temp->pNext = New;
		size++;
	}
	void insert(int Data,int index)
	{
		if (index == 0)push_front(Data);
		if (index > size)return;
		if (index == size)return push_back(Data);
		else
		{
			Element* previous = this->Head;
			for (int i = 0; i < index -2; i++)
			{
				previous = previous->pNext;
			}
			Element* NewElem = new Element(Data, previous->pNext);
			previous->pNext = NewElem;
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
		Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
	}
};
#define BASE_CHECK
//#define COUNT_CHECK
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
	list.erase(3);
	list.print();
	list.push_back(123);
	list.print();

	ForwardList list_2;
	for (int i = 0; i < n; i++)
	{
		list_2.push_back(rand() % 30);
	}
	cout << "Введите индекс добавочного элемента! ";cin >> index;
	cout << "Введите значение добавочного элемента! ";cin >> value;
	list_2.print();
	list_2.insert(value, index);
	list_2.print();
	list_2.clear();

	//ForwardList list3 = list;
	ForwardList list3;
	list3 = list;
	list3.print();
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

	//---------------------------------
	return 0;
}