#ifndef QUEUE_H_
#define QUEUE_H_

template<typename T>
class Queue {
public:
	Queue();
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
