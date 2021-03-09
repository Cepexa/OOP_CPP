#include<iostream>
using namespace std;
using std::cout;
#define tab "\t"

template<typename T>
class ForwardList{
	
	int size;

	struct Element {
		T data; //Значение элемента
		Element* pNext; //Адрес следующего элемента
		Element(T data, Element* pNext = nullptr) :
			data(data), pNext(pNext) {}
	}* head;	//Указатель на начальный (нулевой) элемент списка.

	//алгоритм копирования
	void copy(Element* temp) {
		if (temp->pNext) {
			copy(temp->pNext);
		}
		push_front(temp->data);
	}
	
	//алгоритм переноса
	void move(ForwardList& other) {
		this->head = other.head;
		this->size = other.size;
		other.head = nullptr;
	}

public:

	class Iterator {
		Element* cur;
	public:
		Iterator(Element* Temp) :cur(Temp) {}
		Iterator& operator++() {
			cur = cur->pNext;
			return *this;
		}
		Iterator operator++(int) {
			Iterator old = *this;
			cur = cur->pNext;
			return old;
		}
		const T& operator*()const {
			return cur->data;
		}
		T& operator*() {
			return cur->data;
		}
		bool operator==(const Iterator& other) const {
			return this->cur == other.cur;
		}
		bool operator!=(const Iterator& other) const {
			return !(*this == other);
		}
		//оператор приведения типов
		operator Element* () {
			return this->cur;
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
	ForwardList(){
		size=0;
		head = nullptr;	//Если Голова содержит 0, значит список пуст
	}
	explicit ForwardList(int size) :ForwardList() {
		++size;
		while (size--) {
			push_front(0);
		}
	}
	ForwardList(const ForwardList& other) : ForwardList() {
		copy(other.head);
	}
	ForwardList(const initializer_list<T> il) : ForwardList() {
		for (auto el : il) {
			push_back(el);
		}
	}
	~ForwardList(){
		while (head){
			pop_front();
		}
	}
	//Operators:
	T& operator[](const int index) {
		return *find(index);
	}
	ForwardList& operator=(const ForwardList& other) {
		if (this != &other) {
			this->~ForwardList();
			copy(other.head);
		}
		return *this;
	}
	ForwardList& operator=(ForwardList&& other) {
		this->~ForwardList();
		move(other);
		return *this;
	}
	//поиск элемента по индексу
	Iterator find(const int& index) {
		if ((index >= size) || (index < 0)) {
			throw exception("Out of range");
		}
		Iterator temp = head;
		advance(temp, index);
		return temp;
	}
	//сдвиг итератора на нужное количество шагов вправо
	void advance(Iterator& it, const int& count) {
		for (int i = 0; i < count; ++i) {
			 ++it;
		}
	}
	//Добавление элементов
	void push_front(T data){
			head = new Element(data, head);
		++size;
	}
	void push_back(T data){
		if (head){
			Element* temp = find(size - 1);
			temp->pNext = new Element(data);
			++size;
		}
		else {
			push_front(data);
		}
	}
	//Удаление элементов
	void pop_front() {
		if (head) {
			Element* temp = head;
			head = head->pNext;
			delete temp;
			--size;
		}
	}
	void pop_back() {
		if (head) {
			Element* temp = find(size - 2);
			delete temp->pNext;
			temp->pNext = nullptr;
			--size;
		}
	}
	void insert(int index, T data){
		if (index == 0) {
			push_front(data);
		}
		else if (index == size) {
			push_back(data);
		}
		else {
			Element* temp = find(index-1);
			Element* cur  = temp->pNext;
			cur = new Element(data, cur);
			temp->pNext = cur;
			++size;
		}
	}
	void erase(int index) {
		if (index == 0) {
			pop_front();
		}
		else if (index == size - 1) {
			pop_back();
		}
		else {
			Element* temp = find(index-1);
			Element* cur = temp->pNext;
			temp->pNext = cur->pNext;
			delete cur;
			--size;
		}
	}
	//размер листа
	int getSize() {
		return size;
	}
	//сортировка (f=true - по возрастанию, f=false - по убыванию)
	void sort(bool f = true) {
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
	//	Methods
	void print(){
		Element* temp = head;	
		for (Iterator it = head; it != end(); ++it) {
			cout << *it << tab << endl;
		}
		cout << "Количество элементов списка: " << size << endl;
	}
};

//конкатенация двух списков
template<typename T>
ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right) {
	ForwardList<T> cat = left;
	for (auto el : right) {
		cat.push_back(el);
	}
	return cat;
}

void main(){
	system("chcp 1251 > nul");
	int n;	//Размер списка
	cout << "Введите размер списка: "; cin >> n;
#define BASE_CHECK
#ifdef BASE_CHECK
	ForwardList<int> list;
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
	//list.erase(index);
	//list.print();
	ForwardList<int> list2;
	list2 = list;
	(list2 + list).print();
	list2.push_back(123);
	list2.push_back(456);
	list2.push_back(789);
	list2.print();
	list2.pop_back();
	list2.print();
	list2.sort();
	list2.print();


	ForwardList<string> l3 = { "Маша","Кристина","Наташа" };
	l3.sort(false);
	l3.print();
#endif //BASE_CHECK


//#define COUNT_CHECK
#ifdef COUNT_CHECK
	ForwardList<int> list(n);
	for (int i = 0; i < n; ++i) {
		list[i] = rand() % 100;
	}
	for (int i = 0; i < n; ++i) {
		cout << list[i] << "\t";
	}
	cout << endl;
	ForwardList list2;
	list2 = list;
	list2.print();
#endif //COUNT_CHECK


	//#define CHECK
#ifdef CHECK
	ForwardList<int> list(n);
	for (int& i : list) {
		i = rand() % 100;
	}

	list.print();
#endif // CHECK

}