/**
 * \file rbst.c
 * \brief Implementation of the functions related to Randomized Binary Search Trees (RBST).
 * \author Loïck LHOTE
 * \version 0.1
 * \date janvier 2023
 *
 * Header file defining the data structure of a randomized binary search tree over integers and
 * declaring functions to manipulate them.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "rbst.h"

/**
 * @brief Create an empty binary search tree.
 * @return A pointer to the root of the new empty tree (NULL pointer).
 */
RBinarySearchTree createEmptyRBST(){
    return NULL;
}

/**
 * @brief Free the memory of a binary search tree.
 * @param tree Pointer to the root of the tree.
 */
void freeRBST(RBinarySearchTree tree){
    if(tree !=NULL){
        freeRBST(tree->rightRBST);
        freeRBST(tree->leftRBST);
        free(tree);
    }
    return;
}

/**
 * @brief Compute the size of a randomized binary search tree.
 * @param tree Pointer to the root of the tree.
 * @return The number of nodes in the tree.
 */
int sizeOfRBST(RBinarySearchTree tree) {
    if(tree != NULL){
        return tree->size;
    }
    else{
        return 0;
    }
}

/**
 * @brief Split a randomized binary search tree into two parts according to a value.
 * @param tree The RBST to split.
 * @param value The value to split the tree on.
 * @param inf Pointer to a randomized BST that will store the final tree containing the elements strictly smaller than value.
 * @param sup Pointer to a randomized BST that will store the final tree containing the elements greater or equal to value.
 *
 * Split a randomized binary search tree into two parts according to a value.
 *
 * Be carful: the RBST tree is modified during the process but the inf and sub parts contain together
 * all the nodes of tree.
 */
void splitRBST(RBinarySearchTree tree, int value, RBinarySearchTree* inf, RBinarySearchTree* sup) {
    if (tree == NULL){
        *inf = NULL;
        *sup = NULL;
    } else {
        if (tree->value==value){
            *sup = tree;
            *inf = tree->leftRBST;
        } else {
            if (value>tree->value){
                *inf = tree;
                splitRBST(tree->rightRBST,value, &((*inf)->rightRBST),sup);
            } else {
                *sup = tree;
                splitRBST(tree->leftRBST,value,inf,&((*sup)->leftRBST));
            }
        }
    }
    return;
}

/**
 * @brief Insert a value at the root of a randomized binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to insert.
 * @return A pointer to the root of the modified tree.
 */
RBinarySearchTree insertAtRoot(RBinarySearchTree tree, int value) {
    RBinarySearchTree root = NULL;
    RBinarySearchTree* tempLeft = NULL;
    RBinarySearchTree* tempRight = NULL;
    root = (RBinarySearchTree)calloc(1,sizeof(RBinarySearchTree));
    tempLeft = (RBinarySearchTree*)calloc(1,sizeof(RBinarySearchTree));
    tempRight = (RBinarySearchTree*)calloc(1,sizeof(RBinarySearchTree));
    root->value = value;
    root->size = tree->size;
    splitRBST(tree,value,tempLeft, tempRight);
    root->leftRBST = *tempLeft;
    root->rightRBST = *tempRight;
    return root;
}


/**
 * @brief Add a value to a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to add.
 * @return A pointer to the root of the modified tree.
 */
RBinarySearchTree addToRBST(RBinarySearchTree tree, int value){
    if(tree == NULL){
        tree = (RBinarySearchTree)malloc(sizeof(RBinarySearchTree));
        tree->value = value;
        tree->size = 1;
        tree->leftRBST = NULL;
        tree->rightRBST = NULL;
    } else {
        tree = insertAtRoot(tree, value);
    }
    return tree;
}


/**
 * @brief Compute the height of a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @return The height of the tree.
 */
int heightRBST(RBinarySearchTree tree) {
    int left =1;
    int right = 1;
    if(tree !=NULL){
        if(tree->leftRBST !=NULL){
            left =1 + heightRBST(tree->leftRBST);
        }
        if(tree->rightRBST!=NULL){
            right = 1 + heightRBST(tree->rightRBST);
        }
        if(left > right){
            return left;
        }
        else{
            return right;
        }
    }
    return -1;
}

/**
 * @brief Search for a value in a binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to search for.
 * @return A pointer to the node containing the value, or NULL if the value is not in the tree.
 */
RBinarySearchTree searchRBST(RBinarySearchTree tree, int value){
    if(tree !=NULL){
        RBinarySearchTree node = tree;
        while(node!=NULL){
                if(value > node->value){
                    node = node->rightRBST;
                }
                else if(value < node->value){
                    node = node->leftRBST;
                }
                else{
                    return node;
                }
        }
    }
    return NULL;
}


/**
 * @brief Build a randomized binary search tree from a given permutation.
 * @param permutation Array of integers representing the permutation
 * @param n size of the array
 * @return A random binary such tree built by successively inserting the elements of permutation.
 */
RBinarySearchTree buildRBSTFromPermutation(int *permutation,size_t n) {
    RBinarySearchTree tree = createEmptyRBST();
    int i;
    for(i=0;i<n;i++){
        tree = addToRBST(tree, permutation[i]);
    }
    return tree;
}


/**
 * @brief Print the elements of a binary search tree in a pretty format.
 * @param tree Pointer to the root of the tree.
 * @param space Space to be printed before the current element.
 */
void prettyPrintRBST(RBinarySearchTree tree, int space) {
    if (tree == NULL) {
        return;
    }
    space += 10;

    prettyPrintRBST(tree->rightRBST, space);

    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("[%d,%d]\n", tree->value, tree->size);

    prettyPrintRBST(tree->leftRBST, space);
    return ;
}
