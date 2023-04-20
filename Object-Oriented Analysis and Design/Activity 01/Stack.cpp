#include <iostream>
#include <stdbool.h>

using namespace std;

#define VECTORSIZE 100

typedef int ElementType;

class Stack
{
	private:
		int size = VECTORSIZE;
		int topIndex = 0;
		ElementType vector[VECTORSIZE] = {0};

	public:
	bool push (int insertValue);
	bool pop (int* removeValue);
	bool getTop (int* topValue);
	bool empty ();
	void printStack ();
};

int main (void)
{
	Stack firstStack;

	firstStack.push(1);
	firstStack.push(2);
	firstStack.push(3);

	cout << "Push test: " << endl;
	firstStack.printStack();

	cout << "Pop test: " << endl;
	int removedElement = 0;
	firstStack.pop(&removedElement);

	firstStack.printStack();
}

bool Stack:: push (int insertValue)
{
	if (topIndex == size)
	{
		cout << "Stack is full";
		return false;
	}

	vector[topIndex++] = insertValue;
	return true;
}

bool Stack:: pop (int* removeValue)
{
	if (topIndex == 0)
	{
		cout << "Stack is empty";
		return false;
	}

	*removeValue = vector[topIndex--];
	return true;
}

bool Stack:: getTop (int* topValue)
{
	if (topIndex == 0)
	{
		cout << "Stack is empty";
		return false;
	}

	*topValue = vector[topIndex];
	return true;
}

bool Stack:: empty ()
{
	return (topIndex == 0);
}

void Stack:: printStack ()
{
	for (int i = topIndex - 1; i >= 0; i--)
	{
		cout << vector[i] << " ";
	}
	cout << endl;
}