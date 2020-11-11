#include "../library/graph/graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main()
{
    int numberOfTowns = 0;
    printf("enter the number of towns\n");
    scanf("%d", &numberOfTowns);
    int numberOfRoads = 0;
    printf("enter the number of roads\n");
    scanf("%d", &numberOfRoads);
    printf("enter the start, end and length of the road %d times\n", numberOfRoads);
    Edge** roads = createArrayOfEdges(numberOfRoads);
    int start = 0, end = 0, length = 0;
    for (int i = 0; i < numberOfRoads; ++i) {
        scanf("%d%d%d",&start,&end, &length);
        roads[i] = createEdge(start, end, length, false);
    }
    int numberOfStates = 0;
    printf("enter the number of states\n");
    scanf("%d",&numberOfStates);
    int** states = (int**)malloc(numberOfStates * sizeof(int*));
    for(int i = 0; i < numberOfStates; ++i){
        states[i] = (int*)malloc(numberOfTowns * sizeof(int));
    }
    printf("enter the capital of the state %d times\n", numberOfStates);
    for(int i = 0; i < numberOfStates; ++i){
        scanf("%d", &states[i][0]);
    }
    Graph* connectedTowns = createGraph(numberOfRoads, numberOfTowns, roads);
    bool* canAdd = (bool*)malloc(numberOfStates * sizeof(bool));
    memset(canAdd, true, numberOfStates * sizeof(bool));

}