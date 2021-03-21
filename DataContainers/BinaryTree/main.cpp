#include <iostream>
using namespace std;

class Tree {
	struct Element {
		int data;
		Element* pLeft;
		Element* pRight;
		Element(int data, Element* pLeft = nullptr, Element* pRight = nullptr) :
			data(data), pLeft(pLeft), pRight(pRight){}
	}*root;
	void insert(int data, Element* root) {
		if (this->root) {
			if (root) {
				if (data < root->data) {
					(root->pLeft) ?
						insert(data, root->pLeft), root :
						root->pLeft = new Element(data);
				}
				else if (data > root->data) {
					(root->pRight) ?
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
	int minValue(Element* root) {
		return (root->pLeft) ? minValue(root->pLeft): root->data;
	}
	int maxValue(Element* root) {
		return (root->pRight) ? maxValue(root->pRight) : root->data;
	}
	int size(Element* root) {
		return (root) ? size(root->pLeft) + size(root->pRight) + 1 : 0;
	}
	int sum(Element* root) {
		return (root) ?  sum(root->pLeft) + sum(root->pRight) + root->data : 0;
	}
	void copy(Element* root) {
		if (root) {
			insert(root->data,this->root);
		
			copy(root->pLeft);
		
			copy(root->pRight);
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
	Tree():root(nullptr){
	}

	Tree(const Tree& other):Tree() {
			copy(other.root);
	}
	void insert(int data) {
		insert(data, this->root);
	}
	~Tree()	{
		clear(this->root);
	}
	void clear() {
		clear(this->root);
	}
	Element* getRoot() {
		return this->root;
	}
	int minValue() {
		return(root) ? minValue(this->root) : 0;
	}
	int maxValue() {
		return(root) ? maxValue(this->root) : 0;
	}
	int size() {
		return size(this->root);
	}
	int sum() {
		return sum(this->root);
	}
	float avg() {
		return (this->root)?(float)sum() / size():0;
	}
	void print(){
		print(this->root);
		cout << endl;
	}
};

int main() {
	system("chcp 1251 > nul");
	int n;

	Tree t;

	cout << "Введите кол-во элементов: "; cin >> n;
	for (int i = 0; t.size() < n; ++i) {
		t.insert(rand() % 100);
	}
	t.print();
	Tree t1(t);
	t1.print();
	cout << "минимальное значение в дереве: "<<t.minValue()<<endl;
	cout << "максимальное значение в дереве: " << t.maxValue() << endl;
	cout << "количество элементов дерева: " << t.size() << endl;
	cout << "Сумма элементов дерева: " << t.sum() << endl;
	cout << "Среднее значение элементов дерева: " << t.avg() << endl;
	return 0;
}