#include"List_declaration.h"
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
