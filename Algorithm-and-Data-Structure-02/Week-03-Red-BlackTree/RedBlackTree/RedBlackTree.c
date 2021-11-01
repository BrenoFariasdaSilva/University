#include "RedBlackTree.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void RedBlackTreeInsertR (RedBlackTree** tree, const int key, const int value);
static inline elementType isNodeRed (RedBlackTree* tree);
static void invertColors (RedBlackTree* tree);
static void rotateLeft (RedBlackTree** tree);
static void rotateRight (RedBlackTree** tree);

RedBlackTree* createNode (const int key, const int value)
{
	RedBlackTree* newNode = malloc (sizeof (RedBlackTree));
	newNode->key = key;
	newNode->value = value;
	newNode->left = newNode->right = NULL;
	newNode->color = RED_COLOR;
	return newNode;
}

void RedBlackTreeInsert (RedBlackTree** tree, const int key, const int value)
{
	RedBlackTreeInsertR (tree, key, value);
	(*tree)->color = BLACK_COLOR;
}

void RedBlackTreeInsertR (RedBlackTree** tree, const int key, const int value)
{
	if ((*tree) == NULL)
	{
		(*tree) = createNode(key, value);
		return;
	}

	if (key < (*tree)->key)
		RedBlackTreeInsertR (&(*tree)->left, key, value);

	if (key > (*tree)->key)
		RedBlackTreeInsertR (&(*tree)->right, key, value);

	if (isNodeRed ((*tree)->right) && !isNodeRed ((*tree)->left))
		rotateLeft (tree);

	if (isNodeRed ((*tree)->left) && isNodeRed ((*tree)->left->left))
		rotateRight (tree); 

	if (isNodeRed ((*tree)->left) && isNodeRed ((*tree)->right))
		invertColors (*tree); 
}

static inline elementType isNodeRed (RedBlackTree* tree)
{
	if (tree == NULL) 
		return false;

	return (tree->color == RED_COLOR);
}

static void invertColors (RedBlackTree* tree)
{
	tree->color = RED_COLOR;
	tree->left->color = BLACK_COLOR;
	tree->right->color = BLACK_COLOR;
}

static void rotateLeft (RedBlackTree** tree)
{
	RedBlackTree *treeNode, *rightChild;

	treeNode = *tree;
	rightChild = treeNode->right;
	treeNode->right = rightChild->left;
	rightChild->left = treeNode;
	rightChild->color = treeNode->color;
	treeNode->color = RED_COLOR;
	*tree = rightChild;
}

static void rotateRight (RedBlackTree** tree)
{
	RedBlackTree *treeNode, *leftChild;

	treeNode = *tree;
	leftChild = treeNode->left;
	treeNode->left = leftChild->right;
	leftChild->right = treeNode;
	leftChild->color = treeNode->color;
	treeNode->color = RED_COLOR;
	*tree = leftChild;
}

void RedBlackTreePrint (RedBlackTree* tree, int level, char side)
{
    int i;

    for(i = 0; i < level; i++)
	{
        printf("--> ");
	}

    if(tree == NULL)
        printf("(%c) NONE\n", side);

    else
	{
        printf("(%c) %c [%s]\n", side, (char) tree->value, tree->color == RED_COLOR ? "R" : "B");
        RedBlackTreePrint(tree->left, level+1, 'l');
        RedBlackTreePrint(tree->right, level+1, 'r');
    }
}

void ARN_Sort (int* v, int n)
{
	RedBlackTree* tree = NULL;
	int index = n - 1;

    for (int i = 0; i < n; i++)
        RedBlackTreeInsert(&tree, v[i], 0);

	RedBlackTreePrint(tree, 0, 'r');
	ARN_Sort_R (tree, v, &index);
}

void ARN_Sort_R (RedBlackTree* tree, int* vector, int* currentIndex)
{
	if (vector == NULL)
		return;

	if (tree == NULL)
		return;

	ARN_Sort_R (tree->left, vector, currentIndex);
	vector[(*currentIndex)--] = tree->key;
	ARN_Sort_R (tree->right, vector, currentIndex);
}

int ARN_altura (RedBlackTree* arvore)
{
    if(arvore == NULL || (arvore->left == NULL && arvore->right == NULL))
        return 0;
	else if ((arvore->color == RED_COLOR))
        return 0 + biggestTree(ARN_altura(arvore->left), ARN_altura(arvore->right));
	else
        return 1 + biggestTree(ARN_altura(arvore->left), ARN_altura(arvore->right));
}

int biggestTree(int firstNode, int secondNode)
{
    if (firstNode > secondNode)
        return firstNode;
    else
        return secondNode;
}

void printVector (int* vector, int size)
{
	for (int i = 0; i < size; i++)
    {
		printf("%d ", vector[i]);
    }

	printf("\n");
}