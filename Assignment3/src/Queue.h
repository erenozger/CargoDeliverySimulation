#ifndef QUEUE_H_
#define QUEUE_H_
#include <iostream>
using namespace std;
template<typename T>
class Queue {
public:
	Queue(): _size(0), _frontNode(nullptr), _rearNode(nullptr){};
	~Queue();
	bool isEmpty() const;
	int size() const;
	//Enqueue: Items are added to the back of the queue
	void enqueue(const T &newItem);
	//Dequeue: Items are removed from the front of the queue
	void dequeue();
	//Get Front: Take a look at the first item
	void getFront(T &queueTop) const;

	//Get one cargo truck from its index in queue position.
	T getTruck(int index) const;

private:
	struct QueueNode {
		T item;
		QueueNode *next;
	};
	int _size;
	QueueNode *_frontNode;
	QueueNode *_rearNode;
};

template<typename T>
Queue<T>::~Queue(){
	while(_frontNode != nullptr) {
	        dequeue();
	    }
}

//Checks if the QUEUE is empty.
template<typename T>
bool Queue<T>::isEmpty() const{
	if(_rearNode == nullptr){
		return true;
	}else
		return false;
}
template<typename T>
int Queue<T>::size() const{
	return _size;
}

template<typename T>
void Queue<T>::enqueue(const T &newItem){
	QueueNode *tempNode = new QueueNode;

	if(isEmpty()){
		_rearNode = tempNode;
		_rearNode->next = nullptr;
		_rearNode->item = newItem;
		_frontNode = _rearNode;
		_size++;
	}else{
		_rearNode->next = tempNode;
		tempNode->item = newItem;
		tempNode->next = nullptr;
		_rearNode = tempNode;
		_size++;
	}

}

template<typename T>
void Queue<T>::dequeue(){
	QueueNode *tempNode = new QueueNode;
	tempNode = _frontNode;
	if(_frontNode == nullptr){
		cout<<(
						"The queue is already empty, nothing to pop.")<<endl;
	}else{
		if(tempNode ->next != nullptr){
			tempNode = tempNode->next;
			free(_frontNode);
			_frontNode = tempNode;
			_size--;
		}else{
			free(_frontNode);
			_frontNode = nullptr;
			_rearNode = nullptr;
			_size--;
		}
	}
}

template<typename T>
void Queue<T>::getFront(T &queueTop) const{
	queueTop = _frontNode->item;
}
template<typename T>
T Queue<T>::getTruck(int index) const{
	QueueNode *tempNode = new QueueNode;
	tempNode = _frontNode;
	if(index == 0){
		return _frontNode->item;
	}else {
		for(int i = 0 ; i<index;i++)
			tempNode = tempNode->next;
		return tempNode->item;


	}
}


#endif /* QUEUE_H_ */
