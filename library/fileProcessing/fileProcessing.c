#include "fileProcessing.h"
#include "../stringManipulations/stringManipulations.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readWordFromFile(FILE* file)
{
    char currentCharacter = (char)fgetc(file);
    int i = 0;
    int size = 1;
    char* word = (char*)malloc(sizeof(char));
    word[0] = 0;
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
        if (size > 1)
            return word;
        else {
            free(word);
            return NULL;
        }
    }
    return word;
}