#include"List.h"
#include"List.cpp"


//#define BASE_CHECK
//#define ITERATORS_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	//list.reverse_print();

	int index;
	int value;
	//cout << "Введите индекс добавляемого элемента: "; cin >> index;
	//cout << "Введите значение добавляемого элемента: "; cin >> value;
	//list.insert(value, index);

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);

	list.print();
#endif // BASE_CHECK

#ifdef ITERATORS_CHECK
	List<int> list = { 3, 5, 8, 13, 21 };
	for (int i : list)cout << i << tab; cout << endl;
	for (List<int>::Iterator it = list.begin(); it != list.end(); it++)
	{
		*it *= 100;
		cout << *it << tab;
	}
	cout << endl;

	for (List<int>::ConstReverseIterator it = list.rbegin(); it != list.rend(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // ITERATORS_CHECK

	List<int> i_list = { 3, 5, 8, 13, 21 };
	for (int i : i_list)cout << i << tab; cout << endl;

	for (List<int>::ReverseIterator it = i_list.rbegin(); it != i_list.rend(); ++it)
		cout << *it << tab;
	cout << endl;

	List<double> doublelist = {12.5, 123, 333.1232};
	//doublelist.print();
	for (double i : doublelist)cout << i << tab; cout << endl;
	for (List<double>::ReverseIterator it = doublelist.rbegin(); it != doublelist.rend(); ++it)
		cout << *it << tab;
	cout << endl;

	List<char> charlist = { 'a', 'b', 'c', 'd', 'e' };

	List<const char*> charpointerlist = { "Hello", "World!" };
	for (const char* i : charpointerlist)cout << i << tab; cout << endl;

	List <std::string> s_list = { "Хорошо", "живёт", "на", "свете", "Винни", "Пух" };
	for (std::string i : s_list)cout << i << tab; cout << endl;
	for (List<std::string>::ReverseIterator it = s_list.rbegin(); it != s_list.rend(); ++it)
		cout << *it << tab;
	cout << endl;
}