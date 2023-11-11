#include <stdio.h>

void binario (int x);

int main ()
{
	int number = 0;

	printf("Digite um valor: ");
	scanf("%d", &number);

	binario (number);

	return 0;
}

void binario (int x)
{
	if (x < 2)
	{
		printf("%d", x);
	}

	else
	{
		binario (x / 2);
		printf("%d", x % 2);
	}
}