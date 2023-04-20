#include <stdlib.h>
#include "stack.h"

void push (struct Stack*s, int i)
{
	s->elems[s->top++] = i;
}

int pop (struct Stack*s)
{
	return s->elems[--(s->top)];
}

int empty (struct Stack*s)
{
	return s->top == 0;
}

struct Stack* createStack (void)
{
	struct Stack* s = (struct Stack*) malloc (sizeof(struct Stack));
	s->top = 0;
	return s;
}