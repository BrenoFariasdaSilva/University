#include "vectorSearch.h"

int sequentialSearch (int* vector, int vectorSize, const int key)
{
	for (int i = 0; i < vectorSize; i++)
	{
		if (vector[i] == key)
			return i;
	}
	return -1;
}

int binarySearch (int* vector, int leftIndex, int rightIndex, const int key)
{
    int middleIndex;

    if (leftIndex <= rightIndex)
    {
        middleIndex = (leftIndex + rightIndex) / 2;

        if (vector[middleIndex] == key)
            return middleIndex;

        else
        {
            if (key > vector[middleIndex])
                return binarySearch (vector, middleIndex + 1, rightIndex, key);

            else
                return binarySearch (vector, leftIndex, middleIndex - 1, key);
        }
    }

    return -1;
}

void selectionSort (int* vector, int vectorSize)
{
    int minorElement;

    for (int i = vectorSize - 1; i >= 0; i--)
    {
        minorElement = findMinorValue (vector, 0, i);
        swapElements (vector, minorElement, i);
    }
}

int SelectionMinK (int *vector, int vectorSize, int searchIndex)
{
    if (searchIndex < vectorSize)
    {
        selectionSort(vector, vectorSize);
        return (vector[searchIndex - 1]);
    }

    else
    {
        return (findMinorValue(vector, 0, vectorSize));
    }
}

int findMinorValue (int* vector, int vectorStart, int vectorEnd)
{
    int minorElement = INT_MAX, minorElementIndex = -1;

    for (int i = vectorStart; i < vectorEnd; i++)
    {
        if (vector[i] < minorElement)
        {
            minorElement = vector[i];
            minorElementIndex = i;
        }
    }

    return minorElementIndex;
}

int findGreatestValue (int* vector, int vectorStart, int vectorEnd)
{
    int greatestElement = INT_MIN, greatestElementIndex = -1;

    for (int i = vectorStart; i < vectorEnd; i++)
    {
        if (vector[i] > greatestElement)
        {
            greatestElement = vector[i];
            greatestElementIndex = i;
        }
    }

    return greatestElementIndex;
}

void swapElements (int* vector, int firstIndex, int secondIndex)
{
    int hold = vector[firstIndex];
    vector[firstIndex] = vector[secondIndex];
    vector[secondIndex] = hold;
}

void printVector (int *vector, int vectorSize)
{
    for (int i = 0; i < vectorSize; i++)
        printf("%d ", vector[i]);
    printf("\n");
}

int QuickMinK (int *vector, int leftIndex, int rightIndex, int searchIndex)
{
    if (searchIndex > rightIndex - leftIndex + 1)
    {
        int greatestElementIndex = findGreatestValue (vector, leftIndex, rightIndex);
        return vector[greatestElementIndex];
    }

    if (leftIndex > rightIndex)
    {
        int minorElementIndex = findMinorValue (vector, leftIndex, rightIndex);
        return vector[minorElementIndex];
    }
    
    int q;
	if (leftIndex < rightIndex)
	{
		q = partition (vector, leftIndex, rightIndex);
		QuickMinK (vector, leftIndex, q - 1, searchIndex);
		QuickMinK (vector, q + 1, rightIndex, searchIndex);
        return (vector[searchIndex]);
    }
}

int partition (int* vector, int startIndex, int endIndex)
{
	int pivot = vector[endIndex];
	int i = startIndex - 1;

	for (int j = startIndex; j < endIndex; j++)
	{
		if (vector[j] <= pivot)
		{
			i++;
			swapElements (vector, i, j);
		}
	}

	swapElements (vector, i + 1, endIndex);
	return i + 1;
}

int* random_vector_unique_elems (int vectorSize, int seed)
{
    srand(seed);

    int* vector = malloc (vectorSize * sizeof(int));

    for(int i = 0; i < vectorSize; i++)
        vector[i] = i;

    shuffle (vector, 0, vectorSize);

    return vector;
}

unsigned int random_32bits ()
{
    unsigned int x;
    x = rand() & 0xff;
    x |= (rand() & 0xff) << 8;
    x |= (rand() & 0xff) << 16;
    x |= (rand() & 0xff) << 24;
    return x;
}


void shuffle (int *vector, int vectorStart, int vectorEnd)
{
    for (int i = vectorEnd - 1; i > vectorStart; i--)
    {
        int j = (random_32bits() % (i + 1));

        j = j <= vectorStart ? vectorStart + 1 : j;
        swapElements (vector, i, j);
    }
}