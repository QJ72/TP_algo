#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "../list/list.h"

/**
 * @brief Creates a new, empty queue.
 *
 * @return A pointer to the newly created queue.
 */
 Queue* createQueue() {
    Queue* q;
    q = (Queue*)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}


/**
 * @brief Checks whether the queue is empty.
 *
 * @param q The queue to check.
 * @return 1 if the queue is empty, 0 otherwise.
 */
int isQueueEmpty(Queue q) {
    if ((q.front == NULL)&&(q.rear == NULL)){
        return 1;
    }else {return 0;}
}


/**
 * @brief Prints all the elements in the queue, from front to rear.
 *
 * @param q The queue to print.
 */
void queuePrint(Queue q) {
    Cell* cellule ;
    cellule = (Cell*)malloc(sizeof(Cell));
    cellule = q.front;
    printList(cellule, 0);
    return;
}


/**
 * @brief Adds an element to the rear of the queue.
 *
 * @param q A pointer to the queue to add the element to.
 * @param data The data to be added to the queue.
 */
void enqueue(Queue* q, int data) {
    Cell* cellule ;
    cellule = (Cell*)malloc(sizeof(Cell));
    cellule->value = data;
    cellule->key = NULL;
    cellule->nextCell = NULL;
    if (isQueueEmpty(*q)){
        q->front = cellule;
        q->rear = cellule;
    } else {
        q->rear->nextCell = cellule;
        q->rear = cellule;
    }
    return;
}

/**
 * @brief Removes and returns the front element of the queue.
 *
 * @param q A pointer to the queue to remove the front element from.
 * @return The value stored in the front element of the queue.
 */
int dequeue(Queue* q) {
    if (isQueueEmpty(*q)){
        return -1;
    }else{
        int a = q->front->value;
        if (q->front == q->rear){
            q->front = NULL ;
            q->rear = NULL ;
        } else {
            Cell* cellule;
            cellule = (Cell*)malloc(sizeof(Cell));
            cellule = q->front;
            q->front = q->front->nextCell;
            free(cellule);
    }
    return a;
    }
}


/**
 * @brief Returns the value of the front node but doesn't modify the queue
 *
 * @param q The queue to get the front value.
 * @return The value of the front node.
 */
int queueGetFrontValue(Queue q) {
    if (isQueueEmpty(q)){
        return -1;
    }
    return q.front->value;
}
