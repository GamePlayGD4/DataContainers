#include<iostream>
using namespace std;

class Element
{
	int Data;
	Element* pNext;
	Element* pPrev;
public:
	Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
	{
		cout << "EConstructor" << endl;
	}
	~Element()
	{
		cout << "EDestructor" << endl;
	}
};

class List
{
	int size;
	Element* Head;
	Element* Tail;
public:
	int get_size()const
	{
		return size;
	}
	List()
	{
		size = 0;
		Head = nullptr;
		Tail = nullptr;
		cout << "LConstructor" << endl;
	}
	~List()
	{
		cout << "LDestructor" << endl;
	}
};


void main()
{
	setlocale(LC_ALL, "");
	List list1 = {};
}