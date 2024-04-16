/**
 * @file topo.c
 *
 * @brief This file implements based on the topological ordering.
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../graph/graph.h"
#include "../stack/stack.h"
#include "../queue/queue.h"
#define MAX(i, j) (((i) > (j)) ? (i) : (j))
#define MIN(i, j) (((i) < (j)) ? (i) : (j))

/**
 * @brief Function to perform a topological sort of a graph. Update the field topological_ordering of the graph.
 *
 * @param graph The graph to be sorted.
 */
void topologicalSort(Graph graph){
    numberOfComponents(graph);
    int counter = 0;
    Stack* s = createStack();
    for (int i =0; i< graph.numberVertices;i++){
        if (graph.parents[i] == -1){
            push(s, i);
        }
        graph.parents[i] = -1;
    }

    while (isStackEmpty(*s) == 0){
        int vertex_current = pop(s);
        graph.topological_ordering[counter] = vertex_current;
        counter += 1;
        List list_current = graph.array[vertex_current];
        while (list_current != NULL){
            if (graph.parents[list_current->value] == -1){
                graph.parents[list_current->value] = vertex_current;
                push(s, list_current->value);
            }
            list_current = list_current->nextCell;
        } 
    }

    /*
    numberOfComponents(graph);
    int counter = 0;
    Queue* q = createQueue();
    for (int i =0; i< graph.numberVertices;i++){
        if (graph.parents[i] == -1){
            enqueue(q, i);
        }
        graph.parents[i] = -1;
    }


    while (isQueueEmpty(*q) == 0){
        queuePrint(*q);
        int vertex_current = dequeue(q);
        graph.topological_ordering[counter] = vertex_current;
        counter +=1;
        List list_current = graph.array[vertex_current];
        while (list_current != NULL){
            if (graph.parents[list_current->value] == -1){
                graph.parents[list_current->value] = vertex_current;
                enqueue(q, list_current->value);
            }
            list_current = list_current->nextCell;
        }
    }
    */
    return;
}
/**
 *  @brief Auxiliary function to Dates, put the predecessors in an array 
 * 
 * @param graph The graph for which to compute the earliest dates.
 * @param n indice of the element in topological_order
*/

Stack pred(Graph graph,int n){
    return NULL;
}
/**
 * @brief Function to compute the earliest start date of each vertex in a graph.
 *
 * @param graph The graph for which to compute the earliest start dates.
 * Updates the array containing the earliest start date of each vertex in the graph structure.
 */

void computeEarliestStartDates(Graph graph) {
    
}


Stack suc(Graph graph,int n){
    return NULL;
}

/**
 * @brief Function to compute the latest start date of each vertex in a graph.
 *
 * @param graph The graph for which to compute the latest start dates.
 * Updates the array containing the latest start date of each vertex in the graph structure.
 */
void computeLatestStartDates(Graph graph) {
    return;
}

