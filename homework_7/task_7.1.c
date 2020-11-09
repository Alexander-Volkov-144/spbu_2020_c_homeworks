#include "../library/graph/graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Edge** getNumbers(int numberOfStudents)
{
    Edge** students = createArrayOfEdges(numberOfStudents);
    printf("enter %d student numbers and numbers of students which they copied\n", numberOfStudents);
    int number = 0, copiedFrom = 0;
    for (int i = 0; i < numberOfStudents; ++i) {
        scanf("%d%d", &number, &copiedFrom);
        if (-1 == copiedFrom)
            copiedFrom = 0;
        students[i] = createEdge(copiedFrom, number, 1, true);
    }
    return students;
}

int* findOriginal(Graph* copiedWorks, int numberOfStudents)
{
    int* worksSources = (int*)malloc((numberOfStudents + 4) * sizeof(int));
    memset(worksSources, 0, (numberOfStudents + 4) * sizeof(int));
    bool* isCopied = (bool*)malloc((numberOfStudents + 4) * sizeof(bool));
    for (int i = 0; i < 4; ++i) {
        memset(isCopied, false, (numberOfStudents + 4) * sizeof(bool));
        getAllVertexesConnectedToGiven(copiedWorks, i, isCopied);
        for (int j = 0; j < numberOfStudents + 4; ++j) {
            if (true == isCopied[j])
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
    Edge** students = getNumbers(numberOfStudents);
    Graph* copiedWorks = createGraph(numberOfStudents, numberOfStudents + 4, students);
    int* worksSources = findOriginal(copiedWorks, numberOfStudents);
    for (int i = 1; i < 4; ++i) {
        printf("%d: original work\n", i);
    }
    for (int i = 4; i < numberOfStudents + 4; ++i) {
        if (0 == worksSources[i])
            printf("%d: expelled\n", i);
        else
            printf("%d: copied from %d\n", i, worksSources[i]);
    }
    free(worksSources);
    removeGraph(copiedWorks);
    removeArrayOfEdges(students, numberOfStudents);
    return 0;
}
