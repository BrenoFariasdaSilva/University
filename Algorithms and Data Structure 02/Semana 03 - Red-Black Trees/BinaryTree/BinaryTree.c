#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "BinaryTree.h"

// AuxilaryFunctions:
BinaryTree* removeNode (BinaryTree* currentNode);
BinaryTree* substituteRightNode (BinaryTree* currentNode, int* key);
BinaryTree* freeNode (BinaryTree* node);
void ABB_Sort_R (BinaryTree* binTree, int* vector, int* currentIndex);

// Main Functions:

BinaryTree* BinaryTreeCreateNode (int key, BinaryTree* left, BinaryTree* right)
{
	BinaryTree* new = malloc (sizeof (BinaryTree));
	new->key = key;
	new->left = left;
	new->right = right;

	return new;
}

void BinaryTreeInsert (BinaryTree** node, int key)
{
	if ((*node) == NULL)
	{
		*node = BinaryTreeCreateNode (key, NULL, NULL);
		return;
	}

	if (key < (*node)->key)
		return BinaryTreeInsert (&(*node)->left, key); 
		
	return BinaryTreeInsert (&(*node)->right, key); 
}

void BinaryTreeRemove (BinaryTree** BinTree, int key)
{
	if (*BinTree == NULL)
		return;

	if ((*BinTree)->key == key)
		*BinTree = removeNode (*BinTree);   

	else if ((*BinTree)->key > key)                                  
		return BinaryTreeRemove(&((*BinTree)->left), key);

	else                                                                          
		return BinaryTreeRemove(&((*BinTree)->right), key);                                 
}

BinaryTree* removeNode (BinaryTree* currentNode)
{
	BinaryTree* auxiliaryNode;
	int key;  

  	if (currentNode->left == NULL && currentNode->right == NULL) // Leaf Node
	{            
		currentNode = freeNode(currentNode);                                                      
		return currentNode;                                                                   
  	} 

	auxiliaryNode = currentNode;                                                                      
  	if (currentNode->left == NULL) // One Child: Right Subtree.
	{                          
		currentNode = currentNode->right;                                                             
		auxiliaryNode = freeNode(auxiliaryNode);                                                      
		return currentNode;                                                                   
  	}                                                                             
  	if (currentNode->right == NULL) // One Child: Left Subtree.
	{                        
		currentNode = currentNode->left;                                                            
		auxiliaryNode = freeNode(auxiliaryNode);                                                      
		return currentNode;                                                                   
  	}                                                                             
	
	// Two Childs: substitute the smallest left node from the right subtree.
	currentNode->right = substituteRightNode(currentNode->right, &key);                           
	currentNode->key = key;                                                              
	return currentNode;    
}

BinaryTree* substituteRightNode (BinaryTree* currentNode, int* key)
{                          
	BinaryTree* auxiliaryNode; 
	                                                              
	if (currentNode->left == NULL)
	{                                                    
		*key = currentNode->key;                                                           
		auxiliaryNode = currentNode;                                                                   
		currentNode = currentNode->right;                                                             
		auxiliaryNode = freeNode(auxiliaryNode);                                                
		return currentNode;                                                                   
	}   
	                                                                          
	currentNode->left = substituteRightNode(currentNode->left, key);                          
	return currentNode;                                                                     
}

BinaryTree* freeNode (BinaryTree* node)
{
	if (node == NULL)
		return NULL;
		
	node->left = node->right = NULL;
    free (node);

	return NULL; 
}

BinaryTree* BinaryTreeSearch (BinaryTree* node, int key)
{
	if (node == NULL)
		return NULL;

	if (node->key == key)
		return node;

	if (key < node->key)
		return BinaryTreeSearch (node->left, key);

	return BinaryTreeSearch (node->right, key);
}

bool BinaryTreePrint (BinaryTree* BinTree, int spacing, char nodeName)
{
	if (BinTree == NULL)
		return false;

	for (int i = 0; i < spacing; i++)
		printf("	");
	printf("(%c)%d\n", nodeName, BinTree->key);

	BinaryTreePrint(BinTree->left, spacing + 1, 'l');
	BinaryTreePrint(BinTree->right, spacing + 1, 'r');
	return true;
}

void ABB_Sort (int* v, int n)
{
	BinaryTree* binTree = NULL;
	int index = n - 1;

    for (int i = 0; i < n; i++)
        BinaryTreeInsert(&binTree, v[i]);

	BinaryTreePrint(binTree, 0, 'r');
	ABB_Sort_R (binTree, v, &index);
}

void ABB_Sort_R (BinaryTree* binTree, int* vector, int* currentIndex)
{
	if (vector == NULL)
		return;

	if (binTree == NULL)
		return;

	ABB_Sort_R (binTree->left, vector, currentIndex);
	vector[(*currentIndex)--] = binTree->key;
	ABB_Sort_R (binTree->right, vector, currentIndex);
}

void printVector (int* vector, int size)
{
	for (int i = 0; i < size; i++)
    {
		printf("%d ", vector[i]);
    }

	printf("\n");
}