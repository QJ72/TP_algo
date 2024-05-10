#include <stdlib.h>
#include <stdio.h>
#include "../graph/graph.h"
#include "topo.h"
#include "time.h"

int main() {
    srand(time(NULL));
    // Create a graph
    int n = 15;
    double sigma = 0.3;
    Graph graph = createGraph(1,n,sigma);

    // Print the graph to the console
    printConsoleGraph(graph);

    // Draw the graph to a file
    drawGraph(graph, "graph.svg",0,1);

    //topological ordering
    
    topologicalSort(graph);
  
    printConsoleGraph(graph);
    //drawGraph(graph, "topo.svg",0,1);
    //topological ordering+earlyest dates
  
    computeEarliestStartDates(graph);
    printConsoleGraph(graph);
    drawGraph(graph, "dates.svg",0,2);
    for (int i=0; i< graph.numberVertices;i++){
      printf("%f ", graph.earliest_start[i]);
    }
    printf("\n");
    //topological ordering+earlyest dates+latest dates
    
    computeLatestStartDates(graph);
    printConsoleGraph(graph);
    drawGraph(graph, "dates.svg",3,1);
    for (int i=0; i< graph.numberVertices;i++){
      printf("%f ", graph.latest_start[i]);
    }
    printf("\n");
    
    return 0;
}
