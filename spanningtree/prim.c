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


int IsInHeap(Heap tas, int s){
   for (int i =0;i<tas.nbElements;i++){
      if (tas.heap[i] == s){
         return 1;
      }
   }
   return 0;
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
   int s_min;
   Heap* tas = createHeap(g.numberVertices);
   for (int i = 0; i<g.numberVertices;i++){
      insertHeap(tas,i,INFINITY);
   }
   
   modifyPriorityHeap(tas, s, 0);
   g.parents[s]= -1;
   List list_current;
   
   while (tas != NULL){
      s_min = removeElement(tas);
      list_current = g.array[s_min];
      while (list_current != NULL){
         int d = distance(g.xCoordinates[s_min],g.yCoordinates[s_min],g.xCoordinates[list_current->value],g.yCoordinates[list_current->value]);
         if ((IsInHeap(*tas,s))&&(d<tas->priority[list_current->value])){
            g.parents[list_current->value] = s_min;
            modifyPriorityHeap(tas, list_current->value, d);
         }
         list_current = list_current->nextCell;
      }
   }
   return;

 }

