#include <iostream>
#include <stdbool.h>

// Develop: InsertEnd and InsertStart, RemoveEnd and RemoveStart.

#define VECTOR_SIZE 100

using namespace std;

class List
{
	protected:
		int quantity = 0;
		int size = VECTOR_SIZE; 

	public:
		List(int _quantity);
		~List();
		bool isEmpty();
		bool isFull();
		virtual void printList ();
};

class StaticList : public List
{
	private:
		int start = 0;
		int end = 0;
		int vector[VECTOR_SIZE] = {0};

	public:
		StaticList (int _start, int _end, int _quantity, int _firstElement);
		~StaticList ();
		bool insertElement (int insertValue);
		bool removeElement (int* removedValue);
		void printList ();
};

int main ()
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

	return 0;
}

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