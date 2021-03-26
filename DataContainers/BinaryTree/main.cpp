#include <iostream>
using namespace std;

template<typename T>
class Tree {

	class Iterator;
	struct Element {
		T data;
		Element* pLeft;
		Element* pRight;
		Element(T data, Element* pLeft = nullptr, Element* pRight = nullptr) :
			data(data), pLeft(pLeft), pRight(pRight){}
	}*root;
	void insert(T data, Element* root) {
		if (this->root) {
			if (root) {
				if (data < root->data) {
					root->pLeft ?
						insert(data, root->pLeft), root :
						root->pLeft = new Element(data);
				}
				else if (data > root->data) {
					root->pRight ?
						insert(data, root->pRight), root :
						root->pRight = new Element(data);
				}
			}
		}
		else {
			this->root = new Element(data);
		}
	}
	void clear(Element* root) {
		if (root) {
			clear(root->pLeft);
			clear(root->pRight);
			delete root;
		}
	}
	T minValue(Element* root) {
		return root->pLeft ? minValue(root->pLeft): root->data;
	}
	T maxValue(Element* root) {
		return root->pRight ? maxValue(root->pRight) : root->data;
	}
	int size(Element* root) {
		return root ? size(root->pLeft) + size(root->pRight) + 1 : 0;
	}
	//sum только для числовых типов оставим int
	int sum(Element* root) {
		return root ?  sum(root->pLeft) + sum(root->pRight) + root->data : 0;
	}
	void copy(Element* root) {
		if (root) {
			insert(root->data,this->root);
		
			copy(root->pLeft);
		
			copy(root->pRight);
		}
	}
	Iterator find(T data, Iterator cur) {
		if (cur) {
			Element* temp = cur;
			return (data < *cur) ? find(data, temp->pLeft) : (data > *cur) ? find(data, temp->pRight) : cur;
		}
		else {
			return cur;
		}
	}
	//поиск родителя
	Iterator findParent(Element* child, bool& direction) {
		return (this->root->pLeft== this->root->pRight)? nullptr:findParent(child->data, child, this->root, direction);
	}
	Iterator findParent(T data, Element* child, Element* root,bool& direction) {
		if ((direction = root->pLeft == child) || (root->pRight == child)) {
			return root;
		}
		else {
			return (data < root->data) ? findParent(data, child, root->pLeft, direction) :
				findParent(data, child, root->pRight,direction);
		}
	}
	void erase(Element* root) {
		if (root) {
			bool direction;
			Element *temp, *parent;
			if (root->pRight) {
				temp = find(minValue(root->pRight));
				root->data = temp->data;
				erase(temp);
			}
			else if (root->pLeft) {
				temp = find(maxValue(root->pLeft));
				root->data = temp->data;
				erase(temp);
			}
			else {
				parent = findParent(root, direction);
				delete root;
				if (parent) {
					direction ? parent->pLeft = nullptr : parent->pRight = nullptr;
				}
				else {
					this->root = nullptr;
				}
			}
		}
	}
	void print(Element* root) {
		if (root) {
			print(root->pLeft);
			cout << root->data << "\t";
			print(root->pRight);
		}
	}
public:
	
	class Iterator {
		Element* cur;
	public:
		Iterator() :cur(nullptr){}
		Iterator(Element* cur) :cur(cur) {}
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
	//поиск по значению (интерфейсный метод)
	Iterator find(T data) {
		return find(data,this->root);
	}
	//удаление по значению (интерфейсный метод)
	void erase(T data){
		Element* del = find(data);
		erase(del);
	}

	Tree():root(nullptr){}

	Tree(const Tree& other):Tree() {
			copy(other.root);
	}

	Tree(const initializer_list<T> il) : Tree() {
		for (auto el : il) {
			insert(el);
		}
	}

	Tree& operator=(const Tree& other) {
		if (this != &other) {
			this->clear();
			copy(other.root);
		}
		return *this;
	}

	~Tree()	{
		clear(this->root);
	}
	//добавления элемента в дерево (интерфейсный метод)
	void insert(T data) {
		insert(data, this->root);
	}
	//удаление всех элементов (аналогичен деструктору)
	void clear() {
		clear(this->root);
	}
	Element* getRoot() {
		return this->root;
	}
	//крайний левый элемент в дереве
	T minValue() {
		return root ? minValue(this->root) : 0;
	}
	//крайний правый элемент в дереве
	T maxValue() {
		return root ? maxValue(this->root) : 0;
	}
	int size() {
		return size(this->root);
	}
	//sum только для числовых типов оставим int
	int sum() {
		return sum(this->root);
	}
	//avg только для числовых типов оставим float
	float avg() {
		return this->root ?(float)sum() / size():0;
	}
	void print(){
		print(this->root);
		cout << endl;
	}
};

int main() {
	system("chcp 1251 > nul");
	int n;

	Tree<int> t;

	cout << "Введите кол-во элементов: "; cin >> n;
	for (int i = 0; t.size() < n; ++i) {
		t.insert(rand() % 100);
	}
	t.print();
	Tree<int> t1 = t;
	cout << "t1.erase(67) \n";
	t1.erase(67);
	t1.print();

	cout << "Поиск t1.find(41): ";
	t1.find(41) ? cout << *t1.find(41) : cout << "элемент не найден";
	cout << endl;
	cout << "минимальное значение в дереве: "<<t1.minValue()<<endl;
	cout << "максимальное значение в дереве: " << t1.maxValue() << endl;
	cout << "количество элементов дерева: " << t1.size() << endl;
	cout << "Сумма элементов дерева: " << t1.sum() << endl;
	cout << "Среднее значение элементов дерева: " << t1.avg() << endl;
	
	cout << "\nТип данных string: " << endl;
	Tree<string> strTree({ "Hello","World","!" });
	strTree.print();

	cout << "strTree.erase(\"!\"); \n";
	strTree.erase("!");
	strTree.print();


	return 0;
}