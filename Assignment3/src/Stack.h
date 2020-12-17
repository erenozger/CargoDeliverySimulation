#ifndef STACK_H_
#define STACK_H_
#include <iostream>
using namespace std;

template<typename T>
class Stack {
public:
	Stack() :_head(nullptr), _size(0) {};



	bool isEmpty() const;
	int size() const;

	//Push: Place item on top of the stack
	void push(const T &newItem);
	//Top: Take a look at the topmost item without removing it
	void getTop(T &stackTop) const;
	//Pop: Remove item from the top of the stack
	void pop();

private:
	struct ListNode {
		T item;
		ListNode *next;
	};
	ListNode *_head;
	int _size;
};

template <typename T>
int Stack<T>::size() const {
	return _size;
}

template <typename T>
void Stack<T>::push(const T &newItem) {
	cout<<"push isteði geldi "<<endl;
}






#endif /* STACK_H_ */
