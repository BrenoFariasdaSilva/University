// Marcela needs your help to write a computer program about binary search tree. The program must have the following inputCommands:

// I n: Insert the n element in the current Binary Search Tree.
// PREFIXA: print the pre-order traversal for the current tree
// INFIXA: print the in-order traversal for the current tree
// POSFIXA: print the post-order traversal for the current tree
// P n: Search the n element, printing a message indicanding if n exist.

// By using this program, at any time must be possible to insert a new element, print the Pre-order, In-order or Post-order traversal or search any element inside the tree.

// INPUT:
// The input contains N lines and each line contains an operation using letters (A-Z, a-z) over a binary search tree, that initially will be empty. The first line of input contains an insertion (I). The next lines can have any inputCommand described above, like the given example. The end of input is determined by EOF.
// Obs: Consider that will not be repeated elements in the tree.

// OUTPUT:
// Each line of the input excepting the lines with the "I" inputCommand must produce one output line. The output must be acording to the given example, remembering that "existe" means exist and "nao existe" means don't exist in portuguese. There is no blank space after the last line char, otherwise you`ll get Presentation Error.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct node { // Node Structure
	long int key;
	struct node *left;
	struct node *right;
} node;

node *create_node (long int key) { // Create a new node with the associated key
	node *new_node = (node *) malloc (sizeof (node));
	new_node->key = key;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

node* insert (node **root, long int key) { // Insert a new node with the associated key
	if (*root == NULL) {
		*root = create_node (key);
	} else {
		if (key < (*root)->key) {
			(*root)->left = insert (&(*root)->left, key);
		} else {
			(*root)->right = insert (&(*root)->right, key);
		}
	}
	return (*root); 
}

void print_prefix (node *root) { // Pre-order: root, left, right
	if (root != NULL) {
		printf ("%ld ", root->key);
		print_prefix (root->left);
		print_prefix (root->right);
	} 

}

void print_infix (node *root) { // In-order: left, root, right
	if (root != NULL) {
		print_infix (root->left);
		printf ("%ld ", root->key);
		print_infix (root->right);
	}
}

void print_posfix (node *root) { // Post-order: left, right, root
	if (root != NULL) {
		print_posfix (root->left); 
		print_posfix (root->right);
		printf ("%ld ", root->key);
	}
}

void search (node *root, long int key) { // Search the key in the binary tree using the pre-order traversal
	if (root != NULL) { 
		if (root->key == key) { // If the key is found, print "existe"
			printf ("%ld existe\n", key);
		} else {
			if (key < root->key) { // Search in the left subtree
				search (root->left, key);
			} else { // Search in the right subtree
				search (root->right, key);
			}
		}
	} else { // If the key is not found, print "nao existe"
		printf ("%ld nao existe\n", key);
	}
}

void remove_node (node **root, long int key) { // Remove the node with the associated key
	if (*root != NULL) {
		if (key < (*root)->key) { // Search in the left subtree
			remove_node (&(*root)->left, key);
		} else if (key > (*root)->key) { // Search in the right subtree
			remove_node (&(*root)->right, key);
		} else { // If the key is found, remove the node
			if ((*root)->left == NULL && (*root)->right == NULL) { // If the node is a leaf, remove it
				free (*root);
				*root = NULL;
			} else if ((*root)->left == NULL) { // If the node has only one child, replace it with the child
				node *aux = *root;
				*root = (*root)->right;
				free (aux);
			} else if ((*root)->right == NULL) { // If the node has only one child, replace it with the child
				node *aux = *root;
				*root = (*root)->left;
				free (aux);
			} else { // If the node has two children, replace it with the major node in the left subtree
				node *aux = (*root)->left;
				while (aux->right != NULL) {
					aux = aux->right;
				}
				(*root)->key = aux->key;
				remove_node (&(*root)->left, aux->key);
			}
		}
	}
}

int main () {
	node *root = NULL;
	char inputCommand[10];
	long int key;

	while (scanf ("%s", inputCommand) != EOF) { // Read the inputCommand and execute the corresponding action
		if (strcmp (inputCommand, "I") == 0) { // Insert a new node with the associated key
			scanf ("%ld", &key);
			insert (&root, key);
		} else if (strcmp (inputCommand, "PREFIXA") == 0) { // Pre-order: root, left, right
			print_prefix (root);
			printf ("\n");
		} else if (strcmp (inputCommand, "INFIXA") == 0) { // In-order: left, root, right
			print_infix (root);
			printf ("\n");
		} else if (strcmp (inputCommand, "POSFIXA") == 0) { // Post-order: left, right, root
			print_posfix (root);
			printf ("\n");
		} else if (strcmp (inputCommand, "P") == 0) { // Search the key in the binary tree using the pre-order traversal
			scanf ("%ld", &key);
			search (root, key);
		} else if (strcmp (inputCommand, "R") == 0) { // Remove the node with the associated key
			scanf ("%ld", &key);
			remove_node (&root, key);
		} else {}
	}
	return 0;
}