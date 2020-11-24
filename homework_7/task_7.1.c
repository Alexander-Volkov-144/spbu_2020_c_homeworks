#include "../library/graph/graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Edge** getNumbers(int numberOfStudents, int* numberOfUnfinishedWorks)
{
    Edge** students = createArrayOfEdges(numberOfStudents);
    int index = 0;
    printf("enter %d student numbers and numbers of students which they copied\n", numberOfStudents);
    int number = 0, copiedFrom = 0;
    for (int i = 0; i < numberOfStudents; ++i) {
        scanf("%d%d", &number, &copiedFrom);
        if (copiedFrom == -1)
            (*numberOfUnfinishedWorks)++;
        else {
            students[index] = createEdge(copiedFrom - 1, number - 1, 1, true);
            ++index;
        }
    }
    return students;
}

int* findOriginal(Graph* copiedWorks, int numberOfStudents)
{
    int* worksSources = (int*)malloc((numberOfStudents + 3) * sizeof(int));
    memset(worksSources, -1, (numberOfStudents + 3) * sizeof(int));
    bool* isCopied = (bool*)malloc((numberOfStudents + 3) * sizeof(bool));
    for (int i = 0; i < 3; ++i) {
        memset(isCopied, false, (numberOfStudents + 3) * sizeof(bool));
        getAllVertexesConnectedToGiven(copiedWorks, i, isCopied);
        for (int j = 0; j < numberOfStudents + 3; ++j) {
            if (isCopied[j])
                worksSources[j] = i;
        }
    }
    free(isCopied);
    return worksSources;
}

int main()
{
    printf("enter the number of students (not including the first three)\n");
    int numberOfStudents = 0;
    scanf("%d", &numberOfStudents);
    int numberOfUnfinishedWorks = 0;
    Edge** students = getNumbers(numberOfStudents, &numberOfUnfinishedWorks);
    Graph* copiedWorks = createGraph(numberOfStudents - numberOfUnfinishedWorks, numberOfStudents + 3, students);
    int* worksSources = findOriginal(copiedWorks, numberOfStudents);
    for (int i = 0; i < 3; ++i) {
        printf("%d: original work\n", i + 1);
    }
    for (int i = 3; i < numberOfStudents + 3; ++i) {
        if (worksSources[i] == -1)
            printf("%d: expelled\n", i + 1);
        else
            printf("%d: copied from %d\n", i + 1, worksSources[i] + 1);
    }
    free(worksSources);
    removeGraph(copiedWorks);
    removeArrayOfEdges(students, numberOfStudents);
    return 0;
}
