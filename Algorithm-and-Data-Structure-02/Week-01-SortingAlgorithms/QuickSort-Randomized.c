#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 50000

int* randomVector(int n, int max, int seed);
void troca (int* vector, int i, int j);
int randomPartition (int* vector, int startIndex, int endIndex);
void randomQuickSort (int* vector, int left, int right);

int main (void)
{
	int* vector = randomVector (SIZE, SIZE * 100, 42);
	randomQuickSort(vector, 0, SIZE - 1);

	double start_t = clock();
	randomQuickSort(vector, 0, SIZE - 1);
	double end_t = clock();
	double timeLapse = (end_t - start_t) / CLOCKS_PER_SEC;

	printf("Time Lapse: %f \n", timeLapse);

	return 0;
}

int* randomVector(int n, int max, int seed)
{
	int* vector = malloc(n * sizeof(int));

	srand (seed);
	for (int i = 0; i < SIZE; i++) 
		vector[i] = rand () % max;

	return vector;
}

void troca (int* vector, int i, int j)
{
	int hold = vector[i];
	vector[i] = vector[j];
	vector[j] = hold;
}

int randomPartition (int* vector, int startIndex, int endIndex)
{
	int pivot;
	int i, j;

	int randomIndex = startIndex + rand () % (endIndex - startIndex);
	troca (vector, randomIndex, endIndex);

	pivot = vector[endIndex];
	i = startIndex - 1;

	for (j = startIndex; j < endIndex; j++)
	{
		if (vector[j] <= pivot)
		{
			i++;
			troca (vector, i, j);
		}
	}

	troca (vector, i + 1, endIndex);
	return i + 1;
}

void randomQuickSort (int* vector, int left, int right)
{
	int q;

	if (left < right)
	{
		q = randomPartition (vector, left, right);
		randomQuickSort(vector, left, q - 1);
		randomQuickSort(vector, q + 1, right);
	}
}