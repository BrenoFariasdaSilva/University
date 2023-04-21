#include <iostream>
#include <stdbool.h>

using namespace std;

#define VECTORSIZE 100

typedef int ElementType;

class Queue
{
	private:
		ElementType vector [VECTORSIZE];
		int size = VECTORSIZE; 
		int quantity = 0;
		int startIndex = 0;
		int endIndex = 0;

	public:
	bool insertElement (int element);
	bool removeElement (int* element);
	void printQueue();
};

int main (void)
{
	Queue firstQueue; // Object from Queue's class

	int element = 1;

	cout << "Queue without any insertion: ";

	firstQueue.printQueue();

	cout << "\nQueue after any insertion: ";
	firstQueue.insertElement(element++);
	firstQueue.insertElement(element++);
	firstQueue.insertElement(element++);
	firstQueue.printQueue();

	return 0;
}

bool Queue:: insertElement (int element)
{
	if (quantity == VECTORSIZE)
	{
		cout << "Vector Storage is full";
		return false;
	}

	vector[endIndex++] = element;
	quantity++;

	return true;
}

bool Queue:: removeElement (int* element)
{
	if (quantity == 0)
	{
		cout <<"Queue is empty!" << endl;
		return false;
	}

	*element = vector[startIndex++];

	if (quantity == 1)
	{
		startIndex = 0;
		endIndex = 0;
	}

	quantity--;
	return true;	
}

void Queue:: printQueue()
{
	for (int i = 0; i < quantity; i++)
	{
		cout << vector[startIndex + i] << " ";
	}

	cout << endl;
}