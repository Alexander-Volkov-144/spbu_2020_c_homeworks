#include "../library/graph/graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct State {
    int* cities;
    int numberOfCities;
} State;

State* createState(int capital, int numberOfCities)
{
    State* newState = (State*)malloc(sizeof(State));
    newState->cities = (int*)malloc(sizeof(int) * numberOfCities);
    newState->cities[0] = capital;
    newState->numberOfCities = 1;
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

int findNearestCity(Graph* connectedCities, bool* canBeAdded, State* state){
    bool isFound = false;
    int nearestCity = -1;
    int potentiallyNearestCity = -1;
    int minimumLength = 0;
    int roadLength = 0;
    for (int i = 0; i < state->numberOfCities; ++i) {
         if(getNearestVertex(connectedCities, i, canBeAdded, &potentiallyNearestCity, &roadLength)){
             if(roadLength < minimumLength || !isFound){
                 minimumLength = roadLength;
                 nearestCity = potentiallyNearestCity;
                 isFound = true;
             }
        }
    }
    if(isFound)
        return nearestCity;
    else
        return -1;
}

void addCityToState(State* state, bool* canBeAdded, int city){
    canBeAdded[city] = false;
    state->cities[state->numberOfCities] = city;
    state->numberOfCities++;
}

bool addNearestCity(Graph* connectedTowns, bool* canBeAdded, State* state)
{
    int nearestCity = findNearestCity(connectedTowns, canBeAdded, state);
    if (nearestCity == - 1)
        return false;
    addCityToState(state, canBeAdded, nearestCity);
    return true;
}

int main()
{
    int numberOfCities = 0;
    printf("enter the number of cities\n");
    scanf("%d", &numberOfCities);
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
        states[i] = createState(capital, numberOfCities);
    }
    Graph* connectedCities = createGraph(numberOfRoads, numberOfCities, roads);
    bool* canBeAdded = (bool*)malloc(numberOfStates * sizeof(bool));
    memset(canBeAdded, true, numberOfStates * sizeof(bool));
    bool isAnythingAdded = true;
    while (isAnythingAdded) {
        isAnythingAdded = false;
        for (int i = 0; i < numberOfStates; ++i) {
            isAnythingAdded = isAnythingAdded || addNearestCity(connectedCities, canBeAdded, states[i]);
        }
    }
    for(int i = 0; i < numberOfStates; ++i){
        printf("number of state:%d\n", i);
        for(int j = 0; j < states[i]->numberOfCities; ++j){
            printf("%d ", states[i]->cities[j]);
        }
        printf("\n");
    }
    for (int i = 0; i < numberOfStates; ++i) {
        free(states[i]);
    }
    free(states);
    free(canBeAdded);
}