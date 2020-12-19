#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include <iostream>
using namespace std;

template<typename T>
class LinkedList {
public:
	LinkedList() :
			_headLL(nullptr), _searchLL(nullptr), _truckLL(nullptr), _size(0) {
	}
	;
	bool isEmpty() const;
	int size() const;
	void insertToLL(const T &newItem);
	void deleteFromLL(int deleteIndexm);

	T getLLItem(int index) const;

private:
	struct LinkedListNode {
		T item;
		LinkedListNode *prev;
		LinkedListNode *next;
	};
	LinkedListNode *_headLL;
	LinkedListNode *_searchLL;
	LinkedListNode *_truckLL;
	int _size;
};

template<typename T>
bool LinkedList<T>::isEmpty() const {
	if (_headLL == nullptr) {
		return true;
	} else
		return false;
}

template<typename T>
int LinkedList<T>::size() const {
	return _size;
}

template<typename T>
void LinkedList<T>::insertToLL(const T &newItem) {
	LinkedListNode *tempNode = new LinkedListNode;

	if (isEmpty()) {
		tempNode->item = newItem;
		tempNode->next = nullptr;
		tempNode->prev = nullptr;
		_headLL = tempNode;
		_headLL->next = tempNode;
		_headLL->prev = tempNode;
		_truckLL = _headLL;
		_size++;
	} else {
		tempNode->item = newItem;
		tempNode->next = _headLL;
		tempNode->prev = _headLL->prev;
		_headLL->prev->next = tempNode;
		_headLL->prev = tempNode;
		_size++;
	}
}
template<typename T>
void LinkedList<T>::deleteFromLL(int deleteIndex) {
	LinkedListNode *tempNode = new LinkedListNode;
	_searchLL = _truckLL->next;
	if (_truckLL == _truckLL->next) {
		free(_searchLL);
		free(_headLL);
		free(_truckLL);
		_size--;
		_searchLL = nullptr;
		_headLL = nullptr;
		_truckLL = nullptr;

	} else {
		for (int i = 0; i < deleteIndex; i++) {
			if(_searchLL -> next == _truckLL){
				break;
			}else{
				_searchLL = _searchLL->next;
			}

		}

		_searchLL->prev->next = _searchLL->next;
		_searchLL->next->prev = _searchLL->prev;
		free(_searchLL);
		_searchLL = nullptr;
		_size--;

	}


}
template<typename T>
T LinkedList<T>::getLLItem(int index) const {
	LinkedListNode *tempNode = new LinkedListNode;
	tempNode = _truckLL;
	if (index == 0) {
		return _truckLL->item;

	} else {
		for (int i = 0; i < index; i++)
			tempNode = tempNode->next;
		return tempNode->item;
	}

}
#endif /* LINKEDLIST_H_ */
