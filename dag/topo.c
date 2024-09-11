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

double weight(Graph graph,int vertex1, int vertex2){
    return distance(graph.xCoordinates[vertex1],graph.yCoordinates[vertex1],graph.xCoordinates[vertex2],graph.yCoordinates[vertex2]);
}

void DFS_Topo(Graph* graph,int vertex,int* counter){
    graph->parents[vertex] = 0;
    List voisins = graph->array[vertex];
    List current = voisins;
    while (current != NULL){
        if (graph->parents[current->value] == -1){
            DFS_Topo(graph,current->value,counter);
        }
        current = current->nextCell;
    }
    graph->topological_ordering[graph->numberVertices-1- *counter] = vertex;
    *counter += 1;
    return;
}

/**
 * @brief Function to perform a topological sort of a graph. Update the field topological_ordering of the graph.
 *
 * @param graph The graph to be sorted.
 */
void topologicalSort(Graph graph){
    int counter = 0;
    for (int i =0;i<graph.numberVertices;i++){
        if (graph.parents[i] == -1){ 
            DFS_Topo(&graph,i, &counter);
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

Stack* pred(Graph graph,int n){
    Stack* predStack = createStack();
    if (n ==0){
        freeList(*predStack);
        free(predStack);
        return NULL;
    }
    for (int i =n;i>=0;i--){
        List next_predecessors = graph.array[graph.topological_ordering[i]];
        while (next_predecessors != NULL){
            if (next_predecessors->value == graph.topological_ordering[n]){
                push(predStack,graph.topological_ordering[i]);
            }
            next_predecessors = next_predecessors->nextCell;
        }
    }
    return predStack;
}
/**
 * @brief Function to compute the earliest start date of each vertex in a graph.
 *
 * @param graph The graph for which to compute the earliest start dates.
 * Updates the array containing the earliest start date of each vertex in the graph structure.
 */

void computeEarliestStartDates(Graph graph) {
    for (int i = 0; i<graph.numberVertices;i++){
        graph.earliest_start[i] = 0;
    }
    Stack* predVertex;
    for (int vertexIndex = 0; vertexIndex<graph.numberVertices;vertexIndex++){
        predVertex = pred(graph, vertexIndex);
        if (predVertex != NULL){
            while (*predVertex != NULL){
                int sp = pop(predVertex);
                graph.earliest_start[graph.topological_ordering[vertexIndex]] = MAX(graph.earliest_start[sp] + weight(graph,graph.topological_ordering[vertexIndex],sp),graph.earliest_start[graph.topological_ordering[vertexIndex]]);
            }
            free(predVertex);
        }
    }
}


Stack* suc(Graph graph,int n){
    Stack* sucStack = createStack();
    
    List next_successessors = graph.array[graph.topological_ordering[n]];

    if (next_successessors == NULL){
        freeList(*sucStack);
        free(sucStack);
        return NULL;
    }
    while (next_successessors != NULL){
        push(sucStack,next_successessors->value);
        next_successessors = next_successessors->nextCell;
    }
    return sucStack;
}

/**
 * @brief Function to compute the latest start date of each vertex in a graph.
 *
 * @param graph The graph for which to compute the latest start dates.
 * Updates the array containing the latest start date of each vertex in the graph structure.
 */
void computeLatestStartDates(Graph graph) {
    double latestStart = 0;
    for (int i = 0; i < graph.numberVertices;i++){
        latestStart = MAX(latestStart,graph.earliest_start[i]);
    }

    for (int j = 0; j < graph.numberVertices;j++){
        graph.latest_start[j] = latestStart;
    }
    Stack* sucVertex;

    for (int vertexIndex = graph.numberVertices-1;vertexIndex >= 0; vertexIndex--){
        sucVertex = suc(graph,vertexIndex);
        if (sucVertex != NULL){
            while (*sucVertex != NULL){
                int sp = pop(sucVertex);
                graph.latest_start[graph.topological_ordering[vertexIndex]] = MIN(graph.latest_start[sp] - weight(graph,graph.topological_ordering[vertexIndex],sp),graph.latest_start[graph.topological_ordering[vertexIndex]]);
            }
            free(sucVertex);
        }
    }
    return;
}

