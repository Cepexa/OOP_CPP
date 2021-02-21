#include<iostream>
using namespace std;

#define tab "\t"

class Element{
	int Data;		//Значение элемента
	Element* pNext;	//Адрес следующего элемента
	static int count;//количество элементов
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		++count;
	}
	~Element()
	{
		--count;
	}
	friend class Iterator;
	friend class List;
};
int Element::count = 0;

class Iterator {
	Element* Temp;
public:
	Iterator(Element* Temp) :Temp(Temp) {
	}
	~Iterator() {
	}
	Iterator& operator++() {
		Temp = Temp->pNext;
		return *this;
	}
	Iterator operator++(int) {
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}
	const int& operator*()const {
		return Temp->Data;
	}
	int& operator*(){
		return Temp->Data;
	}
	bool operator==(const Iterator& other) const {
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other) const{
		return !(*this == other);
	}
};

class List
{
	int size;
	Element* Head;	//Указатель на начальный (нулевой) элемент списка.
public:
	Iterator begin() {
		return Head;
	}
	Iterator end() {
		return nullptr;
	}
	const Iterator begin() const {
		return Head;
	}
	const Iterator end() const {
		return nullptr;
	}
	List(){
		size=0;
		Head = nullptr;	//Если Голова содержит 0, значит список пуст
		#ifdef CHECK
		cout << "LConstructor:\t" << this << endl;
		#endif
	}
	explicit List(int size):List(){
		//this->Head = nullptr;
		//this->size = 0;
		while (size--) {
			push_front(0);
		}
		//cout << "LSizeConstructor:\t" << this << endl;
	}
	List(const List& other) : List() {
		Element* Temp = other.Head;
		while (Temp) {
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
	}
	List(List&& other) {
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
	}
	List(const initializer_list<int> il) : List() {
		//cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); ++it) {
			push_back(*it);
		}
	}
	~List()
	{
		while (Head) {
			pop_front();
		}
	}
	int& operator[](const int index) {
		if (index >= size) {
			throw exception("Out of range");
		}
		Element* Temp = Head;
		for (int i = 0; i < index; ++i) {
			Temp = Temp->pNext;
		}
		return Temp->Data;
	}
	List& operator=(const List& other) {
		if (this != &other) {
			while (Head) {
				pop_front();
			}
			for (Element* Temp = other.Head; Temp != nullptr; Temp = Temp->pNext) {
				push_back(Temp->Data);
			}
		}
		return *this;
	}
	List& operator=(List&& other) {
			while (Head) {
				pop_front();
			}
			this->Head = other.Head;
			this->size = other.size;
			other.Head = nullptr;
		return *this;
	}
	
	void push_front(int Data)	//Добавляет значение в начало списка
	{
		
		/*
		//1) Создаем новый элемент
		Element* New = new Element(Data);
		//2) Присоединяем НОВЫЙ элемент к списку
		New->pNext = Head;
		//3)Говорим, что НОВЫЙ элемент является НАЧАЛОМ (Head) списка:
		Head = New;*/

		Head = new Element(Data, Head);
		++size;
	}
	void push_back(int Data)	//Добавляет значение в конец списка
	{
		if (Head == nullptr)//Если список пуст
		{
			push_front(Data);
			return;
		}
		//0) Создать элемент:
		//Element* New = new Element(Data);
		//1) Дойти до последнего элемента
		Element* Temp = Head;
		while (Temp->pNext != nullptr)
			Temp = Temp->pNext;
		//2) Прикрепить добавляемы элемент к концу списка
		Temp->pNext = new Element(Data);
		++size;
	}
	void insert(int Index, int Data)
	{
		//1) Доходим до нужного элемента:
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			if (Temp->pNext == nullptr)return;
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element(Data, Temp->pNext);
		++size;
	}
	void pop_front() {
		Element* ToDel = Head;
		Head = Head->pNext;
		delete ToDel;
		--size;
	}
	void pop_back() {
		Element* Temp = Head;
		while (Temp->pNext->pNext) {
			/*
			...
			*/
		}
		--size;
	}
	void print()
	{
		Element* Temp = Head;	//Temp - это итератор.
		//Итератор - это указатель, при помощи которого можно получить доступ 
		//к элементам структуры данных.
		//while (Temp != nullptr)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext;	//Переход на следующий элемент
		//}
		for (Iterator it = Head; it != nullptr;++it) {
			cout << *it << tab << endl;
		}
		cout << "Количество элементов списка: " << size << endl;
	}
};
List operator+(const List& left, const List& right) {
	List cat = left;
	for (Iterator it = right.begin(); it != right.end(); ++it) {
		cat.push_back(*it);
	}
#ifdef CHECK
	cout << "Operator+:\t" << endl;
#endif // CHECK
	return cat;
}

void main(){
	system("chcp 1251 > nul");
	cout << "Hello World!";
}