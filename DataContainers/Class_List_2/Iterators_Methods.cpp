#include"List_declaration.h"

//Iterators methods
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
template<typename T>typename List<T>::Iterator List<T>::begin() { return Head; }
template<typename T>typename List<T>::Iterator List<T>::end() { return nullptr; }
template<typename T>typename List<T>::ReverseIterator List<T>::rbegin() { return Tail; }
template<typename T>typename List<T>::ReverseIterator List<T>::rend() { return nullptr; }
