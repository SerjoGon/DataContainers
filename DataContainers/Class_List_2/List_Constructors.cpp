#include"List_declaration.h"
// Constructors::
template<typename T>List<T>::List()
{
	Head = Tail = nullptr;//����� ������ ����, ��� ������ � ����� ��������� �� 0
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T>List<T>::List(const std::initializer_list<T>& il) :List()
{
	for (T const* it = il.begin();it != il.end();++it)push_back(*it);
	//for (int i : il)push_back(i);// SuperMaster FOR! ���� �� ��� ��������)))
}
template<typename T>List<T>::List(const List<T>& other) : List()
{
	for (ConstIterator it = other.cbegin();it != other.cend();++it)push_back(*it);
}
template<typename T>List<T>::List(List<T>&& other)noexcept :List()
{
	*this = std::move(other);	//������� move ������������� �������� MoveAssignment ���� �� ����.
	cout << "LMoveConstructor:\t" << this << endl;
}
template<typename T>List<T>::~List()
{
	//while (Head)pop_front();
	while (Tail)pop_back();
	cout << "LDestructor:\t" << this << endl;
}
