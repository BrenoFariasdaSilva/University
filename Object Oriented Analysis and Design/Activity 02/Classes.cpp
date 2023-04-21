#include "Classes.h"

// List.

StaticList::StaticList (int _start, int _end, int _quantity, int _firstElement) : List(_quantity)
{
	start = _start;
	end = _end;
	insertElement(_firstElement);
}

StaticList:: ~StaticList ()
{
	cout << "Static Vector Destroyed" << endl;
}

void StaticList:: printList ()
{
	List:: printList ();

	cout << "Static Vector: ";
	for (int i = start; i < quantity; i++)
	{
		cout << vector[start + i] << " ";
	}
	cout << endl;
}

bool StaticList:: insertElement (int insertValue)
{
	if (quantity >= size)
		return false;

	vector[end++] = insertValue;
	quantity++;
	return true;
}

bool StaticList:: removeElement (int* removedValue)
{
	if (quantity <= 0)
		return false;

	*removedValue = vector[start++];
	quantity--;
	return true;
}

List:: List(int _quantity)
{	
	quantity = _quantity;
}

List:: ~List()
{
	cout << "List Destroyed" << endl;
}

bool List:: isEmpty()
{
	return (quantity == 0);
}

bool List:: isFull()
{
	return (quantity == size);
}

void List:: printList ()
{
	cout << "List Quantity: " << quantity << endl;
}

// Queue.

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
	if (quantity == VECTORSIZE)
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
	return (quantity == VECTORSIZE);
}

void Queue:: printQueue()
{
	cout << "Queue Quantity: " << quantity << endl;
}

// Stack.

StaticStack:: StaticStack (int _topIndex, int _firstElement) : Stack (_topIndex)
{
	push (_firstElement);
}

StaticStack:: ~StaticStack ()
{
	cout << "StaticStack Deleted" << endl;
}

bool StaticStack:: push (int insertValue)
{
	if (topIndex == size)
		return false;

	vector[topIndex++] = insertValue;
	return true;
}

bool StaticStack:: pop (int* removeValue)
{
	if (topIndex == 0)
		return false;

	*removeValue = vector[topIndex--];
	return true;
}

bool StaticStack:: getTop (int* topValue)
{
	if (topIndex == 0)
		return false;

	*topValue = vector[topIndex];
	return true;
}

void StaticStack:: printStack ()
{
	Stack:: printStack ();

	cout << "StaticStack: ";
	for (int i = topIndex - 1; i >= 0; i--)
	{
		cout << vector[i] << " ";
	}
	cout << endl;
}

Stack:: Stack (int _topIndex)
{
	topIndex = _topIndex;
}

Stack:: ~Stack ()
{
	cout << "Stack Deleted" << endl;
}

bool Stack:: isEmpty ()
{
	return (topIndex == 0);
}

bool Stack:: isFull ()
{
	return (topIndex == size - 1);
}

void Stack:: printStack ()
{
	cout << "Stack Quantity: " << topIndex << endl;
}