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


/**
 * @brief Function to perform a topological sort of a graph. Update the field topological_ordering of the graph.
 *
 * @param graph The graph to be sorted.
 */
void topologicalSort(Graph graph){
    int i = 0;
    int c = 0;
    if (graph.topological_ordering != NULL){
        return;
    }
    graph.topological_ordering = (int*)malloc(graph.numberVertices*sizeof(int));
    for (i=0;i<graph.numberVertices;i++){
        if (graph.parents[i] == i){
            Stack* s = createQueue();
            push(s,i);
            while (isStackEmpty(*s) == 0){
                int vertex_current = pop(s);
                graph.topological_ordering[c];
                c += 1;
                List list_current = graph.array[vertex_current];
                while (list_current != NULL){
                    push(s, list_current->value);
                    list_current = list_current->nextCell;
                }
            }
        }
    }

    return;
}


/**
 * @brief Function to compute the earliest start date of each vertex in a graph.
 *
 * @param graph The graph for which to compute the earliest start dates.
 * Updates the array containing the earliest start date of each vertex in the graph structure.
 */

void computeEarliestStartDates(Graph graph) {
    return;
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

