#include "../library/graph/graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    printf("enter the number of students (not including the first three)\n");
    int numberOfStudents = 0;
    scanf("%d", &numberOfStudents);
    Edge** students = createArrayOfEdges(numberOfStudents);
    int number = 0, copiedFrom = 0;
    printf("enter %d student numbers and numbers of students which they copied\n", numberOfStudents);
    for (int i = 0; i < numberOfStudents; ++i) {
        scanf("%d%d", &number, &copiedFrom);
        if (-1 == copiedFrom)
            copiedFrom = 0;
        students[i] = createEdge(copiedFrom, number, 1, true);
    }
    Graph* copiedWorks = createGraph(numberOfStudents, numberOfStudents + 4, students);
    int* worksSources = (int*)malloc((numberOfStudents + 4) * sizeof(int));
    memset(worksSources, 0, (numberOfStudents + 4) * sizeof(int));
    bool* isCopied = (bool*)malloc((numberOfStudents + 4) * sizeof(bool));
    memset(isCopied, false, (numberOfStudents + 4) * sizeof(bool));
    getAllVertexesConnectedToGiven(copiedWorks, 1, isCopied);
    for (int i = 0; i < numberOfStudents + 4; ++i) {
        if (true == isCopied[i])
            worksSources[i] = 1;
    }
    memset(isCopied, false, (numberOfStudents + 4) * sizeof(bool));
    getAllVertexesConnectedToGiven(copiedWorks, 2, isCopied);
    for (int i = 0; i < numberOfStudents + 4; ++i) {
        if (true == isCopied[i])
            worksSources[i] = 2;
    }
    memset(isCopied, false, (numberOfStudents + 4) * sizeof(bool));
    getAllVertexesConnectedToGiven(copiedWorks, 3, isCopied);
    for (int i = 0; i < numberOfStudents + 4; ++i) {
        if (true == isCopied[i])
            worksSources[i] = 3;
    }
    memset(isCopied, false, (numberOfStudents + 4) * sizeof(bool));
    getAllVertexesConnectedToGiven(copiedWorks, 0, isCopied);
    for (int i = 0; i < numberOfStudents + 4; ++i) {
        if (true == isCopied[i])
            worksSources[i] = 0;
    }
    for (int i = 1; i < 4; ++i) {
        printf("%d: original work\n", i);
    }
    for (int i = 4; i < numberOfStudents + 4; ++i) {
        if (0 == worksSources[i])
            printf("%d: expelled\n", i);
        else
            printf("%d: copied from %d\n", i, worksSources[i]);
    }
    free(isCopied);
    free(worksSources);
    removeGraph(copiedWorks);
    removeArrayOfEdges(students);
    return 0;
}
