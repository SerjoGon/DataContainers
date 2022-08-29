#include<iostream>
#include<set>
#include<string>
#include<map>
#include<list>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
//#define STL_SET
//#define STL_MAP
int main()
{
	setlocale(LC_ALL, "Ru");
	typedef int type;
#ifdef STL_SET


	//std::set<type> i_set = { 50,25,75,16,16,16,16,32,64,88,22 };
	std::multiset<type> i_set = { 50,25,75,16,16,16,16,32,64,88,22 };
	for (int i : i_set)cout << i << tab; cout << endl;
	for (std::set<type>::reverse_iterator it = i_set.rbegin(); it != i_set.rend();++it)
		cout << *it << tab;
	cout<< endl;

	std::set<std::string> s_set = { "Хорошо", "Живет", "на" ," свете", "Винни-Пух!" };
	for (std::string i : s_set)cout << i << tab; cout << endl;
#endif // STL_SET
#ifdef STL_MAP


	std::multimap<type, std::string> week =
	{
		std::pair<type, std::string>(0,"Sunday"),
		std::pair<type, std::string>(1,"Monday"),
		{2,"Tuesday"},
		{3, "Wednsday"},
		{4,"Thursday"},
		{5,"Friday"},
		{6,"Saturday"},
		{6,"Saturday"},
		{6,"Saturday"},
		{7,"Sadday"}
	};
	for (std::map<type, std::string>::iterator it = week.begin();it != week.end();++it)
	{
		cout << it->first << tab << it->second << endl;
	}
#endif // STL_MAP
	std::map<std::string, std::list<std::string>> dictionary =
	{
		std::pair<std::string,std::list<std::string>>("clutter",{"беспорядок", "хаос"}),
		{"space", {"Пространство","пробел","космос"}},
		{"plural",{"множественное число",}},
		{"worth",{"ценность","значение","значимость"}}
	};
	/*for (std::map<std::string, std::list<std::string>>::iterator it = dictionary.begin();it != dictionary.end();++it)
	{
		cout << it->first << ":\t";
		for (std::list<std::string>::iterator it2 = it->second.begin();it2 != it->second.end();++it2)
		{
			cout << *it2 << ", ";
		}
		cout << "; \n";
	}*/
	for (std::pair<std::string, std::list<std::string>> i : dictionary)
	{
		cout << i.first << ":\t";
		for (std::string j : i.second)
		{
			cout << j << ", ";
		}
		cout << ";\n";
	}
	return 0;
}