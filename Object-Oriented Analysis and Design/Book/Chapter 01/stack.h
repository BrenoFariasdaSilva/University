#ifndef stack_h

#define stack_h
#define MAX 50

struct Stack 
{
	int top;
	int elems[MAX];

	void push (struct Stack* s, int i);
	// Create Pointer of function
};

void push (struct Stack* s, int i);
int pop (struct Stack* s);
int empty (struct Stack* s);
struct Stack* createStack (void);

#endif