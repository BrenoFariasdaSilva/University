#include <stdbool.h>

typedef int elementType;

typedef enum
{
	RED_COLOR,
	BLACK_COLOR
} RedBlackTreeColor;

typedef struct RedBlackTree
{
	elementType key;
	elementType value;
	struct RedBlackTree* left;
	struct RedBlackTree* right;
	RedBlackTreeColor color;
} RedBlackTree;

void RedBlackTreeInsert (RedBlackTree** tree, const int key, const int value);
void RedBlackTreePrint (RedBlackTree* tree, int level, char side);
void ARN_Sort (int* v, int n);
void ARN_Sort_R (RedBlackTree* tree, int* vector, int* currentIndex);
void printVector (int* vector, int size);
int biggestTree(int firstNode, int secondNode);
int ARN_altura (RedBlackTree* arvore);