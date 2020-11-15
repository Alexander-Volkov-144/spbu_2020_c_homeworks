#include "stringManipulations.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bool isLetter(char character)
{
    return 'a' <= character && character <= 'z' || 'A' <= character && character <= 'Z';
}

char* doubleSize(char* oldString, int* oldSize)
{
    char* newString = (char*)malloc(*oldSize * 2 * sizeof(char));
    if (newString == NULL) {
        printf("error in allocating memory\n");
        return NULL;
    }
    memset(newString, 0, *oldSize * 2 * sizeof(char));
    for (int i = 0; i < *oldSize; ++i) {
        newString[i] = oldString[i];
    }
    free(oldString);
    *oldSize *= 2;
    return newString;
}
