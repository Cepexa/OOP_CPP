#include<iostream>
using namespace std;

#define tab "\t"

class Element {
	int Data; //Значение элемента
	Element* pNext; //Адрес следующего элемента
	static int count;//количество элементов
public:
	Element(int Data, Element* pNext = nullptr)
	{
		++count;
		//cout << " EConstructor:"
	}
	~Element()
	{
		--count;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class Iterator;
	friend class List;
};
int Element::count = 0;

class Iterator{
Element * Temp;
public:
	Iterator(Element* Temp) :Temp(Temp) {
		cout << "IConstructor:\t" << this << endl;
	}
	~Iterator() {
		cout << "IDestructor:\t" << endl;
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
	int& operator*() {
		return Temp->Data;
	}
	bool operator==(const Iterator& other) const {
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other) const {
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
	List()
	{
		//size=0;
		Head = nullptr;	//Если Голова содержит 0, значит список пуст
		cout << "LConstructor:\t" << this << endl;
	}
	explicit List(int size) :List() {
		//this->Head = nullptr;
		//this->size = 0;
		while (size--) {
			push_front(0);
		}
		//cout << "LSizeConstructor:\t" << this << endl;
	}
	List(const List& other) {
		Element* Temp = other.Head;
		while (Temp) {
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		cout << "CopyConstructor:\t" << this << endl;

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
		cout << "LDestructor:\t" << this << endl;
	}
	//		 Operators:
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
		while (Head) {
			pop_front();
		}
		for (Element* Temp = other.Head; Temp != nullptr; Temp = Temp->pNext) {
			push_back(Temp->Data);
		}
		cout << "CopyAssigment:\t" << endl;
		return *this;
	}
	//			Добавление элементов
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
	//			Methods
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
		for (Iterator it = Head; it != nullptr; ++it) {
			cout << *it << tab << endl;
		}
		cout << "Количество элементов списка: " << size << endl;
	}
};
//#define BASE_CHECK
//#define COUNT_CHECK
void main()
{
	setlocale(LC_ALL, "");
	int n;	//Размер списка
	cout << "Введите размер списка: "; cin >> n;
#ifdef BASE_CHECK
	List list;
	/*list.push_back(3);
	list.push_back(5);
	list.push_back(8);
	list.push_back(13);
	list.push_back(21);*/
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.push_back(123);
	list.print();

	int index;
	int data;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> data;
	list.insert(index, data);
	list.print();

	List list2;
	list2.push_back(123);
	list2.push_back(456);
	list2.push_back(789);
	list2.print();
#endif //BASE_CHECK
#ifdef COUNT_CHECK
	List list(n);
	for (int i = 0; i < n; ++i) {
		list[i] = rand() % 100;
	}
	for (int i = 0; i < n; ++i) {
		cout << list[i] << "\t";
	}
	cout << endl;
	List list2;
	list2 = list;
	list2.print();
#endif //COUNT_CHECK
	List list(n);
	for (int& i : list) {
		i = rand() % 100;
	}

	list.print();
}