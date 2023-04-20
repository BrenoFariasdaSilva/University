#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 50000

void standardQuickSortAlgorithm (int* vector);
int* randomVector(int n, int max, int seed);
void troca (int* vector, int i, int j);
int standardPartition (int* vector, int startIndex, int endIndex);
void standardQuickSort (int* vector, int left, int right);

void randomQuickSortAlgorithm (int* vector);
int randomPartition (int* vector, int startIndex, int endIndex);
void randomQuickSort (int* vector, int left, int right);

void medianOfThreeQuickSortAlgorithm (int* vector);
void median (int* vector, int startIndex, int middleIndex, int endIndex);
int medianPartition (int* vector, int startIndex, int endIndex);
void medianQuickSort (int* vector, int left, int right);

int main (void)
{
	int algorithm = 0, vectorType = 0;
	printf("Select one QuickSort algorithm: \n");
	printf("1 - Standard Quick Sort Algorithm \n");
	printf("2 - Random Quick Sort Algorithm \n");
	printf("3 - Median of Three Quick Sort Algorithm \n");
	scanf("%d", &algorithm);
	printf("Select one vector type: \n");
	printf("1 - Previously Sorted: \n");
	printf("2 - Not Previously Sorted: \n");
	scanf("%d", &vectorType);

	if (algorithm <= 3 && algorithm >= 1)
	{
		int* vector = randomVector (SIZE, SIZE * 100, 42);

		if (vectorType == 1)
			standardQuickSort(vector, 0, SIZE - 1); // Sort vector to be sorted again.

		if (algorithm == 1)
			standardQuickSortAlgorithm (vector);

		if (algorithm == 2)
			randomQuickSortAlgorithm (vector);

		if (algorithm == 3)
			medianOfThreeQuickSortAlgorithm (vector);
	}

	return 0;
}

void standardQuickSortAlgorithm (int* vector)
{
	double start_t = clock();
	standardQuickSort(vector, 0, SIZE - 1);
	double end_t = clock();
	double timeLapse = (end_t - start_t) / CLOCKS_PER_SEC;

	printf("Standard Time Lapse for %d elements: %f \n", SIZE, timeLapse);
}

void randomQuickSortAlgorithm (int* vector)
{
	double start_t = clock();
	randomQuickSort(vector, 0, SIZE - 1);
	double end_t = clock();
	double timeLapse = (end_t - start_t) / CLOCKS_PER_SEC;

	printf("Random Time Lapse for %d elements: %f \n", SIZE, timeLapse);
}

void medianOfThreeQuickSortAlgorithm (int* vector)
{
	double start_t = clock();
	medianQuickSort(vector, 0, SIZE - 1);
	double end_t = clock();
	double timeLapse = (end_t - start_t) / CLOCKS_PER_SEC;

	printf("Median of Three Time Lapse for %d elements: %f \n", SIZE, timeLapse);
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

int standardPartition (int* vector, int startIndex, int endIndex)
{
	int x;
	int i, j;

	x = vector[endIndex];
	i = startIndex - 1;

	for (j = startIndex; j < endIndex; j++)
	{
		if (vector[j] <= x)
		{
			i++;
			troca (vector, i, j);
		}
	}

	troca (vector, i + 1, endIndex);
	return i + 1;
}

void standardQuickSort (int* vector, int left, int right)
{
	int q;

	if (left < right)
	{
		q = standardPartition (vector, left, right);
		standardQuickSort(vector, left, q - 1);
		standardQuickSort(vector, q + 1, right);
	}
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
		q = medianPartition (vector, left, right);
		medianQuickSort(vector, left, q - 1);
		medianQuickSort(vector, q + 1, right);
	}
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