#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

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

    temp = h->position[h->heap[i]];
    h->position[h->heap[i]] = h->position[h->heap[j]];
    h->position[h->heap[j]] = temp;
}


/**
 * @brief Creates a new Heap data structure.
 * @param n The maximum number of elements that the heap can store.
 * @return A pointer to the newly created Heap data structure.
 * The elements of the arrays position and priority are initialized to -1
 */
Heap* createHeap(int n) {

    Heap* tas;
    int i;
    if(n<=0){
        return NULL;
    }
    tas = (Heap *) malloc(sizeof(Heap));
    tas -> n = n;
    tas -> nbElements = 0;
    tas -> position = (int *) calloc(n,sizeof(int));
    tas -> heap = (int *) calloc(n,sizeof(int));
    tas -> priority = (double *) calloc(n,sizeof(double));
    for(i = 0; i < n; i++){
        tas->heap[i]=-1;
        tas->priority[i]=-1;
        tas->position[i]=-1;
    }
    return tas;
}

double abs_double(double x){
    if(x>=0.){
        return x;
    }
    return ((-1.)*x);
}

int min(int a,int b){
	return (a > b)?b:a;
}

/**
 * @brief Prints the elements in the Heap data structure.
 * @param h The Heap data structure to print.
 */
void printHeap(Heap h) {
    int i;
    if( h.position == NULL){
	printf("n : %d\n", h.n);
    	printf("nbElements : %d\n",h.nbElements);
    	printf("Position : []\n");
	printf("Priority : []\n");
	printf("Heap : []\n");
	return;
    }
    printf("n : %d\n",h.n);
    printf("nbElements : %d\n",h.nbElements);
    printf("Position : [");
    for( i = 0; i<h.n; i++){
        if( i != 0){
            printf(",");
        }
        if(h.position[i] == -1){
            printf("?");
        }
        else
        {
            printf("%d",h.position[i]);
        }
    }
    printf("]\n");
    printf("Priority : [");
    for( i = 0; i<h.n; i++){
        if( i != 0){
            printf(",");
        }
        if(abs_double(h.priority[i] + 1.) < 10E-3){
            printf("?");
        }
        else
        {
            printf("%f",h.priority[i]);
        }
        
    }
    printf("]\n");
    printf("Heap : [");
    for( i = 0; i<h.nbElements; i++){
        if( i != 0){
            printf(",");
        }
        if(abs_double(h.priority[h.heap[i]] + 1.) < 10E-3){
            printf("?");
        }
        else
        {
            printf("%d",h.heap[i]);
        }
    }
    printf("]\n");
    return;
}

/**
 * @brief Gets the element with the smallest priority (smallest value in the priority array) from the Heap data structure.
 * @param h The Heap data structure to get the element from.
 * @return The element with the smallest priority.
 */
int getElement(Heap h) {
    if(h.nbElements <= 0){
        return -1;
    }
    return h.heap[0];
}

int conditionHeap(Heap tas,int i){
    if(!i){
        return 0;
    }
    if(i%2){
        return (tas.priority [tas.heap[i]] > tas.priority [tas.heap [(i-1)/2]]);
    }
    return (tas.priority[tas.heap[i]]>tas.priority[tas.heap[i/2]]);
}

void freeHeapStruct(Heap h){
	if (h.position != NULL){
		free(h.position);
	}
	if (h.priority != NULL){
		free(h.priority);
	}
	if (h.heap != NULL){
		free(h.heap);
	}

}

void freeHeap(Heap* h){
	freeHeapStruct(*h);
	free(h);
}

/**
 * @brief Inserts a new element into the Heap data structure with the given priority.
 * @param h A pointer to the Heap data structure to insert the element into.
 * @param element The element to insert.
 * @param priority The priority of the element to insert.
 */
void percolateDown(Heap *h,int element){
	int i;
	int posE;
    int posI;
	if(h == NULL){
		return;
	}
	posE = h->position[element];
	posI = 2*(posE)+1;
	if(posI > h->nbElements-1){
		return;
	}
    i = h->heap[posI];
	if(((h->priority[element]>h->priority[i]))){
		if( posI+1 < h->nbElements){
			if(h->priority[i]>h->priority[h->heap[posI+1]]) posI++;
		}
		swap(h,posE,posI);
		percolateDown(h,element);
	}else{
        if( posI+1 < h->nbElements){
			if((h->priority[element]>h->priority[h->heap[posI+1]])){
                 posI++;
                swap(h,posE,posI);
		        percolateDown(h,element);
            }
	    }
    }
}
void percolateUp(Heap *h,int element){
	int posE;
    int pere;
	posE = h->position[element];
	if(h == NULL){
		return;
	}
	if(!posE){
		return;
	}
    pere = h->heap[(posE-1)/2];
	if(h->priority[element]<h->priority[pere]){
		swap(h,posE,(posE-1)/2);
		percolateDown(h,element);
		percolateUp(h,element);
	}
}
void insertHeap(Heap *h, int element, double priority) {
    int i;
    if (h->n == h->nbElements) {
        printf("Le tas est rempli.\n");
        return;
    }
    h->nbElements++;
    i=h->nbElements-1;
    h->position[element] = i;
    h->priority [element] = priority; 
    h->heap[i] = element; 
    percolateUp(h,element);
    return;
}

/**
 * @brief Modifies the priority of an element in the Heap data structure.
 * @param h A pointer to the Heap data structure to modify.
 * @param element The element whose priority is to be modified.
 * @param priority The new priority of the element.
 */



void modifyPriorityHeap(Heap *h, int element, double priority) {
    if(h->position[element]==-1){
        return;
    }
	h->priority[element] = priority;
	percolateUp(h,element);
	percolateDown(h,element);
    return;
}


/**
 * @brief Removes the element with the smallest priority (smallest value in the priority array) from the Heap data structure.
 * @param h A pointer to the Heap data structure to remove the element from.
 * @return The element with the smallest priority that was removed from the Heap data structure.
 */
int removeElement(Heap *h) {
	int res;
    int switchValue;
	if(h->nbElements == 0){
		return -1;
	}
    res = getElement(*h);
	if(h->nbElements == 1){
        h->position[res]=-1;
        h->priority[res]=-1;
		h->nbElements--;
		return res;
	}
    switchValue = h->heap[h->nbElements-1];
	swap(h,0,h->position[switchValue]);
    h->position[res]=-1;
    h->priority[res]=-1;
    h->nbElements--;
    percolateDown(h,switchValue);
    percolateUp(h,switchValue);
    return res;
}


