#include <iostream>
#include <stdbool.h>

using namespace std;

#define VECTOR_SIZE 100

typedef int ElementType;

class Stack
{
	protected:
		int topIndex = 0;
		int size = VECTOR_SIZE;

	public:
		Stack (int _topIndex);
		~Stack ();
		bool isEmpty ();
		bool isFull ();
		virtual void printStack ();
};

class StaticStack : public Stack 
{
	private:
		ElementType vector[VECTOR_SIZE] = {0};

	public: 
		StaticStack (int _topIndex, int _firstElement);
		~StaticStack ();
		bool push (int insertValue);
		bool pop (int* removeValue);
		bool getTop (int* topValue);
		void printStack ();
};

int main (void)
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