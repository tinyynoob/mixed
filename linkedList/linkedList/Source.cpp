#include<iostream>
using namespace std;

template <class T> class Node {
	T data;
	Node<T>* next;
};

template <class T> class List {
private:
	int length;
	Node<T>* head;	// ?
public:
	~List() {

	}
	int getLength();
	void addTail(T value);
	void addAt(int at, T value);
	void deleteTail();
	void deleteAt(int at);
};

int main()
{

	return 0;
}