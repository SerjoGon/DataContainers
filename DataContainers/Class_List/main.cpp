#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define DELIMETER "\n--------------------------------------\n"

class List;
class Element;
class List
{
	class Element
	{
		int data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:data(data), pNext(pNext), pPrev(pPrev)
		{
			cout << "ElementConstructor:\t" << this << endl;
		}
		~Element() { cout << "ElementDestructor:\t" << this << endl; }
		friend class List;
		friend List operator+(const List& left, const List& right);
	}*head, * tail;
	size_t size;
public:
	
	class iterator
	{
		Element* tmp;
	public:
		iterator(Element* tmp) :tmp(tmp)
		{
			cout << "IterarorConstructor:\t" << this << endl;
		}
		~iterator()
		{
			cout << "IteratorConstructor:\t" << this << endl;
		}
		iterator& operator++()
		{
			tmp = tmp->pNext;
			return *this;
		}
		iterator operator++(int)
		{
			iterator old = *this;
			tmp = tmp->pNext;
			return old;
		}
		iterator& operator--()
		{
			tmp = tmp->pPrev;
			return *this;
		}
		iterator operator--(int)
		{
			iterator old = *this;
			tmp = tmp->pPrev;
			return old;
		}
		bool operator==(const iterator& other)const
		{
			return this->tmp == other.tmp;
		}
		bool operator!=(const iterator& other)const
		{
			return this->tmp != other.tmp;
		}
		const int& operator*()const
		{
			return tmp->data;
		}
		int& operator*()
		{
			return tmp->data;
		}
	};
	class reverseiterator
	{
		Element* tmp;
	public:
		reverseiterator(Element* tmp) :tmp(tmp)
		{
			cout << "ReverseIteratorConstructor:\t" << this << endl;
		}
		~reverseiterator() { cout << "ReverseIteratorDestructor:\t" << this << endl; }
		reverseiterator& operator++()
		{
			tmp = tmp->pPrev;
			return *this;
		}
		reverseiterator operator++(int)
		{
			reverseiterator old = *this;
			tmp = tmp->pPrev;
			return old;
		}
		reverseiterator& operator--()
		{
			tmp = tmp->pNext;
			return *this;
		}
		reverseiterator operator--(int)
		{
			reverseiterator old = *this;
			tmp = tmp->pNext;
			return old;
		}
		bool operator==(const reverseiterator& other)const
		{
			return this->tmp == other.tmp;
		}
		bool operator!=(const reverseiterator& other)const
		{
			return this->tmp != other.tmp;
		}
		const int& operator*()const
		{
			return tmp->data;
		}
		int& operator*()
		{
			return tmp->data;
		}
	};
	const iterator begin()const
	{
		return head;
	}
	const iterator end()const
	{
		return nullptr;
	}
	const reverseiterator reverse_begin()
	{
		return tail;
	}
	const reverseiterator reverse_end()
	{
		return nullptr;
	}
	List()
	{
		head = tail = nullptr;
		size = 0;
		cout << "ListContructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin();it != il.end();it++)
		{
			push_back(*it);
		}
	}
	List(const List& other) :List()
	{
		*this = other;
		cout << "CopyConstructor:\t" << this << endl;
	}
	List(List&& other)noexcept :List()
	{
		*this = std::move(other);
		cout << "MoveConstructor:\t" << this << endl;
	}
	~List()
	{
		while(head)pop_front();
	}
	// Operators:
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (head)pop_front();
		for (Element* tmp = other.head; tmp; tmp = tmp->pNext)
		{
			push_back(tmp->data);
			cout << "CopyAssignment:\t" << this << endl;
			return *this;
		}
	}
	List operator=(List&& other)noexcept
	{
		this->head = other.head;
		this->tail = other.tail;
		this->size = other.size;
		other.head = nullptr;
		other.tail = nullptr;
		other.size = 0;
		cout << "MoveAssignment:\t" << this << endl;
		return *this;
	}
	// ADD METHODS:
	void push_front(int data)noexcept
	{
		if (head == nullptr && tail == nullptr)
		{
			head = tail = new Element(data);
			size++;
			return;
		}
		Element* New = new Element(data);
		New->pNext = head;
		head->pPrev = New;
		head = New;
		//head = head->pPrev = new Element(data, head);
		size++;
	}
	void push_back(int data)
	{
		if (head == nullptr && tail == nullptr)return push_front(data);
		tail = tail->pNext = new Element(data, nullptr, tail);
		size++;
	}
	void insert(int index, int data)
	{
		Element* tmp;
		if (index > size)return;
		if (index == 0)return push_front(data);
		if (index == size)return push_back(data);
		if (index < size / 2)
		{
			tmp = head;
			for (int i = 0; i < index;i++)tmp = tmp->pNext;
		}
		else
		{
			tmp = tail;
			for (int i = 0; i < (size - 1 - index); i++) tmp = tmp->pPrev;
		}
		Element* New = new Element(data);
		New->pNext = tmp;
		New->pPrev = tmp->pPrev;
		tmp->pPrev->pNext = New;
		tmp->pPrev = New;
		size++;
	}
	// Remove Methods:
	void pop_front()
	{
		if (head == nullptr && tail == nullptr)return;
		if (head == tail)
		{
			delete head;
			head = tail = nullptr;
			size--;
			return;
		}
		head = head->pNext;
		delete head->pPrev;
		head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (head == tail)return pop_front();
		tail = tail->pPrev;
		delete tail->pNext;
		tail->pNext = nullptr;
		size--;
	}
	void erase(int index)
	{
		Element* tmp;
		if (index == 0)return pop_front();
		if (index == size - 1)return pop_back();
		if (index >= size)return;
		if (index < size / 2)
		{
			tmp = head;
			for (int i = 0; i < index; i++)tmp = tmp->pNext;
		}
		else
		{
			tmp = tail;
			for (int i = 0; i < (size - index - 1); i++)tmp = tmp->pPrev;
		}
		tmp->pPrev->pNext = tmp->pNext;
		tmp->pNext->pPrev = tmp->pPrev;
		delete tmp;
		size--;
	}
	// Methods:
	void print()const
	{
		for (Element* tmp = head;tmp; tmp = tmp->pNext)
			cout << tmp->pPrev << tab << tmp << tab << tmp->data << tab << tmp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
	void reverse_print()const
	{
		for (Element* tmp = tail;tmp; tmp = tmp->pPrev)
			cout << tmp->pPrev << tab << tmp << tab << tmp->data << tab << tmp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
	friend List operator+(const List& left, const List& right);
};

List operator+(const List& left, const List& right)
{
	List cat = left;
	for (List::Element* tmp = right.head; tmp; tmp = tmp->pNext)
	{
		cat.push_back(tmp->data);
	}
	return cat;
}

int main()
{
	setlocale(LC_ALL, "Ru");
	int size;
	cout << "Введите размер списка: ";cin >> size;
	List list;
	for (int i = 0; i < size; i++)
	{
		list.push_front(rand() % 50);
		//list.push_back(rand() % 50);
	}
	//list.print();
	list.reverse_print();
	list.insert(4, 345);
	list.reverse_print();
	list.erase(3);
	list.print();
	cout << DELIMETER;
	List list1 = { 1,2,3,4,5,6,7,8 };
	list = list1;
	list1 = list1;
	for (int i : list1)
	{
		cout << i << tab;
	}
	cout << endl;
	cout << DELIMETER;
	for (List::iterator it = list1.begin();it != list1.end();it++)
	{
		cout << *it << tab;
	}
	cout << DELIMETER;

	// end of main! :D
	return 0;
}