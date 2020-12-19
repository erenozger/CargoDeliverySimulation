#ifndef STACK_H_
#define STACK_H_
#include <iostream>

using namespace std;

template<typename T>
class Stack {
public:
	Stack() :
			_head(nullptr), _size(0) {
	}
	;
	~Stack();
	bool isEmpty() const;
	int size() const;

	//Push: Place item on top of the stack
	void push(const T &newItem);
	//Top: Take a look at the topmost item without removing it
	void getTop(T &stackTop) const;
	//Pop: Remove item from the top of the stack
	void pop();

	T getCargoPackage(int index) const;

private:
	struct ListNode {
		T item;
		ListNode *next;
	};
	ListNode *_head;
	int _size;
};


template<typename T>
Stack<T>::~Stack() {
    while(_head != nullptr) {
        pop();
    }
}
template<typename T>
bool Stack<T>::isEmpty() const {
	if (_head == nullptr) {
		return true;
	} else {
		return false;
	}

}
template<typename T>
int Stack<T>::size() const {
	return _size;
}

template<typename T>
void Stack<T>::push(const T &newItem) {
	ListNode *tempNode = new ListNode;

	if (isEmpty()) {
		tempNode->item = newItem;
		tempNode->next = nullptr;
		_head = tempNode;
		_size++;

	} else {
		tempNode->item = newItem;
		tempNode->next = _head;
		_head = tempNode;
		_size++;
	}

}

template<typename T>
void Stack<T>::getTop(T &stackTop) const {
	stackTop = _head->item;

}

template<typename T>
void Stack<T>::pop() {
	ListNode *tempNode = new ListNode;
	if (_head == nullptr) {
		cout<<("The list is already empty, nothing to pop.")<<endl;
	}

	tempNode = _head;
	_head = _head->next;
	free(tempNode);
	_size--;
}

template<typename T>
T Stack<T>::getCargoPackage(int index) const {

	ListNode *tempNode = new ListNode;
	tempNode = _head;
	if (index == 0) {
		return _head->item;

	} else {
		for (int i = 0; i < index; i++)
			tempNode = tempNode->next;
		return tempNode->item;
	}

}
#endif /* STACK_H_ */
