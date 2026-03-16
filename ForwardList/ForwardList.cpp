#include"ForwardList.h"

///-------------------------------------------------///

//////------------------------------------------------////
/////------------------ Class definition ----------///

//////------------------------------------------------////
/////------------------ Iterator methods ----------///

template<typename T>
Iterator<T>::Iterator(Element<T>* Temp) :Temp(Temp)
{
	cout << "ItConstructor:\t" << this << endl;
}
template<typename T>
Iterator<T>::~Iterator()
{
	cout << "ItDestructor:\t" << this << endl;
}
template<typename T>
Iterator<T>& Iterator<T>::operator++()
{
	Temp = Temp->pNext;
	return *this;
}
template<typename T>
Iterator<T> Iterator<T>::operator++(int)
{
	Iterator<T> old = *this;
	Temp = Temp->pNext;
	return old;
}
template<typename T>
bool Iterator<T>::operator==(const Iterator<T>& other)const
{
	return this->Temp == other.Temp;
}
template<typename T>
bool Iterator<T>::operator!=(const Iterator<T>& other)const
{
	return this->Temp != other.Temp;
}
template<typename T>
T& Iterator<T>::operator*()
{
	return Temp->Data;
}


//////-----------------Iterator methods end-------------////
/////---------------------------------------------------///



//////------------------------------------------------////
/////------------------ ConstIterator methods ----------///

template<typename T>
ConstIterator<T>::ConstIterator(Element<T>* Temp) :Temp(Temp)
{
	cout << "ItConstructor:\t" << this << endl;
}
template<typename T>
ConstIterator<T>::~ConstIterator()
{
	cout << "ItDestructor:\t" << this << endl;
}
template<typename T>
ConstIterator<T>& ConstIterator<T>::operator++()
{
	Temp = Temp->pNext;
	return *this;
}
template<typename T>
ConstIterator<T> ConstIterator<T>::operator++(int)
{
	ConstIterator<T> old = *this;
	Temp = Temp->pNext;
	return old;
}
template<typename T>
bool ConstIterator<T>::operator==(const ConstIterator<T>& other)const
{
	return this->Temp == other.Temp;
}
template<typename T>
bool ConstIterator<T>::operator!=(const ConstIterator<T>& other)const
{
	return this->Temp != other.Temp;
}
template<typename T>
T ConstIterator<T>::operator*()const
{
	return Temp->Data;
}


//////----------------- ConstIterator methods end--------------////
/////------------------------------------------------------///


//////------------------------------------------------////
/////------------------ ForwardList methods ----------///



template<typename T>
Element<T>* ForwardList<T>::get_head()const
{
	return Head;
}
template<typename T>
int ForwardList<T>::get_size()const
{
	return size;
}
template<typename T>
ConstIterator<T> ForwardList<T>::begin()const
{
	return Head;
}
template<typename T>
ConstIterator<T> ForwardList<T>::end()const
{
	return nullptr;
}
template<typename T>
Iterator<T> ForwardList<T>::begin()
{
	return Head;
}
template<typename T>
Iterator<T> ForwardList<T>::end()
{
	return nullptr;
}

template<typename T>ForwardList<T>::ForwardList()
{
	Head = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}

template<typename T>ForwardList<T>::ForwardList(int size) :ForwardList()
{
	while (size--)push_front(0);
	cout << "1argConstructor:\t" << this << endl;
}

template<typename T>
ForwardList<T>::ForwardList(const std::initializer_list<T>& il) : ForwardList()
{
	cout << typeid(il.begin()).name() << endl;
	for (T const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
}
template<typename T>
ForwardList<T>::ForwardList(const ForwardList<T>& other) :ForwardList()
{
	/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_back(Temp->Data);*/
	*this = other;
	cout << "LCopyConstructor:\t" << this << endl;
}
template<typename T>
ForwardList<T>::ForwardList(ForwardList<T>&& other) :ForwardList()
{
	/*this->Head = other.Head;
	this->size = other.size;
	other.Head = nullptr;
	other.size = 0;*/
	*this = std::move(other);
	cout << "LMoveConstructor:\t" << this << endl;
}

template<typename T>
ForwardList<T>::~ForwardList()
{
	while (Head)pop_front();
	cout << "LDestructor:\t" << this << endl;
}

template<typename T>
ForwardList<T>& ForwardList<T>::operator=(const ForwardList<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_front(Temp->Data);
	reverse();
	cout << "LCopyAssignment:\t" << this << endl;
	return *this;
}
template<typename T>
ForwardList<T>& ForwardList<T>::operator=(ForwardList<T>&& other)
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
template<typename T>
T& ForwardList<T>::operator[](int Index)
{
	Element<T>* Temp = Head;
	for (int i = 0; i < Index; i++)Temp = Temp->pNext;
	return Temp->Data;
}

template<typename T>
void ForwardList<T>::push_front(T Data)
{
	/*Element* New = new Element(Data);
	New->pNext = Head;
	Head = New;*/
	Head = new Element<T>(Data, Head);

	size++;
}

template<typename T>
void ForwardList<T>::push_back(T Data)
{
	if (Head == nullptr)return push_front(Data);
	//Element* New = new Element(Data);
	Element<T>* Temp = Head;
	while (Temp->pNext) Temp = Temp->pNext;
	Temp->pNext = new Element<T>(Data);
	size++;
}

template<typename T>
void ForwardList<T>::insert(T Data, int Index)
{
	if (Index == 0)return push_front(Data);
	//Element* New = new Element(Data); 

	Element<T>* Temp = Head;
	for (int i = 0; i < Index - 1; i++)
	{
		if (Temp->pNext == nullptr)break;
		Temp = Temp->pNext;
	}
	//New->pNext = Temp->pNext;
	//Temp->pNext = New;
	Temp->pNext = new Element<T>(Data, Temp->pNext);
	size++;
}

//				Removing elements:

template<typename T>
void ForwardList<T>::pop_front()
{
	Element<T>* Erased = Head;
	Head = Head->pNext;
	delete Erased;
	size--;
}

template<typename T>
void ForwardList<T>::pop_back()
{
	Element<T>* Temp = Head;
	while (Temp->pNext->pNext)Temp = Temp->pNext;
	delete Temp->pNext;
	Temp->pNext = nullptr;
	size--;
}

template<typename T>
void ForwardList<T>::erase(int Index)
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

	Element<T>* Temp = Head;
	for (int i = 0; i < Index - 1; i++)
	{
		Temp = Temp->pNext;
	}

	Element<T>* Erased = Temp->pNext;
	Temp->pNext = Erased->pNext;
	delete Erased;
	size--;
}

template<typename T>
void ForwardList<T>::reverse()
{
	ForwardList<T> reverse;
	while (Head)
	{
		reverse.push_front(Head->Data);
		pop_front();
	}
	this->Head = reverse.Head;
	reverse.Head = nullptr;
}

template<typename T>
void ForwardList<T>::print()const
{
	/*Element* Temp = Head;
	while (Temp)
	{
		cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		Temp = Temp->pNext;
	}*/
	for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов списка: " << size << endl;
	cout << "Общее количество элементов : " << Element<T>::count << endl;
}

//////------------------ ForwardList methods end ---------//
//-------------------------------------------------------//


//////------------------------------------------------////
/////------------------ Element methods ----------///

template<typename T>
Element<T>::Element(T Data, Element<T>* pNext) :Data(Data), pNext(pNext)
{
	count++;
#ifdef DEBUG
	cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

}
template<typename T>
Element<T>::~Element()
{
	count--;
#ifdef DEBUG
	cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
}

//////------------------ Element methods end ---------//
//-------------------------------------------------------//


template<typename T>ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right)
{
	/*ForwardList result;

	for (Element* Temp = this->Head; Temp; Temp = Temp->pNext)
		result.push_back(Temp->Data);

	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		result.push_back(Temp->Data);

	return result;*/
	ForwardList<T> result = left;
	for (ConstIterator<T> it = right.begin(); it != right.end(); ++it)
	{
		//*it *= 100;
		result.push_back(*it);
	}
	return result;
}


//////------------------ Class definition end //---------//
//-------------------------------------------------------//