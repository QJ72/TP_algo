#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#define MIN(i, j) (((i) < (j)) ? (i) : (j))
#include <math.h>

/**
 * @brief Helper function to swap two elements in the heap.
 * @param h A pointer to the Heap data structure.
 * @param i The index of the first element.
 * @param j The index of the second element.
 */
void swap(Heap *h, int i, int j) {
    int temp = h->heap[i];
    h->heap[i] = h->heap[j];
    h->heap[j] = temp;

	h->position[h->heap[i]] = i;
	h->position[h->heap[j]] = j;
}

/**
 * @brief Creates a new Heap data structure.
 * @param n The maximum number of elements that the heap can store.
 * @return A pointer to the newly created Heap data structure.
 * The elements of the arrays position and priority are initialized to -1
 */
Heap* createHeap(int n) {
	int i;
	Heap* h = NULL;
	if (n <= 0){ return NULL;}

	h = (Heap*)malloc(sizeof(Heap));
	h->n = n;
	h->nbElements = 0 ;
	h->position = NULL;
	h->priority = NULL;
	h->heap = NULL;
	h->position = (int*)malloc(n*sizeof(int));
	h->heap = (int*)malloc(n*sizeof(int));
	h->priority = (double*)malloc(n*sizeof(double));
	
	
	for (i=0;i<n;i++){
		*(h->position+i) = -1;
		*(h->heap+i) = '?';
		*(h->priority+i) = -1;
	}
    return h ;
}

/**
 * @brief Prints the elements in the Heap data structure.
 * @param h The Heap data structure to print.
 */

void printHeap(Heap h) {
	int i;

	printf("\n");
	printf("n: %d\n", h.n);
	printf("nElements: %d\n", h.nbElements);
	printf("Position : [");
	for (i=0;i<h.n;i++){
		printf("%d ",h.position[i]);
	}
	printf("] \n");
	printf("Priority : [");
	for (i=0;i<h.n;i++){
			printf("%f ",h.priority[i]);
	}
	printf("] \n");
	printf("Heap : [");
	for (i=0;i<h.n;i++){
		if (h.heap[i] != '?'){
			printf("%d ",h.heap[i]);
		}
	}
	printf("] \n");
    return;
}

/**
 * @brief Gets the element with the smallest priority (smallest value in the priority array) from the Heap data structure.
 * @param h The Heap data structure to get the element from.
 * @return The element with the smallest priority.
 */
int getElement(Heap h) {
	int i;
	int min = h.priority[h.heap[0]];
	int res = h.heap[0];
	for (i=0;i<h.nbElements;i++){
		if (min>h.priority[h.heap[i]]){
			min = h.priority[h.heap[i]];
			res = h.heap[i];
		}
	}
    return res;
}

/**
 * @brief Inserts a new element into the Heap data structure with the given priority.
 * @param h A pointer to the Heap data structure to insert the element into.
 * @param element The element to insert.
 * @param priority The priority of the element to insert.
 */
void insertHeap(Heap *h, int element, double priority) {
	int j = h->nbElements;
    h->heap[j] = element;
    h->position[element] = j;
    h->priority[element] = priority;
    h->nbElements++;

    while (j > 0 && h->priority[h->heap[j]] < h->priority[h->heap[(j-1)/2]]) {
        swap(h, j, (j-1)/2);
        j = (j-1)/2;
    }
}

/**
 * @brief Modifies the priority of an element in the Heap data structure.
 * @param h A pointer to the Heap data structure to modify.
 * @param element The element whose priority is to be modified.
 * @param priority The new priority of the element.
 */
void modifyPriorityHeap(Heap *h, int element, double priority) {
	int j = h->position[element];
    double oldPriority = h->priority[element];
    h->priority[element] = priority;

    if (priority < oldPriority) {
        while (j > 0 && h->priority[h->heap[j]] < h->priority[h->heap[(j-1)/2]]) {
            swap(h, j, (j-1)/2);
            j = (j-1)/2;
        }
    } else {
        while (2*j + 1 < h->nbElements) {
            int smallestChild = 2*j + 1;
            if (2*j + 2 < h->nbElements && h->priority[h->heap[2*j + 2]] < h->priority[h->heap[2*j + 1]]) {
                smallestChild = 2*j + 2;
            }
            if (h->priority[h->heap[j]] <= h->priority[h->heap[smallestChild]]) {
                break;
            }
            swap(h, j, smallestChild);
            j = smallestChild;
        }
    }
}

int fallInTheHeap(Heap* h, int j){
	if (j>h->nbElements){
		return (j-1)/2;
	}
	if (h->priority[h->heap[j*2+1]]< h->priority[h->heap[j*2 +2]]){
		swap(h,j,j*2+1);
		return fallInTheHeap(h,2*j+1);
	} else {
		swap(h,j,j*2+2);
		return fallInTheHeap(h,2*j+2);
	}
}

/**
 * @brief Removes the element with the smallest priority (smallest value in the priority array) from the Heap data structure.
 * @param h A pointer to the Heap data structure to remove the element from.
 * @return The element with the smallest priority that was removed from the Heap data structure.
 */
int removeElement(Heap *h) {
	if (h->nbElements == 0) {
        return -1; // Indicate that the heap is empty.
    }
    int res = h->heap[0];
    h->heap[0] = h->heap[h->nbElements - 1];
	h->position[h->nbElements-1] = -1;
    h->position[h->heap[0]] = 0;
    h->nbElements--;
    modifyPriorityHeap(h, h->heap[0], h->priority[h->heap[0]]);
    return res;
}