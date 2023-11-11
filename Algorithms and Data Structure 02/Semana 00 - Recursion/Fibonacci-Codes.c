#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void Slow_Fibonacci (int n);

int main ()
{
	int x = 0;

	Slow_Fibonacci(x);

	return 0;
}

void Slow_Fibonacci (int n)
{
	if (n <= 1)
	{
		return n;
	}

	return Slow_Fibonacci(n-1) + fib(n-2);
}