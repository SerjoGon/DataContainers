#include<iostream>

using std::cout;
using std::cin;
using std::endl;

#define DELIMETER "\n======================================\n"
#define tab "\t"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
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
		ConstBaseIterator(Element* Temp = nullptr) : Temp(Temp)
		{
			cout << "ConstBaseIteratorConstructor:\t" << this << endl;
		}
		~ConstBaseIterator()
		{
			cout << "CBItDestructor:\t" << this << endl;
		}
		bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		const int& operator*()const
		{
			return Temp->Data;
		}
	};
public:
	class ConstIterator:public ConstBaseIterator
	{
		
	public:
		ConstIterator(Element* Temp) :ConstBaseIterator(Temp)
		{
#ifdef DEBUG

			cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ConstIterator()
		{
			cout << "ItDestructor:\t" << this << endl;
		}
		ConstIterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}

	};

	class ConstReverseIterator:public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp) :ConstBaseIterator(Temp)
		{
			cout << "RITConstructor:\t" << this << endl;
		}
		~ConstReverseIterator()
		{
			cout << "RITDestructor:\t" << this << endl;
		}
		ConstReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		
	};
	class Iterator:public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr): ConstIterator(Temp){}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	class RevereseIterator : public ConstReverseIterator
	{
	public:
		RevereseIterator(Element* Temp = nullptr): ConstReverseIterator(Temp){}
		int& operator*()
		{
			return Temp->Data;
		}
	};

	ConstIterator cbegin()
	{
		return Head;
	}
	ConstIterator cend()
	{
		return nullptr;
	}
	ConstReverseIterator crbegin()
	{
		return Tail;
	}
	ConstReverseIterator crend()
	{
		return nullptr;
	}
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	List()
	{
		Head = Tail = nullptr;//Когда список пуст, его Голова и Хвост указывают на 0
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		//for (int const* it = il.cbegin();it != il.cend();++it)push_back(*it);
		for (int i : il)push_back(i);// SuperMaster FOR! цикл не для слабаков)))
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestrcutor:\t" << this << endl;
	}

	//					Adding Elements:
	void push_front(int Data)
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
	void push_back(int Data)
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
	void insert(int Data, int index)
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
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp,Temp->pPrev);
		size++;
	}

	//					Removing Elements:
	void pop_front()
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
	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	void erase(int index)
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
	void print()const
	{
		cout << "Head: " << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов " << size << endl;
	}
	void reverse_print()const
	{
		cout << "Tail: " << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов " << size << endl;
	}
};

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

	List list = { 3,5,8,13,21,34 };
	list.print();
	for (int i : list)cout << i << tab;cout << endl;
	List::ConstReverseIterator rend = list.crend();
	for (List::ConstReverseIterator rit = list.crbegin();rit != rend;++rit)
	{
		cout << *rit << tab;
	}
	cout << endl;

	return 0;
}