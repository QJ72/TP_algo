/**
 * @file graph.c
 *
 * @brief This file implements a graph data structure using a table of lists.
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "graph.h"
#include "../stack/stack.h"
#include "../queue/queue.h"
#include "../list/list.h"
/**
 * @brief Computes the Euclidean distance between two points.
 *
 * @param x1 x coordinate of the first point
 * @param y1 y coordinate of the first point.
 * @param x2 x coordinate of the second point.
 * @param y2 y coordinate of the second point.
 * @return The Euclidean distance between the input points
 */
double distance(double x1, double y1, double x2, double y2){
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}


/**
 * @brief Function to add an oriented edge in a graph.
 *
 * @param origin Origin vertex  of the edge.
 * @param destination Destination vrtex of the edge.
 * @param graph The graph in which the edge is added.
 *
 * Only the array of adjacency lists is updated.
 */
void addEdgeInGraph(Graph graph, int origin, int destination) {
    double x1 = graph.xCoordinates[origin];
    double y1 = graph.yCoordinates[origin];
    double x2 = graph.xCoordinates[destination];
    double y2 = graph.yCoordinates[destination];

    if (distance(x1,y1,x2,y2)< graph.sigma){
        graph.array[origin]= addKeyValueInList(graph.array[origin], NULL, destination);
    }
    return;
}


/**
 * @brief Function to create a random graph with a specified number of vertices and parameter sigma.
 *
 * @param numVertices The number of vertices in the graph.
 * @param sigma Parameter of the procedure to generate a random graph.
 * @param directedt The graph is undirected if directed==0, directed otherwise
 *
 * @return A pointer to the new graph.
 *
 * The elements of the array parents are set to -1.
 * The array of adjacency lists must be updated.
 * If the graph is a directed one, then there exist an edge from P1(x1,y1)
 * to P2(x2,y2) if and only if the euclidean distance between P1 and P2 is
 * less than sigma and y1<y2.
 * If the graph is a undirected one, then there exist an edge between P1(x1,y1)
 * and P2(x2,y2) if and only if the euclidean distance between P1 and P2 is
 * less than sigma.
 */
Graph createGraph(int directed, int numVertices, double sigma) {
    Graph graph;
    int i;
    int j;

    graph.numberVertices = numVertices;
    graph.array = NULL;
    graph.array = (List*)malloc(graph.numberVertices*sizeof(List));
    graph.xCoordinates = NULL;
    graph.xCoordinates = (double*)malloc(graph.numberVertices*sizeof(double));
    graph.yCoordinates = NULL;
    graph.yCoordinates = (double*)malloc(graph.numberVertices*sizeof(double));
    graph.sigma = sigma;
    graph.parents = NULL;
    graph.parents = (int*)malloc(graph.numberVertices*sizeof(int));
    graph.topological_ordering = NULL;
    graph.topological_ordering = (int*)malloc(graph.numberVertices*sizeof(int));
    graph.earliest_start = (double*)malloc(graph.numberVertices*sizeof(double));
    graph.latest_start = (double*)malloc(graph.numberVertices*sizeof(double));

    for (i=0; i <graph.numberVertices;i++){
        graph.xCoordinates[i] = (double)rand()/RAND_MAX;
        graph.yCoordinates[i] = (double)rand()/RAND_MAX;
        graph.parents[i] = -1;
        graph.topological_ordering[i] = -1; //Pas obligatoire mais permet plus de visibilité
    }

    for(i=0; i <graph.numberVertices;i++){
        graph.array[i] = NULL;
        for(j=0;j<graph.numberVertices;j++){
            if (i != j){
                if((directed == 0)||(graph.yCoordinates[i]<= graph.yCoordinates[j])){
                    addEdgeInGraph(graph, i, j);
                }
            }
        }
    }

    return graph;
}


/**
 * @brief Function to print the graph in the console.
 *
 * @param graph The graph to print.
 */
void printConsoleGraph(Graph graph){
    int i;

    for (i=0;i<graph.numberVertices;i++){
        printf("Vertex %d: (%f,%f) \n", i, graph.xCoordinates[i], graph.yCoordinates[i]);
    }

    for (i=0;i<graph.numberVertices;i++){
        printf("Vertex %d: ", i);
        printList(graph.array[i], 0);
        printf("\n");
    }

    printf("parents : ");
    for (i=0;i<graph.numberVertices;i++){
        printf("%d ", graph.parents[i]);
    }
    printf("\n");

    printf("topological order :");
    for (i=0;i<graph.numberVertices;i++){
        printf("%d ", graph.topological_ordering[i]);
    }
    printf("\n");
    
    return;
}

/**
 * @brief Function to draw the graph in a svg file.
 *
 * @param graph The graph to print.
 * @param filename Name of the svg file.
 * @param type if 0, draws only the graph, if 1 draws the covering tree, if 2 draws both graph and spanning tree, if 3 draws the graph with topological order and dates
 * @param directed If directed==0, the graph is undirected and lines are drawn. Otherwise, arrows are drawn.
 */


void drawGraph(Graph graph, char* filename, int type, int directed){

    FILE *fptr;
    fptr = fopen(filename, "w");
    if (fptr == NULL)
    {
        printf("Error opening file %s\n",filename);
        exit(-1);
    }
    fprintf(fptr, "<?xml version=\"1.0\" standalone=\"no\"?>\n");
    fprintf(fptr, "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n");
    fprintf(fptr, "  \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
    fprintf(fptr, "<svg width=\"800\" height=\"800\"\n");
    fprintf(fptr, "     xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
    fprintf(fptr, "<rect x=\"0\" y=\"0\" width=\"100%%\" height=\"100%%\" fill=\"white\" />\n");

    fprintf(fptr, "<defs>\n");
    fprintf(fptr, "<marker id=\"arrow\" markerWidth=\"10\" markerHeight=\"10\" refX=\"10\" refY=\"3\" orient=\"auto\">\n");
    fprintf(fptr, "<path d=\"M0,0 L0,6 L9,3 z\"/>\n");
    fprintf(fptr, "</marker>\n");
    fprintf(fptr, "</defs>\n");

    for(int i=0;i<graph.numberVertices;i++){
        int x1 = (int) (600*graph.xCoordinates[i])+100;
        int y1 = (int) (600*graph.yCoordinates[i])+100;
        fprintf(fptr, "<circle cx=\"%d\" cy=\"%d\" r=\"%d\" fill=\"blue\" />\n", x1, y1, 3);
    }


    for(int i=0;i<graph.numberVertices;i++){
        int x1 = (int) (600*graph.xCoordinates[i])+100;
        int y1 = (int) (600*graph.yCoordinates[i])+100;
        fprintf(fptr, "<circle cx=\"%d\" cy=\"%d\" r=\"%d\" fill=\"blue\" />\n", x1, y1, 3);
        for(int j=i+1;j<graph.numberVertices;j++)
            if(distance(graph.xCoordinates[i],graph.yCoordinates[i],
                        graph.xCoordinates[j],graph.yCoordinates[j]) <= graph.sigma){
                int x2 = (int) (600*graph.xCoordinates[j])+100;
                int y2 = (int) (600*graph.yCoordinates[j])+100;
                int xorigin, yorigin, xdestination, ydestination;
                if(graph.yCoordinates[i]<graph.yCoordinates[j]){
                    xorigin = x1; yorigin = y1;
                    xdestination = x2; ydestination = y2;
                }
                else{
                    xorigin = x2; yorigin = y2;
                    xdestination = x1; ydestination = y1;
                }
                char arrow[30];
                if(directed==1)
                    strcpy(arrow,"marker-end=\"url(#arrow)\"");
                else
                    strcpy(arrow," ");

                switch(type){
                    case 0:
                    case 3:
                        fprintf(fptr, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\"\n",
                                xorigin, yorigin, xdestination, ydestination);
                        fprintf(fptr, "      style=\"stroke: darkgray;\" %s />\n",arrow);
                        break;
                    case 1:
                        if(graph.parents[i]==j || graph.parents[j]==i){
                            fprintf(fptr, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\"\n",
                                    xorigin, yorigin, xdestination, ydestination);
                            fprintf(fptr, "      style=\"stroke: red;\" %s />\n",arrow);
                        }
                        break;
                    case 2:
                        fprintf(fptr, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\"\n",
                                xorigin, yorigin, xdestination, ydestination);
                        if(graph.parents[i]==j || graph.parents[j]==i)
                            fprintf(fptr, "      style=\"stroke: red;\" %s />\n",arrow);
                        else
                            fprintf(fptr, "      style=\"stroke: darkgray;\" %s />\n",arrow);
                        break;
                }
        }
    }
    if(type==3){
        for(int i=0;i<graph.numberVertices;i++){
            int vertex = graph.topological_ordering[i];
            int x1 = (int) (600*graph.xCoordinates[vertex])+100;
            int y1 = (int) (600*graph.yCoordinates[vertex])+100;
            fprintf(fptr, "<text x=\"%d\" y=\"%d\" font-family=\"Verdana\" font-size=\"10\"> P%d:[%d,%.3lf,%.3lf]  </text>",x1+10,y1,vertex,i,graph.earliest_start[vertex],graph.latest_start[vertex]);
        }
    }
    fprintf(fptr, "</svg>\n");
    fclose(fptr);
}

/**
 * @brief Function that performs a depth first search from a vertex.
 *
 * @param graph The graph on which the depth first search is done.
 * @param vertex The origin of depth first search.
 *
 * The array parents is updated so that it contains the covering tree
 * computed by the depth first search.
 * Note that the array parents is not initialized in the function and
 * must be initialized before calling the function.
 */

void graphDFS(Graph graph, int vertex) {
    Stack* s = createStack();
    //le sommet d'origine est son propre parent
    graph.parents[vertex] = vertex;
    push(s, vertex);
    while (isStackEmpty(*s) == 0){
        int vertex_current = pop(s);
        List list_current = graph.array[vertex_current];
        while (list_current != NULL){
            if (graph.parents[list_current->value] == -1){
                graph.parents[list_current->value] = vertex_current;
                push(s, list_current->value);
            }
            list_current = list_current->nextCell;
        }
    }
    return;
}


/**
 * @brief Function that performs a breadth first search from a vertex.
 *
 * @param graph The graph on which the breadth first search is done.
 * @param vertex The origin of breadth first search.
 *
 * The array parents is updated so that it contains the covering tree
 * computed by the breadth first search.
 * Note that the array parents is not initialized in the function and
 * must be initialized before calling the function.
 */
void graphBFS(Graph graph, int vertex){
    Queue* q = createQueue();
    //le sommet d'origine est son propre parent
    graph.parents[vertex] = vertex;
    enqueue(q, vertex);
    while (isQueueEmpty(*q) == 0){
        int vertex_current = dequeue(q);
        List list_current = graph.array[vertex_current];
        while (list_current != NULL){
            if (graph.parents[list_current->value] == -1){
                graph.parents[list_current->value] = vertex_current;
                enqueue(q, list_current->value);
            }
            list_current = list_current->nextCell;
        }
    }
    return;
}


/**
 * @brief Function that counts te number of connex components in a graph and that computes a covering forest (one tree by components)
 *
 * @param graph The graph
 *
 * The array parents is updated so that it contains the covering tree
 * computed by the breadth first search.
 * Note that the array parents is initialized in the function.
 */
int numberOfComponents(Graph graph){
    int i;
    int c = 0;
    for (i=0;i<graph.numberVertices;i++){
        if (graph.parents[i] == -1){
            c += 1;
            graphDFS(graph, i);
        }
    }
    return c;

}

