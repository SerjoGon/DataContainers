#include<iostream>
using std::cout;
using std::cin;
using std::endl;
#define DEBUG
#define tab  "\t"
#define DELIMETER "\n=================================\n"

class Tree
{
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
	~Tree()
	{
		cout << "TDestr:\t" << this << endl;
	}
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
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
};

int main()
{
	setlocale(LC_ALL, "ru");
	int n; 
	cout << "¬ведите размер дерева: ";cin >> n;
	Tree tree;
	for (int i = 0; i < n;i++)
	{
		tree.insert(rand()%100, tree.getRoot());
	}
	tree.print(tree.getRoot());
	return 0;
}