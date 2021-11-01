#include <stdio.h>

int MDC (int x, int y);

int main ()
{
	int x = 0, y = 0;

	printf("Type two int numbers: ");
	scanf("%d %d", &x, &y);

	int result = MDC (x, y);

	printf("MDC of %d and %d is: %d \n", x, y, result);

	return 0;
}

int MDC (int x, int y)
{
	if ((y <= x) && (x % y == 0))
	{
		return y;
	}

	else if (x < y)
	{
		return (MDC (y, x));
	}

	else
	{
		return (MDC (y, x % y));
	}
}
