#include <iostream>
#include <stdbool.h>

using namespace std;

#define VECTOR_SIZE 100

typedef int ElementType;

class Queue
{
	protected:
		int quantity = 0;
		int size = VECTOR_SIZE; 

	public:
		Queue (int _quantity);
		~Queue ();
		bool isEmpty ();
		bool isFull ();
		virtual void printQueue();
};

class StaticQueue : public Queue 
{
	private:
		int startIndex = 0;
		ElementType vector [VECTOR_SIZE];
	
	public:
		StaticQueue (int _quantity, int _firstElement);
		~StaticQueue ();
		bool enqueue (int element);
		bool dequeue (int* element);
		int front();
		int rear();
		void printQueue();
};

int main (void)
{
	StaticQueue staticQueue = StaticQueue (0, 0);

	if (staticQueue.isEmpty())
		cout << "Empty Queue!" << endl;
	
	else
		cout << "Queue isn't empty!" << endl;

	for (int i = 0; i < 9; i++)
	{
		staticQueue.enqueue(i + 10);
	}

	if (staticQueue.isFull())
		cout << "Full Queue!" << endl;
	
	else
		cout << "Queue isn't full!" << endl;

	cout << "Front staticQueue: " << staticQueue.front() << endl;
	cout << "Rear staticQueue: " << staticQueue.rear() << endl;

	staticQueue.printQueue();

	int removedElement;
	if (staticQueue.dequeue(&removedElement))
		cout << "Removed element: " << removedElement << endl;

	else
		cout << "ERROR: Queue is empty!" << endl;

	staticQueue.printQueue();

	return 0;
}

StaticQueue:: StaticQueue (int _quantity, int _firstElement) : Queue (_quantity)
{
	enqueue(_firstElement);
}

StaticQueue:: ~StaticQueue ()
{
	cout << "StaticQueue Deleted" << endl;
}

bool StaticQueue:: enqueue (int element)
{
	if (quantity == VECTOR_SIZE)
		return false;

	vector[quantity++] = element;

	return true;
}

bool StaticQueue:: dequeue (int* element)
{
	if (quantity == 0)
		return false;

	*element = vector[startIndex++];
	quantity--;

	return true;	
}

int StaticQueue:: front()
{
	return (vector[startIndex]);
}

int StaticQueue:: rear()
{
	return (vector[quantity - 1]);
}

void StaticQueue:: printQueue()
{
	Queue:: printQueue();
	
	cout << "Static Queue: ";
	for (int i = startIndex; i < quantity; i++)
	{
		cout << vector [i] << " ";
	}
	cout << endl;
}

Queue:: Queue (int _quantity)
{
	quantity = _quantity;
}

Queue:: ~Queue ()
{
	cout << "Queue Deleted" << endl;
}

bool Queue:: isEmpty ()
{
	return (quantity == 0);
}

bool Queue:: isFull ()
{
	return (quantity == VECTOR_SIZE);
}

void Queue:: printQueue()
{
	cout << "Queue Quantity: " << quantity << endl;
}