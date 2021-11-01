#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 50000

int* randomVector(int n, int max, int seed);
void troca (int* vector, int i, int j);
void median (int* vector, int startIndex, int middleIndex, int endIndex);
int medianPartition (int* vector, int startIndex, int endIndex);
void medianQuickSort (int* vector, int left, int right);

int main (void)
{
	int* vector = randomVector (SIZE, SIZE * 100, 42);
	medianQuickSort(vector, 0, SIZE - 1);

	double start_t = clock();
	medianQuickSort(vector, 0, SIZE - 1);
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

void median (int* vector, int startIndex, int middleIndex, int endIndex)
{ 
	if (vector[startIndex] > vector[middleIndex] && vector[middleIndex] < vector[endIndex]) // end > start > middle.
		troca (vector, startIndex, middleIndex);

	if (vector[middleIndex] > vector[endIndex] && vector[startIndex] > vector[middleIndex]) // start > middle > end.
		troca (vector, startIndex, endIndex);

	if (vector[endIndex] < vector[startIndex] && vector[endIndex] > vector[middleIndex]) // start > end > middle.
	{
		troca (vector, endIndex, startIndex);
		troca (vector, middleIndex, startIndex);
	}

	troca (vector, middleIndex, endIndex);
}

int medianPartition (int* vector, int startIndex, int endIndex)
{
	int pivot;
	int i, j;

	median (vector, startIndex, (endIndex + startIndex) / 2, endIndex); 

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

void medianQuickSort (int* vector, int left, int right)
{
	int index;

	if (left < right)
	{
		index = medianPartition (vector, left, right);
		medianQuickSort(vector, left, index - 1);
		medianQuickSort(vector, index + 1, right);
	}
}