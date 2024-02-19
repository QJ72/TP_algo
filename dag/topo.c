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
    int i;
    int j; 
    int c = 0;
    Stack* s = createStack();
    for (i=0;i<graph.numberVertices;i++){
        if (graph.parents[i] == -1){
            graphDFS(graph,i);
        }
    }
    for (i=0;i<graph.numberVertices;i++){
        if (i == graph.parents[i]){
            push(s,i);
        }
        while (isStackEmpty(*s) == 0){
            int temp = pop(s);
            graph.topological_ordering[c] = temp;
            c += 1;
            for (j=0;j<graph.numberVertices;j++){
                if ((graph.parents[j] == temp)&&(j != temp)){
                    push(s,j);
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

