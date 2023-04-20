#include <stdio.h>

void Fibonacci (int x, int y);

int main ()
{
	int x = 0, y = 1;

	printf("%d %d ", x, y);

	Fibonacci (x, y);

	return 0;
}

void Fibonacci (int x, int y)
{
	if (x + y > 1000)
	{
		return;
	}

	int sum = x + y;
	printf("%d ", sum);
	x = y;
	y = sum;

	return (Fibonacci(x, y));
}

// void Fibonacci (int x, int y);

// int main ()
// {
// 	int x = 0, y = 1;

// 	printf("%d %d ", x, y);

// 	Fibonacci (x, y);

// 	return 0;
// }

// void Fibonacci (int x, int y)
// {
// 	if (x + y > 1000)
// 	{
// 		return;
// 	}

// 	int sum = x + y;
// 	printf("%d ", sum);
// 	x = y;
// 	y = sum;

// 	return (Fibonacci(x, y));
// }