#include"List_declaration.h"
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
