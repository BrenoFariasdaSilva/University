#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BinaryTree.h"

int main()
{
    // First Test:
    printf("First Test:\n\n");

    BinaryTree* firstBinTree = BinaryTreeCreateNode(70, NULL, NULL);
    BinaryTreeInsert(&firstBinTree, 39);
    BinaryTreeInsert(&firstBinTree, 88);
    printf("Added Items:\n");
    BinaryTreePrint(firstBinTree, 0, 'r');

    printf("Removed Item: %d\n", 70);
    BinaryTreeRemove(&firstBinTree, 70);
    BinaryTreePrint(firstBinTree, 0, 'r');
    printf("\n");

	// Second Test:
    printf("Second Test: \n\n");

    BinaryTree* secondBinTree = BinaryTreeCreateNode(10, NULL, NULL);
    BinaryTreeInsert(&secondBinTree, 4);
    BinaryTreeInsert(&secondBinTree, 20);
    BinaryTreeInsert(&secondBinTree, 6);
    BinaryTreeInsert(&secondBinTree, 2);
    BinaryTreeInsert(&secondBinTree, 3);
    BinaryTreeInsert(&secondBinTree, 5);
    BinaryTreeInsert(&secondBinTree, 7);
    printf("Added Items:\n");
    BinaryTreePrint(secondBinTree, 0, 'r');

    printf("Removed Item: %d\n", 10);
    BinaryTreeRemove(&secondBinTree, 10);
    BinaryTreePrint(secondBinTree, 0, 'r');

    printf("Removed Item: %d\n", 4);
    BinaryTreeRemove(&secondBinTree, 4);
    BinaryTreePrint(secondBinTree, 0, 'r');

    printf("Removed Item: %d\n", 5);
    BinaryTreeRemove(&secondBinTree, 5);
    BinaryTreePrint(secondBinTree, 0, 'r');

    printf("\n");
	// Third Test
    printf("Third Test: \n\n");

    BinaryTree* thirdBinTree = BinaryTreeCreateNode(30, NULL, NULL);
    BinaryTreeInsert(&thirdBinTree, 50);
    BinaryTreeInsert(&thirdBinTree, 40);
    BinaryTreeInsert(&thirdBinTree, 47);
    BinaryTreeInsert(&thirdBinTree, 15);
    BinaryTreeInsert(&thirdBinTree, 20);
    BinaryTreeInsert(&thirdBinTree, 25);
    BinaryTreeInsert(&thirdBinTree, 17);
    BinaryTreeInsert(&thirdBinTree, 19);
    BinaryTreeInsert(&thirdBinTree, 4);
    BinaryTreeInsert(&thirdBinTree, 7);
    BinaryTreeInsert(&thirdBinTree, 0);
    printf("Added Items:\n");
    BinaryTreePrint(thirdBinTree, 0, 'r');

    printf("Removed Item: %d\n", 0);
    BinaryTreeRemove(&thirdBinTree, 0);
    BinaryTreePrint(thirdBinTree, 0, 'r');

    printf("Removed Item: %d\n", 30);
    BinaryTreeRemove(&thirdBinTree, 30);
    BinaryTreePrint(thirdBinTree, 0, 'r');

    printf("Removed Item: %d\n", 15);
    BinaryTreeRemove(&thirdBinTree, 15);
    BinaryTreePrint(thirdBinTree, 0, 'r');

    printf("Removed Item: %d\n", 20);
    BinaryTreeRemove(&thirdBinTree, 20);
    BinaryTreePrint(thirdBinTree, 0, 'r');

    printf("\n");
    return 0;
}