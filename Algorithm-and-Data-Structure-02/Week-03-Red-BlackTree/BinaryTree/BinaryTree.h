#pragma once

#include <stdbool.h>

typedef struct BinaryTree
{
	int key;
	struct BinaryTree* left;
	struct BinaryTree* right;
} BinaryTree;

BinaryTree* BinaryTreeCreateNode (int key, BinaryTree* left, BinaryTree* right);
void BinaryTreeInsert (BinaryTree** node, int key);
void BinaryTreeRemove(BinaryTree** BinTree, int key);
BinaryTree* BinaryTreeSearch(BinaryTree* node, int key);
bool BinaryTreePrint(BinaryTree* BinTree, int spacing, char nodeName);
void ABB_Sort (int* v, int n);
void printVector (int* vector, int size);