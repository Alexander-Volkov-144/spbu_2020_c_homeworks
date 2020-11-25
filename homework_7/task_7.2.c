#include "../library/graph/graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct State {
    int* cities;
    int numberOfCities;
} State;

State* createState(int capital, int numberOfPossibleCities)
{
    State* newState = (State*)malloc(sizeof(State));
    newState->cities = (int*)malloc(sizeof(int) * numberOfPossibleCities);
    newState->cities[0] = capital;
    newState->numberOfCities = 1;
    return newState;
}

Edge** getAnArrayOfRoads(FILE* file, int numberOfRoads)
{
    Edge** roads = createArrayOfEdges(numberOfRoads);
    int start = 0, end = 0, length = 0;
    for (int i = 0; i < numberOfRoads; ++i) {
        fscanf(file, "%d%d%d", &start, &end, &length);
        roads[i] = createEdge(start, end, length, false);
    }
    return roads;
}

int findNearestCity(Graph* connectedCities, bool* canBeAdded, State* state)
{
    bool isFound = false;
    int nearestCity = -1;
    int potentiallyNearestCity = -1;
    int minimumLength = 0;
    int roadLength = 0;
    for (int i = 0; i < state->numberOfCities; ++i) {
        if (getNearestVertex(connectedCities, state->cities[i], canBeAdded, &potentiallyNearestCity, &roadLength)) {
            if (roadLength < minimumLength || !isFound) {
                minimumLength = roadLength;
                nearestCity = potentiallyNearestCity;
                isFound = true;
            }
        }
    }
    if (isFound)
        return nearestCity;
    else
        return -1;
}

void addCityToState(State* state, bool* canBeAdded, int city)
{
    canBeAdded[city] = false;
    state->cities[state->numberOfCities] = city;
    state->numberOfCities++;
}

bool addNearestCity(Graph* connectedTowns, bool* canBeAdded, State* state)
{
    int nearestCity = findNearestCity(connectedTowns, canBeAdded, state);
    if (nearestCity == -1)
        return false;
    addCityToState(state, canBeAdded, nearestCity);
    return true;
}

void printAllCities(State* state)
{
    printf("cities: ");
    for (int j = 0; j < state->numberOfCities; ++j) {
        printf("%d ", state->cities[j]);
    }
    printf("\n");
}

int main()
{
    FILE* file = NULL;
    file = fopen("cities_and_roads.txt", "r");
    if (file == NULL) {
        printf("file not found");
        return 0;
    }

    int numberOfCities = 0;
    fscanf(file, "%d", &numberOfCities);
    int numberOfRoads = 0;
    fscanf(file, "%d", &numberOfRoads);
    Edge** roads = getAnArrayOfRoads(file, numberOfRoads);
    int numberOfStates = 0;
    fscanf(file, "%d", &numberOfStates);

    bool* canBeAdded = (bool*)malloc(numberOfCities * sizeof(bool));
    memset(canBeAdded, true, numberOfCities * sizeof(bool));

    State** states = (State**)malloc(sizeof(State*) * numberOfStates);
    int capital = 0;
    for (int i = 0; i < numberOfStates; ++i) {
        fscanf(file, "%d", &capital);
        states[i] = createState(capital, numberOfCities);
        canBeAdded[capital] = false;
    }

    Graph* connectedCities = createGraph(numberOfRoads, numberOfCities, roads);
    bool isAnythingAdded = true;
    while (isAnythingAdded) {
        isAnythingAdded = false;
        for (int i = 0; i < numberOfStates; ++i) {
            isAnythingAdded = addNearestCity(connectedCities, canBeAdded, states[i]) || isAnythingAdded;
        }
    }
    for (int i = 0; i < numberOfStates; ++i) {
        printf("number of state:%d\n", i);
        printAllCities(states[i]);
    }

    removeGraph(connectedCities);
    for (int i = 0; i < numberOfStates; ++i) {
        free(states[i]->cities);
        free(states[i]);
    }
    free(states);
    removeArrayOfEdges(roads, numberOfRoads);
    free(canBeAdded);
    fclose(file);
}
