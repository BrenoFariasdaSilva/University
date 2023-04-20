#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

int sequentialSearch (int* vector, int vectorSize, const int key);
int binarySearch (int* vector, int leftIndex, int rightIndex, const int key);
void selectionSort (int* vector, int vectorSize);
int findMinorValue (int* vector, int vectorStart, int vectorEnd);
int SelectionMinK (int* vector, int vectorSize, int searchIndex);
int findGreatestValue (int* vector, int vectorStart, int vectorEnd);
void swapElements (int* vector, int firstIndex, int secondIndex);
void printVector (int *vector, int vectorSize);
int QuickMinK (int *vector, int leftIndex, int rightIndex, int searchIndex);
int partition (int* vector, int startIndex, int endIndex);
int* random_vector_unique_elems(int vectorSize, int seed);