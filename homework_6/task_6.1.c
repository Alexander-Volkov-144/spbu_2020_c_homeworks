#include "../library/hashTable/hashTable.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printTheNecessaryInformation(HashTable* words)
{
    printf("load factor: %f\n", getLoadFactor(words));
    printf("average number of probes: %f\n", getAverageNumberOfProbes(words));
    int maximumNumberOfProbes = getMaximumNumberOfProbes(words);
    printf("maximum number of probes: %d\n", maximumNumberOfProbes);
    printf("elements with maximum number of probes: ");
    printAllElementsWithCertainNumberOfProbes(words, maximumNumberOfProbes);
    printf("\n");
    printf("number of words added: %d\n", getElementCount(words));
    printf("number of empty buckets: %d\n", getBucketCount(words) - getElementCount(words));
    printElementsWithBiggestValues(words, 10);
}

bool isLetter(char character)
{
    return 'a' <= character && character <= 'z' || 'A' <= character && character <= 'Z';
}

char* doubleSize(char* oldString, int oldSize){
    char* newString = (char*)malloc(oldSize * 2 * sizeof(char));
    if(newString == NULL){
        printf("error in allocating memory\n");
        return NULL;
    }
    memset(newString, 0, oldSize * 2 * sizeof(char));
    for(int i = 0; i < oldSize; ++i) {
        newString[i] = oldString[i];
    }
    free(oldString);
    return newString;
}

char* readWordFromFile(FILE* file)
{
    char currentCharacter = (char) fgetc(file);
    int i = 0;
    bool isFound = false;
    int size = 1;
    char* word = (char*) malloc(sizeof(char));
    while (!isLetter(currentCharacter) && !feof(file)) {
        currentCharacter = (char) fgetc(file);
    }
    while (!feof(file) && isLetter(currentCharacter)) {
        isFound = true;
        if (i == size) {
            word = doubleSize(word, size);
            size *= 2;
        }
        word[i] = (char) tolower(currentCharacter);
        ++i;
        currentCharacter = (char) fgetc(file);
    }
    if (i == size) {
        word = doubleSize(word, size);
        size *= 2;
    }
    word[i] = '\0';
    if (feof(file)) {
        free(word);
        return NULL;
    }
    return word;
}

int main()
{
    FILE* input = NULL;
    input = fopen("/media/user/Data/input.txt", "r");
    if (input == NULL) {
        printf("file \"input.txt\"not found");
        return 0;
    }
    HashTable* words = createHashTable();
    char* currentWord = readWordFromFile(input);
    while (currentWord != NULL) {
        {
            addElement(words, currentWord, 1);
            free(currentWord);
            currentWord = readWordFromFile(input);
        }
    }

    printTheNecessaryInformation(words);

    destroyHashTable(words);
    free(currentWord);
    fclose(input);
    return 0;
}
