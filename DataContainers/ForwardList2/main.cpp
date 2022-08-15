#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimeter "\n=====================================\n"

template<typename T>
class Forwardlist
{
protected:
	class Element
	{
		T Data;
		Element* pNext;
	public:
		Element(T Data, Element* pNext = nullptr) :Data(Data), pNext(pNext){}
		~Element() {}
		friend class Forwardlist;
	}*Head;
	unsigned int size;
	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp = nullptr) :Temp(Temp) {}
		~Iterator() {}
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
public:
	Iterator begin() { return Head; }
	Iterator end() { return nullptr; }
	Forwardlist(Element* Head = nullptr) :Head(Head)
	{
		size = 0;
	}
	Forwardlist( std::initializer_list<T>& il) :Forwardlist()
	{
		//cout << typeid(il.begin()).name() << endl;
		for (T const* it = il.begin();it != il.end;++it) push_back(*it);
	}

	Forwardlist(const Forwardlist& other):Forwardlist()
	{
		*this = other;
	}
	Forwardlist(Forwardlist&& other):Forwardlist()
	{
		*this = std::move(other);
	}
	~Forwardlist() { while(Head)pop_front(); }
	Forwardlist& operator=(const Forwardlist& other)
	{
		if (this == other)return *this;
		clear();
		Element* Temp = other.Head;
		for (Element* Temp = other.Head; Temp;Temp = Temp->pNext)push_back(Temp->Data);
		return *this;
	}
	Forwardlist& operator=(Forwardlist&& other)
	{
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		return *this;
	}
	// Adding Elements
	void push_front(T Data)
	{
		Head = new Element(Data, Head);
		size++;
	}
	void push_back(T Data)
	{
		if (Head == nullptr) return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext != nullptr)Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(T Data, int index)
	{
		if (index == 0)return push_front(Data);
		if (index > size)return;
		if (index == size)return push_back(Data);
		else
		{
			Element* previus = Head;
			for (int i = 0;i < index - 1;++i)previus = previus->pNext;
			previus->pNext = new Element(Data, previus->pNext);
		}
		size++;
	}
	// Removing Elements
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
		if (index == 0)return pop_front();
		else
		{
			Element* previus = this->Head;
			for (int i = 0;i < index - 1;++i)previus = previus->pNext;
			Element* erased = previus->pNext;
			previus->pNext = erased->pNext;
			delete erased;
		}
		size--;
	}
	void clear()
	{
		while (Head)pop_front();
	}
	//Methods
	void print()const
	{
		for (Element* Temp = Head;Temp;Temp = Temp->pNext)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов списка: " << size << endl;
		//cout << "Общее количество элементов: " << Element::count << endl;
	}
};
template<typename T> Forwardlist<T> operator+(const Forwardlist<T>& left,const Forwardlist<T>& right)
{
	Forwardlist<T> cat = left;
	for (typename Forwardlist<T>::Element* Temp = right.Head;Temp;Temp = Temp->pNext)cat.pop_back(Temp->Data);
	return cat;
}

int main()
{
	setlocale(LC_ALL, "ru");

	//Forwardlist<double> list{2.1, 3.1, 4.2, 5.3, 6.4, 7.6 };
	Forwardlist<int> list;
	for (int i = 0; i < 10;i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();

	return 0;
}