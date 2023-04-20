#include <stdio.h>
#include <limits.h>

void troca (int* v, int i, int j)
{
	int hold = v[j];
	v[j] = v[i];
	v[i] = hold;
}

int partition (int* v, int p, int r)
{
	int x;
	int i, j;

	x = v[r];
	i = p - 1;

	for (j = p; j < r; j++)
	{
		if (v[j] <= x)
		{
			i++;
			troca (v, i, j);
		}
	}

	troca (v, i + 1, r);
	return i + 1;
}

void quickSort (int* v, int e, int d)
{
	int q;

	if (e < d)
	{
		q = partition (v, e, d);
		quickSort(v, e, q - 1);
		quickSort(v, q + 1, d);
	}
}

int main ()
{
	int vector[5] = {1, 2, 3, 4, 5};
	quickSort(vector, 0, 4);
	printf("vector: ");
	for (int i = 0; i < 5; i++) 
	{
		printf("%d", vector[i]);
	}
}