/**
 * @file graph.c
 *
 * @brief This file implements a graph data structure using a table of lists.
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../graph/graph.h"
#include "../heap/heap.h"

void PrimOneComponent(Graph g, int s){
   int s_min;
   Heap* tas = createHeap(g.numberVertices);
   int* marquage = malloc(sizeof(int)*g.numberVertices);
   for (int i = 0; i<g.numberVertices;i++){
      insertHeap(tas,i,INFINITY);
      marquage[i] = 1;
   }
   
   modifyPriorityHeap(tas, s, 0);
   g.parents[s]= -1;
   List list_current;
   
   while (tas->nbElements >= 0){
      s_min = removeElement(tas);
      marquage[s_min] = 0; //On marque que s_min n'est plus dans le tas
      list_current = g.array[s_min];
      while (list_current != NULL){
         int d = distance(g.xCoordinates[s_min],g.yCoordinates[s_min],g.xCoordinates[list_current->value],g.yCoordinates[list_current->value]);
         if ((marquage[list_current->value])&&(d<tas->priority[list_current->value])){
            g.parents[list_current->value] = s_min;
            modifyPriorityHeap(tas, list_current->value, d);
         }
         list_current = list_current->nextCell;
      }
   }
   free(marquage);
   free(tas->position);
   free(tas->heap);
   free(tas->priority);
   free(tas);
   return;
}



/**
 * @brief Function that computes a minimum spanning tree of graph g of the connex component of the vertex s
 *
 * @param graph The graph
 * @param s Index of the initial vertex of the Prim procedure.
 *
 * The array parents is updated so that it contains the spanning tree
 * computed by the Prim algorithm.
 * Note that the array parents must be initialized before calling the function.
 */
 void Prim(Graph g, int s){
   for (int i =0; i<g.numberVertices;i++){
        if (g.parents[i] == -1){
            PrimOneComponent(g, i);
        }
    }
 }

