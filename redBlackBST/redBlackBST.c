/**
 * \file redBlackBST.c
 * \brief Implementation of the functions related to Red-Black Binary Search Trees.
 * \author Loïck LHOTE
 * \version 0.1
 * \date janvier 2023
 *
 * Header file defining the data structure of a red-black binary search tree over integers and
 * declaring functions to manipulate them.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "redBlackBST.h"
#define MIN(i, j) (((i) < (j)) ? (i) : (j))



/**
 * @brief Create an empty red-black binary search tree.
 * @return A pointer to the root of the new empty tree (NULL pointer).
 */
RedBlackBST createEmptyRedBlackBST(){
    return NULL;
}

/**
 * @brief Free the memory of a red-black binary search tree.
 * @param tree Pointer to the root of the tree.
 */

void freeRedBlackBST(RedBlackBST tree){
    if (tree == NULL){
        return;
    }
    freeRedBlackBST(tree->leftBST);
    freeRedBlackBST(tree->rightBST);
    free(tree);
    return;
}

/**
 * @brief Perform a left rotation on the Red-Black BST.
 * @param tree Pointer to the root node of the Red-Black BST.
 * @param node Pointer to the node to rotate around.
 * @return Pointer to the root node of the rotated Red-Black BST.
 */
RedBlackBST leftRotationRedBlackBST(RedBlackBST tree, NodeRedBlackBST *node){
    NodeRedBlackBST *rightChild = node->rightBST;
    node->rightBST = rightChild->leftBST;

    if (rightChild->leftBST != NULL)
        rightChild->leftBST->father = node;

    rightChild->father = node->father;

    if (node->father == NULL)
        tree = rightChild;
    else if (node->father->leftBST == node)
        node->father->leftBST = rightChild;
    else
        node->father->rightBST = rightChild;

    rightChild->leftBST = node;
    node->father = rightChild;

    return tree;
}




/**
 * @brief Perform a right rotation on the Red-Black BST.
 * @param tree Pointer to the root node of the Red-Black BST.
 * @param node Pointer to the node to rotate around.
 * @return Pointer to the root node of the rotated Red-Black BST.
 */
RedBlackBST rightRotationRedBlackBST(RedBlackBST tree, NodeRedBlackBST *node)
{
    NodeRedBlackBST *leftChild = node->leftBST;
    node->leftBST = leftChild->rightBST;

    if (leftChild->rightBST != NULL)
        leftChild->rightBST->father = node;

    leftChild->father = node->father;

    if (node->father == NULL)
        tree = leftChild;
    else if (node->father->leftBST == node)
        node->father->leftBST = leftChild;
    else
        node->father->rightBST = leftChild;

    leftChild->rightBST = node;
    node->father = leftChild;

    return tree;
}

/**
 * @brief Balance the Red-Black BST after inserting (or crating) a red node.
 * @param tree Pointer to the root node of the Red-Black BST. Be careful, the root may change after balancing.
 * @param curr Pointer to the node that was recently inserted. Be careful, the node to deal with may change after each operation.
 *
 * There are several cases:
 *   - if *curr is the root, then change its color in black
 *   - if the father of *curr is black, then it is finished
 *   - the father and the uncle are red (see course)
 *   - the uncle node is black and the current node is a right child (left rotation, see course)
 *   - the uncle node is black and the current node is a left child (right rotation, see course)
 */

int getColorUncle(RedBlackBST* tree, NodeRedBlackBST* curr){
    if (curr->father->father->leftBST == curr->father){
        if (curr->father->father->rightBST == NULL){
            return BLACK;
        }
        return curr->father->father->rightBST->color;
    } else {
        if (curr->father->father->leftBST == NULL){
            return BLACK;
        }
        return curr->father->father->leftBST->color;
    }
}

int isGGorDDorGDorDG(RedBlackBST* tree, NodeRedBlackBST* curr){
    if (curr->father == curr->father->father->leftBST){
        if (curr == curr->father->leftBST){
            return 1;
        } else {
            return 3;
        }
    }
    if (curr->father == curr->father->father->rightBST){
        if(curr == curr->father->rightBST){
            return 2;
        } else {
            return 4;
        }
    }
    return 0;
}

RedBlackBST searchRootRedBlackBST(RedBlackBST currentNode){
    if (!currentNode){
        return NULL;
    }
    if(!(currentNode->father)){
        return currentNode;
    }
    return searchRootRedBlackBST(currentNode->father);
}

void balanceRedBlackBST(RedBlackBST *tree, NodeRedBlackBST *curr)
{
    RedBlackBST grandFather;
    int currIsRight;
    int fatherIsRight;
    if(!(curr -> father)){
        curr->color = BLACK;
        return;
    }
    currIsRight = (curr == curr -> father -> rightBST);
    if(!curr->father->color){
        return;
    }
    grandFather = curr -> father -> father;
    if(!grandFather){
        if ((curr -> father -> color)){
            
            if(currIsRight){
                
                leftRotationRedBlackBST(*tree,curr->father);
                curr->color = BLACK;
                return;
            }
            else{
                rightRotationRedBlackBST(*tree,curr->father);
                curr->color = BLACK;
                return;
            }
        }
        return;
    }
    fatherIsRight = (curr -> father == grandFather -> rightBST );
    if(currIsRight){
        if(fatherIsRight){
            if(grandFather->leftBST){
                if(grandFather->leftBST->color){
                    curr->father->color = BLACK;
                    grandFather->leftBST->color = BLACK;
                    grandFather->color = RED;
                    balanceRedBlackBST(tree,grandFather);
                    return;
                }
            }

            leftRotationRedBlackBST(*tree,grandFather);
            curr->father-> color = BLACK;
            grandFather-> color = RED;
            curr-> color = RED;
        } else{
            if(grandFather->rightBST){
                if(grandFather->rightBST->color){
                    curr->father->color = BLACK;
                    grandFather->rightBST->color = BLACK;
                    grandFather->color = RED;
                    balanceRedBlackBST(tree,grandFather);
                    return;
                }
            }
            leftRotationRedBlackBST(*tree,curr->father);
            (*tree) = searchRootRedBlackBST(*tree);
            balanceRedBlackBST(tree,curr->leftBST);
        }
    }
    else
    {
        if(fatherIsRight){
            if(grandFather->leftBST){
                if(grandFather->leftBST->color){
                    curr->father->color = BLACK;
                    grandFather->leftBST->color = BLACK;
                    grandFather->color = RED;
                    balanceRedBlackBST(tree,grandFather);
                    return;
                }
            }
            rightRotationRedBlackBST(*tree,curr->father);
            (*tree) = searchRootRedBlackBST(*tree);
            balanceRedBlackBST(tree,curr->rightBST);
        }else{
            if(grandFather->rightBST){
                if(grandFather->rightBST->color){
                    curr->father->color = BLACK;
                    grandFather->rightBST->color = BLACK;
                    grandFather->color = RED;
                    //balanceRedBlackBST(tree,grandFather);
                    return;
                }
            }
            rightRotationRedBlackBST(*tree,grandFather);
            curr->father-> color = BLACK;
            grandFather-> color = RED;
            curr-> color = RED;
        }
    }
    return ;
}

/**
 * @brief Insert a node in the Red-Black BST.
 * @param tree Pointer to the root node of the Red-Black BST.
 * @param value Value to be inserted in the Red-Black BST.
 *
 * The root of the tree can be modified so that we have a pointer on a RedBlackBST.
 */
void insertNodeRedBlackBST(RedBlackBST *tree, int value)
{
    RedBlackBST new_node = (NodeRedBlackBST*)malloc(sizeof(NodeRedBlackBST));
    new_node->color = RED;
    new_node->father = NULL;
    new_node->leftBST = NULL;
    new_node->rightBST = NULL;
    new_node->value = value;

    if ((*tree) == NULL){
        new_node->color = BLACK;
        (*tree) = new_node;
        return;
    }
    RedBlackBST y = NULL;
    RedBlackBST x = (*tree);

    while (x != NULL)
    {
        y = x;
        if (new_node->value < x->value){
            x = x->leftBST;
        } else {
            x = x->rightBST;
        }
    }
        new_node->father = y;
        if (new_node->value > y->value){
            y->rightBST = new_node;
        } else {
            y->leftBST = new_node;
        }
    balanceRedBlackBST(tree, new_node);
    if((*tree)->color){
        ((*tree)->color) = BLACK;
    }
    return;
}




/**
 * @brief Compute the height of a red-black binary search tree.
 * @param tree Pointer to the root of the tree.
 * @return The height of the tree.
 */
int heightRedBlackBST(RedBlackBST tree){
    if (tree == NULL) {
        return -1; // height of an empty tree is -1
    }
    int leftHeight = heightRedBlackBST(tree->leftBST);
    int rightHeight = heightRedBlackBST(tree->rightBST);
    if (leftHeight > rightHeight)
        return leftHeight + 1;
    else
        return rightHeight + 1;
}


/**
 * @brief Search for a value in a red-black binary search tree.
 * @param tree Pointer to the root of the tree.
 * @param value The value to search for.
 * @return A pointer to the node containing the value, or NULL if the value is not in the tree.
 */
RedBlackBST searchRedBlackBST(RedBlackBST tree, int value){
    if (tree == NULL)
        return NULL; // value not in the tree
    else if (value < tree->value)
        return searchRedBlackBST(tree->leftBST, value);
    else if (value > tree->value)
        return searchRedBlackBST(tree->rightBST, value);
    else
        return tree; // value found in the tree
}


/**
* @brief Computes the black height of a red-black tree (counts also the root if it is black).
* @param node Pointer to the root node of the tree.
* @return The black height of the tree.
*
* It returns 1 plus the black height of the tree if the root is black or the black height with a red root.
* It returns -1 if the black height of the left and right subtrees of the root are different
* or equal to -1.
*
*/

int blackHeightRedBlackBST(RedBlackBST tree) {
  if (!tree) {
    return 1; // If the tree is empty, then the black height is 1.
  }
  int leftHeight = blackHeightRedBlackBST(tree->leftBST); // Recursively compute the black height of the left subtree.
  int rightHeight = blackHeightRedBlackBST(tree->rightBST); // Recursively compute the black height of the right subtree.

  if(leftHeight!=rightHeight) // the black height of the left and right subtrees must be equal
    return -1;
  if(leftHeight==-1)
    return -1;

  // If the left and right subtrees have the same black height and the root node is black, then the black height of the tree is increased by 1.
  if (tree->color == BLACK) {
    return leftHeight + 1;
  }
  return leftHeight;
}

/**
 * @brief Test if a Red-Black BST is a valid Red-Black BST.
 * @param tree Pointer to the root node of the Red-Black BST.
 * @return 1 if the Red-Black BST is a valid Red-Black BST, 0 otherwise.
 */
int isRedBlackBST(RedBlackBST tree){
    if (tree == NULL){
        return 1;
    }
    if (tree->color == RED){
        if ((tree->leftBST != NULL)&&(tree->leftBST->color == RED)){
            return 0;
        }
        if ((tree->rightBST != NULL)&&(tree->rightBST->color == RED)){
            return 0;
        }
        if (blackHeightRedBlackBST(tree) == -1){
            return -1;
        }
    }
    return MIN(isRedBlackBST(tree->leftBST),isRedBlackBST(tree->rightBST));
}


/**
 * @brief Build a red-black binary search tree from a given permutation.
 * @param permutation Array of integers representing the permutation
 * @param n size of the array
 * @return A red-black binary search tree built by successively inserting the elements of permutation.
 */
RedBlackBST buildRedBlackBSTFromPermutation(int *permutation,size_t n){
    if (n == 0)
        return NULL;
    RedBlackBST tree = createEmptyRedBlackBST();
    for(int i=0;i<n;i++){
        insertNodeRedBlackBST(&tree, permutation[i]);
    }
    return tree;
}


/**
 * @brief Print the elements of a binary search tree in a pretty format.
 * @param tree Pointer to the root of the tree.
 * @param space Space to be printed before the current element.
 */
void prettyPrintRedBlackBST(RedBlackBST tree, int space) {
    if (tree == NULL) {
        return;
    }
    space += 10;

    prettyPrintRedBlackBST(tree->rightBST, space);

    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("[%d,%d]\n", tree->value, tree->color);

    prettyPrintRedBlackBST(tree->leftBST, space);
    return ;
}
