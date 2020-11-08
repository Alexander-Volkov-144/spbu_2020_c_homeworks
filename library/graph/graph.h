#ifndef SPBU_2020_C_HOMEWORKS_GRAPH_H
#define SPBU_2020_C_HOMEWORKS_GRAPH_H


#include <stdbool.h>

typedef struct Graph Graph;
typedef struct Edge Edge;

Graph* createGraph(int countEdges, int countVertex, Edge** edges);

bool depthFirstSearch(Graph* graph, int currentVertex, int* vertexState);

bool isConnected(int fromVertex, int toVertex, Graph* graph);

Edge* createEdge(int start, int end, int weight, bool oriented);

bool isCycled(Graph* graph);

Edge** createArrayOfEdges(int size);

void getAllVertexesConnectedToGiven(Graph* graph, int vertex, bool* result);

bool removeGraph(Graph* graph);

bool removeArrayOfEdges(Edge** array, int size);

#endif //SPBU_2020_C_HOMEWORKS_GRAPH_H
