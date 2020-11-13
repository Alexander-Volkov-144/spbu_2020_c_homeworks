#include "fileProcessing.h"
#include <ctype.h>
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

char* readWordFromFile(FILE* file)
{
    char currentCharacter = (char)fgetc(file);
    int i = 0;
    int size = 1;
    char* word = (char*)malloc(sizeof(char));
    while (!isLetter(currentCharacter) && !feof(file)) {
        currentCharacter = (char)fgetc(file);
    }
    while (!feof(file) && isLetter(currentCharacter)) {
        if (i == size)
            word = doubleSize(word, &size);
        word[i] = (char)tolower(currentCharacter);
        ++i;
        currentCharacter = (char)fgetc(file);
    }
    if (i == size)
        word = doubleSize(word, &size);

    word[i] = '\0';
    if (feof(file)) {
        free(word);
        return NULL;
    }
    return word;
}