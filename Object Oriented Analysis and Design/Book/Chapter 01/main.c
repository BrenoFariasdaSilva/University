#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

int getop(struct Stack* s, int* n1, int* n2)
{
	if (empty(s))
	{
		printf("empty stack!\n");
		return 0;
	}

	*n2 = pop(s);

	if (empty(s))
	{
		push(s, *n2);
		printf("two operands needed!\n");
		return 0;
	}

	*n1 = pop(s);

	return 1;
}

int main(void)
{
	struct Stack* s = createStack();

	while (1)
	{
		char str[31];
		int i;

		printf("> ");
		gets(str);

		if (sscanf(str, " %d", &i)==1)
		{
			push(s, i);
		}

		else
		{
			int n1, n2;
			char c;

			sscanf(str, "%c", &c);

			switch(c)
			{
				case '+':
				if (getop(s, &n1, &n2)) push(s, n1+n2);
				break;

				case '-':
				if (getop(s, &n1, &n2)) push(s, n1-n2);
				break;

				case '/':
				if (getop(s, &n1, &n2)) push(s, n1/n2);
				break;

				case '*':
				if (getop(s, &n1, &n2)) push(s, n1*n2);
				break;

				case 'q':
				return 0;

				default:
				printf("error\n");
			}
		}

		{
			int i;
			for (i=0; i<s->top; i++)
			printf("%d:%6d\n", i, s->elems[i]);
		}
	}
}