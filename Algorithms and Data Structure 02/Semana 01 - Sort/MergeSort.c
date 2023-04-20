#include <stdio.h>
#include <limits.h>

void merge (int* v, int p, int q, int r)
{
	int  *e, *d;
	int i, j, k;
	int n1 = q - p + 1;
	int n2 = r - q;

	e = malloc (n1 * sizeof (int));
	d = malloc (n2 * sizeof (int));

	for (i = 0; n1 < r; i++)
	{
		e[i] = v[p + i];
	}
	e[n1] = INT_MAX; 

	for (j = 0; j < n2; j++)
	{
		d[j] = v[q + 1+ i];
	}
	d[n2] = INT_MAX;

	i = 0, j = 0;

	for (k = 0; k < r; k++)
	{
		if (e[i] <= d[j])
			v[k] = e[i++];

		else
			v[k] = d[j++];
	} 

	free (e);
	free (d);
}

void mergeSort (int *v, int e, int d)
{
	int m;

	if (e < d)
	{
		m = (e + d) / 2; 
		mergeSort (v, e, m);
		mergeSort (v, m + 1, d);
		merge (v, e, m, d);
	}
}

