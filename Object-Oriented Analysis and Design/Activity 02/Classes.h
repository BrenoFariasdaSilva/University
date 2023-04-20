using namespace std;

#define SIZE 100

typedef int ElementType;

// List.

class List
{
	protected:
		int quantity = 0;
		int size = SIZE; 

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
		ElementType vector[SIZE] = {0};

	public:
		StaticList (int _start, int _end, int _quantity, int _firstElement);
		~StaticList ();
		bool insertElement (int insertValue);
		bool removeElement (int* removedValue);
		void printList ();
};

// Queue.

class Queue
{
	protected:
		int quantity = 0;
		int size = SIZE; 

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
		ElementType vector [SIZE];
	
	public:
		StaticQueue (int _quantity, int _firstElement);
		~StaticQueue ();
		bool enqueue (int element);
		bool dequeue (int* element);
		int front();
		int rear();
		void printQueue();
};

// Stack.

class Stack
{
	protected:
		int topIndex = 0;
		int size = SIZE;

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
		ElementType vector[SIZE] = {0};

	public: 
		StaticStack (int _topIndex, int _firstElement);
		~StaticStack ();
		bool push (int insertValue);
		bool pop (int* removeValue);
		bool getTop (int* topValue);
		void printStack ();
};