#include "../library/graph/graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct State {
    int* towns;
    int numberOfTowns;
} State;

State* createState(int capital)
{
    State* newState = (State*)malloc(sizeof(State));
    newState->towns = (int*)malloc(sizeof(int));
    newState->towns[0] = capital;
    newState->numberOfTowns = 1;
    return newState;
}

Edge** getAnArrayOfRoads(int numberOfRoads)
{
    Edge** roads = createArrayOfEdges(numberOfRoads);
    int start = 0, end = 0, length = 0;
    for (int i = 0; i < numberOfRoads; ++i) {
        scanf("%d%d%d", &start, &end, &length);
        roads[i] = createEdge(start, end, length, false);
    }
    return roads;
}

int findNearestCity(Graph* connectedTowns, bool* canBeAdded, State* state){
    bool isFound = false;
    for (int i = 0; i < state->numberOfTowns; ++i) {

    }
}

bool addNearestCity(Graph* connectedTowns, bool* canBeAdded, State* state)
{
    for (int i = 0; i < state->numberOfTowns; ++i) {

    }
    return false;
}

int main()
{
    int numberOfTowns = 0;
    printf("enter the number of towns\n");
    scanf("%d", &numberOfTowns);
    int numberOfRoads = 0;
    printf("enter the number of roads\n");
    scanf("%d", &numberOfRoads);
    printf("enter the start, end and length of the road %d times\n", numberOfRoads);
    Edge** roads = getAnArrayOfRoads(numberOfRoads);
    int numberOfStates = 0;
    printf("enter the number of states\n");
    scanf("%d", &numberOfStates);
    State** states = (State**)malloc(sizeof(State*) * numberOfStates);
    printf("enter the capital of the state %d times\n", numberOfStates);
    int capital = 0;
    for (int i = 0; i < numberOfStates; ++i) {
        scanf("%d", &capital);
        states[i] = createState(capital);
    }
    Graph* connectedTowns = createGraph(numberOfRoads, numberOfTowns, roads);
    bool* canBeAdded = (bool*)malloc(numberOfStates * sizeof(bool));
    memset(canBeAdded, true, numberOfStates * sizeof(bool));
    bool isAnythingAdded = true;
    while (isAnythingAdded) {
        isAnythingAdded = false;
        for (int i = 0; i < numberOfStates; ++i) {
            isAnythingAdded = isAnythingAdded || addNearestCity(connectedTowns, canBeAdded, states[i]);
        }
    }
}