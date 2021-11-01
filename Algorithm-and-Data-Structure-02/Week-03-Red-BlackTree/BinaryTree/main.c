#include "BinaryTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 15

int* randomVector(int n, int max, int seed);
bool alreadyInserted (int* vector, const int key);
void testA ();

int main()
{
	testA();

    return 0;
}

int* randomVector(int n, int max, int seed)
{
	int* vector = malloc (n * sizeof(int));

	srand (seed);
	for (int i = 0; i < SIZE; i++) 
	{
		int randomValue = rand () % max;
		if (!alreadyInserted(vector, randomValue))
			vector[i] = randomValue;
		else
			i--;
	}

	return vector;
}

bool alreadyInserted (int* vector, const int key)
{
	for (int i = 0; i < SIZE; i++)
	{
		if (vector[i] == key)
			return true;
	}
	return false;
}

void testA ()
{
	int* vector = randomVector (SIZE, 100, 42);

	printf("Unsorted Vector: ");
	printVector(vector, SIZE);

    ABB_Sort (vector, SIZE);

	printf("Sorted Vector: ");
	printVector(vector, SIZE);

    printf("\n");
}