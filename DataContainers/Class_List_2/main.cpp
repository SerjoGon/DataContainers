#include<iostream>

using std::cout;
using std::cin;
using std::endl;

#define DELIMETER "\n======================================\n"
#define tab "\t"
template <typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List;
	}*Head, * Tail;
	//Element* Head;
	//Element* Tail;
	unsigned int size;
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr);
		~ConstBaseIterator();
		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;
		const T& operator*()const;
	};
public:
	class ConstIterator:public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp);
		~ConstIterator();
		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};

	class ConstReverseIterator:public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp);
		~ConstReverseIterator();
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};
	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr):ConstIterator(Temp){}
		~Iterator(){}
		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr):ConstReverseIterator(Temp){}
		~ReverseIterator(){}
		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};
	//OperatorsMethods:
	ConstIterator cbegin()const;
	ConstIterator cend()const;
	ConstReverseIterator crbegin()const;
	ConstReverseIterator crend()const;
	Iterator begin();
	Iterator end();
	ReverseIterator rbegin();
	ReverseIterator rend();
	//Constructors:
	List();
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	List(List<T>&& other)noexcept;
	~List();
	//					Operators:
	List<T>& operator=(const List<T>& other);
	List<T>& operator=(List<T>&& other)noexcept;
	//					Adding Elements:
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int index);
	//					Removing Elements:
	void pop_front();
	void pop_back();
	void erase(int index);
	//					Methods:
	void print()const;
	void reverse_print()const;
};

//Element of List:
template<typename T>List<T>::Element::Element(T Data, Element* pNext, Element* pPrev)
	:Data(Data), pNext(pNext), pPrev(pPrev)
{
	//cout << "EConstructor:\t" << this << endl;
}
template<typename T>List<T>::Element::~Element()
{
	//cout << "EDestructor:\t" << this << endl;
}

//ConstBaseIterator:
template<typename T>List<T>::ConstBaseIterator::ConstBaseIterator(Element* Temp) : Temp(Temp)
{
	//cout << "CBItConstructor:\t" << this << endl;
}
template<typename T>List<T>::ConstBaseIterator::~ConstBaseIterator()
{
	//cout << "CBItDestructor:\t" << this << endl;
}
template<typename T>bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T>bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}
template<typename T>const T& List<T>::ConstBaseIterator::operator*()const
{
	return Temp->Data;
}

//ConstIterator:
template<typename T>List<T>::ConstIterator::ConstIterator(Element* Temp) :ConstBaseIterator(Temp)
{
	//cout << "CItConstructor:\t" << this << endl;
}
template<typename T>List<T>::ConstIterator::~ConstIterator()
{
	//cout << "CItDestructor:\t" << this << endl;
}
template<typename T>typename List<T>::ConstIterator::ConstIterator& List<T>::ConstIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstIterator::ConstIterator List<T>::ConstIterator::operator++(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T>typename List<T>::ConstIterator::ConstIterator& List<T>::ConstIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstIterator::ConstIterator List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
//ConstReverseIterator:
template<typename T> List<T>::ConstReverseIterator::ConstReverseIterator(Element* Temp) :ConstBaseIterator(Temp)
{
	cout << "CRITConstructor:\t" << this << endl;
}
template<typename T> List<T>::ConstReverseIterator::~ConstReverseIterator()
{
	cout << "CRITDestructor:\t" << this << endl;
}
template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}

template<typename T>typename List<T>::ConstIterator List<T>::cbegin()const
{
	return Head;
}
template<typename T>typename List<T>::ConstIterator List<T>::cend()const
{
	return nullptr;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::crbegin()const
{
	return Tail;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::crend()const
{
	return nullptr;
}
//Iterators methods
template<typename T>typename List<T>::Iterator List<T>::begin() { return Head; }
template<typename T>typename List<T>::Iterator List<T>::end() { return nullptr; }
template<typename T>typename List<T>::ReverseIterator List<T>::rbegin() { return Tail; }
template<typename T>typename List<T>::ReverseIterator List<T>::rend() { return nullptr; }
// Constructors::
template<typename T>List<T>::List()
{
	Head = Tail = nullptr;//Когда список пуст, его Голова и Хвост указывают на 0
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T>List<T>::List(const std::initializer_list<T>& il):List()
{
	for (T const* it = il.begin();it != il.end();++it)push_back(*it);
	//for (int i : il)push_back(i);// SuperMaster FOR! цикл не для слабаков)))
}
template<typename T>List<T>::List(const List<T>& other) : List()
{
	for (ConstIterator it = other.cbegin();it != other.cend();++it)push_back(*it);
}
template<typename T>List<T>::List(List<T>&& other)noexcept :List()
{
	*this = std::move(other);	//Функция move принудительно вызывает MoveAssignment если он есть.
	cout << "LMoveConstructor:\t" << this << endl;
}
template<typename T>List<T>::~List()
{
	//while (Head)pop_front();
	while (Tail)pop_back();
	cout << "LDestructor:\t" << this << endl;
}
//Operators
template<typename T>List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (List<T>::ConstIterator it = other.cbegin(); it != other.cend(); ++it)
		push_back(*it);
	cout << "LCopyAssignment:\t" << this << endl;
	return *this;
}
template<typename T>List<T>& List<T>::operator=(List<T>&& other)noexcept
{
	if (this == &other)return *this;
	while (Head)pop_front();
	this->Head = other.Head;
	this->Tail = other.Tail;
	this->size = other.size;
	other.Head = nullptr;
	other.Tail = nullptr;
	other.size = 0;
	cout << "LMoveAssignment:\t" << this << endl;
	return *this;
}
template<typename T>void List<T>::push_front(T Data)
{
	/*Element* New = new Element(Data);
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = New;
	}
	else
	{
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;
	}*/
	if (Head == nullptr && Tail == nullptr)
		Head = Tail = new Element(Data);
	else
		Head = Head->pPrev = new Element(Data, Head);
	size++;
}
template<typename T>void List<T>::push_back(T Data)
{
	/*Element* New = new Element(Data);
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = New;
	}
	else
	{
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;
	}*/

	if (Head == nullptr && Tail == nullptr)
		Head = Tail = new Element(Data);
	else
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	size++;
}
template<typename T>void List<T>::insert(T Data, int index)
{
	if (index > size)throw std::out_of_range("Eror: Out of range exception in Insert function!"); //throw std::exception("Error: Out of range!");
	if (index == 0) return push_back(Data);
	if (index == size)return push_back(Data);
	Element* Temp;
	if (index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < index;i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < (size - index - 1);i++) Temp = Temp->pPrev;
	}
	/*Element* NEW = new Element(Data);
	NEW->pNext = Temp;
	NEW->pPrev = Temp->pPrev;
	Temp->pPrev->pNext = NEW;
	Temp->pPrev = NEW;*/
	Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
	size++;
}
//					Removing Elements:
template<typename T>void List<T>::pop_front()
{
	if (Head == nullptr && Tail == nullptr)return;
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
	}
	else
	{
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
	}
	size--;
}
template<typename T>void List<T>::pop_back()
{
	if (Head == Tail)return pop_front();
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}
template<typename T>void List<T>::erase(int index)
{
	if (index > size)throw std::out_of_range("Error: Out of range exception in Erase function!");
	if (index == 0)return pop_front();
	if (index == size - 1)return pop_back();
	Element* Temp;
	if (index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < (size - index - 1); i++) Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - index - 1;i++) Temp = Temp->pPrev;
	}
	Temp->pPrev->pNext = Temp->pNext;
	Temp->pNext->pPrev = Temp->pPrev;
	delete Temp;
	size--;
}
//					Methods:
template<typename T>void List<T>::print()const
{
	cout << "Head: " << Head << endl;
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов " << size << endl;
}
template<typename T>void List<T>::reverse_print()const
{
	cout << "Tail: " << Tail << endl;
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов " << size << endl;
}

template<typename T>List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> cat = left;
	for (typename List<T>::ConstIterator it = right.cbegin();it != right.cend();++it)
	{
		cat.push_back(*it);

	}
	return cat;
}

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

	return 0;
}

