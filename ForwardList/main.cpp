#include<iostream>
#include<ctime>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n----------------------------\n"

class Element
{
	int Data;
	Element* pNext;
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

	}
	friend class ForwardList;
	friend class Iterator;
	friend class ConstIterator;
};
int Element::count = 0;

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}
	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	int& operator*()
	{
		return Temp->Data;
	}
};
class ConstIterator
{
	Element* Temp;
public:
	ConstIterator(Element* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~ConstIterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}
	ConstIterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	ConstIterator operator++(int)
	{
		ConstIterator old = *this;
		Temp = Temp->pNext;
		return old;
	}
	bool operator==(const ConstIterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const ConstIterator& other)const
	{
		return this->Temp != other.Temp;
	}
	int operator*()const
	{
		return Temp->Data;
	}
	
};
class ForwardList
{
	Element* Head;
	int size;
public:
	int get_size()const
	{
		return size;
	}
	ConstIterator begin()const
	{
		return Head;
	}
	ConstIterator end()const
	{
		return nullptr;
	}
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	explicit ForwardList(int size) :ForwardList()
	{
		while (size--)push_front(0);
		cout << "1argConstructor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<int> il) : ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other;
		cout << "LCopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& other):ForwardList()
	{
		/*this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;*/
		*this = std::move(other);
		cout << "LMoveConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		reverse();
		cout << "LCopyAssignment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "LMoveAssignment:\t" << endl;
		return *this;
	}
	int& operator[](int Index)
	{
		Element* Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}
	ForwardList operator+(const ForwardList& other) const
	{
		ForwardList result;

		for (Element* Temp = this->Head; Temp; Temp = Temp->pNext)
			result.push_back(Temp->Data);

		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			result.push_back(Temp->Data);

		return result;
		/*ForwardList result = left;
		for (Iterator it = right.begin(); it != right.end(); ++it)
		{
			*it *= 100;
			result.push_back(*it);
		}
		return result;*/
	}
	void push_front(int Data)
	{
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;*/
		Head = new Element(Data, Head);

		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext) Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
		size++;
	}

	void insert(int Data, int Index)
	{
		if (Index == 0)return push_front(Data);
		//Element* New = new Element(Data); 

		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			if (Temp->pNext == nullptr)break;
			Temp = Temp->pNext;
		}
		//New->pNext = Temp->pNext;
		//Temp->pNext = New;
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}

	void pop_front()
	{
		Element* Erased = Head;
		Head = Head->pNext;
		delete Erased;
		size--;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	// ////////

	void erase(int Index)
	{
		if (Head == nullptr)
		{
			cout << "Список пуст" << endl;
			return;
		}

		if (Index < 0 || Index >= size)
		{
			cout << "Неверный индекс" << endl;
			return;
		}

		if (Index == 0)
		{
			pop_front();
			return;
		}

		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			Temp = Temp->pNext;
		}

		Element* Erased = Temp->pNext;
		Temp->pNext = Erased->pNext;
		delete Erased;
		size--;
	}

	/// /////////////

	void reverse()
	{
		ForwardList reverse;
		while (Head)
		{
			reverse.push_front(Head->Data);
			pop_front();
		}
		this->Head = reverse.Head;
		reverse.Head = nullptr;
	}

	void print()const
	{
		/*Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}*/
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов : " << Element::count << endl;
	}
};

//#define BASE_CHECK
//#define SIZE_CHECK
//#define HOME_WORK_1
//#define ERASE_CHECK
//#define COPY_SEMANTIC_CHECK
//#define OPERATORPLUS_CHECK
//#define PERFORMANCE_CHECK
//#define RANGE_BASED_FOR_ARRAY
//#define RANGE_BASED_FOR_LIST

void main()
{
	setlocale(LC_ALL, "");
	//cout << "Hello ForwardList" << endl;

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	//list.push_back(123);
	//list.pop_back();
	int Index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> Index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, Index);
	list.print();
#endif // BASE_CHECK

#ifdef SIZE_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);

	list1.print();
	list2.print();
#endif // SIZE_CHECK

#ifdef HOME_WORK_1
	ForwardList list(5);
	list.print();

	for (int i = 0; i < list.get_size(); i++)
	{
		list[i] = rand() % 100;
	}
	for (int i = 0; i < list.get_size(); i++)
	{
		cout << list[i] << tab;
	}
	cout << endl;
#endif // HOME_WORK_1

#ifdef ERASE_CHECK
	ForwardList list1;
	list1.push_back(1);
	list1.push_back(2);
	list1.push_back(3);

	list1.print();

	list1.erase(1);

	list1.print();
#endif // ERASE_CHECK

#ifdef COPY_SEMANTIC_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1 = list1;
	list1.print();

	ForwardList list2;
	list2 = list1;
	list2.print();
#endif // COPY_SEMANTIC_CHECK

#ifdef OPERATORPLUS_CHECK

	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	ForwardList list2;
	list2.push_back(4);
	list2.push_back(5);
	list2.push_back(6);
	cout << delimiter << endl;
	ForwardList list3 = list1 + list2;
	cout << delimiter << endl;
	list3.print();
#endif // OPERATORPLUS_CHECK

#ifdef PERFORMANCE_CHECK

	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list1;
	clock_t start = clock();
	for (int i = 0; i < n; i++)
	{
		list1.push_front(rand() % 100);
	}
	clock_t end = clock();
	//list1.print();
	cout << delimiter << endl;
	cout << "list1 заполнен за " << double(end - start) / CLOCKS_PER_SEC << " секунд" << endl;
	cout << delimiter << endl;
	start = clock();
	system("PAUSE");
	ForwardList list2 = list1;
	end = clock();
	cout << delimiter << endl;
	cout << "list2 скопирован за " << double(end - start) / CLOCKS_PER_SEC << " секунд" << endl;
	cout << delimiter << endl;
	//list2.print();
#endif // PERFORMANCE_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST
	ForwardList list = { 3, 5, 8, 13, 21 };
	//list.print();
	for (int i : list)
	{
		cout << i << endl;
	}
	cout << endl;

	for (Iterator it = list.begin(); it != list.end(); it++)
	{
		cout << *it << endl;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_LIST

	ForwardList list1 = { 3, 5, 8, 13, 21 };
	ForwardList list2 = { 34, 55, 89};
	ForwardList list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
}