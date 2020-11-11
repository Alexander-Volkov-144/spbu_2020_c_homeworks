#include "../library/hashTable/hashTable.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

bool readWordFromFile(FILE* file, char* word, int* size)
{
    char currentCharacter = (char)fgetc(file);
    int i = 0;
    bool notEndOfFile = (currentCharacter != EOF);
    while (notEndOfFile && isLetter(currentCharacter)) {
        if (i >= *size) {
            realloc(word, *size * 2 * sizeof(char));
            if (word == NULL) {
                printf("error in memory allocation\n");
                return false;
            }
            *size *= 2;
        }
        word[i] = (char)tolower(currentCharacter);
        ++i;
        currentCharacter = (char)fgetc(file);
        notEndOfFile = (currentCharacter != EOF);
    }
    word[i] = '\0';
    return notEndOfFile;
}

int main()
{
    FILE* input = NULL;
    input = fopen("input.txt", "r");
    if (input == NULL) {
        printf("file \"input.txt\"not found");
        return 0;
    }
    char* currentWord = (char*)malloc(sizeof(char));
    int size = 1;
    HashTable* words = createHashTable();
    while (readWordFromFile(input, currentWord, &size)) {
        if (currentWord[0] != '\0')
            addElement(words, currentWord, 1);
    }
    if (currentWord[0] != '\0')
        addElement(words, currentWord, 1);

    printTheNecessaryInformation(words);

    destroyHashTable(words);
    free(currentWord);
    fclose(input);
    return 0;
}
