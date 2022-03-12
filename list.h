#ifndef DOUBLY_LINKED_LIST_HEADER
#define DOUBLY_LINKED_LIST_HEADER

#include <iostream>
#include <fstream>
using namespace std;

template<typename T>
class list {

private:

	class Node {

	public:
		Node* prev;
		Node* next;
		T data;
		Node(Node* prev, Node* next, T data) {
			this->prev = prev;
			this->next = next;
			this->data = data;
		}
	};
	Node* head;
	Node* tail;
	int elements;

	Node* position(int i)     //returns a pointer to the i-th element
	{
		Node* p = head;
		while (i > 0)
		{
			p = p->next;
			--i;
		}
		return p;
	}

	Node* rposition(int i)     //returns a pointer to the i-th element (the list is numbered from end to start)
	{
		Node* p = tail;
		while (i > 0)
		{
			p = p->prev;
			--i;
		}
		return p;
	}

	void swap_pos(T& x, T& y)				//swaps two elements
	{										//it's called by erase, rerase functions
		T m = x;
		x = y;
		y = m;
	}
											  
	void destroy(Node* p, Node* q)			//frees the memory from the p-th to q-th memory address
	{									    //it's called by erase, rerase functions
		Node* a;
		while (p != q)
		{
			a = p;
			p = p->next;
			delete a;
		}
		delete p;
	}

	int split(int left, int right)			//splitting used by quick_sort() function
	{
		Node* p = position(left);
		Node* q = p;
		T pivot = value(right);
		T data;
		int i = left;

		for (int j = left; j < right; ++j)
		{
			if (q->data <= pivot)
			{
				data = p->data;
				p->data = q->data;
				q->data = data;

				p = p->next;
				++i;
			}

			q = q->next;
		}
		data = p->data;
		p->data = q->data;
		q->data = data;

		return i;
	}

	void quick_sort(int left, int right)		//sorts in ascending order
	{
		if (left < right)
		{
			int m = split(left, right);
			quick_sort(left, m - 1);
			quick_sort(m + 1, right);
		}
	}

	int rsplit(int left, int right)				//splitting used by quick_rsort() function
	{
		Node* p = position(left);
		Node* q = p;
		T pivot = value(right);
		T data;
		int i = left;

		for (int j = left; j < right; ++j)
		{
			if (q->data >= pivot)
			{
				data = p->data;
				p->data = q->data;
				q->data = data;

				p = p->next;
				++i;
			}

			q = q->next;
		}
		data = p->data;
		p->data = q->data;
		q->data = data;

		return i;
	}

	void quick_rsort(int left, int right)		//sorts in descending order
	{
		if (left < right)
		{
			int m = rsplit(left, right);
			quick_rsort(left, m - 1);
			quick_rsort(m + 1, right);
		}
	}

public:
	list();							//default constructor
	list(int, T x = 0);				//initializer constructor
	~list();						//destructor
	void push_front(T);				//adds a new element at the beginning of the list
	void push_back(T);				//adds a new element at the end of the list
	void pop_front();				//removes the first element of the list
	void pop_back();				//removes the last element of the list
	T front();						//returns the first element of the list
	T back();						//returns the last element of the list
	T value(int);					//returns the i-th element
	T rvalue(int);					//returns the i-th element from the backward numbered list
	T min();						//returns the smallest element of the list
	T max();						//returns the largest element of the list
	void clear();					//removes all the elements from the list
	bool empty();					//checks if the list is empty (returns a boolean value)
	int size();						//returns the number of elements in the list

	void swap(int, int);			//swaps 2 elements at the given positions
	void rswap(int, int);			//swaps 2 elements at the given positions from the backward numbered list
	void replace(T, T);				//replaces all elements to the 2nd parameter that are equal to the first parameter
	void remove(T);					//deletes all elements equal to the given parameter
	void reverse();					//reverses the list
	void resize(int);				//resizes the list
	void rresize(int);				//resizes the list (numbered from backwards)
	void resize(int, T);			//resizes the list and initializes the new elements with the given 2nd parameter

	bool contains(T);				//checks if the given element is in the list
	void sort();					//sorts the list in ascending order
	void rsort();					//sorts the list in descending order
	bool ascending();				//checks if the elements in the list are in ascending order
	bool descending();				//checks if the elements in the list are in descending order
	void unique();					//transforms the sorted list to a set

	void insert_before(int, T);		  //inserts an element before the i-th position	
	void insert_after(int, T);        //inserts an element after the i-th position	
	void rinsert_before(int, T);	  //inserts an element before the i-th position	(numbered from backwards)
	void rinsert_after(int, T);		  //inserts an element after the i-th position (numbered from backwards)

	void insert_before(int, int, T);   //inserts N element before the i-th position	
	void insert_after(int, int, T);    //inserts N element after the i-th position	
	void rinsert_before(int, int, T);  //inserts N element before the i-th position	(numbered from backwards)
	void rinsert_after(int, int, T);   //inserts N element after the i-th position (numbered from backwards)

	void erase(int);				//removes the element on the i-th position
	void erase(int, int);			//removes the elements between the i- and j-th positions
	void rerase(int);				//removes the element on the i-th position (numbered from backwards)
	void rerase(int, int);			//removes the elements between the i- and j-th positions (numbered from backwards)

	void read();					//reads the list from console
	void read(const char*);			//reads the list from file
	void print();					//prints the list to console
	void print(const char*);		//prints the list to file
	void rprint();					//prints the list to console in reversed order
	void rprint(const char*);		//prints the list to file in reversed order
};


template<typename T>
list<T>::list()
{
	head = nullptr;
	tail = nullptr;
	elements = 0;
}


template<typename T>
list<T>::list(int n, T data)
{
	elements = n;
	Node* p = new Node(nullptr, nullptr, data);
	head = p;
	tail = p;

	for (int i = 1; i < elements; ++i)
	{
		p = new Node(tail, nullptr, data);
		p->prev->next = p;
		tail = p;
	}
}


template<typename T>
list<T>::~list()
{
	Node* p;
	while (tail != nullptr)
	{
		p = tail;
		tail = tail->prev;
		delete p;
	}
	head = nullptr;
	elements = 0;
}


template<typename T>
void list<T>::push_front(T data)
{
	if (head != nullptr)
	{
		Node* p = new Node(nullptr, head, data);
		p->next->prev = p;
		head = p;
	}
	else
	{
		Node* p = new Node(nullptr, nullptr, data);
		head = p;
		tail = p;
	}

	++elements;
}


template<typename T>
void list<T>::push_back(T data)
{
	if (tail != nullptr)
	{
		Node* p = new Node(tail, nullptr, data);
		p->prev->next = p;
		tail = p;
	}
	else
	{
		Node* p = new Node(nullptr, nullptr, data);
		head = p;
		tail = p;
	}

	++elements;
}


template<typename T>
void list<T>::pop_front()
{
	if (head == nullptr)
	{
		cout << "Empty list! Cannot delete!" << endl;
		return;
	}

	if (elements != 1)
	{
		head = head->next;
		delete head->prev;
		head->prev = nullptr;
	}
	else
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}

	--elements;
}

template<typename T>
void list<T>::pop_back()
{
	if (tail == nullptr)
	{
		cout << "Empty list! Cannot delete!" << endl;
		return;
	}

	if (elements != 1)
	{
		tail = tail->prev;
		delete tail->next;
		tail->next = nullptr;
	}
	else
	{
		delete tail;
		head = nullptr;
		tail = nullptr;
	}

	--elements;
}


template<typename T>
T list<T>::front()
{
	return head->data;
}


template<typename T>
T list<T>::back()
{
	return tail->data;
}


template<typename T>
T list<T>::value(int i)
{
	return position(i)->data;
}

template<typename T>
T list<T>::rvalue(int i)
{
	return rposition(i)->data;
}

template<typename T>
T list<T>::min()
{
	if (elements == 1)
		return head->data;

	Node* p = head->next;
	T minimum = head->data;
	while (p != nullptr)
	{
		if (p->data < minimum)
			minimum = p->data;
		p = p->next;
	}

	return minimum;
}


template<typename T>
T list<T>::max()
{
	if (elements == 1)
		return head->data;

	Node* p = head->next;
	T maximum = head->data;
	while (p != nullptr)
	{
		if (p->data > maximum)
			maximum = p->data;
		p = p->next;
	}

	return maximum;
}


template<typename T>
void list<T>::clear()
{
	list<T>::~list();
}


template<typename T>
bool list<T>::empty()
{
	return elements == 0;
}


template<typename T>
int list<T>::size()
{
	return elements;
}


template<typename T>
void list<T>::swap(int i, int j)
{
	if (i < 0 || i >= elements || j < 0 || j >= elements)
	{
		cout << "Error! Non-existent positions!" << endl;
		return;
	}

	Node* p = position(i);
	Node* q = position(j);
	T data = p->data;
	p->data = q->data;
	q->data = data;
}


template<typename T>
void list<T>::rswap(int i, int j)
{
	if (i < 0 || i >= elements || j < 0 || j >= elements)
	{
		cout << "Error! Non-existent positions!" << endl;
		return;
	}

	Node* p = rposition(i);
	Node* q = rposition(j);
	T data = p->data;
	p->data = q->data;
	q->data = data;
}


template<typename T>
void list<T>::replace(T x, T y)
{
	Node* p = head;
	while (p != nullptr)
	{
		if (p->data == x)
			p->data = y;
		p = p->next;
	}
}


template<typename T>
void list<T>::remove(T x)
{
	if (head == nullptr)
	{
		cout << "Empty list! Cannot delete!" << endl;
		return;
	}

	if (elements == 1)
	{
		if (head->data == x)
			pop_front();
		return;
	}
	if (elements == 2)
	{
		if (head->data == x)
			pop_front();
		if (tail->data == x)
			pop_back();
		return;
	}

	Node* p = head->next;
	Node* q;
	while (p != tail)
	{
		if (p->data == x)
		{
			q = p;
			p = p->next;
			q->prev->next = q->next;
			q->next->prev = q->prev;

			delete q;
			--elements;
		}
		else
			p = p->next;
	}

	if (head->data == x)
		pop_front();
	if (tail != nullptr && tail->data == x)
		pop_back();
}


template<typename T>
void list<T>::reverse()
{
	int n = elements / 2;
	Node* p = head;
	Node* q = tail;
	T data;

	for (int i = 0; i < n; ++i)
	{
		data = p->data;
		p->data = q->data;
		q->data = data;
		p = p->next;
		q = q->prev;
	}
}


template<typename T>
void list<T>::resize(int n)
{
	if (n <= 0)
	{
		cout << "Error! Cannot resize!" << endl;
		return;
	}

	if (elements > n)
		erase(n, elements - 1);
	else
		if (elements < n)
			for (int i = elements; i < n; ++i)
				push_back(0);
}


template<typename T>
void list<T>::rresize(int n)
{
	if (n <= 0)
	{
		cout << "Error! Cannot resize!" << endl;
		return;
	}

	if (elements > n)
		rerase(n, elements - 1);
	else
		if (elements < n)
			for (int i = elements; i < n; ++i)
				push_front(0);
}


template<typename T>
void list<T>::resize(int n, T x)
{
	if (n <= 0)
	{
		cout << "Error! Cannot resize!" << endl;
		return;
	}

	if (elements > n)
		erase(n, elements - 1);

	Node* p = head;
	for (int i = 0; i < elements; ++i)
	{
		p->data = x;
		p = p->next;
	}

	if (elements < n)
		for (int i = elements; i < n; ++i)
			push_back(x);
}


template<typename T>
bool list<T>::contains(T x)
{
	Node* p = head;
	while (p != nullptr)
	{
		if (p->data == x)
			return true;
		p = p->next;
	}
	return false;
}


template<typename T>
void list<T>::sort()
{
	quick_sort(0, elements - 1);
}


template<typename T>
void list<T>::rsort()
{
	quick_rsort(0, elements - 1);
}


template<typename T>
bool list<T>::ascending()
{
	if (elements == 1)
		return true;

	T x = head->data;
	Node* p = head->next;
	while (p != nullptr)
	{
		if (x > p->data)
			return false;
		x = p->data;
		p = p->next;
	}
	return true;
}


template<typename T>
bool list<T>::descending()
{
	if (elements == 1)
		return true;

	T x = head->data;
	Node* p = head->next;
	while (p != nullptr)
	{
		if (x < p->data)
			return false;
		x = p->data;
		p = p->next;
	}
	return true;
}


template<typename T>
void list<T>::unique()
{
	if (elements == 1)
		return;

	if (elements == 2)
	{
		if (head->data == tail->data)
			pop_front();
		return;
	}

	if (!ascending() && !descending())
	{
		cout << "Error! The list is not sorted!" << endl;
		return;
	}

	Node* p = head->next;
	Node* q;
	while (p->next != nullptr)
	{
		q = p;
		while (q->next != nullptr && q->data == p->data)
			q = q->next;

		if (p->next != q)
		{
			destroy(p->next, q->prev);
			p->next = q;
			q->prev = p;
		}
		p = q;
	}

	if (head->data == head->next->data)
		pop_front();
	if (elements != 1 && tail->data == tail->prev->data)
		pop_back();
}


template<typename T>
void list<T>::insert_before(int i, T data)
{
	if (i < 0 || i >= elements)
	{
		cout << "Error! Cannot insert element!" << endl;
		return;
	}

	if (i == 0)
		push_front(data);
	else
	{
		Node* p = position(i);
		Node* a = new Node(p->prev, p, data);
		p->prev->next = a;
		p->prev = a;
	}

	++elements;
}


template<typename T>
void list<T>::insert_after(int i, T data)
{
	if (i < 0 || i >= elements)
	{
		cout << "Error! Cannot insert element!" << endl;
		return;
	}

	if (i == elements - 1)
		push_back(data);
	else
	{
		Node* p = position(i);
		Node* a = new Node(p, p->next, data);
		p->next->prev = a;
		p->next = a;
	}

	++elements;
}


template<typename T>
void list<T>::rinsert_before(int i, T data)
{
	if (i < 0 || i >= elements)
	{
		cout << "Error! Cannot insert element!" << endl;
		return;
	}

	if (i == 0)
		push_back(data);
	else
	{
		Node* p = rposition(i);
		Node* a = new Node(p, p->next, data);
		p->next->prev = a;
		p->next = a;
	}

	++elements;
}


template<typename T>
void list<T>::rinsert_after(int i, T data)
{
	if (i < 0 || i >= elements)
	{
		cout << "Error! Cannot insert element!" << endl;
		return;
	}

	if (i == elements - 1)
		push_front(data);
	else
	{
		Node* p = rposition(i);
		Node* a = new Node(p->prev, p, data);
		p->prev->next = a;
		p->prev = a;
	}

	++elements;
}


template<typename T>
void list<T>::insert_before(int i, int n, T x)
{
	if (i < 0 || i >= elements)
	{
		cout << "Error! Cannot insert element!" << endl;
		return;
	}
	if (n <= 0)
	{
		cout << "Error! List size must be at least 1" << endl;
		return;
	}
	Node* p;
	Node* q;

	if (i == 0)
	{
		push_front(x);
		p = head->next;
		--n;
	}
	else
		p = position(i);

	for (int i = 0; i < n; ++i)
	{
		q = new Node(p->prev, p, x);
		p->prev->next = q;
		p->prev = q;
		p = q;
	}

	elements += n;
}


template<typename T>
void list<T>::insert_after(int i, int n, T x)
{
	if (i < 0 || i >= elements)
	{
		cout << "Error! Cannot insert element!" << endl;
		return;
	}
	if (n <= 0)
	{
		cout << "Error! List size must be at least 1" << endl;
		return;
	}
	Node* p;
	Node* q;

	if (i == elements - 1)
	{
		push_back(x);
		p = tail->prev;
		--n;
	}
	else
		p = position(i);

	for (int i = 0; i < n; ++i)
	{
		q = new Node(p, p->next, x);
		p->next->prev = q;
		p->next = q;
		p = q;
	}

	elements += n;
}


template<typename T>
void list<T>::rinsert_before(int i, int n, T x)
{
	if (i < 0 || i >= elements)
	{
		cout << "Error! Cannot insert element!" << endl;
		return;
	}
	if (n <= 0)
	{
		cout << "Error! List size must be at least 1" << endl;
		return;
	}
	Node* p;
	Node* q;

	if (i == 0)
	{
		push_back(x);
		p = tail->prev;
		--n;
	}
	else
		p = rposition(i);

	for (int i = 0; i < n; ++i)
	{
		q = new Node(p, p->next, x);
		p->next->prev = q;
		p->next = q;
		p = q;
	}

	elements += n;
}


template<typename T>
void list<T>::rinsert_after(int i, int n, T x)
{
	if (i < 0 || i >= elements)
	{
		cout << "Error! Cannot insert element!" << endl;
		return;
	}
	if (n <= 0)
	{
		cout << "Error! List size must be at least 1" << endl;
		return;
	}
	Node* p;
	Node* q;

	if (i == elements - 1)
	{
		push_front(x);
		p = head->next;
		--n;
	}
	else
		p = rposition(i);

	for (int i = 0; i < n; ++i)
	{
		q = new Node(p->prev, p, x);
		p->prev->next = q;
		p->prev = q;
		p = q;
	}

	elements += n;
}


template<typename T>
void list<T>::erase(int i)
{
	if (head == nullptr)
	{
		cout << "Empty list! Cannot delete!" << endl;
		return;
	}
	if (i < 0 || i >= elements)
	{
		cout << "Error! Invalid position" << endl;
		return;
	}

	if (i == 0)
		pop_front();
	else
		if (i == elements - 1)
			pop_back();
		else
		{
			Node* p = position(i);
			p->prev->next = p->next;
			p->next->prev = p->prev;
			delete p;
			--elements;
		}
}


template<typename T>
void list<T>::erase(int begin, int end)
{
	if (head == nullptr)
	{
		cout << "Empty list! Cannot delete!" << endl;
		return;
	}

	if (begin < 0 || begin >= elements || end < 0 || end >= elements)
	{
		cout << "Error! Non-existent interval!" << endl;
		return;
	}

	if (begin > end)
		swap_pos(begin, end);

	if (begin == 0 && end == elements - 1)
	{
		list<T>::~list();
		return;
	}

	Node* p = position(begin);
	Node* q = position(end);

	if (begin == 0)
	{
		head = q->next;
		q->next->prev = nullptr;
	}
	else
		if (end == elements - 1)
		{
			tail = p->prev;
			p->prev->next = nullptr;
		}
		else
		{
			p->prev->next = q->next;
			q->next->prev = p->prev;
		}

	destroy(p, q);
	elements = elements - (end - begin + 1);
}


template<typename T>
void list<T>::rerase(int i)
{
	if (tail == nullptr)
	{
		cout << "Empty list! Cannot delete!" << endl;
		return;
	}
	if (i < 0 || i >= elements)
	{
		cout << "Error! Non-existent position!" << endl;
		return;
	}

	if (i == 0)
		pop_back();
	else
		if (i == elements - 1)
			pop_front();
		else
		{
			Node* p = rposition(i);
			p->prev->next = p->next;
			p->next->prev = p->prev;
			delete p;
			--elements;
		}
}


template<typename T>
void list<T>::rerase(int begin, int end)
{
	if (tail == nullptr)
	{
		cout << "Empty list! Cannot delete!" << endl;
		return;
	}

	if (begin < 0 || begin >= elements || end < 0 || end >= elements)
	{
		cout << "Error! Non-existent interval!" << endl;
		return;
	}

	if (begin > end)
		swap_pos(begin, end);

	if (begin == 0 && end == elements - 1)
	{
		list<T>::~list();
		return;
	}

	Node* p = rposition(begin);
	Node* q = rposition(end);

	if (begin == 0)
	{
		tail = q->prev;
		q->prev->next = nullptr;
	}
	else
		if (end == elements - 1)
		{
			head = p->next;
			p->next->prev = nullptr;
		}
		else
		{
			q->prev->next = p->next;
			p->next->prev = q->prev;
		}

	destroy(q, p);
	elements = elements - (end - begin + 1);

}

template<typename T>
void list<T>::read()
{
	cout << "elements = "; cin >> elements; cout << endl;
	T data;
	cin >> data;
	Node* p = new Node(nullptr, nullptr, data);
	head = p;
	tail = p;

	for (int i = 1; i < elements; ++i)
	{
		cin >> data;
		p = new Node(tail, nullptr, data);
		p->prev->next = p;
		tail = p;
	}
}

template<typename T>
inline void list<T>::read(const char* input)
{
	ifstream fin(input);
	fin >> elements;
	T data;
	fin >> data;
	Node* p = new Node(nullptr, nullptr, data);
	head = p;
	tail = p;

	for (int i = 1; i < elements; ++i)
	{
		fin >> data;
		p = new Node(tail, nullptr, data);
		p->prev->next = p;
		tail = p;
	}
	fin.close();
}

template<typename T>
void list<T>::print()
{
	if (elements == 0)
		return;

	Node* p = head;
	while (p != nullptr)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

template<typename T>
inline void list<T>::print(const char* output)
{
	ofstream fout(output);
	Node* p = head;
	while (p != nullptr)
	{
		fout << p->data << " ";
		p = p->next;
	}
	fout.close();
}

template<typename T>
inline void list<T>::rprint()
{
	if (elements == 0)
		return;

	Node* p = tail;
	while (p != nullptr)
	{
		cout << p->data << " ";
		p = p->prev;
	}
	cout << endl;
}

template<typename T>
inline void list<T>::rprint(const char* output)
{
	ofstream fout(output);
	Node* p = tail;
	while (p != nullptr)
	{
		fout << p->data << " ";
		p = p->prev;
	}
	fout.close();
}

//DOUBLY_LINKED_LIST_HEADER
#endif  