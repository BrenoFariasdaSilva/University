#include <stdio.h>

int sucessor (int x);

int main ()
{
	int number = 0, result = 0;

	printf("Digite um valor: ");
	scanf("%d", &number);

	result = sucessor (number);

	printf("Resultado: %d", result);

	return 0;
}

int sucessor (int x)
{
	if (x == 10)
	{
		return 10;
	}
	return (x + sucessor (x+1));
}