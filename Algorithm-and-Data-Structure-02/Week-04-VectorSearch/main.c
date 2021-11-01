#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "vectorSearch.h"

#define SIZE 1000
#define SEARCHINDEX 3
#define SEED 42

void test01 (int* vector, const int vectorSize);
void test02 (int* vector, const int vectorSize);
void test03 ();

int main()
{
	int* vector = malloc (sizeof(SIZE));
	vector[0] = 2;
	vector[1] = 4;
	vector[2] = 5;
	vector[3] = 3;
	vector[4] = 1;
	
	// test01 (vector, SIZE);
	// test02 (vector, SIZE);
	test03 (vector, SIZE);

    return 0;
}

void test01 (int* vector, const int vectorSize)
{
	printf("Test01 - Start \n");
	printVector (vector, SIZE);
	clock_t startTimeLapse = clock();
	printf("%d menor elemento do vetor: %d\n", SEARCHINDEX, SelectionMinK (vector, SIZE, SEARCHINDEX));
	clock_t endTimeLapse = clock();
	printVector (vector, SIZE);
	printf("Test01 - End \n\n");
}

void test02 (int* vector, const int vectorSize)
{
    printf("Test02 - Start \n");
	printVector (vector, SIZE);
	clock_t startTimeLapse = clock();
	printf("%d menor elemento do vetor: %d\n", SEARCHINDEX, QuickMinK (vector, 0, SIZE, SEARCHINDEX));
    clock_t endTimeLapse = clock();
	printVector (vector, SIZE);

    printf("Tempo: %f\n", (double) ((endTimeLapse - startTimeLapse) / CLOCKS_PER_SEC));
	printf("Test02 - End \n\n");
}

void test03 ()
{
    printf("Test03 - Start \n");
	clock_t startTimeLapse;
    clock_t endTimeLapse;
	int* vector = random_vector_unique_elems(SIZE, SEED);
	printVector (vector, SIZE);
	startTimeLapse = clock();
	printf("%d menor elemento do vetor: %d\n", SEARCHINDEX, SelectionMinK (vector, SIZE, SEARCHINDEX));
    endTimeLapse = clock();
	printVector (vector, SIZE);

    printf("Tempo: %f\n", (double) ((endTimeLapse - startTimeLapse) / CLOCKS_PER_SEC));
	printf("Test03 - End \n\n");
}