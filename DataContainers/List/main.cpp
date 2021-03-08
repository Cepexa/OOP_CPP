#include<iostream>
using namespace std;
using std::cout;
#define tab "\t"

template<typename T>
class List{
private:

	int size;

	struct Element {
		T data;		//Значение элемента
		Element* pNext; //Адрес следующего элемента
		Element* pPrev;	//Адрес предыдущего элемента
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
			data(Data), pNext(pNext), pPrev(pPrev) {}
	}*head, *tail;//Указатель на Голову и Хвост


	//алгоритм копирования
	void copy(const List& other) {
		Element* temp = other.head;
		while (temp) {
			push_back(temp->data);
			temp = temp->pNext;
		}
	}

	//алгоритм переноса
	void move(List& other) {
		this->head = other.head;
		this->tail = other.tail;
		this->size = other.size;
		other.head = nullptr;
		other.tail = nullptr;
	}

	//алгоритм добавления в начало или в конец
	void push(T& Data, Element* &a, Element* &b, bool front = true) {
		if (a) {
			Element* temp = a;
			if (front) {
				temp->pPrev = a = new Element(Data, a);//в начало
			}
			else {
				temp->pNext = a = new Element(Data, nullptr, a);//в конец
			}
		}
		else {
			b = a = new Element(Data);//когда список пуст
		}
		++size;
	}

	//алгоритм исключения из начала или конца
	void pop(Element*& a, bool front = true) {
		if (a) {
			Element* temp = a;
			if (front) {
				a = a->pNext;
				(a)?a->pPrev = nullptr:a;
			}
			else {
				a = a->pPrev;
				(a)?a->pNext = nullptr:a;
			}
			delete temp;
			--size;
		}
	}

public:

	class Iterator{
	protected:
		Element* cur;
	public:
		Iterator(Element* cur) :cur(cur) {}
		//префиксный инкремент
		Iterator& operator++() {
			cur = cur->pNext;
			return *this;
		}
		//постфиксный инкремент
		Iterator operator++(int) {
			Iterator temp = *this;
			cur = cur->pNext;
			return temp;
		}
		//префиксный декремент
		Iterator& operator--() {
			cur = cur->pPrev;
			return *this;
		}
		//постфиксный декремент
		Iterator operator--(int) {
			Iterator temp = *this;
			cur = cur->pPrev;
			return temp;
		}
		//оператор разыменования const
		const T& operator*()const {
			return cur->data;
		}
		//оператор разыменования
		T& operator*() {
			return cur->data;
		}
		bool operator==(const Iterator& other) const {
			return this->cur == other.cur;
		}
		bool operator!=(const Iterator& other) const {
			return !operator==(other);
		}
		//оператор приведения типов
		operator Element* () {
			return this->cur;
		}
	};
	class ReverseIterator : public Iterator {
	public:
		ReverseIterator(Element* cur) : Iterator(cur) {}
		//префиксный декремент 
		Iterator& operator--() {
			return Iterator::operator++();
		}
		//постфиксный декремент 
		Iterator operator--(int) {
			Iterator temp = *this;
			Iterator::operator++();
			return temp;
		}
		//префиксный инкремент
		Iterator& operator++() {
			return Iterator::operator--();
		}
		//постфиксный инкремент
		Iterator operator++(int) {
			Iterator temp = *this;
			Iterator::operator--();
			return temp;
		}
	};

	Iterator begin() {
		return head;
	}
	Iterator end() {
		return nullptr;
	}
	const Iterator begin() const {
		return head;
	}
	const Iterator end() const {
		return nullptr;
	}
	ReverseIterator rbegin() {
		return tail;
	}
	ReverseIterator rend() {
		return nullptr;
	}
	const ReverseIterator rbegin() const {
		return tail;
	}
	const ReverseIterator rend() const {
		return nullptr;
	}

	List(){
		size=0;
		head = nullptr;
		tail = nullptr;
	}
	explicit List(int size):List(){
		++size;
		while (--size) {
			push_front(0);
		}
	}
	List(const List& other) : List() {
		copy(other);
	}
	List(List&& other) {
		move(other);
	}
	List(const initializer_list<T> il) : List() {
		for (auto el : il) {
			push_back(el);
		}
	}
	~List(){
		while (head) {
			pop_front();
		}
	}


	List& operator=(const List& other) {
		if (this != &other) {
			this->~List();
			copy(other);
		}
		return *this;
	}
	List& operator=(List&& other) {
			this->~List();
			move(other);
		return *this;
	}

	//Добавляет значение в начало списка
	void push_front(T data){
		push(data, head, tail);
	}
	//Добавляет значение в конец списка
	void push_back(T data){
		push(data, tail, head,0);
	}
	//Удаляет значение из начала списка
	void pop_front() {
		pop(head);
	}
	//Удаляет значение из конца списка
	void pop_back() {
		pop(tail, 0);
	}
	//поиск элемента по индексу
	Iterator find(const int& index) {
		if ((index >= size) || (index < 0)) {
			throw exception("Out of range");
		}
		Iterator temp = head;
		if (index <= size / 2) {
			advance(temp, index);
		}
		else {
			temp = tail;
			advance(temp, size-1-index,false);
		}
		return temp;
	}
	//сдвиг итератора на нужное количество шагов, inc = true вправо, inc = false влево
	void advance(Iterator& it, const int& count, bool inc = true) {
			for (int i = 0; i < count; ++i) {
				(inc)?++it:--it;
			}
	}
	//Оператор []
	T& operator[](const int index) {
		return *find(index);
	}
	//добавление элемента в список по индексу
	void insert(int index, T data){
		if (index == 0) {
			push_front(data);
		}
		else if (index == size) {
			push_back(data);
		}
		else {
			Element* cur = find(index);
			Element* temp = cur;
			temp->pPrev = cur = new Element(data, cur, cur->pPrev);
			cur->pPrev->pNext = cur;
			++size;
		}
	}
	//удаление элемента из списка по индексу
	void erase(int index) {
		if (index == 0) {
			pop_front();
		}
		else if (index == size-1) {
			pop_back();
		}
		else {
			Element* cur = find(index);
			Element* temp = cur;
			cur->pNext->pPrev = temp->pPrev;
			cur->pPrev->pNext = temp->pNext;
			delete temp;
			--size;
		}
	}
	//сортировка (f=true - по возрастанию, f=false - по убыванию)
	void sort(bool f=true) {
		auto pred = [&f](T& a, T& b) {
			return (f) ? a<b : a>b;
		};
		for (T& el1 : *this) {
			for (T& el2 : *this) {
				if (pred(el1, el2)) {
					auto buf = el1;
					el1 = el2;
					el2 = buf;
				}
			}
		}
	}
	//вывод в консоль
	void print(){
		for (auto el:*this) {
			cout << el << endl;
		}
		cout << "Количество элементов списка: " << size << endl;
	}
	//вывод в консоль в обратном порядке
	void print_reverce() {
		for (auto rIt = rbegin(); rIt != rend(); ++rIt) {
			cout << *rIt << tab << endl;
		}
		cout << "Количество элементов списка: " << size << endl;
	}

	int getSize() {
		return size;
	}
};

//конкатенация двух списков
template<typename T>
List<T> operator+(const List<T>& left, const List<T>& right) {
	List<T> cat = left;
	for (auto el:right) {
		cat.push_back(el);
	}
	return cat;
}

void main(){
	system("chcp 1251 > nul");

//#define BASE_CHECK
#ifdef BASE_CHECK
	cout << "Проверочный код:\n";
	cout << "Создаём List<int> l: \n"
		">------------------------->\n";
	List<int> l = { 3,5,8,13,21 };
	for (int i : l) {
		cout << i << tab;
	}
	cout << endl;
	cout << ">------------------------->\n"
		"Выводим l[1]:\n"
		">------------------------->\n";
	cout << l[1] << endl;

	cout << ">------------------------->\n"
		"Создаём List<int> l1,l2:\n"
		">------------------------->\n";
	List<int> l1, l2;
	cout << ">------------------------->\n"
		"l1.push_back(124);\n"
		"l1.push_front(111);\n"
		"l1.push_back(15);\n"
		"l1.push_back(51);\n"
		"l1.insert(2, 9999);\n"
		"l1.erase(3);\n"
		"l1.print();\n"
		">------------------------->\n";
	l1.push_back(124);
	l1.push_front(111);
	l1.push_back(15);
	l1.push_back(51);
	l1.insert(2, 9999);
	l1.erase(3);
	l1.print();
	l1.print_reverce();
	cout << ">------------------------->\n"
		"l1.sort();\n"
		"l1.print();\n"
		">------------------------->\n";

	l1.sort();
	l1.print();

	cout << ">------------------------->\n"
		"l1.pop_back();\n"
		"l1.pop_front();\n"
		"l1.print();\n"
		">------------------------->\n";

	l1.pop_back();
	l1.pop_front();
	l1.print();

	cout << ">------------------------->\n"
		"l2 = l1;\n"
		"l2.print();\n"
		">------------------------->\n";

	l2 = l1;
	l2.print();
	cout << ">------------------------->\n"
		"(l + l1 + l2).print();\n"
		">------------------------->\n";
	(l + l1 + l2).print();

	cout << ">------------------------->\n"
		"Создаём List<string> l3:\n"
		"l3.sort(false); //сортировка по убыванию\n"
		"l3.print();\n"
		">------------------------->\n";
	List<string> l3 = { "Маша","Кристина","Наташа" };
	l3.sort(false);
	l3.print();
	cout << ">------------------------->\n"
		"for (auto it = l3.rbegin(); it != l3.rend(); ++it) {\n"
		"   cout << *it << endl;\n"
		"}\n"
		">------------------------->\n";
	for (auto it = l3.rbegin(); it != l3.rend(); ++it) {
		cout << *it << endl;
	}
#endif // BASE_CHECK

	
//#define SUBSCRIPT
#ifdef SUBSCRIPT
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	List<int> list(n);
	cout << "Список создан загружаем данные...\n";
	for (size_t i = 0; i < list.getSize(); ++i)	{

		list[i] = rand();

	}
	/*for (auto& el : list) {
		el = rand();
	}*/
	cout << endl;
	cout << "Список загружен...\n";
#endif // subscript

//#define CHECK_2
#ifdef CHECK_2
	cout << "Проверочный код Iterator:\n";
	List<int> l = { 3,5,8,13,21 };
	for (auto it = l.begin(); it != l.end(); ++it) {
		cout << *it << endl;
	}
	cout << endl;
	cout << "Проверочный код ReverseIterator:\n";
	for (auto it = l.rbegin(); it != l.rend(); it++) {
		cout << *it<<endl;
	}

#endif // CHECK_2


	system("pause");
}