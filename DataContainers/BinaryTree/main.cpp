#include<iostream>
using std::cout;
using std::cin;
using std::endl;
//#define DEBUG
#define tab  "\t"
#define DELIMETER "\n=================================\n"

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :
			Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstr:\t" << this << endl;
#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestr:\t" << this << endl;
#endif // DEBUG
		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree() :Root(nullptr)
	{
		cout << "TConstr:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			insert(*it, Root);
		}
	}
	~Tree()
	{
		clear(Root);
		//Root = nullptr;
		cout << "TDestr:\t" << this << endl;
	}
	void insert(int Data)
	{
		insert(Data, Root);
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}
	int Count()const
	{
		return Count(Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int Sum()const
	{
		return Sum(Root);
	}
	int depth()const
	{
		return depth(Root);
	}
	void clear()
	{
		return clear(Root);
		//Root = nullptr;
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
private:

	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (Count(Root->pLeft) > Count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = maxValue(Root->pRight);
					erase(maxValue(Root->pRight), Root->pRight);
				}
			}
		}
	}
	int minValue(Element* Root)const
	{
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
		/*if (Root->pLeft == nullptr) return Root->Data;
		else return minValue(Root->pLeft);*/
		//while (Root->pLeft) Root = Root->pLeft;
	}
	int maxValue(Element* Root)const
	{
		return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
		/*if (Root->pRight == nullptr)return Root->Data;
		else return maxValue(Root->pRight);*/
		//while (Root->pRight) Root = Root->pRight;
	}
	int Count(Element* Root)const
	{
		return Root == nullptr ? 0 : Count(Root->pLeft) + Count(Root->pRight) + 1;
		/*if (Root == nullptr)return 0;
		else return Count(Root->pLeft) + Count(Root->pRight)+ 1;*/
	}
	int Sum(Element* Root)const
	{
		return Root == nullptr ? 0 : Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;
	}
	int depth(Element* Root)const
	{
		if (Root == nullptr)return 0;
		else return
			depth(Root->pLeft) + 1 > depth(Root->pRight) + 1?
		depth(Root->pLeft) + 1:
		depth(Root->pRight) + 1;
	}
	void clear(Element*& Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
		Root = nullptr;
	}
	//int AVG(Element* Root);
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
};

class UniqueTree :public Tree
{

	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		if(Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

//#define BASE_CHECK

int main()
{
	setlocale(LC_ALL, "ru");
#ifdef BASE_CHECK


	int n; 
	cout << "Введите размер дерева: ";cin >> n;
	
	Tree tree;
	for (int i = 0; i < n;i++)
	{
		tree.insert(rand()%100);
	}
	tree.print();cout << endl;
	cout <<"Кол-во элементов в дереве:" << tree.Count() << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue()<<endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue()<<endl;
	cout << "Сумма элементов дерева: " << tree.Sum() << endl;
	UniqueTree utree;
	for (int i = 0; i < n;i++)
	{
		utree.insert(rand() % 100);
	}
	utree.print();cout << endl;
	cout << "Кол-во элементов в дереве:" << utree.Count() << endl;
	cout << "Минимальное значение в дереве: " << utree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << utree.maxValue() << endl;
	cout << "Сумма элементов дерева: " << utree.Sum() << endl;
	cout << "Глубина дерева: " << utree.depth()<< endl;
	utree.print();
#endif // BASE_CHECK
	Tree tree3 = { 50, 25, 75, 16, 32, 64, 85, 48, 49 };
	tree3.print();
	int value;
	cout << "Введите удаляемое значение: ";cin >> value;
	tree3.erase(value);
	tree3.print();
	return 0;
}