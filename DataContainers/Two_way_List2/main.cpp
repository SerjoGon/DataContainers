#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

template<typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
			Data(Data), pNext(pNext), pPrev(pPrev) {}
		~Element() {}
		friend class List;
	}*Head, *Tail;
	unsigned int size;
	class CBIterator
	{
	protected:
		Element* Temp;
	public:
		CBIterator(Element* Temp = nullptr) :Temp(Temp){}
		~CBIterator(){}
		bool operator==(const CBIterator& other)const{return this->Temp == other.Temp;}
		bool operator!=(const CBIterator& other)const{return this->Temp != other.Temp;}
		const T& operator*()const { return Temp->Data; }
	};
public:
	class CIterator :public CBIterator
	{
	public:
		CIterator(Element*Temp):CBIterator(Temp) {}
		~CIterator(){}
		CIterator& operator++()
		{
			CBIterator::Temp = CBIterator::Temp->pNext;
			return *this;
		}
		CIterator operator++(int)
		{
			CIterator old = *this;
			CBIterator::Temp = CBIterator::Temp->pNext;
			return old;
		}
		CIterator& operator--()
		{
			CBIterator::Temp = CBIterator::Temp->pPrev;
			return *this;
		}
		CIterator operator--(int)
		{
			CIterator old = *this;
			CBIterator::Temp = CBIterator::Temp->pPrev;
			return old;
		}
	};
	class CReverseIterator :public CBIterator
	{
	public:
		CReverseIterator(ELement* Temp):CBIterator(Temp){}
		~CReverseIterator(){}
		CReverseIterator& operator++()
		{
			CBIterator::Temp = CBIterator::Temp->pPrev;
			return *this;
		}
		CReverseIterator operator++(int)
		{
			CReverseIterator old = *this;
			CBIterator::Temp = CBIterator::Temp->pPrev;
			return old;
		}
		CReverseIterator& operator--()
		{
			CBIterator::Temp = CBIterator::Temp->pNext;
			return *this;
		}
		CReverseIterator operator--(int)
		{
			CReverseIterator old = *this;
			CBIterator::Temp = CBIterator::Temp->pNext;
			return old;
		}
	};
	class Iterator :public CBIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :CBIterator(Temp){}
		~Iterator(){}
		T& operator*() { return CBIterator::Temp->Data; }
	};
	class ReverseIterator :public CBIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) :CBIterator(Temp) {}
		~ReverseIterator() {}
		T& operator*() { return CBIterator::Temp->Data; }
	};
};

int main()
{
	setlocale(LC_ALL, "Ru");
	
	return 0;
}