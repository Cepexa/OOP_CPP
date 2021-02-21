#include<iostream>
using namespace std;

#define tab "\t"

class Element{
	int Data;		//�������� ��������
	Element* pNext;	//����� ���������� ��������
	static int count;//���������� ���������
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		++count;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		--count;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class List;
};
int Element::count = 0;
class List
{
	int size;
	Element* Head;	//��������� �� ��������� (�������) ������� ������.
public:
	List()
	{
	//size=0;
		Head = nullptr;	//���� ������ �������� 0, ������ ������ ����
		cout << "LConstructor:\t" << this << endl;
	}
	explicit List(int size):List(){
		//this->Head = nullptr;
		//this->size = 0;
		while (size--) {
			push_front(0);
		}
		//cout << "LSizeConstructor:\t" << this << endl;
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
	//			���������� ���������
	void push_front(int Data)	//��������� �������� � ������ ������
	{
		
		/*
		//1) ������� ����� �������
		Element* New = new Element(Data);
		//2) ������������ ����� ������� � ������
		New->pNext = Head;
		//3)�������, ��� ����� ������� �������� ������� (Head) ������:
		Head = New;*/

		Head = new Element(Data, Head);
		++size;
	}
	void push_back(int Data)	//��������� �������� � ����� ������
	{
		if (Head == nullptr)//���� ������ ����
		{
			push_front(Data);
			return;
		}
		//0) ������� �������:
		//Element* New = new Element(Data);
		//1) ����� �� ���������� ��������
		Element* Temp = Head;
		while (Temp->pNext != nullptr)
			Temp = Temp->pNext;
		//2) ���������� ���������� ������� � ����� ������
		Temp->pNext = new Element(Data);
		++size;
	}

	void insert(int Index, int Data)
	{
		//1) ������� �� ������� ��������:
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
		Element* Temp = Head;	//Temp - ��� ��������.
		//�������� - ��� ���������, ��� ������ �������� ����� �������� ������ 
		//� ��������� ��������� ������.
		while (Temp != nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//������� �� ��������� �������
		}
		cout << "���������� ��������� ������: " << size << endl;
	}
};
//#define BASE_CHECK
void main()
{
	setlocale(LC_ALL, "");
	int n;	//������ ������
	cout << "������� ������ ������: "; cin >> n;
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
	cout << "������� ������ ������������ ��������: "; cin >> index;
	cout << "������� �������� ������������ ��������: "; cin >> data;
	list.insert(index, data);
	list.print();

	List list2;
	list2.push_back(123);
	list2.push_back(456);
	list2.push_back(789);
	list2.print();
	#endif //BASE_CHECK
	List list(n);
	for (int i = 0; i < n; ++i) {
		list[i] = rand() % 100;
	}
	for (int i = 0; i < n; ++i) {
		cout << list[i] << "\t";
	}
	cout << endl;
}