#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimiter "\n----------------------\n"

//////////////////////////////////////////////////////////////////
/////////////////////// Class declaration /////////////////////////



template<typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
			Data(Data), pNext(pNext), pPrev(pPrev)
		{
#ifdef DEBUG
			cout << "EConstructor\t" << this << endl;
#endif // DEBUG

		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor\t" << this << endl;
#endif // DEBUG

		}
		friend class List;
	}*Head, * Tail;
	size_t size;

	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) : Temp(Temp) {}
		~ConstBaseIterator() {}
		bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		T operator*()const
		{
			return Temp->Data;
		}
	};
public:

	class ConstIterator: public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) : ConstBaseIterator(Temp) {}
		~ConstIterator() {}
		
		ConstIterator& operator++()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
	};

	class ConstReverseIterator:public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp) {}
		~ConstReverseIterator() {}

		ConstReverseIterator& operator++()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
	};

	int get_size()const
	{
		return size;
	}

	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) : ConstIterator(Temp) {}
		~Iterator() {}
		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};

	class ReverseIterator : public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp) : ConstReverseIterator(Temp) {}
		~ReverseIterator() {}
		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};
	ConstIterator cbegin()const;
	ConstIterator cend()const;
	ConstReverseIterator crbegin()const;
	ConstReverseIterator crend()const;
	Iterator begin();
	Iterator end();
	ReverseIterator rbegin();
	ReverseIterator rend();

	List();
	List(const std::initializer_list<T>& il);
	~List();

	// adding elements
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int Index);

	void pop_front();
	void pop_back();

	// removing elements
	void erase(int index);
	
	// methods

	void print()const;
	void reverse_print()const;
	
	
};


//////////////////////Class declaration end////////////////////////
//////////////////////////////////////////////////////////////////

///----------------------------------------------------------///

//////////////////////////////////////////////////////////////////
/////////////////////// Class definition /////////////////////////

template<typename T>typename
List<T>::ConstIterator List<T>::cbegin()const
{
	return Head;
}
template<typename T>typename
List<T>::ConstIterator List<T>::cend()const
{
	return nullptr;
}
template<typename T>typename
List<T>::ConstReverseIterator List<T>::crbegin()const
{
	return Tail;
}
template<typename T>typename
List<T>::ConstReverseIterator List<T>::crend()const
{
	return nullptr;
}
template<typename T>typename
List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T>typename
List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template<typename T>typename
List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template<typename T>typename
List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}

template<typename T>
List<T>::List()
{
	size = 0;
	Head = nullptr;
	Tail = nullptr;
	cout << "LConstructor" << this << endl;
}
template<typename T>
List<T>::List(const std::initializer_list<T>& il) :List()
{
	for (T const* it = il.begin(); it != il.end(); ++it)
		push_back(*it);
}
template<typename T>
List<T>::~List()
{
	while (Head)pop_front();
	cout << "LDestructor" << this << endl;
}

// adding elements
template<typename T>
void List<T>::push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr)
		Head = Tail = new Element(Data);
	else
		Head = Head->pPrev = new Element(Data, Head);
	size++;
}
template<typename T>
void List<T>::push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr)
		Head = Tail = new Element(Data);
	else
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	size++;
}
template<typename T>
void List<T>::insert(T Data, int Index)
{
	if (Index > size)return;
	if (Index == size - 1)return push_back(Data);
	if (Index == 0)return push_front(Data);
	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
	}
	Temp->pPrev->pNext = Temp->pNext->pPrev = new Element(Data, Temp->pNext, Temp->pPrev);
	size++;
}

template<typename T>
void List<T>::pop_front()
{
	if (Head == nullptr && Tail == nullptr)return;
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
	}
	else
	{
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
	}
	size--;
}
template<typename T>
void List<T>::pop_back()
{
	if (Head == nullptr && Tail == nullptr)return;
	if (Head == Tail)
	{
		delete Tail;
		Head = Tail = nullptr;
	}
	else
	{
		Tail = Tail->pNext;
		delete Head->pNext;
		Tail->pNext = nullptr;
	}
	size--;
}

// removing elements
template<typename T>
void List<T>::erase(int index)
{
	if (index >= size)return;
	if (index == size - 1)return pop_back();
	if (index == 0)return pop_front();
	Element* Temp;
	if (index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
	}
	Temp->pPrev->pNext = Temp->pNext;
	Temp->pNext->pPrev = Temp->pPrev;
	delete Temp;
	size--;
}

// methods

template<typename T>
void List<T>::print()const
{
	cout << "Head:\t" << Head << endl;
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Tail:\t" << Tail << endl;
	cout << "Количество элементов в списке: " << size << endl;
}
template<typename T>
void List<T>::reverse_print()const
{
	cout << "Tail:\t" << Tail << endl;
	for (Element* Temp = Tail; Temp; Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Head:\t" << Tail << endl;
}


//////////////////////Class definition end////////////////////////
//////////////////////////////////////////////////////////////////


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