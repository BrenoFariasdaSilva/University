#include <stdio.h>

int COM (int n, int k);

int main ()
{
	int n = 0, k = 0;

	printf("Type two int numbers: ");
	scanf("%d %d", &n, &k);

	int result = COM (n, k);

	printf("COMB of %d and %d is: %d \n", n, k, result);

	return 0;
}

int COM (int n, int k)
{
	if (k > n)
	{
		return 0;
	}

	else if (k == 1)
	{
		return n;
	}

	else
	{
		return (COM (n - 1, k) + COM (n - 1, k - 1));
	}
}
