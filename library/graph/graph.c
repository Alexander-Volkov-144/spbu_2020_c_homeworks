#include "graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Edge {
    int start;
    int end;
    int weight;
    bool oriented;
};

struct Graph {
    int** matrix;
    int countVertex;
    int countEdges;
};

Edge* createEdge(int start, int end, int weight, bool oriented)
{
    Edge* edge = malloc(sizeof(Edge));
    edge->start = start;
    edge->end = end;
    edge->weight = weight;
    edge->oriented = oriented;
    return edge;
}

Graph* createGraph(int countEdges, int countVertex, Edge** edges)
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->countVertex = countVertex;
    graph->countEdges = countEdges;
    graph->matrix = (int**)malloc(countVertex * sizeof(int*));
    for (int i = 0; i < countVertex; ++i) {
        graph->matrix[i] = (int*)malloc(countVertex * sizeof(int));
        memset(graph->matrix[i], 0, countVertex * sizeof(int));
    }
    for (int i = 0; i < countEdges; ++i) {
        graph->matrix[edges[i]->start][edges[i]->end] = edges[i]->weight;
        if (!edges[i]->oriented) {
            graph->matrix[edges[i]->end][edges[i]->start] = edges[i]->weight;
        }
    }
    return graph;
}

bool removeGraph(Graph* graph)
{
    for (int i = 0; i < graph->countVertex; ++i) {
        free(graph->matrix[i]);
    }
    free(graph->matrix);
    free(graph);
    return true;
}

bool isConnected(int fromVertex, int toVertex, Graph* graph)
{
    int* vertexState = (int*)malloc(graph->countVertex * sizeof(int));
    memset(vertexState, 0, graph->countVertex * sizeof(int));
    depthFirstSearch(graph, fromVertex, vertexState);
    return vertexState[toVertex] > 0;
}

bool depthFirstSearch(Graph* graph, int currentVertex, int* vertexState)
{
    vertexState[currentVertex] = 1;
    for (int i = 0; i < graph->countVertex; i++) {
        if (graph->matrix[currentVertex][i] != 0) {
            if (vertexState[i] == 1) {
                return true;
            }
            if (vertexState[i] == 0) {
                if (depthFirstSearch(graph, i, vertexState)) {
                    return true;
                }
            }
        }
    }
    vertexState[currentVertex] = 2;
    return false;
}

bool isCycled(Graph* graph)
{
    int* vertexState = (int*)malloc(graph->countVertex * sizeof(int));
    memset(vertexState, 0, graph->countVertex * sizeof(int));
    for (int i = 0; i < graph->countVertex; ++i) {
        if (vertexState[i] == 0) {
            if (depthFirstSearch(graph, i, vertexState)) {
                return true;
            }
        }
    }
    return false;
}

Edge** createArrayOfEdges(int size)
{
    Edge** newArray = (Edge**)malloc(size * sizeof(Edge*));
    return newArray;
}

bool removeArrayOfEdges(Edge** array, int size)
{
    for (int i = 0; i < size; ++i) {
        free(array[i]);
    }
    free(array);
    return true;
}

void getAllVertexesConnectedToGiven(Graph* graph, int vertex, bool* result)
{
    for (int i = 0; i < graph->countVertex; ++i) {
        if (graph->matrix[vertex][i] != 0) {
            result[i] = true;
            getAllVertexesConnectedToGiven(graph, i, result);
        }
    }
}

bool getNearestVertex(Graph* graph, int originalVertex, const bool* vertexesThatCanBeUsed, int* nearestVertex,int* weightOfEdge)
{
    *nearestVertex = -1;
    *weightOfEdge = 0;
    for (int i = 0; i < graph->countVertex; ++i) {
        if ((graph->matrix[originalVertex][i] < *weightOfEdge && graph->matrix[originalVertex][i] != 0 || nearestVertex == -1) && vertexesThatCanBeUsed[i]) {
            nearestVertex = i;
            *weightOfEdge = graph->matrix[originalVertex][i];
        }
    }
    return *nearestVertex != -1;
}
