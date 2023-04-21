#include <iostream>
#include <stdbool.h>
#include "Classes.h"

using namespace std;

void ListTest ();
void QueueTest ();
void StackTest ();

int main (void)
{
	cout << "Select one structure: " << endl;
	cout << "1 - List : " << endl;
	cout << "2 - Queue : " << endl;
	cout << "3 - Stack : " << endl;
	
	int classSelector = 0;
	cin >> classSelector;

	if (classSelector < 0 || classSelector > 3)
		cout << "Invalid class number" << endl;

	else
	{
		// List.
		if (classSelector == 1)
			ListTest();

		// Queue.
		if (classSelector == 2)
			QueueTest ();

		// Stack.
		if (classSelector == 3)
			StackTest();
	}	
}

void ListTest ()
{
	StaticList staticList = StaticList (0, 0, 0, 0);

	if (staticList.isEmpty())
		cout << "Empty List" << endl;
	else
		cout << "List isn't empty" << endl;

	for (int i = 0; i < 10; i++)
	{
		staticList.insertElement (i + 10);
	}

	staticList.printList ();

	int removedValue;
	staticList.removeElement (&removedValue);
	staticList.printList ();
}

void QueueTest ()
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
}

void StackTest ()
{
	StaticStack staticStack = StaticStack (0, 0);

	if (staticStack.isEmpty())
		cout << "Empty Stack!" << endl;
	
	else
		cout << "Stack isn't empty!" << endl;

	for (int i = 0; i < 9; i++)
	{
		staticStack.push(i + 10);
	}

	if (staticStack.isFull())
		cout << "Full Stack!" << endl;
	
	else
		cout << "Stack isn't full!" << endl;

	staticStack.printStack();

	int removeValue;
	staticStack.pop (&removeValue);
	staticStack.pop (&removeValue);

	int topValue = staticStack.getTop(&topValue);
	cout << "getTop: " << topValue << endl;

	staticStack.pop (&removeValue);

	staticStack.printStack();
}