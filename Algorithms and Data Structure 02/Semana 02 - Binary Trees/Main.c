#include <stdio.h>

#include "BinaryTree.h"

int main (int argc, char** argv)
{
	BinaryTree* BinTree = NULL;

	BinaryTreeInsert(&BinTree, 10);
	BinaryTreeInsert(&BinTree, 4);
	BinaryTreeInsert(&BinTree, 20);
	BinaryTreeInsert(&BinTree, 6);
	BinaryTreeInsert(&BinTree, 2);
	BinaryTreeInsert(&BinTree, 3);

	printf("%c? %p\n", 1, BinaryTreeSearch(BinTree, 1));
	printf("%c? %p\n", 20, BinaryTreeSearch(BinTree, 20));
	printf("%c? %p\n", 5, BinaryTreeSearch(BinTree, 5));
	printf("%c? %p\n", 0, BinaryTreeSearch(BinTree, 0));
	printf("%c? %p\n", 3, BinaryTreeSearch(BinTree, 3));

	// BinaryTreePrint(BinTree, 0, 'r');

	return 0;
}