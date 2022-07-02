#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"

class Element
{
	int Data;
	Element* pNext;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	Element* Head;
public:
	ForwardList(Element* Head = nullptr ):Head(Head)
	{
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}
	//				Adding Elements:
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
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
	}
	void insert(int Data,int index)
	{
		if (index == 0)
		{
			push_front(Data);
		}
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
	}
	//				Removing Elements:
	void pop_front()
	{
		Element* erased = Head;
		Head = Head->pNext;
		delete erased;
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
	void pop_back()
	{
		if (Head->pNext == nullptr)return pop_front();
		Element* temp = Head;
		while (temp->pNext->pNext)temp = temp->pNext;
		delete temp->pNext;
		temp->pNext = nullptr;
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
	}
};

int main()
{
	setlocale(LC_ALL, "Ru");
	int n;
	cout << "Введите размер списка: ";cin >> n;
	ForwardList list;
	for (int i = 0; i < n;i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	list.push_back(123);
	list.print();
	ForwardList list_2;
	for (int i = 0; i < n; i++)
	{
		list_2.push_back(rand() % 30);
	}
	list_2.print();
	/*list_2.pop_front();
	list_2.print();
	list_2.insert(23, 4);
	list_2.print();*/
	list_2.pop_back();
	list_2.print();
	list_2.clear();
	//---------------------------------
	return 0;
}