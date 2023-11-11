#include <stdio.h>

int soma (int x, int y);

int main ()
{
	int number = 0, y = 0, result = 0;

	printf("Digite dois valores: ");
	scanf("%d %d", &number, &y);

	result = soma (number, y);

	printf("Resultado: %d", result);

	return 0;
}

int soma (int x, int y)
{
	if (x == 0 || y == 0)
	{
		return 0;
	}

	if (x == 1)
	{
		return y;
	}

	return (y + soma (x-1, y));
}