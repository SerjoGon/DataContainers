#include<iostream>

using std::cin; using std::cout; using std::endl;
#define tab "\t"
template<typename T2>
class Iterator;
template<typename T3>
class ReverseIterator;
template<typename T1>
class List;
// ниже описан шаблонный класс element:

template<typename T>
class element
{
	T data;
	element* pNext;
	element* pPrev;
	static int count;
public:
	element(T data, element pNext = nullptr, element* pPrev = nullptr)
		:data(data), pNext(pNext), pPrev(pPrev)
	{
		cout << "ElemConstr:\t" << this << endl;
	}
	~element() { cout << "ElemDestruct:\t" << this << endl; }
	friend class List<element>;
	friend class Iterator<element>;
	friend class ReverseIterator<element>;
};

int element<int>::count = 0; // уникальная передача параметров в шаблонный класс :D

template<typename T2>
class Iterator // Итератор для головы списка
{
	//возможны конфликты при использовании других типов данных с таким итератором
	T2* tmp;
public:
	Iterator(T2* tmp) :tmp(tmp) { cout << "Itconstr:\t" << this << endl; }
	~Iterator() { cout << "ItDestr:\t" << this << endl; }
	Iterator& operator++()
	{
		tmp = tmp->pNext;
		return *this;
	}
	Iterator operator++(int)
	{
		Iterator old = *this;
		tmp = tmp->pNext;
		return old;
	}
	Iterator& operator--()
	{
		tmp = tmp->pPrev;
		return *this;
	}
	Iterator operator--(int)
	{
		Iterator old = *this;
		tmp = tmp->pPrev;
		return old;
	}
	bool operator==(const Iterator& other)const
	{
		return this->tmp == other.tmp;
	}
	bool operator!=(const Iterator& other)const
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

template<typename T3>
class ReverseIterator // итератор для хвоста списка
{
	T3* tmp;
public:
	ReverseIterator(T3* tmp) : tmp(tmp) { cout << "RevConstr:\t" << this << endl; }
	~ReverseIterator() { cout << "RevDestr:\t" << this << endl; }
	ReverseIterator& operator++()
	{
		tmp = tmp->pPrev;
		return *this;
	}
	ReverseIterator operator++(T3)
	{
		ReverseIterator old = *this;
		tmp = tmp->pPrev;
		return old;
	}
	ReverseIterator& operator--()
	{
		tmp = tmp->pNext;
		return *this;
	}
	ReverseIterator operator--(T3)
	{
		ReverseIterator old = *this;
		tmp = tmp->pNext;
		return old;
	}
	bool operator==(const ReverseIterator& other)const
	{
		return this->tmp == other.tmp;
	}
	bool operator!=(const ReverseIterator& other)const
	{
		return this->tmp != other.tmp;
	}
	const int& operator*()const { return tmp->data; }
	int& operator*() { return tmp->data; }
};

//Задумка реализовать двусвязный список для хранения любых данных
template<typename T1>
class List
{
	T1* head;
	T1* tail;
	uint64_t size;
public:
	// Methods Iterator's:
	const Iterator<T1> begin()const { return head; }
	const Iterator<T1> end()const { return nullptr; }
	ReverseIterator<T1> revers_begin() { return tail; }
	ReverseIterator<T1> revers_end() { return nullptr; }
	// Constructors:
	List()
	{
		head = tail = nullptr;
		size = 0;
		cout << "ListConstructor:\t" << this << endl;
	}
	List(std::initializer_list<int> il) :List()
	{
		for (int const* it = il.begin(); it != il.end();it++)
			push_back(*it);
	}
	List(const List& other) :List()
	{
		*this = other;
		cout << "LCopyConstructor:\t" << this << endl;
	}
	List(List&& other) :List()
	{
		*this = std::move(other);
		cout << "LMoveConstructor:\t" << this << endl;
	}
	~List()
	{
		//while (tail) { pop_back(); }
		cout << "ListDestructor:\t" << this << endl;
	}
	// Operators:
	List& operator=(const List& other)
	{
		if (this == &other) return *this;
		while (head)pop_front();
		for (element<T1>* tmp = other.head;tmp;tmp = tmp->pNext)push_back(tmp->data);
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	List& operator=(List&& other)
	{
		this->head = other.head;
		this->size = other.size;
		other.head = nullptr;
		other.size = 0;
		cout << "MoveAssignment:\t" << this << endl;
		return *this;
	}
	// Adding methods:
	void push_front(T1 data)
	{
		if (head == nullptr && tail == nullptr)
		{
			head = tail = new element<T1>(data);
			size++;
			return;
		}
		element<T1>* New = new element<T1>(data);
		New->pNext = head;
		head->pPrev = New;
		head = New;
		size++;
	}
	void push_back(T1 data)
	{
		if (head == nullptr && tail == nullptr)return push_front(data);
		tail = tail->pNext = new element<T1>(data, nullptr, tail);
		size++;
	}
	void insert(int index, T1 data)
	{
		if (index > size)return;
		if (index == 0)return push_front(data);
		if (index == size)return	push_back(data);
		element<T1>* tmp;
		if (index < size / 2)//проверка на заход с головы в противном случае с хвоста
		{
			tmp = head;
			for (int i = 0; i < index; i++)tmp = tmp->pNext;
		}
		else
		{
			tmp = tail;
			for (int i = 0; i < (size - index - 1);i++)tmp = tmp->pPrev;
		}
		element<T1>* NEW = new element<T1>(data);
		NEW->pNext = tmp;
		NEW->pPrev = tmp->pPrev;
		tmp->pPrev->pNext = NEW;// Указательная головоломка для вставки нового элемента
		tmp->pPrev = NEW;
		size++;
	}
	// Removing Methods:
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
		if (index == 0)return pop_front();
		if (index == size - 1)return pop_back();
		if (index >= size)return;
		element<T1>* tmp;
		if (index < size / 2)
		{
			tmp = head;
			for (int i = 0; i < index;i++)tmp = tmp->pNext;
		}
		else
		{
			tmp = tail;
			for (int i = 0; i < (size - index - 1);i++)tmp = tmp->pPrev;
		}
		tmp->pPrev->pNext = tmp->pNext;
		tmp->pNext->pPrev = tmp->pPrev;
		delete tmp;
		size--;
	}
	// other Methods:
	void print()
	{
		for (element<T1>* tmp = head;tmp;tmp = tmp->pNext)
		{
			cout << tmp->pPrev << tab << tmp << tab << tmp->data << tab << tmp->pNext << endl;
			cout << "Количество Элементов списка: " << size << endl;
		}
	}
	/*void reverse_print()
	{
		for (element<T1>* tmp = tail;tmp;tmp = tmp->pPrev)
		{
			cout << tmp->pPrev << tab << tmp << tab << tmp->data << tab << tmp->pNext << endl;
			cout << "Количество Элементов списка: " << size << endl;
		}
	}*/
	friend class element<T1>;
};

int main()
{
	setlocale(LC_ALL, "Ru");
	int size_of_list;
	cout << "Введите размер списка: ";cin >> size_of_list;
	List<int> list;
	for (int i = 0; i < size_of_list;i++)
	{
		list.push_back(rand() % 234);
		//list.push_front(rand() % 24);
	}
	list.print();
	//list.reverse_print();
	//end of main function:D
	return 0;
}