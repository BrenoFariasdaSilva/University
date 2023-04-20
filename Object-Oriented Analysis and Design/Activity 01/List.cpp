#include <iostream>
#include <stdbool.h>

#define SIZE 100

using namespace std;

class List
{
	private:
		int start = 0;
		int end = 0;
		int quantity = 0;
		int vector[SIZE] = {0};

	public:
		List (int _start, int _end, int _quantity);
		~List();
		void insertElement (int insertValue);
		void removeElement (int* removedValue);
		void printList ();
};

int main ()
{
	List firstList = List(0, 0, 0);

	firstList.insertElement(1);
	firstList.insertElement(2);
	firstList.insertElement(3);
	firstList.printList();

	firstList.~List();

	return 0;
}

List:: List (int _start, int _end, int _quantity)
{
	start = _start;
	end = _end;
	quantity = _quantity;
}

List:: ~List()
{
	cout << "List Destroyer" << endl;
}

void List:: insertElement (int insertValue)
{
	vector[end++] = insertValue;
	quantity++;
}

void List:: removeElement (int* removedValue)
{
	*removedValue = vector[start++];
}

void List:: printList ()
{
	for (int i = 0; i < quantity; i++)
	{
		cout << vector[start + i] << endl;
	}
}