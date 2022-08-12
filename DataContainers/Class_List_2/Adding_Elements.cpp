#include"List_declaration.h"

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
