/**
 * \file bst.c
 * \brief Implementation of classical functions for BST
 * \author Loïck LHOTE
 * \version 0.1
 * \date janvier 2023
 *
 * Source code of the functions declared in bst.h.
 * Thes functions are to manipulate binary search trees.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "bst.h"
#define MAX(i, j) (((i) > (j)) ? (i) : (j))


/**
 * @brief Create an empty binary search tree.
 * @return A pointer to the root of the new empty tree (NULL pointer).
 */
BinarySearchTree createEmptyBST() {
    return NULL;
}

/**
 * @brief Free the memory of a binary search tree.
 * @param tree Pointer to the root of the tree.
 */
void freeBST(BinarySearchTree tree) {
	if (tree != NULL){
		freeBST(tree->leftBST);
		freeBST(tree->rightBST);
		free(tree);
	}
    return;
}


/**
 * @brief Add a value to a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to add.
 * @return A pointer to the root of the modified tree.
 */
BinarySearchTree addToBST(BinarySearchTree tree, int value) {
	if (tree == NULL){
		tree = (BinarySearchTree)malloc(sizeof(BinarySearchTree));
		tree->value = value ;
		tree->leftBST = NULL;
		tree->rightBST = NULL;
	} else {
		if (tree->value > value){
			tree->leftBST = addToBST(tree->leftBST, value);
		} else { tree->rightBST = addToBST(tree->rightBST, value); }
	}
	return tree;
}


/**
 * @brief Compute the height of a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @return The height of the tree.
 */
int heightBST(BinarySearchTree tree) {
    if (tree == NULL) {
        return -1; 
    }
    int leftHeight = heightBST(tree->leftBST);
    int rightHeight = heightBST(tree->rightBST);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}


/**
 * @brief Search for a value in a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to search for.
 * @return A pointer to the node containing the value, or NULL if the value is not in the tree.
 */
BinarySearchTree searchBST(BinarySearchTree tree, int value) {
    if (tree == NULL || tree->value == value) {
        return tree;
    }
    if (value < tree->value) {
        return searchBST(tree->leftBST, value);
    }
    return searchBST(tree->rightBST, value);
}


/**
 * @brief Delete the root of a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @return A pointer to the root of the modified tree.
 */

BinarySearchTree deleteRootBST(BinarySearchTree tree) {
	return deleteFromBST(tree,tree->value);
}


/**
 * @brief Delete a value from a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to delete.
 * @return A pointer to the root of the modified tree.
 */
BinarySearchTree deleteFromBST(BinarySearchTree tree, int value) {
	BinarySearchTree nodeToDelete = searchBST(tree,value);
	if (nodeToDelete == NULL){
		return NULL;
	}
	if (heightBST(nodeToDelete->leftBST) <= heightBST(nodeToDelete->rightBST)){
	}
    return NULL;
}

/**
 * @brief Build a binary search tree from a given permutation.
 * @param permutation Array of integers representing the permutation
 * @param n size of the array
 * @return A binary such tree built by successively inserting the elements of permutation.
 */
BinarySearchTree buildBSTFromPermutation(int *permutation,size_t n) {
	int i ;
	BinarySearchTree tree = NULL;

	for (i=0;i<n;i++){
		tree = addToBST(tree, permutation[i]);
	}
    return tree;
}


/**
 * @brief Print the elements of a binary search tree in a pretty format.
 * @param tree Pointer to the root of the tree.
 * @param space Space to be printed before the current element.
 */
void prettyPrintBST(BinarySearchTree tree, int space) {
    if (tree == NULL) {
        return;
    }
    space += 10;

    prettyPrintBST(tree->rightBST, space);

    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", tree->value);

    prettyPrintBST(tree->leftBST, space);
}

/**

Quelles conclusions pouvez-vous tirer des résultats d’expériences que vous obtenez ?

... Répondre ici.


*/
