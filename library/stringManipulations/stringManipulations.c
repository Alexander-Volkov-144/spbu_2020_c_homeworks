#include "stringManipulations.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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

char* readString()
{
    char* newString = (char*)malloc(sizeof(char));
    int size = 1;
    char currentCharacter = 0;
    scanf("%c", &currentCharacter);
    int index = 0;
    while ((currentCharacter != '\0') && (currentCharacter != '\n')) {
        if (index == size)
            newString = doubleSize(newString, &size);
        newString[index] = currentCharacter;
        ++index;
        scanf("%c", &currentCharacter);
    }
    if (index == size)
        newString = doubleSize(newString, &size);
    newString[index] = '\0';
    return newString;
}
