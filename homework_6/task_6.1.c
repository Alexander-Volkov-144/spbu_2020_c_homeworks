#include "../library/hashTable/hashTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

const int MAX_WORD_LENGTH = 20;

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

bool readWordFromFile(FILE* file, char* word)
{
    char currentCharacter = fgetc(file);
    int i = 0;
    bool notEndOfFile = (currentCharacter != EOF);
    while (notEndOfFile && isLetter(currentCharacter)) {
        word[i] = tolower(currentCharacter);
        ++i;
        currentCharacter = fgetc(file);
        notEndOfFile = (currentCharacter != EOF);
    }
    word[i] = '\0';
    return notEndOfFile;
}

int main()
{
    FILE* input = NULL;
    input = fopen("input.txt", "r");
    char* currentWord = (char*)malloc(sizeof(char) * MAX_WORD_LENGTH);
    memset(currentWord, 0, sizeof(char) * MAX_WORD_LENGTH);
    HashTable* words = createHashTable(2);

    while (readWordFromFile(input, currentWord)) {
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
