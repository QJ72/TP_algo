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
#define MAX(i, j) (((i) > (j)) ? (i) : (j))
#define MIN(i, j) (((i) < (j)) ? (i) : (j))

/**
 * @brief Function to perform a topological sort of a graph. Update the field topological_ordering of the graph.
 *
 * @param graph The graph to be sorted.
 */
void topologicalSort(Graph graph){
    int fin = 1;
    int c = graph.numberVertices;
    while (fin == 1){
        fin = 0;
    }

    return;
}
/**
 *  @brief Auxiliary function to Dates, put the predecessors in an array 
 * 
 * @param graph The graph for which to compute the earliest dates.
 * @param n indice of the element in topological_order
*/

Stack pred(Graph graph,int n){
    Stack* s = createStack();
    for (int j=0;j<n;j++){
        if (findKeyInList(graph.array[graph.topological_ordering[j]],graph.topological_ordering[n]) != NULL){
            push(s,graph.topological_ordering[j]);
        }
    return s;
    }
}
/**
 * @brief Function to compute the earliest start date of each vertex in a graph.
 *
 * @param graph The graph for which to compute the earliest start dates.
 * Updates the array containing the earliest start date of each vertex in the graph structure.
 */

void computeEarliestStartDates(Graph graph) {
    for (int i =0;i<graph.numberVertices;i++){
        Stack st = pred(graph,i);
        int max = 0;
        while (st != NULL){
            int p = pop(st);
            max = MAX(max,graph.earliest_start[p] + distance( graph.xCoordinates[p], graph.yCoordinates[p],graph.xCoordinates[graph.topological_ordering[i]], graph.yCoordinates[graph.topological_ordering[i]]));
        }
        graph.earliest_start[graph.parents[i]] = max;
    }
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

