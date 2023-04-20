#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pilha.h"

int test ();

bool _DEBUG_ = false;
bool _INFO_ = true;

#define MAX_LIMIT 301

int main ()
{
	int expresions = 0;

	scanf("%d", &expresions);

	if (expresions < 1)
	{
		printf("Error. Input invalido do numero de expressoes.");
		return 1;
	}

	for (int i = 0; i < expresions; i++)
	{
		printf("%d\n", test ());
	}

	return 0;
}

int test ()
{
	Pilha* Stack = pilha_criar();
	
	char String [200] = {'\0'};
	while (getchar() != '\n');
	scanf("%[^\n]", String);

	char Output = 0;
	int abriu = 0;
	int fechou = 0;

	for (int i = 0; String[i] != '\0'; i++)
	{
		if (String[i] == '[' || String[i] == '{' || String[i] == '(')
		{
			pilha_empilhar (Stack, String[i]);
		    abriu++;
		}

		if ((String[i] == ')' || String[i] == '}' || String[i] == ']'))
		{
			if (abriu == 0 || abriu <= fechou)
			{
				pilha_destruir (&Stack);
				return -3;
			}
	
			pilha_desempilhar (Stack, &Output);
		    fechou++;

			if((Output == '(' && String[i] != ')') || (Output == '{' && String[i] != '}') || (Output == '[' && String[i] != ']'))
			{
				pilha_destruir (&Stack);
			    return -1;
			}
		}
	}

	pilha_destruir (&Stack);

	if (abriu > fechou)
	    return -2;
	if (fechou > abriu)
	    return -3;

	return 1;
}
