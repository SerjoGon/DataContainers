#include<iostream>

using std::cin; using std::cout; using std::endl;

template<typename T1>
class List;
template<typename T2>
class Iterator;
template<typename T3>
class ReverseIterator;
// ниже описан шаблонный класс element:
//Задумка реализовать двусвязный список для хранения любых данных
// из за сложности класса List возникают некоторые неудобства с обьявлением элемента в других классах

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
	~element(){ cout << "ElemDestruct:\t" << this << endl; }
	friend class List<element>;
	friend class Iterator<element>;
	friend class ReverseIterator<element>;
};

int element<int>::count = 0; // уникальная запись шаблонного класса:D

template<typename T2>
class Iterator // Итератор для головы списка
{
	//возможны конфликты при использовании других типов данных с таким итератором
	T2* tmp;
public:
	Iterator(T2* tmp) :tmp(tmp) { cout << "Itconstr:\t" << this << endl; }
	~Iterator(){ cout << "ItDestr:\t" << this << endl; }
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

template<typename T1>
class List
{
	T1* head;
	T1* tail;
	uint64_t size;
};

int main()
{
	setlocale(LC_ALL, "Ru");

	//end of main function:D
	return 0;
}