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
        graph.earliest_start[graph.topological_ordering[i]] = max;
    }
    return;
}


Stack suc(Graph graph,int n){
    Stack* s = createStack();
    for (int j=n+1;j<graph.numberVertices;j++){
        if (findKeyInList(graph.array[graph.topological_ordering[n]],graph.topological_ordering[j]) != NULL){
            push(s,graph.topological_ordering[j]);
        }
    return s;
    }
}

/**
 * @brief Function to compute the latest start date of each vertex in a graph.
 *
 * @param graph The graph for which to compute the latest start dates.
 * Updates the array containing the latest start date of each vertex in the graph structure.
 */
void computeLatestStartDates(Graph graph) {
    for (int i=0;i<graph.numberVertices;i++){
        Stack st = suc(graph,i);
        if (st == NULL){
            graph.latest_start[graph.topological_ordering[i]];
        } else {
            int min = 1; // 1 est max global
            while (st != NULL){
                int p = pop(st);
                min = MIN(min,graph.latest_start[p] - distance( graph.xCoordinates[p], graph.yCoordinates[p],graph.xCoordinates[graph.topological_ordering[i]], graph.yCoordinates[graph.topological_ordering[i]]));
            }
            graph.latest_start[graph.topological_ordering[i]] = min;
        }
    }
    
    return;
}

