#ifndef QUEUE_H_
#define QUEUE_H_
#include <iostream>
template<typename T>
class Queue {
public:
	Queue(): _size(0), _lastNode(NULL){};
	~Queue();
	bool isEmpty() const;
	int size() const;
	//Enqueue: Items are added to the back of the queue
	void enqueue(const T &newItem);
	//Dequeue: Items are removed from the front of the queue
	void dequeue();
	//Get Front: Take a look at the first item
	void getFront(T &queueTop) const;

private:
	struct QueueNode {
		T item;
		QueueNode *next;
	};
	int _size;
	QueueNode *_lastNode;
};

#endif /* QUEUE_H_ */
